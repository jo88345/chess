// =====================================================================================
//  perft.cpp – Perft-Test für die Schachengine der Maturaarbeit
//  ("En passent, Transposition Tables und Zugreihenfolgen", Johannes Rappazzo, 2026)
//
//  Geschrieben mit Claude (Anthropic) als Hilfsmittel, siehe Kapitel 3.1.4 / 3.3.1.
//
//  IDEE
//  Ein Perft zählt alle Blattknoten des Zugbaums bis zu einer festen Tiefe. Stimmt die
//  Zahl mit den bekannten Werten (Chess Programming Wiki, "Perft Results") überein,
//  ist die Zuggeneration mit sehr hoher Wahrscheinlichkeit korrekt.
//
//  Dieses Programm schreibt KEINEN eigenen Zuggenerator. Es bindet die Engine-Datei
//  per #include ein und ruft genau die Funktionen auf, die auch Tree() benutzt:
//      legal_moves() -> actual_legal_moves() -> white_/black_expansion()
//      domove() / undomove()
//  Damit wird wirklich der Code der Engine getestet und nicht eine Kopie davon.
//  Die Engine-Datei selbst wird dabei nicht verändert.
//
//  KOMPILIEREN (perft.cpp im selben Ordner wie die Engine):
//      g++ -O2 -std=c++17 perft.cpp -o perft
//  Andere Engine-Version testen (muss dieselben Funktionen besitzen):
//      g++ -O2 -std=c++17 -DENGINE_FILE='"archive/chess_bunny.cpp"' perft.cpp -o perft
//  Unter Windows (MinGW/PowerShell) die Anführungszeichen so schreiben:
//      g++ -O2 -std=c++17 "-DENGINE_FILE=\"chess_new_1_opt.cpp\"" perft.cpp -o perft.exe
//
//  BENUTZUNG
//      perft                                  Testsuite: 6 CPW-Stellungen, jede Stellung auf Tiefe 4 (~2 s)
//      perft --maxdepth 4                     Testsuite auf Tiefe 4 (bzw. tiefer, falls kleiner)
//      perft --position 2 --depth 4           nur CPW-Stellung 2 (Kiwipete) bis Tiefe 4
//      perft --fen "<FEN>" --depth 3          beliebige Stellung, Tiefe 1..3
//      perft --fen "<FEN>" --depth 3 --divide Knoten pro Wurzelzug (zum Vergleich mit
//                                             Stockfish: "position fen <FEN>" + "go perft 3")
//      perft --fen "<FEN>" --moves "h1f1 d8d7" --depth 2 --divide
//                                             zuerst Züge mit domove() ausführen (wie
//                                             "position fen ... moves ..." bei UCI)
//      perft ... --csv perft_resultate.csv    Resultate zusätzlich als CSV speichern
// =====================================================================================

#ifndef ENGINE_FILE
#define ENGINE_FILE "chess_new_1_opt.cpp"
#endif

// Die Engine hat ihre eigene main() (startet die UCI-Schleife). Diese wird beim
// Einbinden umbenannt, damit das Perft-Programm seine eigene main() haben kann.
#define main engine_main
#include ENGINE_FILE
#undef main

#include <fstream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>

// -------------------------------------------------------------------------------------
//  Referenzwerte: https://www.chessprogramming.org/Perft_Results  (Quelle [33])
// -------------------------------------------------------------------------------------
struct Teststellung{
    std::string name;
    std::string fen;
    std::vector<uint64_t> erwartet;   // erwartet[0] = Tiefe 1, erwartet[1] = Tiefe 2, ...
    int standardtiefe;                // Tiefe für den normalen Testlauf
};

