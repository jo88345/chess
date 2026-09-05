#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <chrono>
#include <cmath>


class King{
    public:
    int square;
    std::vector<char> legal_moves;
    bool color = true;
    bool hasmoved = false;
    std::vector<char> legal_destinations;
};
class Queen{
    public:
    int square;
    std::vector<char> legal_moves;
    bool color = true;
    double value = 9;
    bool has_moved_previously = false;
    std::vector<char> legal_destinations;
};
class Rook{
    public:
    int square;
    std::vector<char> legal_moves;
    bool color = true;
    bool hasmoved = false;
    double value = 5;
    bool has_moved_previously = false;
    std::vector<char> legal_destinations;
};
class Bishop{
    public:
    int square;
    std::vector<char> legal_moves;
    bool color = true;
    double value = 3.5;
    bool has_moved_previously = false;
    std::vector<char> legal_destinations;
};
class Knight{
    public:
    int square;
    std::vector<char> legal_moves;
    bool color = true;
    double value = 3;
    bool has_moved_previously = false;
    std::vector<char> legal_destinations;
};
class pawn{
    public:
    int square;
    std::vector<char> legal_moves;
    bool color = true;
    bool has_moved = false;
    bool en_passent_able = false;
    double value = 1;
    bool ispassed = true;
    bool is_weak= true;
    std::vector<char> legal_destinations; //Die Frage war, ob ich hier ein char Vektor oder ien int Vektor machen sollte. Ein int Vektor würde dabei nur die Zielfelder beinhalten. Dies wäre zwar effizienter, jedoch ist es ein Albtraum, damit ein Programm zu debugen, sodass ich mch für char entschieden habe
};

class Previous_move{
    public:
    int current_square;
    char currentsquare;
    int  initial_square;
    char initialsquare;
    bool was_en_passent = false;
    bool was_promotion = false;
    bool white_queenside = false;
    bool white_kingside = false;
    bool black_queenside = false;
    bool black_kingside = false;
    int en_passent_able_square = -1;
    bool is_forcing = false;
    char previous_promotion;
    double difference;
    bool was_check = false;
};

class Board{ //Idee aus ChatGPT
    public:
    std::vector<char> board;
    std::string previous_board;
    std::vector<std::string> previous_boards;
    std::vector<pawn> whitePawns;
    std::vector<pawn> blackPawns;
    std::vector<Knight> whiteKnight;
    std::vector<Knight> blackKnight;
    std::vector<Bishop> whiteBishop;
    std::vector<Bishop> blackBishop;
    std::vector<Rook> whiterook;
    std::vector<Rook> blackrook;
    std::vector<Queen> whiteQueen;
    std::vector<Queen> blackQueen;
    std::vector<King> whiteKing;
    std::vector<King> blackKing;
    std::vector<char> legal_black_moves;
    std::vector<char> legal_white_moves;
    bool turn; //true --> weiss am Zug, false --> schwarz am Zug
    std::vector<int> legal_starting_squares;
    std::vector<int> legal_target_squares;
    std::vector<std::string> boards;
    std::string previous_move;
    double eval = 0;
    std::vector<double> tempmax;
    std::vector<double> tempmin;
    std::vector<std::string> previous_moves;
    std::vector<double> maxer;
    std::vector<std::vector<double>> eval_tree;
    std::vector<double> miner;
    std::string move;
    std::vector<std::string> candidates;
    bool breaker = false;
    bool was_check;
    bool isset = false;
    int saved_amount;
    bool punish = false;
    int numMove;
    std::vector<Previous_move> Previous_moves;
    bool search;
    bool printer;
    std::vector<char> interpose_help_white;
    std::vector<char> interpose_help_black;

    void printboard(std::vector<char> board){
        for(int i = 0; i < 64; i++){
            std::cout << board[i];
            if(i % 8 == 7){
                std::cout << '\n';
            }
        }
        std::cout << '\n';
    }
    void fillboard(std::vector<char> &board){
    board.assign(64, '0'); //command von Claude
    }
};


void FEN_to_position(Board &board, std::string FEN);
std::string index_to_square(int index);
void piecelist(Board &board);
void whiteQueenmovement(Board &board);
void blackQueenmovement(Board&board);
bool isblackpiece(std::vector<char> &board, int square);
bool iswhitepiece(std::vector<char> &board, int square);
void whiteRookmovement(Board &board);
void blackRookmovement(Board &board);
void whiteBishopmovement(Board &board);
void blackBishopmovement(Board &board);
void whiteKingmovement(Board &board);
void blackKingmovement(Board &board);
void legal_moves(Board &board);
void whiteKnightmovement(Board &board);
void blackKnightmovement(Board &board);
void Whitepawnmovement(Board &board);
void Blackpawnmovement(Board &board);
void FEN_extra(Board &board, std::string FEN);
int rookfinder(std::vector<Rook> &rooks, int square);
bool ismove(char x, char y);
int square_to_index(char file, char row);
int pawnfinder(std::vector<pawn> &pawns, int square);
int movecounter(Board &board);
bool iswhiteincheck(Board &board);
bool isblackincheck(Board &board);
int onecounter(std::vector<char> legalboard);
int zerocounter(std::vector<char> legalboard);
bool check_check_white(Board &board, int startingsquare, int targetsquare);
bool check_check_black(Board &board, int startingsquare, int targetsquare);
void actual_legal_moves(Board &board);
std::string position_to_FEN(Board &board);
void domove(Board &board, int startingsquare, int targetsquare, char promotion);
void white_expansion(Board &board);
void black_expansion(Board &board);
int positionfinder(std::vector<std::string> positions, std::string wanted_position);
double Tree(Board &board, int depth, int &positions, const int &constant_depth, double alpha, double beta);
int knightfinder(std::vector<Knight> &knights, int square);
int bishopfinder(std::vector<Bishop> &bishops, int square);
int queenfinder(std::vector<Queen> &queens, int square);
void remember_board(Board &board, int startingsquare, int targetsquare, char promotion);
void undomove(Board &board);
void legal_white_moves(Board &board);
void legal_black_moves(Board &board);
void random_Play(Board &board);
double evaluation(Board &board);
double difference(Board &board, int startingsquare, int targetsquare);
void domove_temp(std::vector<char> &board, int startingsquare, int targetsquare, char promotion);
bool square_attacked(std::vector<char> &b, int square, bool byWhite);
void cycle(Board &board, int depth);
int piececounter (std::vector<char> &board);
int distance(int start, int target);
int distance(int start, int target);
void weak_pawns(Board &board);
bool is_mate_threatened(Board &board, bool bywhite);
bool can_interpose(Board &board, int startingsquare, int targetsquare, bool color);
bool only_king(Board &board, int square, bool color);














int main(){
    std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; //rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    std::string FEN2;
    std::vector<char> testboard;
    std::vector<std::string> positions_2;
    std::vector<std::string> positions_3;
    std::vector<std::vector<std::string>> tree;
    std::vector<std::string> temppositions;
    int depth = 4;
    int temp = 0;
    int positions = 0;
    int counter = 0;
    int random;
    int random_2;
    std::string start;
    std::string target;
    double alpha = -10000;
    double beta = 10000;
    char promotion;
    int rep = 0;
    bool breaker = false;

    Board board;

    board.fillboard(board.board);

    board.printboard(board.board);

    
    board.fillboard(board.board);
    board.fillboard(board.legal_black_moves);
    board.fillboard(board.legal_white_moves);


    for(int i = 0; i < 64; i++){
        std::cout << i << " ";
        if(i % 8 == 7){
            std::cout << '\n';
        }
    }
    
    FEN_to_position(board, FEN);

    piecelist(board);

    FEN_extra(board, FEN);

    legal_moves(board);
    actual_legal_moves(board);

    if(board.turn){
        white_expansion(board);        
    } 
    else{
        black_expansion(board);         
    }

    Tree(board, 4, positions, 4, alpha, beta);
    std::cout << board.move << '\n';

    /*

    while(board.legal_target_squares.size() != 0 && !breaker){
        if(board.turn){
            cycle(board, 4);
            if(board.board[square_to_index(board.move[0], board.move[1])] == 'P' && board.move[3] == '8'){
                domove(board, square_to_index(board.move[0], board.move[1]), square_to_index(board.move[2], board.move[3]), board.move[4]);
            }
            else{
                domove(board, square_to_index(board.move[0], board.move[1]), square_to_index(board.move[2], board.move[3]), '0');
            }
            std::cout << board.legal_target_squares.size() << '\n';
            std::cout << board.move << '\n';
        }

        board.printboard(board.board);  
        if(!board.turn){
            std::cout << "Startingsquare: " << '\n';
            std::cin >> start;
            std::cout << "Targetsquare: " << '\n';
            std::cin >> target;
            if(board.board[square_to_index(start[0],start[1])] == 'p' && target[1] == '1'){
                std::cout << "promotion:" << '\n';
                std::cin >> promotion;
                domove(board, square_to_index(start[0], start[1]), square_to_index(target[0], target[1]), promotion);
            }
            else{
                domove(board, square_to_index(start[0], start[1]), square_to_index(target[0], target[1]), '0');
            }
            for(int i = 0; i < board.previous_boards.size(); i++){ //3-fach Stellungswiederholungs check
                for(int j = 0; j < board.previous_boards.size(); j++){
                    if(board.previous_boards[j] == board.previous_boards[i] && i != j){
                        rep++;
                    if(rep == 3){
                        std::cout << "draw" << '\n';
                        breaker = true;
                    }
                }
            }
        }
    }

        
        board.previous_moves.clear();
        board.printboard(board.board);
    }

    /*
    

    for(int i = 1; i < 4; i++){
        std::cout << i << '\n';
        Tree(board, i, positions, i, alpha, beta);
        std::cout <<  board.move << '\n';
        board.previous_moves.clear();
    }

    
    
    for(int i = 1; i < 4; i++){
        Tree(board, i, positions, i, alpha, beta);
        std::cout << i <<'\n';
        std::cout << board.move << '\n';
    }


    

    
    while(board.legal_starting_squares.size() != 0){
        Play(board);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        board.printboard(board.board);
        std::cout << position_to_FEN(board) << '\n';
    }
    */
    
    
    return 0;
}

void FEN_to_position(Board &board, std::string FEN){ 
    int n = 0;
    int m = 0;
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == '/'){
            FEN.erase(FEN.begin() + i);
        }
    }
    for(int i = 0; i < FEN.length(); i++){
        if(std::isalpha(FEN[i]) && i+n < 64){ //std::isalpha() command von ChatGPT
            board.board[i + n] = FEN[i];
        }
        if(std::isdigit(FEN[i])){
            n += FEN[i] - '0' - 1;
        }
        if(FEN[i] == ' '){
            break;
        }
    }
}

std::string index_to_square(int index){
    std::string square;
    std::string rank = std::to_string(-(index / 8) + 8); //Da wir bei FEN und anderen nummereierungssysteme bei a8 beginnen zu zählen, stellt dies eine Herausforderung dar für das Umrechnen einer Zahl zu einem Feld. Deshalb diese komische Gleichung.
    int file = index % 8;
    switch(file){
        case 0:
        square = "a" + rank;
        break;
        case 1:
        square = "b" + rank;
        break;
        case 2:
        square = "c" + rank;
        break;
        case 3:
        square = "d" + rank;
        break;
        case 4:
        square = "e" + rank;
        break;
        case 5:
        square = "f" + rank;
        break;
        case 6:
        square = "g" + rank;
        break;
        case 7:
        square = "h" + rank;
        break;
    }
    return square;
}

int square_to_index(char file, char row){
    int index = 0;
    switch(file){
        case 'a':
        break;
        case 'b':
        index += 1;
        break;
        case 'c':
        index += 2;
        break;
        case 'd':
        index += 3;
        break;
        case 'e':
        index += 4;
        break;
        case 'f':
        index += 5;
        break;
        case 'g':
        index += 6;
        break;
        case 'h':
        index += 7;
        break; 
    }
    index += (8 - (row - 48)) * 8;

    return index;
}

void piecelist(Board &board){
    bool temp_0 = false;
    bool temp_7 = false;
    bool temp_56 = false;
    bool temp_63 = false;
    if(rookfinder(board.blackrook, 0) != -1 &&board.board[0] == 'r' && board.blackrook.size() != 0 && board.blackrook[rookfinder(board.blackrook, 0)].hasmoved == true){
        temp_0 = true;
    }
    if(rookfinder(board.blackrook, 7) != -1 &&board.board[7] == 'r' && board.blackrook.size() != 0 && board.blackrook[rookfinder(board.blackrook, 7)].hasmoved == true){
        temp_7 = true;
    }
    if(rookfinder(board.whiterook, 56) != -1 && board.board[56] == 'R' && board.whiterook.size() != 0 && board.whiterook[rookfinder(board.whiterook, 56)].hasmoved == true){
        temp_56 = true;
    }
    if(rookfinder(board.whiterook, 63) != -1 &&board.board[63] == 'R' && board.whiterook.size() != 0 && board.whiterook[rookfinder(board.whiterook, 63)].hasmoved == true){
        temp_63 = true;
    } 
    
    board.whitePawns.clear();
    board.blackPawns.clear();
    board.whiteBishop.clear();
    board.blackBishop.clear();
    board.whiteKnight.clear();
    board.blackKnight.clear();
    board.whiterook.clear();
    board.blackrook.clear();
    board.whiteQueen.clear();
    board.blackQueen.clear();
    board.whiteKing.clear();
    board.blackKing.clear(); //Sonst würde das updaten unmöglich sein, da es einfach neue Objekte macht
    for(int i = 0; i < 64; i++){
        if(board.board[i] == 'p'){
            pawn pawn;
            pawn.color = 0;
            pawn.square = i;
            if(i / 8 == 1){
                pawn.has_moved = 0;
            }
            board.blackPawns.push_back(pawn);
        }
        if(board.board[i] == 'P'){
            pawn pawn;
            pawn.color = 1;
            pawn.square = i;
            if(i / 8 == 6){
                pawn.has_moved = 0;
            }
            board.whitePawns.push_back(pawn);
        }
        if(board.board[i] == 'n'){
            Knight knight;
            knight.color = 0;
            knight.square = i;
            board.blackKnight.push_back(knight);

        }
        if(board.board[i] == 'N'){
            Knight knight;
            knight.color = 1;
            knight.square = i;
            board.whiteKnight.push_back(knight);
        }
        if(board.board[i] == 'b'){
            Bishop bishop;
            bishop.color = 0;
            bishop.square = i;
            board.blackBishop.push_back(bishop);
        }
        if(board.board[i] == 'B'){
            Bishop bishop;
            bishop.color = 1;
            bishop.square = i;
            board.whiteBishop.push_back(bishop);
        }
        if(board.board[i] == 'r'){
            Rook rook;
            rook.color = 0;
            rook.square = i;
            if(i == 0){
                rook.hasmoved = temp_0;
            }
            if(i == 7){
                rook.hasmoved = temp_7;
            }
            board.blackrook.push_back(rook);
        }
        if(board.board[i] == 'R'){
            Rook rook;
            rook.color = 1;
            rook.square = i;
            if(i == 56){
                rook.hasmoved = temp_56;
            }
            if(i == 63){
                rook.hasmoved = temp_63;
            }
            board.whiterook.push_back(rook);
        }
        if(board.board[i] == 'q'){
            Queen queen;
            queen.color = 0;
            queen.square = i;
            board.blackQueen.push_back(queen);
        }
        if(board.board[i] == 'Q'){
            Queen queen;
            queen.color = 1;
            queen.square = i;
            board.whiteQueen.push_back(queen);
        }
        if(board.board[i] == 'k'){
            King king;
            king.color = 0;
            king.square = i;
            board.blackKing.push_back(king);
        }
        if(board.board[i] == 'K'){
            King king;
            king.color = 1;
            king.square = i;
            board.whiteKing.push_back(king);
        }
    }
}