static const std::vector<Teststellung> TESTSUITE = {
    {"Startstellung",
     "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
     {20, 400, 8902, 197281, 4865609, 119060324}, 4},
    {"Kiwipete",
     "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",
     {48, 2039, 97862, 4085603, 193690690}, 4},
    {"Stellung 3",
     "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1",
     {14, 191, 2812, 43238, 674624, 11030083}, 4},
    {"Stellung 4",
     "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1",
     {6, 264, 9467, 422333, 15833292}, 4},
    {"Stellung 5",
     "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8",
     {44, 1486, 62379, 2103487, 89941194}, 4},
    {"Stellung 6",
     "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10",
     {46, 2079, 89890, 3894594, 164075551}, 4},
};

// -------------------------------------------------------------------------------------
//  Stellung aufbauen – dieselben Schritte wie setPosition() in uciLoop()
// -------------------------------------------------------------------------------------
static void stellung_setzen(Board &board, const std::string &fen){
    board.fillboard(board.board);
    board.fillboard(board.legal_black_moves);
    board.fillboard(board.legal_white_moves);
    board.previous_boards.clear();
    board.boards.clear();
    board.previous_moves.clear();
    board.Previous_moves.clear();
    board.candidates.clear();
    board.tempmax.clear();
    board.tempmin.clear();
    board.breaker = false;
    board.move = "";
    // alle Figurenlisten leeren, falls das Board schon einmal benutzt wurde
    board.whitePawns.clear();   board.blackPawns.clear();
    board.whiteKnight.clear();  board.blackKnight.clear();
    board.whiteBishop.clear();  board.blackBishop.clear();
    board.whiterook.clear();    board.blackrook.clear();
    board.whiteQueen.clear();   board.blackQueen.clear();
    board.whiteKing.clear();    board.blackKing.clear();

    assign_random_key(board.h_pieces, board.h_castling, board.h_en_passent, board.h_turn);
    FEN_to_position(board, fen);
    piecelist(board);
    FEN_extra(board, fen);
    legal_moves(board);
    actual_legal_moves(board);
    if(board.turn){
        white_expansion(board);
    }
    else{
        black_expansion(board);
    }
    board.hash = hashing(board);
    board.previous_boards.push_back(position_to_FEN(board));
}

// -------------------------------------------------------------------------------------
//  Zugfolge ausführen (wie "position fen ... moves ..." in uciLoop()).
//  Praktisch, um Fehler zu finden, die nur nach bestimmten Zügen auftreten,
//  z.B. "Turm zieht weg und wieder zurück".
// -------------------------------------------------------------------------------------
static void zuege_ausfuehren(Board &board, const std::string &zuege){
    std::istringstream iss(zuege);
    std::string m;
    while(iss >> m){
        if(m.size() < 4) continue;
        int from = square_to_index(m[0], m[1]);
        int to = square_to_index(m[2], m[3]);
        char promotion = '0';
        if(m.size() >= 5){
            promotion = board.turn ? std::toupper(m[4]) : std::tolower(m[4]);
        }
        domove(board, from, to, promotion);
    }
}

// -------------------------------------------------------------------------------------
//  Zuggeneration der Engine aufrufen (genau wie am Anfang von Tree())
// -------------------------------------------------------------------------------------
static void zuege_generieren(Board &board, std::vector<int> &starts, std::vector<int> &targets){
    legal_moves(board);
    actual_legal_moves(board);
    if(board.turn){
        white_expansion(board);
    }
    else{
        black_expansion(board);
    }
    // Kopieren, weil die rekursiven Aufrufe die Listen im Board überschreiben
    starts = board.legal_starting_squares;
    targets = board.legal_target_squares;
}

// Ist der Zug eine Umwandlung? (gleiche Bedingung wie in Tree())
static bool ist_umwandlung(Board &board, int start, int target){
    char figur = board.board[start];
    return (figur == 'P' && target / 8 == 0) || (figur == 'p' && target / 8 == 7);
}

// Umwandlungsfiguren in der Schreibweise, die domove() erwartet:
// Weiss = Grossbuchstaben, Schwarz = Kleinbuchstaben
static const char UMWANDLUNG_WEISS[4]   = {'Q', 'R', 'B', 'N'};
static const char UMWANDLUNG_SCHWARZ[4] = {'q', 'r', 'b', 'n'};

// -------------------------------------------------------------------------------------
//  Der eigentliche Perft (rekursiv)
// -------------------------------------------------------------------------------------
static uint64_t perft(Board &board, int depth){
    if(depth == 0){
        return 1;
    }
    std::vector<int> starts, targets;
    zuege_generieren(board, starts, targets);

    // "Bulk counting": auf der letzten Ebene muss man die Züge nicht ausführen,
    // die Länge der Zugliste genügt. Eine Umwandlung steht nur einmal in der Liste,
    // zählt aber als 4 Züge (Dame, Turm, Läufer, Springer).
    if(depth == 1){
        uint64_t anzahl = 0;
        for(size_t i = 0; i < starts.size(); i++){
            anzahl += ist_umwandlung(board, starts[i], targets[i]) ? 4 : 1;
        }
        return anzahl;
    }

    uint64_t knoten = 0;
    for(size_t i = 0; i < starts.size(); i++){
        if(ist_umwandlung(board, starts[i], targets[i])){
            const char *figuren = board.turn ? UMWANDLUNG_WEISS : UMWANDLUNG_SCHWARZ;
            for(int f = 0; f < 4; f++){
                domove(board, starts[i], targets[i], figuren[f]);
                knoten += perft(board, depth - 1);
                undomove(board);
            }
        }
        else{
            domove(board, starts[i], targets[i], '0');
            knoten += perft(board, depth - 1);
            undomove(board);
        }
    }
    return knoten;
}

// -------------------------------------------------------------------------------------
//  Divide: Knotenzahl pro Wurzelzug, im selben Format wie Stockfish ("e2e4: 20")
//  Damit kann man einen Fehler bis zum falschen Zug zurückverfolgen.
// -------------------------------------------------------------------------------------
static uint64_t divide(Board &board, int depth){
    std::vector<int> starts, targets;
    zuege_generieren(board, starts, targets);

    std::vector<std::pair<std::string, uint64_t>> zeilen;
    uint64_t total = 0;
    for(size_t i = 0; i < starts.size(); i++){
        std::string zug = index_to_square(starts[i]) + index_to_square(targets[i]);
        if(ist_umwandlung(board, starts[i], targets[i])){
            const char *figuren = board.turn ? UMWANDLUNG_WEISS : UMWANDLUNG_SCHWARZ;
            for(int f = 0; f < 4; f++){
                domove(board, starts[i], targets[i], figuren[f]);
                uint64_t n = perft(board, depth - 1);
                undomove(board);
                zeilen.push_back({zug + (char)std::tolower(figuren[f]), n});
                total += n;
            }
        }
        else{
            domove(board, starts[i], targets[i], '0');
            uint64_t n = perft(board, depth - 1);
            undomove(board);
            zeilen.push_back({zug, n});
            total += n;
        }
    }
    std::sort(zeilen.begin(), zeilen.end());   // alphabetisch, wie bei Stockfish
    for(auto &z : zeilen){
        std::cout << z.first << ": " << z.second << '\n';
    }
    std::cout << "\nAnzahl Wurzelzüge: " << zeilen.size() << '\n';
    std::cout << "Knoten gesamt:     " << total << "\n\n";
    return total;
}

// -------------------------------------------------------------------------------------
//  Ausgabe
// -------------------------------------------------------------------------------------
struct Resultat{
    std::string stellung;
    int tiefe;
    uint64_t knoten;
    bool hat_referenz;
    uint64_t erwartet;
    double ms;
};

// Zahl mit Apostroph als Tausendertrennzeichen (Schweizer Schreibweise): 4'865'609
static std::string tausender(uint64_t n){
    std::string s = std::to_string(n);
    for(int i = (int)s.size() - 3; i > 0; i -= 3){
        s.insert(i, "'");
    }
    return s;
}