void whiteQueenmovement(Board &board){
    for(Queen &piece : board.whiteQueen){
        board.fillboard(piece.legal_moves);
        bool breaker = false;
        piece.legal_moves[piece.square] = 'Q';
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*9) >= 0 && (piece.square-(i-1)*9) % 8 != 0 && (board.board[piece.square - 9*i] == '0' || isblackpiece(board.board, piece.square - 9*i))&& !iswhitepiece(board.board, piece.square - 9*i)){
                piece.legal_moves[piece.square - i*9] = '1';
                board.legal_white_moves[piece.square - i*9] = '1';
                board.interpose_help_white[piece.square - i*9] = '1';
                if(isblackpiece(board.board, piece.square - 9*i)){
                   breaker = true;
                }
            }
            else{
                breaker = true;
                }
        }
    
    breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*8) >= 0  && (board.board[piece.square - 8*i] == '0' || isblackpiece(board.board, piece.square - 8*i))&& !iswhitepiece(board.board, piece.square - 8*i)){
                piece.legal_moves[piece.square - i*8] = '1';
                board.legal_white_moves[piece.square - i*8] = '1';
                board.interpose_help_white[piece.square - i*8] = '1';
                if(isblackpiece(board.board, piece.square - 8*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*7) >= 0 && (piece.square-(i-1)*7) % 8 != 7 && (board.board[piece.square - 7*i] == '0' || isblackpiece(board.board, piece.square - 7*i))&& !iswhitepiece(board.board, piece.square - 7*i)){
                piece.legal_moves[piece.square - i*7] = '1';
                board.legal_white_moves[piece.square - i*7] = '1';
                board.interpose_help_white[piece.square - i*7] = '1';
                if(isblackpiece(board.board, piece.square - 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if((piece.square-(i-1)) % 8 != 0 && (board.board[piece.square - i] == '0' || isblackpiece(board.board, piece.square - i))&& !iswhitepiece(board.board, piece.square - i)){
                piece.legal_moves[piece.square - i] = '1';
                board.legal_white_moves[piece.square - i] = '1';
                board.interpose_help_white[piece.square - i] = '1';
                if(isblackpiece(board.board, piece.square - i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*7) <= 63 && (piece.square+(i-1)*7) % 8 != 0 && (board.board[piece.square + 7*i] == '0' || isblackpiece(board.board, piece.square + 7*i))&& !iswhitepiece(board.board, piece.square + 7*i)){
                piece.legal_moves[piece.square + i*7] = '1';
                board.legal_white_moves[piece.square + i*7] = '1';
                board.interpose_help_white[piece.square + i*7] = '1';
                if(isblackpiece(board.board, piece.square + 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            } 
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*8) <= 63 && (board.board[piece.square + 8*i] == '0' || isblackpiece(board.board, piece.square + 8*i))&& !iswhitepiece(board.board, piece.square + 8*i)){
                piece.legal_moves[piece.square + i*8] = '1';
                board.legal_white_moves[piece.square + i*8] = '1';
                board.interpose_help_white[piece.square + i*7] = '1';
                if(isblackpiece(board.board, piece.square + 8*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*9) <= 63 && (piece.square+(i-1)*9) % 8 != 7 && (board.board[piece.square + 9*i] == '0' || isblackpiece(board.board, piece.square + 9*i))&& !iswhitepiece(board.board, piece.square + 9*i)){
                piece.legal_moves[piece.square + i*9] = '1';
                board.legal_white_moves[piece.square + i*9] = '1';
                if(isblackpiece(board.board, piece.square + 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
                if((piece.square+(i-1)) % 8 != 7 && (board.board[piece.square + i] == '0' || isblackpiece(board.board, piece.square + i))&& !iswhitepiece(board.board, piece.square + i)){
                    piece.legal_moves[piece.square + i] = '1';
                    board.legal_white_moves[piece.square + i] = '1';
                    board.interpose_help_white[piece.square + i] = '1';
                    if(isblackpiece(board.board, piece.square + i)){
                        breaker = true;
                    }
                }
                else{
                    breaker = true;
                }
            }
        breaker = false;
    }
}

void blackQueenmovement(Board&board){
    for(Queen &piece : board.blackQueen){
        board.fillboard(piece.legal_moves);
        bool breaker = false;
        piece.legal_moves[piece.square] = 'Q';
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*9) >= 0 && (piece.square-(i-1)*9) % 8 != 0 && (board.board[piece.square - 9*i] == '0' || iswhitepiece(board.board, piece.square - 9*i))&& !isblackpiece(board.board, piece.square - 9*i)){
                piece.legal_moves[piece.square - i*9] = '1';
                board.legal_black_moves[piece.square - i*9] = '1';
                board.interpose_help_black[piece.square - i*9] = '1';
                if(iswhitepiece(board.board, piece.square - 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*8) >= 0  && (board.board[piece.square - 8*i] == '0' || iswhitepiece(board.board, piece.square - 8*i))&& !isblackpiece(board.board, piece.square - 8*i)){
                piece.legal_moves[piece.square - i*8] = '1';
                board.legal_black_moves[piece.square - i*8] = '1';
                board.interpose_help_black[piece.square - i*8] = '1';
                if(iswhitepiece(board.board, piece.square - 8*i)){
                    breaker = true;
                }
                }
                else{
                    breaker = true;
                }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*7) >= 0 && (piece.square-(i-1)*7) % 8 != 7 && (board.board[piece.square - 7*i] == '0' || iswhitepiece(board.board, piece.square - 7*i))&& !isblackpiece(board.board, piece.square - 7*i)){
                piece.legal_moves[piece.square - i*7] = '1';
                board.legal_black_moves[piece.square - i*7] = '1';
                board.interpose_help_black[piece.square - i*7] = '1';
                if(iswhitepiece(board.board, piece.square - 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if((piece.square-(i-1)) % 8 != 0 && (board.board[piece.square - i] == '0' || iswhitepiece(board.board, piece.square - i))&& !isblackpiece(board.board, piece.square - i)){
                piece.legal_moves[piece.square - i] = '1';
                board.legal_black_moves[piece.square - i] = '1';
                board.interpose_help_black[piece.square - i] = '1';
                if(iswhitepiece(board.board, piece.square - i)){
                        breaker = true;
                    }
                }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*7) <= 63 && (piece.square+(i-1)*7) % 8 != 0 && (board.board[piece.square + 7*i] == '0' || iswhitepiece(board.board, piece.square + 7*i))&& !isblackpiece(board.board, piece.square + 7*i)){
                piece.legal_moves[piece.square + i*7] = '1';
                board.legal_black_moves[piece.square + i*7] = '1';
                board.interpose_help_black[piece.square + i*7] = '1';
                if(iswhitepiece(board.board, piece.square + 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*8) <= 63 && (board.board[piece.square + 8*i] == '0' || iswhitepiece(board.board, piece.square + 8*i))&& !isblackpiece(board.board, piece.square + 8*i)){
                piece.legal_moves[piece.square + i*8] = '1';
                board.legal_black_moves[piece.square + i*8] = '1';
                board.interpose_help_black[piece.square + i*8] = '1';
                if(iswhitepiece(board.board, piece.square + 8*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*9) <= 63 && (piece.square+(i-1)*9) % 8 != 7 && (board.board[piece.square + 9*i] == '0' || iswhitepiece(board.board, piece.square + 9*i))&& !isblackpiece(board.board, piece.square + 9*i)){
                piece.legal_moves[piece.square + i*9] = '1';
                board.legal_black_moves[piece.square + i*9] = '1';
                board.interpose_help_black[piece.square + i*9] = '1';
                if(iswhitepiece(board.board, piece.square + 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if((piece.square+(i-1)) % 8 != 7 && (board.board[piece.square + i] == '0' || iswhitepiece(board.board, piece.square + i))&& !isblackpiece(board.board, piece.square + i)){
                piece.legal_moves[piece.square + i] = '1';
                board.legal_black_moves[piece.square + i] = '1';
                board.interpose_help_black[piece.square + i] = '1';
                if(iswhitepiece(board.board, piece.square + i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
    }
}

bool isblackpiece(std::vector<char> &board, int square){
    if(board[square] == 'p'){
        return true;
    }
    else if(board[square] == 'k'){
        return true;
    }
    else if(board[square] == 'n'){
        return true;
    }
    else if(board[square] == 'b'){
        return true;
    }
    else if(board[square] == 'r'){
        return true;
    }
    else if(board[square] == 'q'){
        return true;
    }
    else{
        return false;
    }
}

bool iswhitepiece(std::vector<char> &board, int square){ //Hilfsfunktion
    if(board[square] == 'P'){
        return true;
    }
    else if(board[square] == 'K'){
        return true;
    }
    else if(board[square] == 'N'){
        return true;
    }
    else if(board[square] == 'B'){
        return true;
    }
    else if(board[square] == 'R'){
        return true;
    }
    else if(board[square] == 'Q'){
        return true;
    }
    else{
        return false;
    }
}

void whiteRookmovement(Board &board){
    for(Rook &piece : board.whiterook){
        board.fillboard(piece.legal_moves);
        bool breaker = false;
        piece.legal_moves[piece.square] = 'R';
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*8) >= 0  && (board.board[piece.square - 8*i] == '0' || isblackpiece(board.board, piece.square - 8*i))&& !iswhitepiece(board.board, piece.square - 8*i)){
                piece.legal_moves[piece.square - i*8] = '1';
                board.legal_white_moves[piece.square - i*8] = '1';
                board.interpose_help_white[piece.square - i*8] = '1';
                if(isblackpiece(board.board, piece.square - 8*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if((piece.square-(i-1)) % 8 != 0 && (board.board[piece.square - i] == '0' || isblackpiece(board.board, piece.square - i))&& !iswhitepiece(board.board, piece.square - i)){
                piece.legal_moves[piece.square - i] = '1';
                board.legal_white_moves[piece.square - i] = '1';
                board.interpose_help_white[piece.square - i] = '1';
                if(isblackpiece(board.board, piece.square - i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*8) <= 63 && (board.board[piece.square + 8*i] == '0' || isblackpiece(board.board, piece.square + 8*i))&& !iswhitepiece(board.board, piece.square + 8*i)){
                piece.legal_moves[piece.square + i*8] = '1';
                board.legal_white_moves[piece.square + i*8] = '1';
                board.interpose_help_white[piece.square + i*8] = '1';
                if(isblackpiece(board.board, piece.square + 8*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }  
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
                if((piece.square+(i-1)) % 8 != 7 && (board.board[piece.square + i] == '0' || isblackpiece(board.board, piece.square + i))&& !iswhitepiece(board.board, piece.square + i)){
                    piece.legal_moves[piece.square + i] = '1';
                    board.legal_white_moves[piece.square + i] = '1';
                    board.interpose_help_white[piece.square + i] = '1';
                    if(isblackpiece(board.board, piece.square + i)){
                        breaker = true;
                    }
                }
                else{
                    breaker = true;
                }
            }
        breaker = false;
    }
}

void blackRookmovement(Board &board){
    for(Rook &piece : board.blackrook){
        board.fillboard(piece.legal_moves);
        bool breaker = false;
        piece.legal_moves[piece.square] = 'R';
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*8) >= 0  && (board.board[piece.square - 8*i] == '0' || iswhitepiece(board.board, piece.square - 8*i))&& !isblackpiece(board.board, piece.square - 8*i)){
                piece.legal_moves[piece.square - i*8] = '1';
                board.legal_black_moves[piece.square - i*8] = '1';
                board.interpose_help_black[piece.square - i*8] = '1';
                if(iswhitepiece(board.board, piece.square - 8*i)){
                    breaker = true;
                }
                }
                else{
                    breaker = true;
                }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if((piece.square-(i-1)) % 8 != 0 && (board.board[piece.square - i] == '0' || iswhitepiece(board.board, piece.square - i))&& !isblackpiece(board.board, piece.square - i)){
                piece.legal_moves[piece.square - i] = '1';
                board.legal_black_moves[piece.square - i] = '1';
                board.interpose_help_black[piece.square - i] = '1';
                if(iswhitepiece(board.board, piece.square - i)){
                        breaker = true;
                    }
                }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*8) <= 63 && (board.board[piece.square + 8*i] == '0' || iswhitepiece(board.board, piece.square + 8*i))&& !isblackpiece(board.board, piece.square + 8*i)){
                piece.legal_moves[piece.square + i*8] = '1';
                board.legal_black_moves[piece.square + i*8] = '1';
                board.interpose_help_black[piece.square + i*8] = '1';
                if(iswhitepiece(board.board, piece.square + 8*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if((piece.square+(i-1)) % 8 != 7 && (board.board[piece.square + i] == '0' || iswhitepiece(board.board, piece.square + i))&& !isblackpiece(board.board, piece.square + i)){
                piece.legal_moves[piece.square + i] = '1';
                board.legal_black_moves[piece.square + i] = '1';
                board.interpose_help_black[piece.square + i] = '1';
                if(iswhitepiece(board.board, piece.square + i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
    }
}

void whiteBishopmovement(Board &board){
    for(Bishop &piece : board.whiteBishop){
        board.fillboard(piece.legal_moves);
        bool breaker = false;
        piece.legal_moves[piece.square] = 'B';
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*9) >= 0 && (piece.square-(i-1)*9) % 8 != 0 && (board.board[piece.square - 9*i] == '0' || isblackpiece(board.board, piece.square - 9*i))&& !iswhitepiece(board.board, piece.square - 9*i)){
                piece.legal_moves[piece.square - i*9] = '1';
                board.legal_white_moves[piece.square - i*9] = '1';
                board.interpose_help_white[piece.square - i*9] = '1';
                if(isblackpiece(board.board, piece.square - 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
            
            
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*7) >= 0 && (piece.square-(i-1)*7) % 8 != 7 && (board.board[piece.square - 7*i] == '0' || isblackpiece(board.board, piece.square - 7*i))&& !iswhitepiece(board.board, piece.square - 7*i)){
                piece.legal_moves[piece.square - i*7] = '1';
                board.legal_white_moves[piece.square - i*7] = '1';
                board.interpose_help_white[piece.square - i*7] = '1';
                if(isblackpiece(board.board, piece.square - 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*7) <= 63 && (piece.square+(i-1)*7) % 8 != 0 && (board.board[piece.square + 7*i] == '0' || isblackpiece(board.board, piece.square + 7*i))&& !iswhitepiece(board.board, piece.square + 7*i)){
                piece.legal_moves[piece.square + i*7] = '1';
                board.legal_white_moves[piece.square + i*7] = '1';
                board.interpose_help_white[piece.square + i*7] = '1';
                if(isblackpiece(board.board, piece.square + 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*9) <= 63 && (piece.square+(i-1)*9) % 8 != 7 && (board.board[piece.square + 9*i] == '0' || isblackpiece(board.board, piece.square + 9*i))&& !iswhitepiece(board.board, piece.square + 9*i)){
                piece.legal_moves[piece.square + i*9] = '1';
                board.legal_white_moves[piece.square + i*9] = '1';
                board.interpose_help_white[piece.square + i*9] = '1';
                if(isblackpiece(board.board, piece.square + 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
    
        breaker = false;
    }
}

void blackBishopmovement(Board &board){
    for(Bishop &piece : board.blackBishop){
        board.fillboard(piece.legal_moves);
        bool breaker = false;
        piece.legal_moves[piece.square] = 'B';
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*9) >= 0 && (piece.square-(i-1)*9) % 8 != 0 && (board.board[piece.square - 9*i] == '0' || iswhitepiece(board.board, piece.square - 9*i))&& !isblackpiece(board.board, piece.square - 9*i)){
                piece.legal_moves[piece.square - i*9] = '1';
                board.legal_black_moves[piece.square - i*9] = '1';
                board.interpose_help_black[piece.square - i*9] = '1';
                if(iswhitepiece(board.board, piece.square - 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square-(i*7) >= 0 && (piece.square-(i-1)*7) % 8 != 7 && (board.board[piece.square - 7*i] == '0' || iswhitepiece(board.board, piece.square - 7*i))&& !isblackpiece(board.board, piece.square - 7*i)){
                piece.legal_moves[piece.square - i*7] = '1';
                board.legal_black_moves[piece.square - i*7] = '1';
                board.interpose_help_black[piece.square - i*7] = '1';
                if(iswhitepiece(board.board, piece.square - 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*7) <= 63 && (piece.square+(i-1)*7) % 8 != 0 && (board.board[piece.square + 7*i] == '0' || iswhitepiece(board.board, piece.square + 7*i))&& !isblackpiece(board.board, piece.square + 7*i)){
                piece.legal_moves[piece.square + i*7] = '1';
                board.legal_black_moves[piece.square + i*7] = '1';
                board.interpose_help_black[piece.square + i*7] = '1';
                if(iswhitepiece(board.board, piece.square + 7*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
        breaker = false;
        for(int i = 1; breaker == false; i++){
            if(piece.square+(i*9) <= 63 && (piece.square+(i-1)*9) % 8 != 7 && (board.board[piece.square + 9*i] == '0' || iswhitepiece(board.board, piece.square + 9*i))&& !isblackpiece(board.board, piece.square + 9*i)){
                piece.legal_moves[piece.square + i*9] = '1';
                board.legal_black_moves[piece.square + i*9] = '1';
                board.interpose_help_black[piece.square + i*9] = '1';
                if(iswhitepiece(board.board, piece.square + 9*i)){
                    breaker = true;
                }
            }
            else{
                breaker = true;
            }
        }
    }
}

void whiteKingmovement(Board &board){
    for(King &piece : board.whiteKing){ 
        board.fillboard(piece.legal_moves);
        piece.legal_moves[piece.square] = 'K';
            if(piece.square-9 >= 0 && piece.square % 8 != 0 && (board.board[piece.square - 9] == '0' || isblackpiece(board.board, piece.square - 9))&& !iswhitepiece(board.board, piece.square - 9)){
                piece.legal_moves[piece.square - 9] = '1';
                board.legal_white_moves[piece.square - 9] = '1';
                }

            if(piece.square-8 >= 0  && (board.board[piece.square - 8] == '0' || isblackpiece(board.board, piece.square - 8))&& !iswhitepiece(board.board, piece.square - 8)){
                piece.legal_moves[piece.square - 8] = '1';
                board.legal_white_moves[piece.square - 8] = '1';
                }
            
            if(piece.square-7 >= 0 && piece.square % 8 != 7 && (board.board[piece.square - 7] == '0' || isblackpiece(board.board, piece.square - 7))&& !iswhitepiece(board.board, piece.square - 7)){
                piece.legal_moves[piece.square - 7] = '1';
                board.legal_white_moves[piece.square - 7] = '1';
                }
            
            if(piece.square % 8 != 0 && (board.board[piece.square - 1] == '0' || isblackpiece(board.board, piece.square - 1))&& !iswhitepiece(board.board, piece.square - 1)){
                piece.legal_moves[piece.square - 1] = '1';
                board.legal_white_moves[piece.square - 1] = '1';
                }
            
            if(piece.square+7 <= 63 && piece.square % 8 != 0 && (board.board[piece.square + 7] == '0' || isblackpiece(board.board, piece.square + 7))&& !iswhitepiece(board.board, piece.square + 7)){
                piece.legal_moves[piece.square + 7] = '1';
                board.legal_white_moves[piece.square + 7] = '1';
                }
            
            if(piece.square+8 <= 63 && (board.board[piece.square + 8] == '0' || isblackpiece(board.board, piece.square + 8))&& !iswhitepiece(board.board, piece.square + 8)){
                piece.legal_moves[piece.square + 8] = '1';
                board.legal_white_moves[piece.square + 8] = '1';
                }
            
            if(piece.square+9 <= 63 && piece.square % 8 != 7 && (board.board[piece.square + 9] == '0' || isblackpiece(board.board, piece.square + 9))&& !iswhitepiece(board.board, piece.square + 9)){
                piece.legal_moves[piece.square + 9] = '1';
                board.legal_white_moves[piece.square + 9] = '1';
                }
            
            if(piece.square % 8 != 7 && (board.board[piece.square + 1] == '0' || isblackpiece(board.board, piece.square + 1))&& !iswhitepiece(board.board, piece.square + 1)){
                piece.legal_moves[piece.square + 1] = '1';
                board.legal_white_moves[piece.square + 1] = '1';
                }
            
            if(piece.hasmoved == false && board.board[60] == 'K' && board.board[63] == 'R' && rookfinder(board.whiterook, 63) != -1 && board.whiterook[rookfinder(board.whiterook, 63)].hasmoved == false && board.legal_black_moves[61] == '0' && board.legal_black_moves[62] == '0' && board.board[62] == '0' && board.board[61] == '0'){
                board.legal_white_moves[62] = '1';
                piece.legal_moves[62] = '1';
                }
            if(piece.hasmoved == false && board.board[60] == 'K' && board.board[56] == 'R' && rookfinder(board.whiterook, 56) != -1 && board.whiterook[rookfinder(board.whiterook, 56)].hasmoved == false && board.legal_black_moves[58] == '0' && board.legal_black_moves[59] == '0' && board.board[58] == '0' && board.board[59] == '0' && board.board[57] == '0'){
                board.legal_white_moves[58] = '1';
                piece.legal_moves[58] = '1';
            }
    }
}

void blackKingmovement(Board &board){
        for(King &piece : board.blackKing){
            board.fillboard(piece.legal_moves);
                piece.legal_moves[piece.square] = 'K';
                if(piece.square-9 >= 0 && piece.square % 8 != 0 && (board.board[piece.square - 9] == '0' || iswhitepiece(board.board, piece.square - 9))&& !isblackpiece(board.board, piece.square - 9)){
                    piece.legal_moves[piece.square - 9] = '1';
                    board.legal_black_moves[piece.square - 9] = '1';
                }
        
                if(piece.square-8 >= 0  && (board.board[piece.square - 8] == '0' || iswhitepiece(board.board, piece.square - 8))&& !isblackpiece(board.board, piece.square - 8)){
                    piece.legal_moves[piece.square - 8] = '1';
                    board.legal_black_moves[piece.square - 8] = '1';
                }
            
                if(piece.square-7 >= 0 && piece.square % 8 != 7 && (board.board[piece.square - 7] == '0' || iswhitepiece(board.board, piece.square - 7))&& !isblackpiece(board.board, piece.square - 7)){
                    piece.legal_moves[piece.square - 7] = '1';
                    board.legal_black_moves[piece.square - 7] = '1';
                }
            
                if(piece.square % 8 != 0 && (board.board[piece.square - 1] == '0' || iswhitepiece(board.board, piece.square - 1))&& !isblackpiece(board.board, piece.square - 1)){
                    piece.legal_moves[piece.square - 1] = '1';
                    board.legal_black_moves[piece.square - 1] = '1';
                }
            
                if(piece.square+7 <= 63 && piece.square % 8 != 0 && (board.board[piece.square + 7] == '0' || iswhitepiece(board.board, piece.square + 7))&& !isblackpiece(board.board, piece.square + 7)){
                    piece.legal_moves[piece.square + 7] = '1';
                    board.legal_black_moves[piece.square + 7] = '1';
                }
            
                if(piece.square+8 <= 63 && (board.board[piece.square + 8] == '0' || iswhitepiece(board.board, piece.square + 8)) && !isblackpiece(board.board, piece.square + 8)){
                    piece.legal_moves[piece.square + 8] = '1';
                    board.legal_black_moves[piece.square + 8] = '1';
                }
            
                if(piece.square+9 <= 63 && piece.square % 8 != 7 && (board.board[piece.square + 9] == '0' || iswhitepiece(board.board, piece.square + 9))&& !isblackpiece(board.board, piece.square + 9)){
                    piece.legal_moves[piece.square + 9] = '1';
                    board.legal_black_moves[piece.square + 9] = '1';
                }
            
                if(piece.square % 8 != 7 && (board.board[piece.square + 1] == '0' || iswhitepiece(board.board, piece.square + 1))&& !isblackpiece(board.board, piece.square + 1)){
                    piece.legal_moves[piece.square + 1] = '1';
                    board.legal_black_moves[piece.square + 1] = '1';
                }
            
                if(piece.hasmoved == false && board.board[4] == 'k' && board.board[0] == 'r' && rookfinder(board.blackrook, 0) != -1 && board.blackrook[rookfinder(board.blackrook, 0)].hasmoved == false && board.legal_white_moves[2] == '0' && board.legal_white_moves[3] == '0' && board.board[2] == '0' && board.board[3] == '0' && board.board[1] == '0'){
                    board.legal_black_moves[2] = '1';
                    piece.legal_moves[2] = '1';
                }
                if(piece.hasmoved == false && board.board[4] == 'k' && board.board[7] == 'r' && rookfinder(board.blackrook, 0) != -1 && board.blackrook[rookfinder(board.blackrook, 7)].hasmoved == false && board.legal_white_moves[6] == '0' && board.legal_white_moves[5] == '0' && board.board[5] == '0' && board.board[6] == '0'){
                    board.legal_black_moves[6] = '1';
                    piece.legal_moves[6] = '1';
                }
        }
}

int rookfinder(std::vector<Rook> &rooks, int square){
    for(int i = 0; i < rooks.size(); i++){
        if(rooks[i].square == square){
            return i;
        }
    }
    return -1;
}

void whiteKnightmovement(Board &board){
    for(Knight &piece : board.whiteKnight){
        board.fillboard(piece.legal_moves);
        piece.legal_moves[piece.square] = 'N';
        if(piece.square - 10 >= 0 && piece.square % 8 > 1 &&(board.board[piece.square - 10] == '0' || isblackpiece(board.board, piece.square - 10)) && !iswhitepiece(board.board, piece.square - 10)){
            piece.legal_moves[piece.square - 10] = '1';
            board.legal_white_moves[piece.square - 10] = '1';
            board.interpose_help_white[piece.square - 10] = '1';
        }
        
        if(piece.square - 17 >= 0 && piece.square % 8 > 0 &&(board.board[piece.square - 17] == '0' || isblackpiece(board.board, piece.square - 17)) && !iswhitepiece(board.board, piece.square - 17)){
            piece.legal_moves[piece.square - 17] = '1';
            board.legal_white_moves[piece.square - 17] = '1';
            board.interpose_help_white[piece.square - 17] = '1';
        }
        if(piece.square - 15 >= 0 && piece.square % 8 < 7 &&(board.board[piece.square - 15] == '0' || isblackpiece(board.board, piece.square - 15)) && !iswhitepiece(board.board, piece.square - 15)){
            piece.legal_moves[piece.square - 15] = '1';
            board.legal_white_moves[piece.square - 15] = '1';
            board.interpose_help_white[piece.square - 15] = '1';
        }
        if(piece.square - 6 >= 0 && piece.square % 8 < 6 &&(board.board[piece.square - 6] == '0' || isblackpiece(board.board, piece.square - 6)) && !iswhitepiece(board.board, piece.square - 6)){
            piece.legal_moves[piece.square - 6] = '1';
            board.legal_white_moves[piece.square - 6] = '1';
            board.interpose_help_white[piece.square - 6] = '1';
        }
        
        if(piece.square + 10 <= 63 && piece.square % 8 < 6 &&(board.board[piece.square + 10] == '0' || isblackpiece(board.board, piece.square + 10)) && !iswhitepiece(board.board, piece.square + 10)){
            piece.legal_moves[piece.square + 10] = '1';
            board.legal_white_moves[piece.square + 10] = '1';
            board.interpose_help_white[piece.square + 10] = '1';
        }
        
        if(piece.square + 17 <= 63 && piece.square % 8 < 7 &&(board.board[piece.square + 17] == '0' || isblackpiece(board.board, piece.square + 17)) && !iswhitepiece(board.board, piece.square + 17)){
            piece.legal_moves[piece.square + 17] = '1';
            board.legal_white_moves[piece.square + 17] = '1';
        }
        
        if(piece.square + 15 <= 63 && piece.square % 8 > 0 &&(board.board[piece.square + 15] == '0' || isblackpiece(board.board, piece.square + 15)) && !iswhitepiece(board.board, piece.square + 15)){
            piece.legal_moves[piece.square + 15] = '1';
            board.legal_white_moves[piece.square + 15] = '1';
            board.interpose_help_white[piece.square + 15] = '1';
        }
        
        if(piece.square + 6 <= 63 && piece.square % 8 > 1 &&(board.board[piece.square + 6] == '0' || isblackpiece(board.board, piece.square + 6)) && !iswhitepiece(board.board, piece.square + 6)){
            piece.legal_moves[piece.square + 6] = '1';
            board.legal_white_moves[piece.square + 6] = '1';
            board.interpose_help_white[piece.square + 6] = '1';
        }
    }
}

void blackKnightmovement(Board &board){
    for(Knight &piece : board.blackKnight){
        board.fillboard(piece.legal_moves);
        piece.legal_moves[piece.square] = 'N';
        if(piece.square - 10 >= 0 && piece.square % 8 > 1 &&(board.board[piece.square - 10] == '0' || iswhitepiece(board.board, piece.square - 10)) && !isblackpiece(board.board, piece.square - 10)){
            piece.legal_moves[piece.square - 10] = '1';
            board.legal_black_moves[piece.square - 10] = '1';
            board.interpose_help_black[piece.square - 10] = '1';
        }
        
        if(piece.square - 17 >= 0 && piece.square % 8 > 0 &&(board.board[piece.square - 17] == '0' || iswhitepiece(board.board, piece.square - 17)) && !isblackpiece(board.board, piece.square - 17)){
            piece.legal_moves[piece.square - 17] = '1';
            board.legal_black_moves[piece.square - 17] = '1';
            board.interpose_help_black[piece.square - 17] = '1';
        }
        
        if(piece.square - 15 >= 0 && piece.square % 8 < 7 &&(board.board[piece.square - 15] == '0' || iswhitepiece(board.board, piece.square - 15)) && !isblackpiece(board.board, piece.square - 15)){
            piece.legal_moves[piece.square - 15] = '1';
            board.legal_black_moves[piece.square - 15] = '1';
            board.interpose_help_black[piece.square - 15] = '1';
        }
        
        if(piece.square - 6 >= 0 && piece.square % 8 < 6 &&(board.board[piece.square - 6] == '0' || iswhitepiece(board.board, piece.square - 6)) && !isblackpiece(board.board, piece.square - 6)){
            piece.legal_moves[piece.square - 6] = '1';
            board.legal_black_moves[piece.square - 6] = '1';
            board.interpose_help_black[piece.square - 6] = '1';
        }
        
        if(piece.square + 10 <= 63 && piece.square % 8 < 6 &&(board.board[piece.square + 10] == '0' || iswhitepiece(board.board, piece.square + 10)) && !isblackpiece(board.board, piece.square + 10)){
            piece.legal_moves[piece.square + 10] = '1';
            board.legal_black_moves[piece.square + 10] = '1';
            board.interpose_help_black[piece.square + 10] = '1';
        }
        
        if(piece.square + 17 <= 63 && piece.square % 8 < 7 &&(board.board[piece.square + 17] == '0' || iswhitepiece(board.board, piece.square + 17)) && !isblackpiece(board.board, piece.square + 17)){
            piece.legal_moves[piece.square + 17] = '1';
            board.legal_black_moves[piece.square + 17] = '1';
            board.interpose_help_black[piece.square + 17] = '1';
        }
        
        if(piece.square + 15 <= 63 && piece.square % 8 > 0 &&(board.board[piece.square + 15] == '0' || iswhitepiece(board.board, piece.square + 15)) && !isblackpiece(board.board, piece.square + 15)){
            piece.legal_moves[piece.square + 15] = '1';
            board.legal_black_moves[piece.square + 15] = '1';
            board.interpose_help_black[piece.square + 15] = '1';
        }
        if(piece.square + 6 <= 63 && piece.square % 8 > 1 &&(board.board[piece.square + 6] == '0' || iswhitepiece(board.board, piece.square + 6)) && !isblackpiece(board.board, piece.square + 6)){
            piece.legal_moves[piece.square + 6] = '1';
            board.legal_black_moves[piece.square + 6] = '1';
            board.interpose_help_black[piece.square + 6] = '1';
        }  
    }  
}

void Whitepawnmovement(Board &board){
    for(pawn &pawn : board.whitePawns){
        board.fillboard(pawn.legal_moves);
        pawn.legal_moves[pawn.square] = 'P';
        if(pawn.square > 7 && board.board[pawn.square - 8] == '0'){
            pawn.legal_moves[pawn.square - 8] = '1';
            board.interpose_help_white[pawn.square - 8] = '1';
        }
        if((pawn.square / 8) == 6 && pawn.square > 16 && board.board[pawn.square - 8] == '0' && board.board[pawn.square - 16] == '0'){
            pawn.legal_moves[pawn.square - 16] = '1';
            board.interpose_help_white[pawn.square - 16] = '1';
        }
        if(pawn.square > 7 && pawn.square % 8 != 0){
            board.legal_white_moves[pawn.square - 9] = '1';
            if(isblackpiece(board.board, pawn.square - 9)){
                pawn.legal_moves[pawn.square - 9] = '1';
            }
        }
        if(pawn.square > 7 && pawn.square % 8 != 7){
            board.legal_white_moves[pawn.square - 7] = '1';
            if(isblackpiece(board.board, pawn.square - 7)){
                pawn.legal_moves[pawn.square - 7] = '1';
            }
        }
        if(pawn.square / 8 == 3 && pawn.square % 8 != 7 && board.board[pawn.square + 1] == 'p' && board.blackPawns[pawnfinder(board.blackPawns, pawn.square + 1)].en_passent_able){
            pawn.legal_moves[pawn.square - 7] = '1';
            board.legal_white_moves[pawn.square - 7] = '1';
        }
        if(pawn.square / 8 == 3 && pawn.square % 8 != 0 && board.board[pawn.square - 1] == 'p' && board.blackPawns[pawnfinder(board.blackPawns, pawn.square - 1)].en_passent_able){
            pawn.legal_moves[pawn.square - 9] = '1';
            board.legal_white_moves[pawn.square - 9] = '1';
        }
    }
}

void Blackpawnmovement(Board &board){
    for(pawn &pawn : board.blackPawns){
        board.fillboard(pawn.legal_moves);
        pawn.legal_moves[pawn.square] = 'P';
        if(pawn.square < 56 && board.board[pawn.square + 8] == '0'){
            pawn.legal_moves[pawn.square + 8] = '1';
            board.interpose_help_black[pawn.square + 8] = '1';
        }
        if(pawn.square / 8 == 1 && board.board[pawn.square + 8] == '0' && board.board[pawn.square + 16] == '0'){
            pawn.legal_moves[pawn.square + 16] = '1';
            board.interpose_help_black[pawn.square + 16] = '1';
        }
        if(pawn.square < 56 && pawn.square % 8 != 0){
            board.legal_black_moves[pawn.square + 7] = '1';
            if(iswhitepiece(board.board, pawn.square + 7)){
                pawn.legal_moves[pawn.square + 7] = '1';
            }
        }
        if(pawn.square < 56 && pawn.square % 8 != 7){
            board.legal_black_moves[pawn.square + 9] = '1';
            if(iswhitepiece(board.board, pawn.square + 9)){
                pawn.legal_moves[pawn.square + 9] = '1';
            }
        }
        if(pawn.square / 8 == 4 && pawn.square % 8 != 0 && board.board[pawn.square - 1] == 'P' && board.whitePawns[pawnfinder(board.whitePawns, pawn.square - 1)].en_passent_able){
            pawn.legal_moves[pawn.square + 7] = '1';
            board.legal_black_moves[pawn.square + 7] = '1';
        }
        if(pawn.square / 8 == 4 && pawn.square % 8 != 7 && board.board[pawn.square + 1] == 'P' && board.whitePawns[pawnfinder(board.whitePawns, pawn.square + 1)].en_passent_able){
            pawn.legal_moves[pawn.square + 9] = '1';
            board.legal_black_moves[pawn.square + 9] = '1';
        }
    }
}

int pawnfinder(std::vector<pawn> &pawns, int square){
    for(int i = 0; i < pawns.size(); i++){
        if(pawns[i].square == square){
            return i;
        }
    }
    return -1;
}

void legal_moves(Board &board){
    board.fillboard(board.legal_white_moves);
    board.fillboard(board.legal_black_moves);
    board.fillboard(board.interpose_help_black);
    board.fillboard(board.interpose_help_white);
    whiteQueenmovement(board);
    whiteRookmovement(board);
    whiteBishopmovement(board);
    whiteKingmovement(board);
    whiteKnightmovement(board);
    Whitepawnmovement(board);
    blackQueenmovement(board);
    blackRookmovement(board);
    blackBishopmovement(board);
    blackKingmovement(board);
    blackKnightmovement(board);
    Blackpawnmovement(board);

}

void legal_white_moves(Board &board){
    board.fillboard(board.legal_white_moves);
    whiteQueenmovement(board);
    whiteRookmovement(board);
    whiteBishopmovement(board);
    whiteKingmovement(board);
    whiteKnightmovement(board);
    Whitepawnmovement(board);
}

void legal_black_moves(Board &board){
    board.fillboard(board.legal_black_moves);
    blackQueenmovement(board);
    blackRookmovement(board);
    blackBishopmovement(board);
    blackKingmovement(board);
    blackKnightmovement(board);
    Blackpawnmovement(board);
}

void FEN_extra(Board &board, std::string FEN){
    int n = 0; 
    for(int i = 0; i < FEN.length(); i++){
        if (FEN[i] == ' '){
            n = i;
            break;
        }
    }
    for(int i = n; i < FEN.length(); i++){
        if (FEN[i] == 'w'){
            board.turn = true; 
        }
        if(FEN[i] == 'b'){
            board.turn = false;
        }
        if(FEN[i] == 'K' && board.board[63] == 'R'){
            board.whiteKing[0].hasmoved = false;
            board.whiterook[rookfinder(board.whiterook, 63)].hasmoved = false; 
        }
        if(FEN[i] == 'Q' && board.board[56] == 'R'){
            board.whiteKing[0].hasmoved = false;
            board.whiterook[rookfinder(board.whiterook, 56)].hasmoved = false;
        }
        if(FEN[i] == 'k' && board.board[7] == 'r'){
            board.blackKing[0].hasmoved = false;
            board.blackrook[rookfinder(board.blackrook, 7)].hasmoved = false;
        }
        if(FEN[i] == 'q' && board.board[0] == 'r'){
            board.blackKing[0].hasmoved = false;
            board.blackrook[rookfinder(board.blackrook, 0)].hasmoved = false;
        }
        if(i != FEN.length() - 1 && ismove(FEN[i], FEN[i+1])){ 
            if(FEN[i+1] == '3' && board.board[square_to_index(FEN[i], FEN[i+1]) - 8] == 'P'){
                board.legal_black_moves[square_to_index(FEN[i], FEN[i+1])] = '1';
                board.whitePawns[pawnfinder(board.whitePawns, square_to_index(FEN[i], FEN[i+1]) - 8)].en_passent_able = true;
            }
            if(FEN[i+1] == '6' && board.board[square_to_index(FEN[i], FEN[i+1]) + 8] == 'p'){
                board.legal_white_moves[square_to_index(FEN[i], FEN[i+1])] = '1';
                board.blackPawns[pawnfinder(board.blackPawns, square_to_index(FEN[i], FEN[i+1]) + 8)].en_passent_able = true;
            }
        }
    }   
} 

bool ismove(char x, char y){
    if(std::isalpha(x)){
        if(x == 'a' || x == 'b' || x == 'c' || x == 'd' || x == 'e' || x == 'f' || x == 'g' || x == 'h'){
            if(std::isdigit(y)){
                if(y > 47 && y < 57){
                    return true;
                }
            }
        }
    }
    return false;
}

int knightfinder(std::vector<Knight> &knights, int square){
    for(int i = 0; i < knights.size(); i++){
        if(knights[i].square == square){
            return i;
        }
    }
    return -1;
}

int bishopfinder(std::vector<Bishop> &bishops, int square){
    for(int i = 0; i < bishops.size(); i++){
        if(bishops[i].square == square){
            return i;
        }
    }
    return -1;
}

int queenfinder(std::vector<Queen> &queens, int square){
    for(int i = 0; i < queens.size(); i++){
        if(queens[i].square == square){
            return i;
        }
    }
    return -1;
}

int movecounter(Board &board){
    int counter = 0;
    if(board.turn){
        for(pawn piece : board.whitePawns){
            for(int i = 0; i < 64; i++){
                if(piece.legal_destinations[i] == '1'){
                    if(i / 8 == 0){
                        counter += 4;
                }
                else{
                counter++;
                }
            }
        }
    }
    for(Bishop piece : board.whiteBishop){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(Knight piece : board.whiteKnight){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(Rook piece : board.whiterook){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(Queen piece : board.whiteQueen){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(King piece : board.whiteKing){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    return counter;
    }
    else{
        for(pawn piece : board.blackPawns){
            for(int i = 0; i < 64; i++){
                if(piece.legal_destinations[i] == '1'){
                    if(i / 8 == 0){
                        counter += 4;
                }
                else{
                counter++;
                }
            }
        }
    }
    for(Bishop piece : board.blackBishop){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(Knight piece : board.blackKnight){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(Rook piece : board.blackrook){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(Queen piece : board.blackQueen){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    for(King piece : board.blackKing){
        for(int i = 0; i < 64; i++){
            if(piece.legal_destinations[i] == '1'){
                counter++;
            }
        }
    }
    return counter;
    } 

}

bool iswhiteincheck(Board &board){
    if(board.legal_black_moves[board.whiteKing[0].square] == '1'){
        return true;
    }
    return false;
}

bool isblackincheck(Board &board){
    if(board.legal_white_moves[board.blackKing[0].square] == '1'){
        return true;
    }
    return false;
}

int onecounter(std::vector<char> legalboard){
    int counter = 0;
    for(int i = 0; i < 64; i++){
        if(legalboard[i] == '1'){
            counter++;
        }
    }
    return counter;
}

int zerocounter(std::vector<char> legalboard){
    int counter = 0;
    for(int i = 0; i < 64; i++){
        if(legalboard[i] == '0'){
            counter++;
        }
    }
    return counter;
}

bool square_attacked(std::vector<char> &b, int square, bool byWhite){ //Diese Funtion sowie die Check_check Funktionen sind aus Claude. ich hatte zwar selber Funktionen gemacht, jedoch waren diese so brutal ineffizient, dass ich kaum damit arbeiten konnte. Vor diesem update rechnete meine Engine auf ca. 60-70 Stellungen/s. Jetzt rechnet sie mit ca. 1400 Stellungen/s. Dies liegt daran, dass ich zuvor das gesamte Brett mit all seinen Variablen mitkopiert habe und alle Figurenlisten nochmals neu organisiert habe. Nun ist dies jedoch nicht mehr der Fall, da man mithilfe dieser Funktion leicht schauen kann, ob ein Feld in einer Stellung angegriffen ist.
    int f = square % 8;
    int r = square / 8;
    auto on_board = [](int file, int rank){ return file >= 0 && file < 8 && rank >= 0 && rank < 8; };
    auto idx = [](int file, int rank){ return rank * 8 + file; };

    // Pawns: a white pawn sits one rank higher (larger row index, toward rank 1)
    // and attacks diagonally toward rank 8; black pawns attack the opposite way.
    if(byWhite){
        if(on_board(f - 1, r + 1) && b[idx(f - 1, r + 1)] == 'P') return true;
        if(on_board(f + 1, r + 1) && b[idx(f + 1, r + 1)] == 'P') return true;
    }
    else{
        if(on_board(f - 1, r - 1) && b[idx(f - 1, r - 1)] == 'p') return true;
        if(on_board(f + 1, r - 1) && b[idx(f + 1, r - 1)] == 'p') return true;
    }

    // Knights
    static const int kdf[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    static const int kdr[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    char knightchar = byWhite ? 'N' : 'n';
    for(int i = 0; i < 8; i++){
        int nf = f + kdf[i], nr = r + kdr[i];
        if(on_board(nf, nr) && b[idx(nf, nr)] == knightchar) return true;
    }

    // King (needed for completeness/adjacency; also cheap)
    char kingchar = byWhite ? 'K' : 'k';
    for(int df = -1; df <= 1; df++){
        for(int dr = -1; dr <= 1; dr++){
            if(df == 0 && dr == 0) continue;
            int nf = f + df, nr = r + dr;
            if(on_board(nf, nr) && b[idx(nf, nr)] == kingchar) return true;
        }
    }

    // Sliding pieces: rook/queen on ranks & files
    char rookchar = byWhite ? 'R' : 'r';
    char queenchar = byWhite ? 'Q' : 'q';
    char bishopchar = byWhite ? 'B' : 'b';
    static const int orthdf[4] = {1, -1, 0, 0};
    static const int orthdr[4] = {0, 0, 1, -1};
    for(int d = 0; d < 4; d++){
        int nf = f + orthdf[d], nr = r + orthdr[d];
        while(on_board(nf, nr)){
            char c = b[idx(nf, nr)];
            if(c != '0'){
                if(c == rookchar || c == queenchar) return true;
                break;
            }
            nf += orthdf[d]; nr += orthdr[d];
        }
    }

    // Sliding pieces: bishop/queen on diagonals
    static const int diagdf[4] = {1, 1, -1, -1};
    static const int diagdr[4] = {1, -1, 1, -1};
    for(int d = 0; d < 4; d++){
        int nf = f + diagdf[d], nr = r + diagdr[d];
        while(on_board(nf, nr)){
            char c = b[idx(nf, nr)];
            if(c != '0'){
                if(c == bishopchar || c == queenchar) return true;
                break;
            }
            nf += diagdf[d]; nr += diagdr[d];
        }
    }

    return false;
}

bool check_check_white(Board &board, int startingsquare, int targetsquare){
    std::vector<char> &b = board.board;
    char movedPiece = b[startingsquare];
    char capturedPiece = b[targetsquare];

    // Replicate domove's en-passant capture removal (white pawn moving
    // diagonally into an empty square captures the black pawn beside it).
    int epSquare = -1;
    char epPiece = '0';
    if(movedPiece == 'P' && capturedPiece == '0'){
        if(startingsquare - 7 == targetsquare && startingsquare % 8 != 7 && b[startingsquare + 1] == 'p'){
            epSquare = startingsquare + 1;
        }
        else if(startingsquare - 9 == targetsquare && startingsquare % 8 != 0 && b[startingsquare - 1] == 'p'){
            epSquare = startingsquare - 1;
        }
        if(epSquare != -1){
            epPiece = b[epSquare];
            b[epSquare] = '0';
        }
    }

    // Replicate domove's rook shuffle for castling, so a rook that would land
    // next to the king can still block/not-block an attack correctly.
    int rookFrom = -1, rookTo = -1;
    char rookPiece = '0';
    if(movedPiece == 'K'){
        if(startingsquare - targetsquare == 2 && b[56] == 'R'){ rookFrom = 56; rookTo = 59; }
        else if(startingsquare - targetsquare == -2 && b[63] == 'R'){ rookFrom = 63; rookTo = 61; }
        if(rookFrom != -1){
            rookPiece = b[rookFrom];
            b[rookFrom] = '0';
            b[rookTo] = rookPiece;
        }
    }

    b[targetsquare] = movedPiece;
    b[startingsquare] = '0';

    int kingSquare = (movedPiece == 'K') ? targetsquare : board.whiteKing[0].square;
    bool attacked = square_attacked(b, kingSquare, false);

    // Undo, in reverse order.
    b[startingsquare] = movedPiece;
    b[targetsquare] = capturedPiece;
    if(rookFrom != -1){
        b[rookFrom] = rookPiece;
        b[rookTo] = '0';
    }
    if(epSquare != -1){
        b[epSquare] = epPiece;
    }

    return attacked;
}

void domove(Board &board, int startingsquare, int targetsquare, char promotion){
    remember_board(board, startingsquare, targetsquare, promotion);
    bool showboard = false;
    board.previous_move = index_to_square(startingsquare) + index_to_square(targetsquare);
    if(board.board[startingsquare] == 'P'){
        int idx = pawnfinder(board.whitePawns, startingsquare);
        if(idx != -1){
            board.whitePawns[idx].square = targetsquare;
        }
        if(startingsquare - 7 == targetsquare && board.board[targetsquare] == '0' && board.board[startingsquare + 1] == 'p'){
            board.board[startingsquare + 1] = '0';
            idx = pawnfinder(board.blackPawns, startingsquare + 1);
            if(idx != -1){
                board.blackPawns.erase(board.blackPawns.begin() + idx);
            }
        }
        if(startingsquare - 9 == targetsquare && board.board[targetsquare] == '0' && board.board[startingsquare - 1] == 'p'){
            board.board[startingsquare - 1] = '0';
            idx = pawnfinder(board.blackPawns, startingsquare - 1);
            if(idx != -1){
                board.blackPawns.erase(board.blackPawns.begin() + idx);
            }
        }
    }
    for(int i = 0; i < board.blackPawns.size(); i++){
        if(board.blackPawns[i].en_passent_able == true){
            board.blackPawns[i].en_passent_able = false;
        }
    }

    if(board.board[startingsquare] == 'p'){
        int idx2 = pawnfinder(board.blackPawns, startingsquare);
        if(idx2 != -1){
            board.blackPawns[idx2].square = targetsquare;
        }        
        if(startingsquare + 9 == targetsquare && board.board[targetsquare] == '0' && board.board[startingsquare + 1] == 'P'){
            board.board[startingsquare + 1] = '0';
            idx2 = pawnfinder(board.whitePawns, startingsquare + 1);
            if(idx2 != -1){
                board.whitePawns.erase(board.whitePawns.begin() + idx2);
            }
        }
        if(startingsquare + 7 == targetsquare && board.board[targetsquare] == '0' && board.board[startingsquare - 1] == 'P'){
            board.board[startingsquare - 1] = '0';
            idx2 = pawnfinder(board.whitePawns, startingsquare - 1);
            if(idx2 != -1){
                board.whitePawns.erase(board.whitePawns.begin() + idx2);
            }
        } 
    }
    for(int i = 0; i < board.whitePawns.size(); i++){
        if(board.whitePawns[i].en_passent_able == true){
            board.whitePawns[i].en_passent_able = false;
        }
    } 

    int idx3 = -1;
    if(board.board[startingsquare] == 'R' && (idx3 = rookfinder(board.whiterook, startingsquare)) != -1){
        board.whiterook[idx3].hasmoved = true;
        board.whiterook[idx3].square = targetsquare;
    
    }
    if(board.board[startingsquare] == 'r' && (idx3 = rookfinder(board.blackrook, startingsquare)) != -1){
        board.blackrook[idx3].hasmoved = true;
        board.blackrook[idx3].square = targetsquare;
    }
    
    if(board.board[startingsquare] == 'K'){
        board.whiteKing[0].hasmoved = true;
        board.whiteKing[0].square = targetsquare;
        if(startingsquare - targetsquare == 2 && board.board[56] == 'R' && (idx3 = rookfinder(board.whiterook, 56)) != -1){
            board.whiterook[idx3].hasmoved = true;
            board.whiterook[idx3].square = 59;
            board.board[59] = 'R';
            board.board[56] = '0';
        }
        if(startingsquare - targetsquare == -2 && board.board[63] == 'R' && (idx3 = rookfinder(board.whiterook, 63)) != -1){
            board.whiterook[idx3].hasmoved = true;
            board.whiterook[idx3].square = 61;
            board.board[61] = 'R';
            board.board[63] = '0';
        }
    }
    if(board.board[startingsquare] == 'k'){
        board.blackKing[0].hasmoved = true;
        board.blackKing[0].square = targetsquare;
        if(startingsquare - targetsquare == 2 && board.board[0] == 'r' && (idx3 = rookfinder(board.blackrook, 0)) != -1){
            board.blackrook[idx3].hasmoved = true;
            board.blackrook[idx3].square = 3;
            board.board[3] = 'r';
            board.board[0] = '0';
        }
        if(startingsquare - targetsquare == -2 && board.board[7] == 'r' && (idx3 = rookfinder(board.blackrook, 7)) != -1){
            board.blackrook[idx3].hasmoved = true;
            board.blackrook[idx3].square = 5;
            board.board[5] = 'r';
            board.board[7] = '0';
        }
    }
    
    //idx3 von Claude

    if(board.board[startingsquare] == 'Q' && (idx3 = queenfinder(board.whiteQueen, startingsquare)) != -1){
        board.whiteQueen[idx3].square = targetsquare;
    }
    if(board.board[startingsquare] == 'q' && (idx3 = queenfinder(board.blackQueen, startingsquare)) != -1){
        board.blackQueen[idx3].square = targetsquare;
    }

    if(board.board[startingsquare] == 'B' && (idx3 = bishopfinder(board.whiteBishop, startingsquare)) != -1){
        board.whiteBishop[idx3].square = targetsquare;
    }
    if(board.board[startingsquare] == 'b' && (idx3 = bishopfinder(board.blackBishop, startingsquare)) != -1){
        board.blackBishop[idx3].square = targetsquare;
    }

    if(board.board[startingsquare] == 'N' && (idx3 = knightfinder(board.whiteKnight, startingsquare)) != -1){
        board.whiteKnight[idx3].square = targetsquare;

    }
    if(board.board[startingsquare] == 'n' && (idx3 = knightfinder(board.blackKnight, startingsquare)) != -1){
        board.blackKnight[idx3].square = targetsquare;
    }

    if(board.board[targetsquare] == 'P' && (idx3 = pawnfinder(board.whitePawns, targetsquare)) != -1){
        board.whitePawns.erase(board.whitePawns.begin() + idx3);
    }
    if(board.board[targetsquare] == 'p' && (idx3 = pawnfinder(board.blackPawns, targetsquare)) != -1){
        board.blackPawns.erase(board.blackPawns.begin() + idx3);
    }
    if(board.board[targetsquare] == 'N' && (idx3 = knightfinder(board.whiteKnight, targetsquare)) != -1){
        board.whiteKnight.erase(board.whiteKnight.begin() + idx3);
    }
    if(board.board[targetsquare] == 'n' && (idx3 = knightfinder(board.blackKnight, targetsquare)) != -1){
        board.blackKnight.erase(board.blackKnight.begin() + idx3);
    }
    if(board.board[targetsquare] == 'B' && (idx3 = bishopfinder(board.whiteBishop, targetsquare)) != -1){
        board.whiteBishop.erase(board.whiteBishop.begin() + idx3);
    }
    if(board.board[targetsquare] == 'b' && (idx3 = bishopfinder(board.blackBishop, targetsquare)) != -1){
        board.blackBishop.erase(board.blackBishop.begin() + idx3);
    }
    if(board.board[targetsquare] == 'R' && (idx3 = rookfinder(board.whiterook, targetsquare)) != -1){
        board.whiterook.erase(board.whiterook.begin() + idx3);
    }
    if(board.board[targetsquare] == 'r' && (idx3 = rookfinder(board.blackrook, targetsquare)) != -1){
        board.blackrook.erase(board.blackrook.begin() + idx3);
    }
    if(board.board[targetsquare] == 'Q' && (idx3 = queenfinder(board.whiteQueen, targetsquare)) != -1){
        board.whiteQueen.erase(board.whiteQueen.begin() + idx3);
    }
    if(board.board[targetsquare] == 'q' && (idx3 = queenfinder(board.blackQueen, targetsquare)) != -1){
        board.blackQueen.erase(board.blackQueen.begin() + idx3);
    }

    board.board[targetsquare] = board.board[startingsquare];
    board.board[startingsquare] = '0';  
    

    idx3 = pawnfinder(board.whitePawns, targetsquare);
    if(idx3 != -1 && board.board[targetsquare] == 'P' && startingsquare - targetsquare == 16 && ((board.board[targetsquare + 1] == 'p' && targetsquare % 8 != 7  && !check_check_black(board, targetsquare + 1, targetsquare + 8)) || (board.board[targetsquare - 1] == 'p' && targetsquare % 8 != 0 && !check_check_black(board, targetsquare - 1, targetsquare + 8)))){
        board.whitePawns[idx3].en_passent_able = true;
    }

    idx3 = pawnfinder(board.blackPawns, targetsquare);
    if(idx3 != -1 && board.board[targetsquare] == 'p' && startingsquare - targetsquare == -16 && ((board.board[targetsquare + 1] == 'P' && targetsquare % 8 != 7 && !check_check_white(board, targetsquare + 1, targetsquare - 8)) || (board.board[targetsquare - 1] == 'P' && targetsquare % 8 != 0 && !check_check_white(board, targetsquare - 1, targetsquare - 8)))){
        board.blackPawns[idx3].en_passent_able = true;
    }
    
    if(board.board[targetsquare] == 'P' && targetsquare / 8 == 0){
        board.board[targetsquare] = promotion;
        switch(promotion){
            case 'Q':{ //debugging: https://chatgpt.com/share/6a93f34d-f3cc-83eb-8946-ecaba49bd983
            Queen queen;
            queen.square = targetsquare;
            queen.color = true;
            board.whiteQueen.push_back(queen);
            break;
            }
            case 'R':{
            Rook rook;
            rook.square = targetsquare;
            rook.color = true;
            board.whiterook.push_back(rook);
            break;
            }
            case 'B':{
            Bishop bishop;
            bishop.square = targetsquare;
            bishop.color = true;
            board.whiteBishop.push_back(bishop);
            break;
            }
            case 'N':{
            Knight knight;
            knight.square = targetsquare;
            knight.color = true;
            board.whiteKnight.push_back(knight);
            break;
            }
        }
        board.whitePawns.erase(board.whitePawns.begin() + pawnfinder(board.whitePawns, targetsquare));
    }
    if(board.board[targetsquare] == 'p' && targetsquare / 8 == 7){
        board.board[targetsquare] = promotion;
        switch(promotion){
            case 'q':{ 
            Queen queen;
            queen.square = targetsquare;
            queen.color = false;
            board.blackQueen.push_back(queen);
            break;
            }
            case 'r':{
            Rook rook;
            rook.square = targetsquare;
            rook.color = false;
            board.blackrook.push_back(rook);
            break;
            }
            case 'b':{
            Bishop bishop;
            bishop.square = targetsquare;
            bishop.color = false;
            board.blackBishop.push_back(bishop);
            break;
            }
            case 'n':{
            Knight knight;
            knight.square = targetsquare;
            knight.color = false;
            board.blackKnight.push_back(knight);
            break;
            }
        }
        board.blackPawns.erase(board.blackPawns.begin() + pawnfinder(board.blackPawns, targetsquare));
    }

    if(board.turn){
        board.turn = false;
    }
    else{
        board.turn = true;
    }
}

bool check_check_black(Board &board, int startingsquare, int targetsquare){
    std::vector<char> &b = board.board;
    char movedPiece = b[startingsquare];
    char capturedPiece = b[targetsquare];

    // Replicate domove's en-passant capture removal (black pawn moving
    // diagonally into an empty square captures the white pawn beside it).
    int epSquare = -1;
    char epPiece = '0';
    if(movedPiece == 'p' && capturedPiece == '0'){
        if(startingsquare + 9 == targetsquare && startingsquare % 8 != 7 && b[startingsquare + 1] == 'P'){
            epSquare = startingsquare + 1;
        }
        else if(startingsquare + 7 == targetsquare && startingsquare % 8 != 0 && b[startingsquare - 1] == 'P'){
            epSquare = startingsquare - 1;
        }
        if(epSquare != -1){
            epPiece = b[epSquare];
            b[epSquare] = '0';
        }
    }

    // Replicate domove's rook shuffle for castling.
    int rookFrom = -1, rookTo = -1;
    char rookPiece = '0';
    if(movedPiece == 'k'){
        if(startingsquare - targetsquare == 2 && b[0] == 'r'){ rookFrom = 0; rookTo = 3; }
        else if(startingsquare - targetsquare == -2 && b[7] == 'r'){ rookFrom = 7; rookTo = 5; }
        if(rookFrom != -1){
            rookPiece = b[rookFrom];
            b[rookFrom] = '0';
            b[rookTo] = rookPiece;
        }
    }

    b[targetsquare] = movedPiece;
    b[startingsquare] = '0';

    int kingSquare = (movedPiece == 'k') ? targetsquare : board.blackKing[0].square;
    bool attacked = square_attacked(b, kingSquare, true);

    // Undo, in reverse order.
    b[startingsquare] = movedPiece;
    b[targetsquare] = capturedPiece;
    if(rookFrom != -1){
        b[rookFrom] = rookPiece;
        b[rookTo] = '0';
    }
    if(epSquare != -1){
        b[epSquare] = epPiece;
    }

    return attacked;
}

void actual_legal_moves(Board &board){
    for(pawn &pawn : board.whitePawns){
        board.fillboard(pawn.legal_destinations);
        pawn.legal_destinations[pawn.square] = 'P';
        for(int i = 0; i < 64; i++){
            if(pawn.legal_moves[i] == '1'){
                if(!check_check_white(board, pawn.square, i)){
                    pawn.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(pawn &pawn : board.blackPawns){
        board.fillboard(pawn.legal_destinations);
        pawn.legal_destinations[pawn.square] = 'p';
        for(int i = 0; i < 64; i++){
            if(pawn.legal_moves[i] == '1'){
                if(!check_check_black(board, pawn.square, i)){
                    pawn.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Knight &knight : board.whiteKnight){
        board.fillboard(knight.legal_destinations);
        knight.legal_destinations[knight.square] = 'N';
        for(int i = 0; i < 64; i++){
            if(knight.legal_moves[i] == '1'){
                if(!check_check_white(board, knight.square, i)){
                    knight.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Knight &knight : board.blackKnight){
        board.fillboard(knight.legal_destinations);
        knight.legal_destinations[knight.square] = 'n';
        for(int i = 0; i < 64; i++){
            if(knight.legal_moves[i] == '1'){
                if(!check_check_black(board, knight.square, i)){
                    knight.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Bishop &bishop : board.whiteBishop){
        board.fillboard(bishop.legal_destinations);
        bishop.legal_destinations[bishop.square] = 'B';
        for(int i = 0; i < 64; i++){
            if(bishop.legal_moves[i] == '1'){
                if(!check_check_white(board, bishop.square, i)){
                    bishop.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Bishop &bishop : board.blackBishop){
        board.fillboard(bishop.legal_destinations);
        bishop.legal_destinations[bishop.square] = 'b';
        for(int i = 0; i < 64; i++){
            if(bishop.legal_moves[i] == '1'){
                if(!check_check_black(board, bishop.square, i)){
                    bishop.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Rook &rook : board.whiterook){
        board.fillboard(rook.legal_destinations);
        rook.legal_destinations[rook.square] = 'R';
        for(int i = 0; i < 64; i++){
            if(rook.legal_moves[i] == '1'){
                if(!check_check_white(board, rook.square, i)){
                    rook.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Rook &rook : board.blackrook){
        board.fillboard(rook.legal_destinations);
        rook.legal_destinations[rook.square] = 'r';
        for(int i = 0; i < 64; i++){
            if(rook.legal_moves[i] == '1'){
                if(!check_check_black(board, rook.square, i)){
                    rook.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Queen &queen : board.whiteQueen){
        board.fillboard(queen.legal_destinations);
        queen.legal_destinations[queen.square] = 'Q';
        for(int i = 0; i < 64; i++){
            if(queen.legal_moves[i] == '1'){
                if(!check_check_white(board, queen.square, i)){
                    queen.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(Queen &queen : board.blackQueen){
        board.fillboard(queen.legal_destinations);
        queen.legal_destinations[queen.square] = 'q';
        for(int i = 0; i < 64; i++){
            if(queen.legal_moves[i] == '1'){
                if(!check_check_black(board, queen.square, i)){
                    queen.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(King &king : board.whiteKing){
        board.fillboard(king.legal_destinations);
        king.legal_destinations[king.square] = 'K';
        for(int i = 0; i < 64; i++){
            if(king.legal_moves[i] == '1'){
                if(!check_check_white(board, king.square, i) && !(king.square == 60 && ((i == 62 && (iswhiteincheck(board) || board.legal_black_moves[61] == '1')) || (i == 58 && (iswhiteincheck(board) || board.legal_black_moves[59] == '1'))))){
                    king.legal_destinations[i] = '1';
                }
            }
        }
    }
    for(King &king : board.blackKing){
        board.fillboard(king.legal_destinations);
        king.legal_destinations[king.square] = 'k';
        for(int i = 0; i < 64; i++){
            if(king.legal_moves[i] == '1'){
                if(!check_check_black(board, king.square, i) && !(king.square == 4 && ((i == 2 && (isblackincheck(board) || board.legal_white_moves[3] == '1')) || (i == 6 && (isblackincheck(board) || board.legal_white_moves[5] == '1'))))){
                    king.legal_destinations[i] = '1';
                }
            }
        }
    }
}

std::string position_to_FEN(Board &board){
    std::string FEN;
    char zerocounter = 48;
    int Kingcounter = 0;
    for(int i = 0; i < 64; i++){
        if(board.board[i] == '0'){
            zerocounter++;
        }
        if(board.board[i] != '0' || i % 8 == 7){
            if(zerocounter != '0'){
                FEN += zerocounter;
                zerocounter = 48;
            }
            if(board.board[i] != '0'){
            FEN += board.board[i];
            }
        }
        if(i % 8 == 7 && i != 63){
            FEN += "/";
        }
    }
    if(board.turn){
        FEN += " w ";
    }
    else{
        FEN += " b ";
    }
    if(rookfinder(board.whiterook, 63) != -1 && board.whiteKing[0].square == 60 && board.whiteKing[0].hasmoved == false && board.whiterook[rookfinder(board.whiterook, 63)].hasmoved == false){
        FEN += "K";
        Kingcounter++;
    }
    if(rookfinder(board.whiterook, 56) != -1 && board.whiteKing[0].square == 60 && board.whiteKing[0].hasmoved == false && board.whiterook[rookfinder(board.whiterook, 56)].hasmoved == false){
        FEN += "Q";
        Kingcounter++;
    }
    if(rookfinder(board.blackrook, 7) != -1 && board.blackKing[0].square == 4 && board.blackKing[0].hasmoved == false && board.blackrook[rookfinder(board.blackrook, 7)].hasmoved == false){
        FEN += "k";
        Kingcounter++;
    }
    if(rookfinder(board.blackrook, 0) != -1 && board.blackKing[0].square == 4 && board.blackKing[0].hasmoved == false && board.blackrook[rookfinder(board.blackrook, 0)].hasmoved == false){
        FEN += "q";
        Kingcounter++;
    }
    if(Kingcounter == 0){
        FEN += "-";
    }
    for(pawn Pawn : board.whitePawns){
        if(Pawn.en_passent_able){
            FEN += " ";
            FEN += index_to_square(Pawn.square + 8);
        }
    }
    for(pawn Pawn : board.blackPawns){
        if(Pawn.en_passent_able){
            FEN += " ";
            FEN += index_to_square(Pawn.square - 8);
        }
    }
    return FEN;
}

void white_expansion(Board &board){
    int temp = 0;
    board.legal_starting_squares.clear();
    board.legal_target_squares.clear();
    int counter = 0;
    for(Queen queen : board.whiteQueen){
        for(int i = 0; i < 64; i++){
            if(queen.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(queen.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(Rook rook : board.whiterook){
        for(int i = 0; i < 64; i++){
            if(rook.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(rook.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
        for(Bishop bishop : board.whiteBishop){
        for(int i = 0; i < 64; i++){
            if(bishop.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(bishop.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(Knight knight : board.whiteKnight){
        for(int i = 0; i < 64; i++){
            if(knight.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(knight.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(pawn Pawn : board.whitePawns){
        for(int i = 0; i < 64; i++){
            if(Pawn.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(Pawn.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(King king : board.whiteKing){
        for(int i = 0; i < 64; i++){
            if(king.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(king.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if((check_check_black(board, board.legal_starting_squares[i], board.legal_target_squares[i]))){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(isblackpiece(board.board, board.legal_target_squares[i]) && difference(board, board.legal_starting_squares[i], board.legal_target_squares[i]) < 0){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(isblackpiece(board.board, board.legal_target_squares[i]) && difference(board, board.legal_starting_squares[i], board.legal_target_squares[i]) == 0){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(isblackpiece(board.board, board.legal_target_squares[i]) && difference(board, board.legal_starting_squares[i], board.legal_target_squares[i]) > 0){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(board.move == index_to_square(board.legal_starting_squares[i]) + index_to_square(board.legal_target_squares[i])){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
}

void black_expansion(Board &board){
    int temp = 0;
    board.legal_starting_squares.clear();
    board.legal_target_squares.clear();
    std::string FEN = "";
    int counter = 0;
    for(Queen queen : board.blackQueen){
        for(int i = 0; i < 64; i++){
            if(queen.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(queen.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(Rook rook : board.blackrook){
        for(int i = 0; i < 64; i++){
            if(rook.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(rook.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(Knight knight : board.blackKnight){
        for(int i = 0; i < 64; i++){
            if(knight.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(knight.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(pawn Pawn : board.blackPawns){
        for(int i = 0; i < 64; i++){
            if(Pawn.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(Pawn.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(Bishop bishop : board.blackBishop){
        for(int i = 0; i < 64; i++){
            if(bishop.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(bishop.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    for(King king : board.blackKing){
        for(int i = 0; i < 64; i++){
            if(king.legal_destinations[i] == '1'){
                board.legal_starting_squares.push_back(king.square);
                board.legal_target_squares.push_back(i);
            }
        }
    }
    
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if((check_check_white(board, board.legal_starting_squares[i], board.legal_target_squares[i]))){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(iswhitepiece(board.board, board.legal_target_squares[i]) && difference(board, board.legal_starting_squares[i], board.legal_target_squares[i]) < 0){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(iswhitepiece(board.board, board.legal_target_squares[i]) && difference(board, board.legal_starting_squares[i], board.legal_target_squares[i]) == 0){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(iswhitepiece(board.board, board.legal_target_squares[i]) && difference(board, board.legal_starting_squares[i], board.legal_target_squares[i]) > 0){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
    for(int i = 0; i < board.legal_starting_squares.size(); i++){
        if(board.move == index_to_square(board.legal_starting_squares[i]) + index_to_square(board.legal_target_squares[i])){
            temp = board.legal_starting_squares[i];
            board.legal_starting_squares.erase(board.legal_starting_squares.begin() + i);
            board.legal_starting_squares.insert(board.legal_starting_squares.begin(), temp);
            temp = board.legal_target_squares[i];
            board.legal_target_squares.erase(board.legal_target_squares.begin() + i);
            board.legal_target_squares.insert(board.legal_target_squares.begin(), temp);
        }
    }
}

int positionfinder(std::vector<std::string> positions, std::string wanted_position){
    for(int i = 0; i < positions.size(); i++){
        if(positions[i] == wanted_position){
            return i;
        }
    }
    return -1;
}

double Tree(Board &board, int depth, int &positions, const int &constant_depth, double alpha, double beta){ //Die Grundidee ist aus Claude, da ich komplett verzweifelt war

    double maxEval;
    double minEval;

    if(depth <= 0 && (((board.Previous_moves.size() > 0 && !board.Previous_moves.back().is_forcing) || depth <= -4) && ((board.Previous_moves.size() > 1  && !board.Previous_moves[board.Previous_moves.size() - 2].was_check)))){
        positions++;
        return evaluation(board);
    }
    int temppositions = positions;

    legal_moves(board);
    actual_legal_moves(board);

    if(board.turn){
        white_expansion(board); 
        maxEval = -10000;       
    } 
    else{
        black_expansion(board); 
        minEval = 10000;        
    }

    // copy the move lists locally — board.legal_starting_squares/target_squares
    // will get overwritten by the recursive call otherwise
    std::vector<int> starts = board.legal_starting_squares;
    std::vector<int> targets = board.legal_target_squares;

    if(starts.size() == 0){ //Das fehlen dieser Linie war eine enorme Fehlerquelle
        

        if(iswhiteincheck(board)){
            if(depth < 0){
                return -999.99;
            }
            return -1000;
        }
        else if(isblackincheck(board)){
            if(depth < 0){
                return 999.99;
            }
            return 1000;
        }
        return 0;
    }

    for(size_t i = 0; i < starts.size(); i++){
        if(depth == constant_depth){ //Für debugging. ich habe es auf -1 gesetzt, damit ich es schnell wieder aktivieren kann. Als Erinnerung: oben = Tiefe, unten = Tiefe - 1
            board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]);
            board.previous_moves.push_back(board.previous_move);
            std::cout << board.previous_move << '\n';
        }
        if(board.turn && targets[i] / 8 == 0 && board.board[starts[i]] == 'P'){
            if(depth == constant_depth){
                if(board.previous_moves.size() != 0){
                    board.previous_moves.pop_back();
                }
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'B';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'N';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'R';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'Q';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
            }
            domove(board, starts[i], targets[i], 'B');
            double tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.breaker){
                break;
            }
            if(board.turn){
                if(depth == constant_depth){
                    board.tempmax.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval > maxEval){
                    maxEval = tempeval;
                }
                if(maxEval > alpha){
                    alpha = maxEval;
                }
            }
            if(beta <= alpha){
                break;
            }
            domove(board, starts[i], targets[i], 'N');
            tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.breaker){
                break;
            }
            if(board.turn){
                if(depth == constant_depth){
                    board.tempmax.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval > maxEval){
                    maxEval = tempeval;
                }
                if(maxEval > alpha){
                    alpha = maxEval;
                }
            }

            if(beta <= alpha){
                break;
            }
            domove(board, starts[i], targets[i], 'R');
            tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.breaker){
                break;
            }
            if(board.turn){
                if(depth == constant_depth){
                    board.tempmax.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval > maxEval){
                    maxEval = tempeval;
                }
                if(maxEval > alpha){
                    alpha = maxEval;
                }
            }

            if(beta <= alpha){
                break;
            }
            domove(board, starts[i], targets[i], 'Q');
            tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.turn){
                if(depth == constant_depth){
                    board.tempmax.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval > maxEval){
                    maxEval = tempeval;
                }
                if(maxEval > alpha){
                    alpha = maxEval;
                }
            }

            if(beta <= alpha){
                break;
            }
        }
        
        else if(!board.turn && targets[i] / 8 == 7 && board.board[starts[i]] == 'p'){
            if(depth == constant_depth){
                if(board.previous_moves.size() != 0){
                    board.previous_moves.pop_back();
                }
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'b';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'b';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'r';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
                board.previous_move = index_to_square(starts[i]) + index_to_square(targets[i]) + 'q';
                board.previous_moves.push_back(board.previous_move);
                std::cout << board.previous_move << '\n';
            }
            domove(board, starts[i], targets[i], 'b');
            double tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.breaker){
                break;
            }
            
            if(!board.turn){
                if(depth == constant_depth){
                    board.tempmin.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval < minEval){
                    minEval = tempeval;
                }
                if(minEval < beta){
                    beta = minEval;
                }
            }
            if(beta <= alpha){
                break;
            }
            domove(board, starts[i], targets[i], 'n');
            tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.breaker){
                break;
            }
            
            if(!board.turn){
                if(depth == constant_depth){
                    board.tempmin.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval < minEval){
                    minEval = tempeval;
                }
                if(minEval < beta){
                    beta = minEval;
                }
            }
            if(beta <= alpha){
                break;
            }
            domove(board, starts[i], targets[i], 'r');
            tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            if(board.breaker){
                break;
            }
            
            if(!board.turn){
                if(depth == constant_depth){
                    board.tempmin.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval < minEval){
                    minEval = tempeval;
                }
                if(minEval < beta){
                    beta = minEval;
                }
            }
            if(beta <= alpha){
                break;
            }
            domove(board, starts[i], targets[i], 'q');
            tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);
            
            if(!board.turn){
                if(depth == constant_depth){
                    board.tempmin.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval < minEval){
                    minEval = tempeval;
                }
                if(minEval < beta){
                    beta = minEval;
                }
            }
            if(beta <= alpha){
                break;
            }
        }
        
        else{
            domove(board, starts[i], targets[i], '0');
            double tempeval = Tree(board, depth - 1, positions, constant_depth, alpha, beta);
            undomove(board);

            if(board.turn){
                if(depth == constant_depth){
                    board.tempmax.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval > maxEval){
                    maxEval = tempeval;
                }
                if(maxEval > alpha){
                    alpha = maxEval;
                }
            }
            if(!board.turn){
                if(depth == constant_depth){
                    board.tempmin.push_back(tempeval);
                    board.candidates.push_back(board.previous_moves.back());
                }
                if(tempeval < minEval){
                    minEval = tempeval;
                }
                if(minEval < beta){
                    beta = minEval;
                }
            }
            if(beta <= alpha){
                break;
            }
        }
    }

    if(depth == constant_depth){
        if(board.turn){
            for(int i = 0; i < board.candidates.size(); i++){
                if(board.tempmax[i] == *std::max_element(board.tempmax.begin(), board.tempmax.end())){
                    board.move = board.candidates[i];
                    std::cout << board.tempmax[i] << '\n';
                    std::cout << "AAAA" << '\n';
                    board.candidates.clear();
                    board.tempmax.clear();
                }
            }
        }
        if(!board.turn){
            for(int i = 0; i < board.candidates.size(); i++){
                if(board.tempmin[i] == *std::min_element(board.tempmin.begin(), board.tempmin.end())){
                    board.move = board.candidates[i];
                    std::cout << board.tempmin[i] << '\n';
                    std::cout << "AAAA" << '\n';
                    board.candidates.clear();
                    board.tempmin.clear();
                    break;
                }
            }
        }
    }

    if(board.previous_boards.size() != 0){
        board.previous_boards.pop_back();
    }
    if(board.turn){
        return maxEval;
    }
    if(!board.turn){
        return minEval;
    }
    
    return 0;
}

void remember_board(Board &board, int startingsquare, int targetsquare, char promotion){
    Previous_move previous_move;

    if((board.turn  && (isblackpiece(board.board, targetsquare) || check_check_black(board, startingsquare, targetsquare) || (board.board[startingsquare] == 'P' && targetsquare / 8 == 7))) || (!board.turn && (iswhitepiece(board.board, targetsquare) || check_check_white(board, startingsquare, targetsquare) || (board.board[startingsquare] == 'p' && targetsquare / 8 == 0)))){
        previous_move.is_forcing = true;
    }
    else{
        previous_move.is_forcing = false;
    }
    if(board.turn && check_check_black(board, startingsquare, targetsquare)){
        previous_move.was_check = true;
    }
    else if(!board.turn && check_check_white(board, startingsquare, targetsquare)){
        previous_move.was_check = true;
    }
    if(board.Previous_moves.size() > 0 && board.Previous_moves.back().was_check){
        previous_move.is_forcing = true;
    }
    if(board.board[targetsquare] != '0'){
        previous_move.difference = difference(board, startingsquare, targetsquare);
    }
    else{
        previous_move.difference = -0.01;
    }

    previous_move.current_square = targetsquare;
    previous_move.initial_square = startingsquare;
    if(startingsquare != -1){
    previous_move.currentsquare = board.board[targetsquare];
    previous_move.initialsquare = board.board[startingsquare];
    if((board.board[startingsquare] == 'P' || board.board[startingsquare] == 'p') && board.board[targetsquare] == '0' && (startingsquare - targetsquare) % 8 != 0 && (abs(startingsquare - targetsquare) == 9 || abs(startingsquare - targetsquare) == 7)){
        previous_move.was_en_passent = true;
    }
    else{
        previous_move.was_en_passent = false;
    }
    if(((board.board[startingsquare] == 'P' && targetsquare / 8 == 0) || (board.board[startingsquare] == 'p' && targetsquare / 8 == 7))){
        previous_move.was_promotion = true;
        previous_move.previous_promotion = promotion;
    }
    else{
        previous_move.was_promotion = false;
    }
    }
    if(!board.whiteKing[0].hasmoved && (rookfinder(board.whiterook, 56) != -1 && !board.whiterook[rookfinder(board.whiterook, 56)].hasmoved)){
        previous_move.white_queenside = true;
    }
    if(!board.whiteKing[0].hasmoved && (rookfinder(board.whiterook, 63) != -1 && !board.whiterook[rookfinder(board.whiterook, 63)].hasmoved)){
        previous_move.white_kingside = true;
    }
    if(!board.blackKing[0].hasmoved && (rookfinder(board.blackrook, 0) != -1 && !board.blackrook[rookfinder(board.blackrook, 0)].hasmoved)){
        previous_move.black_queenside = true;
    }
    if(!board.blackKing[0].hasmoved && (rookfinder(board.blackrook, 7) != -1 && !board.blackrook[rookfinder(board.blackrook, 7)].hasmoved)){
        previous_move.black_kingside = true;
    }
    for(pawn &Pawn : board.whitePawns){
        if(Pawn.en_passent_able && Pawn.square / 8 == 4){
            previous_move.en_passent_able_square = Pawn.square;
        }
    }
    for(pawn &Pawn : board.blackPawns){
        if(Pawn.en_passent_able && Pawn.square / 8 == 3){
            previous_move.en_passent_able_square = Pawn.square;
        }
    }
    board.Previous_moves.push_back(previous_move);
}

void undomove(Board &board){
    if(board.Previous_moves.size() != 0){
        if(board.Previous_moves.back().initial_square != -1){
            board.board[board.Previous_moves.back().initial_square] = board.Previous_moves.back().initialsquare;
            board.board[board.Previous_moves.back().current_square] = board.Previous_moves.back().currentsquare;
            if(board.Previous_moves.back().currentsquare == 'p'){
                pawn pawn;
                pawn.square = board.Previous_moves.back().current_square;
                board.blackPawns.push_back(pawn);
            }
            if(board.Previous_moves.back().currentsquare == 'P'){
                pawn pawn;
                pawn.square = board.Previous_moves.back().current_square;
                board.whitePawns.push_back(pawn);
            }
            if(board.Previous_moves.back().currentsquare == 'n'){
                Knight knight;
                knight.square = board.Previous_moves.back().current_square;
                board.blackKnight.push_back(knight);
            }
            if(board.Previous_moves.back().currentsquare == 'N'){
                Knight knight;
                knight.square = board.Previous_moves.back().current_square;
                board.whiteKnight.push_back(knight);
            }
            if(board.Previous_moves.back().currentsquare == 'b'){
                Bishop bishop;
                bishop.square = board.Previous_moves.back().current_square;
                board.blackBishop.push_back(bishop);
            }
            if(board.Previous_moves.back().currentsquare == 'B'){
                Bishop bishop;
                bishop.square = board.Previous_moves.back().current_square;
                board.whiteBishop.push_back(bishop);
            }
            if(board.Previous_moves.back().currentsquare == 'r'){
                Rook rook;
                rook.square = board.Previous_moves.back().current_square;
                board.blackrook.push_back(rook);
            }
            if(board.Previous_moves.back().currentsquare == 'R'){
                Rook rook;
                rook.square = board.Previous_moves.back().current_square;
                board.whiterook.push_back(rook);
            }
            if(board.Previous_moves.back().currentsquare == 'q'){
                Queen queen;
                queen.square = board.Previous_moves.back().current_square;
                board.blackQueen.push_back(queen);
            }
            if(board.Previous_moves.back().currentsquare == 'Q'){
                Queen queen;
                queen.square = board.Previous_moves.back().current_square;
                board.whiteQueen.push_back(queen);
            }

            if(board.Previous_moves.back().initialsquare == 'p' && pawnfinder(board.blackPawns, board.Previous_moves.back().current_square) != -1){
                board.blackPawns[pawnfinder(board.blackPawns, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'P' && pawnfinder(board.whitePawns, board.Previous_moves.back().current_square) != -1){
                board.whitePawns[pawnfinder(board.whitePawns, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'n' && knightfinder(board.blackKnight, board.Previous_moves.back().current_square) != -1){
                board.blackKnight[knightfinder(board.blackKnight, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'N' && knightfinder(board.whiteKnight, board.Previous_moves.back().current_square) != -1){
                board.whiteKnight[knightfinder(board.whiteKnight, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'b' && bishopfinder(board.blackBishop, board.Previous_moves.back().current_square) != -1){
                board.blackBishop[bishopfinder(board.blackBishop, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'B' && bishopfinder(board.whiteBishop, board.Previous_moves.back().current_square) != -1){
                board.whiteBishop[bishopfinder(board.whiteBishop, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'r' && rookfinder(board.blackrook, board.Previous_moves.back().current_square) != -1){
                board.blackrook[rookfinder(board.blackrook, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'R' && rookfinder(board.whiterook, board.Previous_moves.back().current_square) != -1){
                board.whiterook[rookfinder(board.whiterook, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'q' && queenfinder(board.blackQueen, board.Previous_moves.back().current_square) != -1){
                board.blackQueen[queenfinder(board.blackQueen, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'Q' && queenfinder(board.whiteQueen, board.Previous_moves.back().current_square) != -1){
                board.whiteQueen[queenfinder(board.whiteQueen, board.Previous_moves.back().current_square)].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'k'){
                board.blackKing[0].square = board.Previous_moves.back().initial_square;
            }
            if(board.Previous_moves.back().initialsquare == 'K'){
                board.whiteKing[0].square = board.Previous_moves.back().initial_square;
            }    

            if(rookfinder(board.whiterook, 59) != -1 && board.Previous_moves.back().initialsquare == 'K' && board.Previous_moves.back().initial_square - board.Previous_moves.back().current_square == 2){
                board.board[59] = '0';
                board.board[56] = 'R';
                board.whiterook[rookfinder(board.whiterook, 59)].square = 56;
            }
            if(rookfinder(board.whiterook, 61)!= -1 && board.Previous_moves.back().initialsquare == 'K' && board.Previous_moves.back().initial_square - board.Previous_moves.back().current_square == -2){
                board.board[61] = '0';
                board.board[63] = 'R';
                board.whiterook[rookfinder(board.whiterook, 61)].square = 63;
            }
            if(rookfinder(board.blackrook, 3) != -1 && board.Previous_moves.back().initialsquare == 'k' && board.Previous_moves.back().initial_square - board.Previous_moves.back().current_square == 2){
                board.board[3] = '0';
                board.board[0] = 'r';
                board.blackrook[rookfinder(board.blackrook, 3)].square = 0;
            }
            if(rookfinder(board.blackrook, 5) != -1 && board.Previous_moves.back().initialsquare == 'k' && board.Previous_moves.back().initial_square - board.Previous_moves.back().current_square == -2){
                board.board[5] = '0';
                board.board[7] = 'r';
                board.blackrook[rookfinder(board.blackrook, 5)].square = 7;
            }
            for(pawn &Pawn : board.whitePawns){
                Pawn.en_passent_able = false;
            }
            for(pawn &Pawn : board.blackPawns){
                Pawn.en_passent_able = false;
            }
            if(board.Previous_moves.back().was_en_passent){
                if(!board.turn){
                    pawn pawn;
                    pawn.square = board.Previous_moves.back().initial_square - (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8);
                    board.blackPawns.push_back(pawn);
                    board.board[board.Previous_moves.back().initial_square - (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8)] = 'p';
                    if(pawnfinder(board.blackPawns, board.Previous_moves.back().initial_square - (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8)) != -1){
                        board.blackPawns[pawnfinder(board.blackPawns, board.Previous_moves.back().initial_square - (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8))].en_passent_able = true;
                    }
                }
                if(board.turn){
                    pawn pawn;
                    pawn.square = board.Previous_moves.back().initial_square + (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8);
                    board.whitePawns.push_back(pawn);
                    board.board[board.Previous_moves.back().initial_square + (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8)] = 'P';
                    if(pawnfinder(board.whitePawns, board.Previous_moves.back().initial_square + (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8)) != -1){
                        board.whitePawns[pawnfinder(board.whitePawns, board.Previous_moves.back().initial_square + (abs(board.Previous_moves.back().current_square - board.Previous_moves.back().initial_square) - 8))].en_passent_able = true;
                    }
                }
            }
            
            if(board.turn){
            board.turn = false;
            }
            else{
                board.turn = true;
            }
        }
        if(board.Previous_moves.back().was_promotion){
            switch(board.Previous_moves.back().previous_promotion){
                case 'Q':
                board.whiteQueen.erase(board.whiteQueen.begin() + queenfinder(board.whiteQueen, board.Previous_moves.back().current_square));
                break;
                case 'q':
                board.blackQueen.erase(board.blackQueen.begin() + queenfinder(board.blackQueen, board.Previous_moves.back().current_square));
                break;
                case 'R':
                board.whiterook.erase(board.whiterook.begin() + rookfinder(board.whiterook, board.Previous_moves.back().current_square));
                break;
                case 'r':
                board.blackrook.erase(board.blackrook.begin() + rookfinder(board.blackrook, board.Previous_moves.back().current_square));
                break;
                case 'B':
                board.whiteBishop.erase(board.whiteBishop.begin() + bishopfinder(board.whiteBishop, board.Previous_moves.back().current_square));
                break;
                case 'b':
                board.blackBishop.erase(board.blackBishop.begin() + bishopfinder(board.blackBishop, board.Previous_moves.back().current_square));
                break;
                case 'N':
                board.whiteKnight.erase(board.whiteKnight.begin() + knightfinder(board.whiteKnight, board.Previous_moves.back().current_square));
                break;
                case 'n':
                board.blackKnight.erase(board.blackKnight.begin() + knightfinder(board.blackKnight, board.Previous_moves.back().current_square));
                break;
            }
            if(board.turn){
                pawn Pawn;
                Pawn.square = board.Previous_moves.back().initial_square;
                board.whitePawns.push_back(Pawn);
            }
            if(!board.turn){
                pawn Pawn;
                Pawn.square = board.Previous_moves.back().initial_square;
                board.blackPawns.push_back(Pawn);
            }
        }
        if(board.Previous_moves.back().en_passent_able_square != -1 && pawnfinder(board.whitePawns, board.Previous_moves.back().en_passent_able_square) != -1){
            board.whitePawns[pawnfinder(board.whitePawns, board.Previous_moves.back().en_passent_able_square)].en_passent_able = true;
        }
        if(board.Previous_moves.back().en_passent_able_square != -1 && pawnfinder(board.blackPawns, board.Previous_moves.back().en_passent_able_square) != -1){
            board.blackPawns[pawnfinder(board.blackPawns, board.Previous_moves.back().en_passent_able_square)].en_passent_able = true;
        }
        if(board.Previous_moves.back().black_kingside && rookfinder(board.blackrook, 7) != -1){
            board.blackKing[0].hasmoved = false;
            board.blackrook[rookfinder(board.blackrook, 7)].hasmoved = false;
        }
        if(board.Previous_moves.back().black_queenside && rookfinder(board.blackrook, 0) != -1){
            board.blackKing[0].hasmoved = false;
            board.blackrook[rookfinder(board.blackrook, 0)].hasmoved = false;
        }
        if(board.Previous_moves.back().white_kingside && rookfinder(board.whiterook, 63) != -1){
            board.whiteKing[0].hasmoved = false;
            board.whiterook[rookfinder(board.whiterook, 63)].hasmoved = false;
        }
        if(board.Previous_moves.back().white_queenside && rookfinder(board.whiterook, 56) != -1){
            board.whiteKing[0].hasmoved = false;
            board.whiterook[rookfinder(board.whiterook, 56)].hasmoved = false;
        }
        board.Previous_moves.pop_back();
        legal_moves(board);
    }
}

double evaluation(Board &board){
    
    int counter = 0;
    int rep = 0;
    double pieces = 0;
    int dist = 1000;

    legal_moves(board);
    actual_legal_moves(board);

    if(board.turn){
        white_expansion(board);        
    } 
    else{
        black_expansion(board);         
    }
    weak_pawns(board);
    double eval = 0;
    /*
    for(int i = 0; i < board.Previous_moves.back().pre_pos.size(); i++){ //3-fach Stellungswiederholungs check
        for(int j = 0; j < board.Previous_moves.back().pre_pos.size(); j++){
            if(board.Previous_moves.back().pre_pos[j] == board.Previous_moves.back().pre_pos[i] && i != j){
                rep++;
                if(rep == 3){
                    return 0;
                }
            }
        }
    }
    */
    
    if(board.legal_starting_squares.size() == 0){
        if(iswhiteincheck(board)){
            return 1000;
        }
        if(isblackincheck(board)){
            return -1000;
        }
        return 0;
    }
    for(Knight &knight : board.whiteKnight){
        counter++;
        knight.value = 3;
        if(knight.square / 8 == 0){
            knight.value += -0.5;
        }
        if(knight.square / 8 == 1){
            knight.value += -0.1;
        }
        if(knight.square / 8 == 2){
            knight.value += 0.1;
        }
        if(knight.square / 8 == 3){
            knight.value += 0.2;
        }
        if(knight.square / 8 == 4){
            knight.value += 0.2;
        }
        if(knight.square / 8 == 5){
            knight.value += 0.2;
        }
        if(knight.square / 8 == 6){
            knight.value += -0.1;
        }
        if(knight.square / 8 == 7){
            knight.value += -0.2;
        }
        if(knight.square % 8 == 0 || knight.square % 8 == 7){
            knight.value += -0.5;
        }
        if(knight.square % 8 == 1 || knight.square % 8 == 6){
            knight.value += -0.1;
        }
        if(knight.square % 8 == 2 || knight.square % 8 == 5){
            knight.value += 0.1;
        }
        if(knight.square % 8 == 3 || knight.square % 8 == 4){
            knight.value += 0.2;
        }
        eval += knight.value;
        eval += 0.1 * onecounter(knight.legal_destinations);
        for(int i = 0; i < 64; i++){
            if(knight.legal_destinations[i] == '1'){
                if(!isblackincheck(board) && check_check_black(board, knight.square, i)) {
                    eval += 0.1;
                }
            }
        }
        if((knight.square % 8 != 0 && knight.square > 16 && board.board[knight.square - 7] != 'p' && (board.board[knight.square - 15] != 'p' || (pawnfinder(board.blackPawns, knight.square - 15) != -1 && board.blackPawns[pawnfinder(board.blackPawns, knight.square - 15)].legal_moves[knight.square - 7] == '0'))) && (knight.square % 8 != 7 && knight.square > 16 && board.board[knight.square - 9] != 'p' && (board.board[knight.square - 17] != 'p' || (pawnfinder(board.blackPawns, knight.square - 17) != -1 &&board.blackPawns[pawnfinder(board.blackPawns, knight.square - 17)].legal_moves[knight.square - 9] == '0'))) && (knight.square / 8 == 5 && (knight.square != 39 && (board.board[knight.square - 23] != 'p' || (pawnfinder(board.blackPawns, knight.square - 23) != -1 && board.blackPawns[pawnfinder(board.blackPawns, knight.square - 23)].legal_moves[knight.square - 7] == '0'))) && (knight.square != 32 && (board.board[knight.square] - 25 != 'p' || (pawnfinder(board.blackPawns, knight.square - 25) != -1 &&board.blackPawns[pawnfinder(board.blackPawns, knight.square - 25)].legal_moves[knight.square - 9] == '0')))) && knight.square / 8 < 5){
            eval += 0.5;
        }
    }
    for(Knight &knight : board.blackKnight){
        counter++;
        knight.value = 3;
        if(knight.square / 8 == 0){
            knight.value += -0.2;
        }
        if(knight.square / 8 == 1){
            knight.value += -0.1;
        }
        if(knight.square / 8 == 2){
            knight.value += 0.1;
        }
        if(knight.square / 8 == 3){
            knight.value += 0.2;
        }
        if(knight.square / 8 == 4){
            knight.value += 0.2;
        }
        if(knight.square / 8 == 5){
            knight.value += 0.2;
        }
        if(knight.square / 8 == 6){
            knight.value += -0.1;
        }
        if(knight.square / 8 == 7){
            knight.value += -0.5;
        }
        if(knight.square % 8 == 0 || knight.square % 8 == 7){
            knight.value += -0.5;
        }
        if(knight.square % 8 == 1 || knight.square % 8 == 6){
            knight.value += -0.1;
        }
        if(knight.square % 8 == 2 || knight.square % 8 == 5){
            knight.value += 0.1;
        }
        if(knight.square % 8 == 3 || knight.square % 8 == 4){
            knight.value += 0.2;
        }
        eval -= knight.value;
        eval -= 0.1 * onecounter(knight.legal_destinations);
        for(int i = 0; i < 64; i++){
            if(knight.legal_destinations[i] == '1'){
                if(!iswhiteincheck(board) && check_check_white(board, knight.square, i)){
                    eval -= 0.1;
                }
            }
        }
        if((knight.square % 8 != 0 && knight.square < 48 && board.board[knight.square + 7] != 'P' && (board.board[knight.square + 15] != 'P' || (pawnfinder(board.whitePawns, knight.square + 15) != -1 && board.whitePawns[pawnfinder(board.whitePawns, knight.square + 15)].legal_moves[knight.square + 7] == '0'))) && (knight.square % 8 != 7 && knight.square < 47 && board.board[knight.square + 9] != 'P' && (board.board[knight.square + 17] != 'P' || (pawnfinder(board.whitePawns, knight.square + 17) != -1 &&board.whitePawns[pawnfinder(board.whitePawns, knight.square + 17)].legal_moves[knight.square + 9] == '0'))) && (knight.square / 8 == 4 && (((knight.square != 24 && (board.board[knight.square + 23] != 'P' || (pawnfinder(board.whitePawns, knight.square + 23) != -1 && board.whitePawns[pawnfinder(board.whitePawns, knight.square + 23)].legal_moves[knight.square + 7] == '0'))) && (knight.square != 31 && (board.board[knight.square] + 25 != 'P' || (pawnfinder(board.whitePawns, knight.square + 25) != -1 && board.whitePawns[pawnfinder(board.whitePawns, knight.square + 25)].legal_moves[knight.square + 9]) == '0'))))) && knight.square / 8 > 2){ //Bedingung für Vorpfostenfeld. Ist tendenzeill ungenau, da es auch Felder als Vorpfostenfelder gelten lässt, wenn sie nur vorübergehend sicher sind für den Springer.
            eval -= 0.5;
        }
    }
    for(Bishop &bishop : board.whiteBishop){
        counter++;
        eval += 3.5;
        if(bishop.square == 58 || bishop.square == 61){
            eval -= 0.2;
        }
        eval += 0.1 * onecounter(bishop.legal_destinations);
        for(int i = 0; i < 64; i++){
            if(bishop.legal_destinations[i] == '1'){
                if(!isblackincheck(board) && check_check_black(board, bishop.square, i)){
                    eval += 0.1;
                }
            }
        }
    }
    for(Bishop &bishop : board.blackBishop){
        counter++;
        eval -= 3.5;
        if(bishop.square == 2 || bishop.square == 5){
            eval += 0.2;
        }
        eval -= 0.1 * onecounter(bishop.legal_destinations);
        for(int i = 0; i < 64; i++){
            if(bishop.legal_destinations[i] == '1'){
                if(!iswhiteincheck(board) && check_check_white(board, bishop.square, i)){
                    eval -= 0.1;
                }
            }
        }
    }
    for(Rook &rook : board.whiterook){
        counter++;
        eval += 5;
        eval += 0.1 * onecounter(rook.legal_destinations);
        for(int i = 0; i < 64; i++){
            if(rook.legal_destinations[i] == '1'){
                if(!isblackincheck(board) && check_check_black(board, rook.square, i)){
                    eval += 0.1;
                }
            }
        }
    }
    for(Rook &rook : board.blackrook){
        counter++;
        eval -= 5;
        eval -= 0.1 * onecounter(rook.legal_destinations);
        for(int i = 0; i < 64; i++){
            if(rook.legal_destinations[i] == '1'){
                if(!iswhiteincheck(board) &&  check_check_white(board, rook.square, i)){
                    eval -= 0.1;
                }
            }
        }
    }
    for(Queen &queen : board.whiteQueen){
        counter++;
        eval += 9;
        if(piececounter(board.board) < 12){
            eval += 0.05 * onecounter(queen.legal_destinations);
        }
        for(int i = 0; i < 64; i++){
            if(queen.legal_destinations[i] == '1'){
                if(!isblackincheck(board) && check_check_black(board, queen.square, i)){
                    eval += 0.1;
                }
            }
        }
    }
    for(Queen &queen : board.blackQueen){
        counter++;
        eval -= 9;
        if(piececounter(board.board) < 12){
            eval -= 0.05 * onecounter(queen.legal_destinations);
        }
        for(int i = 0; i < 64; i++){
            if(queen.legal_destinations[i] == '1'){
                if(!iswhiteincheck(board) && check_check_white(board, queen.square, i)){
                    eval -= 0.1;
                }
            }
        }
    }
    for(pawn &pawn : board.whitePawns){
        counter++;
        eval += 1;
        for(int j = pawn.square / 8; j < 8; j++){
                if(board.board[j*8 + pawn.square % 8] == 'P' || (pawn.square % 8 != 7 && board.board[j*8 + 1 + pawn.square % 8] == 'P') || (pawn.square % 8 != 0 && board.board[j*8 - 1 + pawn.square % 8] == 'P')){
                    pawn.ispassed = false; 
                    break;
                }
            }
        if(pawn.square == 27 || pawn.square == 28 || pawn.square == 35 || pawn.square == 36){
            eval += 1.2*piececounter(board.board) / 14;
        }
        for(int i = 0; i < 64; i++){
            if(pawn.legal_destinations[i] == '1'){
                if(!isblackincheck(board) && check_check_black(board, pawn.square, i)){
                    eval += 0.1;
                }
            }
        }
        if(pawn.ispassed){
            eval += 0.5*((8-(pawn.square / 8)) * (8-(pawn.square / 8))) * (1/(piececounter(board.board) + 1));
        }
        if(pawn.is_weak){
            eval -= 0.2;
        }
    }
    for(pawn &pawn : board.blackPawns){
        counter++;
        eval -= 1;
        for(int j = pawn.square / 8; j < 8; j++){
                if(board.board[j*8 - pawn.square % 8] == 'p' || (pawn.square % 8 != 7 && board.board[j*8 - 1 - pawn.square % 8] == 'p') || (pawn.square % 8 != 0 && board.board[j*8 - 1 - pawn.square % 8] == 'p')){
                    pawn.ispassed = false; 
                    break;
                }
            }
        if(pawn.square == 27 || pawn.square == 28 || pawn.square == 35 || pawn.square == 36){
            eval -= 1.2*piececounter(board.board) / 14;
        }
        for(int i = 0; i < 64; i++){
            if(pawn.legal_destinations[i] == '1'){
                if(!iswhiteincheck(board) && check_check_white(board, pawn.square, i)){
                    eval -= 0.1;
                }
            }
        }
        if(pawn.ispassed){
            eval -= 0.5*((pawn.square / 8)*(pawn.square / 8)) * (1/(piececounter(board.board) + 1));
        }
        if(pawn.is_weak){
            eval += 0.2;
        }
    }
    if((piececounter(board.board) > 6 && board.whiteQueen.size() != 0 && board.blackQueen.size() != 0) || (piececounter(board.board) > 10 && board.whiteQueen.size() == 0 && board.blackQueen.size() == 0)){
        if(board.whiteKing[0].square == 63 || board.whiteKing[0].square == 62 || board.whiteKing[0].square == 58 || board.whiteKing[0].square == 57 || board.whiteKing[0].square == 56){
            eval += 1;
        }
        if(board.blackKing[0].square == 1 || board.blackKing[0].square == 2 || board.blackKing[0].square == 0 || board.blackKing[0].square == 6 || board.blackKing[0].square == 7){
            eval -= 1;
        }
        eval -= onecounter(board.whiteKing[0].legal_moves) / 8;
        eval += onecounter(board.blackKing[0].legal_moves) / 8;
    }
    if(piececounter(board.board) <= 2 && board.whiteQueen.size() == 0){ //maximiert Königsmobilität im Endspiel
        eval -= onecounter(board.blackKing[0].legal_destinations) / 8;
        eval -= 4/(abs(board.blackKing[0].square / 8 - 4)+1);
        for(pawn &Pawn : board.whitePawns){ //sollte die Distanz zwischen König und dem nächsten unverteidigtwn Bauern minimieren.
            if(!square_attacked(board.board, Pawn.square, 1)){
                if(distance(board.blackKing[0].square, Pawn.square) < dist){
                    dist = distance(board.blackKing[0].square, Pawn.square);
                }
            }
        }
        eval -= 8/sqrt(dist); 
    }
    if(piececounter(board.board) <= 2 && board.blackQueen.size() == 0){ //maximiert Königsmobilität im Endspiel
        eval += onecounter(board.whiteKing[0].legal_destinations) / 8;
        eval += 4/(abs(board.whiteKing[0].square / 8 - 4)+2);
        for(pawn &Pawn : board.blackPawns){ //sollte die Distanz zwischen König und dem nächsten unverteidigtwn Bauern minimieren.
            if(!square_attacked(board.board, Pawn.square, 0)){
                if(distance(board.whiteKing[0].square, Pawn.square) < dist){
                    dist = distance(board.blackKing[0].square, Pawn.square);
                }
            }
        }
        eval += 8/sqrt(dist); 
    }
    if(eval > 8){
        eval += (8-onecounter(board.blackKing[0].legal_destinations)/8); //bei gewonnen Stellungen sollte der König eingeengt werden
        if(piececounter(board.board) <= 4){ //Bei gewonnenen Endspielen sollte der Abstand zum gegnerischen König minimiert werden sowie dessen Distanz zu der Ecke.
            eval -= sqrt(((board.whiteKing[0].square / 8) - (board.blackKing[0].square / 8)) * ((board.whiteKing[0].square / 8) - (board.blackKing[0].square / 8)) + ((board.whiteKing[0].square % 8 - board.blackKing[0].square % 8)) * ((board.whiteKing[0].square % 8 - board.blackKing[0].square % 8))); //Distanz zum gegerischen König
            eval += 1/(abs(board.whiteKing[0].square / 8 - 4)+1) + 1/(abs(board.whiteKing[0].square % 8 - 4)+1); //Distanz zur Ecke
        }
    }
    if(eval < -8){
        eval -= (8-onecounter(board.whiteKing[0].legal_destinations)) / 8;
        if(piececounter(board.board) <= 4){
            eval += sqrt(((board.whiteKing[0].square / 8) - (board.blackKing[0].square / 8)) * ((board.whiteKing[0].square / 8) - (board.blackKing[0].square / 8)) + ((board.whiteKing[0].square % 8 - board.blackKing[0].square % 8)) * ((board.whiteKing[0].square % 8 - board.blackKing[0].square % 8)));
            eval -= 1/(abs(board.blackKing[0].square / 8 - 4)+1) + 1/(abs(board.blackKing[0].square % 8 - 4)+1);
        }
    }
    return eval;
}

void random_Play(Board &board){
    int random;
    int random_2;

    srand(time(0));

    legal_moves(board);
    actual_legal_moves(board);

    if(board.turn){
        white_expansion(board);        
    } 
    else{
        black_expansion(board);         
    } 
    if(board.turn){
        random = rand() % board.legal_starting_squares.size();
        if(board.board[board.legal_starting_squares[random]] == 'P' && board.legal_target_squares[random] / 8 == 0){
            random_2 = rand() % 4;
            switch(random_2){
                case 0:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'N');
                break;
                case 1:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'B');
                break;
                case 2:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'R');
                break;
                case 3:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'Q');
                break;
            }
        }
        else{
            domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], '0');
        }
    }
    else{
        random = rand() % board.legal_starting_squares.size();
        if(board.board[board.legal_starting_squares[random]] == 'p' && board.legal_target_squares[random] / 8 == 7){
            random_2 = rand() % 4;
            switch(random_2){
                case 0:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'n');
                break;
                case 1:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'b');
                break;
                case 2:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'r');
                break;
                case 3:
                domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], 'q');
                break;
            }
        }
        else{
            domove(board, board.legal_starting_squares[random], board.legal_target_squares[random], '0');
        }
    }
}

double difference(Board &board, int startingsquare, int targetsquare){
    double difference = 0;
    switch(board.board[startingsquare]){
        case 'P':
        difference -= 1;
        break;
        case 'p':
        difference -= 1;
        break;
        case 'N':
        difference -= 3;
        break;
        case 'n':
        difference -= 3;
        break;
        case 'B':
        difference -= 3.5;
        break;
        case 'b':
        difference -= 3.5;
        break;
        case 'R':
        difference -= 5;
        break;
        case 'r':
        difference -= 5;
        break;
        case 'Q':
        difference -= 9;
        break;
        case 'q':
        difference -= 9;
        break;
    }
    switch(board.board[targetsquare]){
        case 'P':
        difference += 1;
        break;
        case 'p':
        difference += 1;
        break;
        case 'N':
        difference += 3;
        break;
        case 'n':
        difference += 3;
        break;
        case 'B':
        difference += 3.5;
        break;
        case 'b':
        difference += 3.5;
        break;
        case 'R':
        difference += 5;
        break;
        case 'r':
        difference += 5;
        break;
        case 'Q':
        difference += 9;
        break;
        case 'q':
        difference += 9;
        break;
    }
    return difference;
}

void domove_temp(std::vector<char> &board, int startingsquare, int targetsquare, char promotion){
    
    bool showboard = false;
    if(board[startingsquare] == 'P'){
        if(startingsquare - 7 == targetsquare && board[targetsquare] == '0' && board[startingsquare + 1] == 'p'){
            board[startingsquare + 1] = '0';
        }
        if(startingsquare - 9 == targetsquare && board[targetsquare] == '0' && board[startingsquare - 1] == 'p'){
            board[startingsquare - 1] = '0';
        } 
    }

    if(board[startingsquare] == 'p'){
        if(startingsquare + 9 == targetsquare && board[targetsquare] == '0' && board[startingsquare + 1] == 'P'){
            board[startingsquare + 1] = '0';
        }
        if(startingsquare + 7 == targetsquare && board[targetsquare] == '0' && board[startingsquare - 1] == 'P'){
            board[startingsquare - 1] = '0';
        } 
    }
    
    if(board[startingsquare] == 'K'){
        if(startingsquare - targetsquare == 2 && board[56] == 'R'){
            board[59] = 'R';
            board[56] = '0';
        }
        if(startingsquare - targetsquare == -2 && board[63] == 'R'){
            board[61] = 'R';
            board[63] = '0';
        }
    }
    if(board[startingsquare] == 'k'){
        if(startingsquare - targetsquare == 2 && board[0] == 'r'){
            board[3] = 'r';
            board[0] = '0';
        }
        if(startingsquare - targetsquare == -2 && board[7] == 'r'){
            board[5] = 'r';
            board[7] = '0';
        }
    }


    board[targetsquare] = board[startingsquare];
    board[startingsquare] = '0';    

    
    if(board[targetsquare] == 'P' && targetsquare / 8 == 0){
        board[targetsquare] = promotion;
    }
    if(board[targetsquare] == 'p' && targetsquare / 8 == 7){
        board[targetsquare] = promotion;
    }
}

void cycle(Board &board, int depth){
    int positions;
    int tempeval;
    double alpha;
    double beta;
    for(int i = 2; i < depth + 1; i += 2){
        alpha = -10000;
        beta = 10000;
        tempeval = Tree(board, i, positions, i, alpha, beta);
        if(board.turn && tempeval == 1000){
            break;
        }
        if(!board.turn && tempeval == -1000){
            break;
        }

    } 
}

int piececounter (std::vector<char> &board){
    int counter = 0;
    for(int i = 0; i < 64; i++){
        if(iswhitepiece(board, i) && board[i] != 'P'){
            counter++;
        }
        if(isblackpiece(board, i) && board[i] != 'p'){
            counter++;
        }
    }
    return counter - 2;
}

int distance(int start, int target){
    return sqrt(abs(start*start - target*target));
}

void weak_pawns(Board &board){

    for(pawn &pawn : board.whitePawns){
        for(int i = pawn.square; i < 56; i += 8){
            if((pawn.square % 8 != 7 && board.board[i+1] == 'P') || (pawn.square % 8 != 0 && board.board[i-1] == 'P')){
                pawn.is_weak = false;
            }
        }
        if(pawn.square / 8 == 6){
            pawn.is_weak = false;
        }
    }
    for(pawn &pawn : board.blackPawns){
        for(int i = pawn.square; i > 8; i -= 8){
            if((pawn.square % 8 != 7 && board.board[i+1] == 'p') || (pawn.square % 8 != 0 && board.board[i-1] == 'p')){
                pawn.is_weak = false;
            }
        }
        
        if(pawn.square / 8 == 1){
            pawn.is_weak = false;
        }
    }
}

bool is_mate_threatened(Board &board, bool bywhite){ //Die Funktion schaut, ob es ein Schach gibt nachdem der Gegner keinen Königszug hat. Er schaut nicht, ob es tatsächlich matt ist
    legal_moves(board);
    int counter = 0;
    if(bywhite){
        for(pawn &Pawn : board.whitePawns){
            for(int i = 0; i < 64; i++){
                if(Pawn.legal_moves[i] == '1' && i != Pawn.square){
                    domove(board, Pawn.square, i, '0');
                    if(square_attacked(board.board, board.blackKing[0].square, 1)){
                        for(int j = 0; j < 64; j++){
                            if(board.blackKing[0].legal_moves[j] == '1'){
                                domove(board, board.blackKing[0].square, j, '0');
                                if(check_check_black(board, board.blackKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.blackKing[0].legal_moves) && counter != 0){
                                return true;
                            }
                            std::cout << "B" << '\n';
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Knight &knight : board.whiteKnight){
            for(int i = 0; i < 64; i++){
                if(knight.legal_moves[i] == '1' && i != knight.square){
                    domove(board, knight.square, i, '0');
                    if(square_attacked(board.board, board.blackKing[0].square, 1)){
                        for(int j = 0; j < 64; j++){
                            if(board.blackKing[0].legal_moves[j] == '1'){
                                domove(board, board.blackKing[0].square, j, '0');
                                if(check_check_black(board, board.blackKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                        }
                        if(counter == onecounter(board.blackKing[0].legal_moves) && counter != 0){
                            return true;
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Bishop &bishop : board.whiteBishop){
            for(int i = 0; i < 64; i++){
                if(bishop.legal_moves[i] == '1' && i != bishop.square){
                    domove(board, bishop.square, i, '0');
                    if(square_attacked(board.board, board.blackKing[0].square, 1)){
                        for(int j = 0; j < 64; j++){
                            if(board.blackKing[0].legal_moves[j] == '1'){
                                domove(board, board.blackKing[0].square, j, '0');
                                if(check_check_black(board, board.blackKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                        }
                        if(counter == onecounter(board.blackKing[0].legal_moves)  && counter != 0){
                            return true;
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Rook &rook : board.whiterook){
            for(int i = 0; i < 64; i++){
                if(rook.legal_moves[i] == '1' && i != rook.square){
                    domove(board, rook.square, i, '0');
                    if(square_attacked(board.board, board.blackKing[0].square, 1)){
                        for(int j = 0; j < 64; j++){
                            if(board.blackKing[0].legal_moves[j] == '1'){
                                domove(board, board.blackKing[0].square, j, '0');
                                if(check_check_black(board, board.blackKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.blackKing[0].legal_moves) &&  counter != 0){
                                return true;
                            }
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Queen &queen : board.whiteQueen){
            for(int i = 0; i < 64; i++){
                if(queen.legal_moves[i] == '1' && i != queen.square){
                    domove(board, queen.square, i, '0');    
                    if(square_attacked(board.board, board.blackKing[0].square, 1)){
                        for(int j = 0; j < 64; j++){
                            if(board.blackKing[0].legal_moves[j] == '1'){
                                domove(board, board.blackKing[0].square, j, '0');
                                if(check_check_black(board, board.blackKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.blackKing[0].legal_moves) && counter != 0){
                                return true;
                            }
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        for(int i = 0; i < 64; i++){
            if(board.whiteKing[0].legal_moves[i] == '1'){
                domove(board, board.whiteKing[0].square, i, '0');
                if(square_attacked(board.board, board.blackKing[0].square, 1)){
                    for(int j = 0; j < 64; j++){
                        if(board.blackKing[0].legal_moves[j] == '1'){
                            domove(board, board.blackKing[0].square, j, '0');
                                if(check_check_black(board, board.blackKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                        }
                        if(counter == onecounter(board.blackKing[0].legal_moves)){
                            return true;
                        }
                    }
                }
                counter = 0;
                undomove(board);
            }
        } 
        counter = 0;
    }
    if(!bywhite){
        for(pawn &Pawn : board.blackPawns){
            for(int i = 0; i < 64; i++){
                if(Pawn.legal_moves[i] == '1' && i != Pawn.square){
                    domove(board, Pawn.square, i, '0');
                    if(square_attacked(board.board, board.whiteKing[0].square, 0)){
                        for(int j = 0; j < 64; j++){
                            if(board.whiteKing[0].legal_moves[j] == '1'){
                                domove(board, board.whiteKing[0].square, j, '0');
                                if(check_check_white(board, board.whiteKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.whiteKing[0].legal_moves) && counter != 0){
                                return true;
                            }
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Knight &knight : board.blackKnight){
            for(int i = 0; i < 64; i++){
                if(knight.legal_moves[i] == '1' && i != knight.square){
                    domove(board, knight.square, i, '0');
                    if(square_attacked(board.board, board.whiteKing[0].square, 0)){
                        for(int j = 0; j < 64; j++){
                            if(board.whiteKing[0].legal_moves[j] == '1'){
                                domove(board, board.whiteKing[0].square, j, '0');
                                if(check_check_white(board, board.whiteKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.whiteKing[0].legal_moves) && counter != 0){
                                return true;
                            }
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Bishop &bishop : board.blackBishop){
            for(int i = 0; i < 64; i++){
                if(bishop.legal_moves[i] == '1' && i != bishop.square){
                    domove(board, bishop.square, i, '0');
                    if(square_attacked(board.board, board.whiteKing[0].square, 0)){
                        for(int j = 0; j < 64; j++){
                            if(board.whiteKing[0].legal_moves[j] == '1'){
                                domove(board, board.whiteKing[0].square, j, '0');
                                if(check_check_white(board, board.whiteKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.whiteKing[0].legal_moves) && counter != 0){
                                return true;
                            }
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(Rook &rook : board.blackrook){
            for(int i = 0; i < 64; i++){
                if(rook.legal_moves[i] == '1' && i != rook.square){
                    domove(board, rook.square, i, '0');
                    if(square_attacked(board.board, board.whiteKing[0].square, 0)){
                        for(int j = 0; j < 64; j++){
                            if(board.whiteKing[0].legal_moves[j] == '1'){
                                domove(board, board.whiteKing[0].square, j, '0');
                                if(check_check_white(board, board.whiteKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                        }
                        if(counter == onecounter(board.whiteKing[0].legal_moves) && counter != 0 ){
                            return true;
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        
        for(Queen &queen : board.blackQueen){
            for(int i = 0; i < 64; i++){
                if(queen.legal_moves[i] == '1' && i != queen.square){
                    domove(board, queen.square, i, '0');
                    if(square_attacked(board.board, board.whiteKing[0].square, 0)){
                        for(int j = 0; j < 64; j++){
                            if(board.whiteKing[0].legal_moves[j] == '1'){
                                domove(board, board.whiteKing[0].square, j, '0');
                                if(check_check_white(board, board.whiteKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                            }
                            if(counter == onecounter(board.whiteKing[0].legal_moves) && counter != 0){
                                return true;
                            }
                        }
                    }
                    counter = 0;
                    undomove(board);
                }
            }
        }
        counter = 0;
        for(int i = 0; i < 64; i++){
            if(board.blackKing[0].legal_moves[i] == '1'){
                domove(board, board.blackKing[0].square, i, '0');
                if(square_attacked(board.board, board.whiteKing[0].square, 1)){
                    for(int j = 0; j < 64; j++){
                        if(board.whiteKing[0].legal_moves[j] == '1'){
                            domove(board, board.whiteKing[0].square, j, '0');
                                if(check_check_white(board, board.whiteKing[0].square, j)){
                                    counter++;
                                }
                                undomove(board);
                        }
                        if(counter == onecounter(board.whiteKing[0].legal_moves) && counter != 0){
                            return true;
                        }
                    }
                }
                counter = 0;
                undomove(board);
            }
        }
    }
    return false;
}

bool can_interpose(Board &board, int startingsquare, int targetsquare, bool color){
    legal_moves(board);
    if(!color){
        if(startingsquare / 8 == targetsquare / 8){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i++){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i--){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
        }
        if(startingsquare % 8 == targetsquare % 8){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i += 8){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i -= 8){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
        }
        if(abs(startingsquare - targetsquare) % 7 == 0){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i > targetsquare; i -= 7){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i < targetsquare; i += 7){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }

        }
        if(abs(startingsquare - targetsquare) % 9 == 0){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i += 9){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i -= 9){
                    if(board.interpose_help_black[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
        }
    }
    if(color){
        if(startingsquare / 8 == targetsquare / 8){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i++){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i--){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
        }
        if(startingsquare % 8 == targetsquare % 8){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i += 8){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i -= 8){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
        }
        if(abs(startingsquare - targetsquare) % 7 == 0){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i += 7){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i -= 7){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }

        }
        if(abs(startingsquare - targetsquare) % 9 == 0){
            if(startingsquare - targetsquare > 0){
                for(int i = startingsquare; i < targetsquare; i += 9){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
            if(startingsquare - targetsquare < 0){
                for(int i = startingsquare; i > targetsquare; i -= 9){
                    if(board.interpose_help_white[i] == '1'){
                        return true;
                    }
                }
                return false;
            }
        }
    }
    return false;
}

bool only_king(Board &board, int square, bool color){
    legal_moves(board);
    if(color){
        for(pawn Pawn : board.whitePawns){
            if(Pawn.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Knight knight : board.whiteKnight){
            if(knight.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Bishop bishop : board.whiteBishop){
            if(bishop.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Rook rook : board.whiterook){
            if(rook.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Queen queen : board.whiteQueen){
            if(queen.legal_moves[square] == '1'){
                return false;
            }
        }
        if((square + 8 == board.whiteKing[0].square && square < 56) || (square - 8 == board.whiteKing[0].square && square > 7) || (square + 1 == board.whiteKing[0].square && square % 8 != 7) || (square - 1 == board.whiteKing[0].square && square % 8 != 0) || (square - 7 == board.whiteKing[0].square && square > 7 && square % 8 != 7) || (square - 9 == board.whiteKing[0].square && square > 7 && square % 8 != 0) || (square + 7 == board.whiteKing[0].square && square < 56 && square % 8 != 0) || (square + 9 == board.whiteKing[0].square && square < 56 && square % 8 != 7)){
            return true;
        }
    }
    if(!color){
        for(pawn Pawn : board.blackPawns){
            if(Pawn.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Knight knight : board.blackKnight){
            if(knight.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Bishop bishop : board.blackBishop){
            if(bishop.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Rook rook : board.blackrook){
            if(rook.legal_moves[square] == '1'){
                return false;
            }
        }
        for(Queen queen : board.blackQueen){
            if(queen.legal_moves[square] == '1'){
                return false;
            }
        }
        if(board.blackKing[0].legal_moves[square] == '1'){
            return true;
        }
    }
    return false;

}