static void kopfzeile(){
    std::cout << std::left  << std::setw(18) << "Stellung"
              << std::right << std::setw(6)  << "Tiefe"
              << std::setw(15) << "Erwartet"
              << std::setw(15) << "Engine"
              << std::setw(9)  << "Status"
              << std::setw(12) << "Zeit [ms]"
              << std::setw(12) << "Knoten/s" << '\n';
    std::cout << std::string(87, '-') << '\n';
}

static void zeile(const Resultat &r){
    std::string status = !r.hat_referenz ? "-" : (r.knoten == r.erwartet ? "OK" : "FEHLER");
    uint64_t nps = r.ms > 0 ? (uint64_t)(r.knoten / (r.ms / 1000.0)) : 0;
    std::cout << std::left  << std::setw(18) << r.stellung
              << std::right << std::setw(6)  << r.tiefe
              << std::setw(15) << (r.hat_referenz ? tausender(r.erwartet) : "-")
              << std::setw(15) << tausender(r.knoten)
              << std::setw(9)  << status
              << std::setw(12) << std::fixed << std::setprecision(1) << r.ms
              << std::setw(12) << tausender(nps) << '\n';
    std::cout.flush();
}

static void csv_schreiben(const std::string &datei, const std::vector<Resultat> &res){
    std::ofstream out(datei);
    out << "Stellung;Tiefe;Erwartet;Engine;Korrekt;Zeit_ms\n";
    for(const Resultat &r : res){
        out << r.stellung << ';' << r.tiefe << ';'
            << (r.hat_referenz ? std::to_string(r.erwartet) : "") << ';'
            << r.knoten << ';'
            << (!r.hat_referenz ? "" : (r.knoten == r.erwartet ? "ja" : "nein")) << ';'
            << std::fixed << std::setprecision(1) << r.ms << '\n';
    }
    std::cout << "CSV gespeichert: " << datei << '\n';
}

static Resultat messen(Board &board, const std::string &name, const std::string &fen,
                       const std::string &zuege, int tiefe, const std::vector<uint64_t> *erwartet){
    stellung_setzen(board, fen);
    zuege_ausfuehren(board, zuege);
    auto t0 = std::chrono::steady_clock::now();
    uint64_t n = perft(board, tiefe);
    auto t1 = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    Resultat r{name, tiefe, n, false, 0, ms};
    if(erwartet && tiefe >= 1 && tiefe <= (int)erwartet->size()){
        r.hat_referenz = true;
        r.erwartet = (*erwartet)[tiefe - 1];
    }
    return r;
}

static void hilfe(){
    std::cout <<
        "Benutzung:\n"
        "  perft                                   Testsuite (6 CPW-Stellungen)\n"
        "  perft --maxdepth N                      Testsuite, höchstens bis Tiefe N\n"
        "  perft --position K --depth N            nur CPW-Stellung K (1-6)\n"
        "  perft --fen \"<FEN>\" --depth N           eigene Stellung\n"
        "  perft --fen \"<FEN>\" --depth N --divide  Knoten pro Wurzelzug\n"
        "  zusätzlich: --moves \"e2e4 e7e5\"        Züge nach der FEN ausführen\n"
        "              --csv datei.csv             Resultate als CSV speichern\n";
}

// -------------------------------------------------------------------------------------
//  main
// -------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
    std::string fen;
    int depth = -1;
    int maxdepth = -1;
    int position = -1;
    bool mit_divide = false;
    std::string csv;
    std::string zuege;   // optionale Zugfolge nach der FEN, z.B. "e2e4 e7e5"

    for(int i = 1; i < argc; i++){
        std::string a = argv[i];
        auto naechstes = [&](void) -> std::string {
            if(i + 1 >= argc){ hilfe(); std::exit(1); }
            return argv[++i];
        };
        if(a == "--fen")           fen = naechstes();
        else if(a == "--depth")    depth = std::stoi(naechstes());
        else if(a == "--maxdepth") maxdepth = std::stoi(naechstes());
        else if(a == "--position") position = std::stoi(naechstes());
        else if(a == "--divide")   mit_divide = true;
        else if(a == "--csv")      csv = naechstes();
        else if(a == "--moves")    zuege = naechstes();
        else { hilfe(); return a == "--help" || a == "-h" ? 0 : 1; }
    }

    // Board ist wegen der Transposition Table gross -> auf dem Heap anlegen
    auto board = std::make_unique<Board>();

    std::cout << "Perft-Test  |  Engine: " << ENGINE_FILE << "\n\n";

    std::vector<Resultat> resultate;
    int fehler = 0;

    if(!fen.empty()){
        // ---- eigene Stellung ----
        if(depth < 1){ std::cout << "Bitte --depth N (N >= 1) angeben.\n"; return 1; }
        std::cout << "FEN: " << fen << '\n';
        if(!zuege.empty()) std::cout << "Züge: " << zuege << '\n';
        std::cout << '\n';
        if(mit_divide){
            stellung_setzen(*board, fen);
            zuege_ausfuehren(*board, zuege);
            divide(*board, depth);
        }
        else{
            kopfzeile();
            for(int d = 1; d <= depth; d++){
                Resultat r = messen(*board, "eigene", fen, zuege, d, nullptr);
                zeile(r);
                resultate.push_back(r);
            }
        }
    }
    else{
        // ---- Testsuite (alle oder eine CPW-Stellung) ----
        if(position != -1 && (position < 1 || position > (int)TESTSUITE.size())){
            std::cout << "--position muss zwischen 1 und " << TESTSUITE.size() << " liegen.\n";
            return 1;
        }
        if(mit_divide){
            if(position == -1 || depth < 1){
                std::cout << "--divide braucht --position K --depth N (oder --fen).\n";
                return 1;
            }
            const Teststellung &t = TESTSUITE[position - 1];
            std::cout << t.name << ": " << t.fen << "\n\n";
            stellung_setzen(*board, t.fen);
            uint64_t n = divide(*board, depth);
            if(depth <= (int)t.erwartet.size()){
                std::cout << "Erwartet: " << t.erwartet[depth - 1]
                          << (n == t.erwartet[depth - 1] ? "  -> OK\n" : "  -> FEHLER\n");
            }
            return 0;
        }

        kopfzeile();
        auto t_start = std::chrono::steady_clock::now();
        for(size_t k = 0; k < TESTSUITE.size(); k++){
            if(position != -1 && (int)k != position - 1){
                continue;
            }
            const Teststellung &t = TESTSUITE[k];
            int bis = t.standardtiefe;
            if(depth > 0)    bis = depth;
            if(maxdepth > 0) bis = std::min(bis, maxdepth);
            // nur die Zieltiefe messen und anzeigen (nicht 1 bis Zieltiefe)
            Resultat r = messen(*board, std::to_string(k + 1) + " " + t.name, t.fen, "", bis, &t.erwartet);
            zeile(r);
            if(r.hat_referenz && r.knoten != r.erwartet){
                fehler++;
            }
            resultate.push_back(r);
        }
        double total_s = std::chrono::duration<double>(std::chrono::steady_clock::now() - t_start).count();

        int mit_ref = 0;
        for(auto &r : resultate) if(r.hat_referenz) mit_ref++;
        std::cout << std::string(87, '=') << '\n';
        std::cout << "Bestanden: " << (mit_ref - fehler) << " / " << mit_ref
                  << "   |   Gesamtzeit: " << std::fixed << std::setprecision(1) << total_s << " s\n";
        if(fehler == 0){
            std::cout << "Alle Perft-Werte stimmen mit dem Chess Programming Wiki überein.\n";
        }
        else{
            std::cout << "Abweichung gefunden. Mit --position K --depth N --divide den Fehler eingrenzen.\n";
        }
    }

    if(!csv.empty()){
        csv_schreiben(csv, resultate);
    }
    return fehler == 0 ? 0 : 2;
}