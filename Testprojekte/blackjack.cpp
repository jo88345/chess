#include <iostream>
#include <random>
#include <vector>

std::string number_to_card(int index);
int random_index(std::vector<int> &deck);
int cardvalue(int index);

class player{
    public:
       int balance;
       int id;
       std::vector<int> cards;
       bool isbust;
    void assign_card(std::vector<int> &deck, int amount){
        for(int i = 0; i < amount; i++){
            cards.push_back(random_index(deck));
            deck[cards.back() - 1] = -1;
        }    
    }
    void dealer_algorithm(std::vector<int> &deck){

        while(sum() < 17){
            assign_card(deck, 1);
        }
        show_cards();
        std::cout << sum() << '\n';
    }
    void show_cards(){
        for(int i = 0; i < cards.size(); i++){
            std::cout << number_to_card(cards[i]) << '\n';
        }
    }
    int sum(){
        int sum = 0;
        for(int i = 0; i < cards.size(); i++){
            sum += cardvalue(cards[i]);

        }
        for(int i = 0; i < cards.size(); i++){
            if (cards[i] % 13 == 12 && sum > 21){
                sum -= 10;
            }
        }
        return sum;
    }
    bool bust(){
        if(sum() > 21){
            isbust = true;
            return isbust;
        }
        else{
            isbust = false;
            return isbust;
        }

    }
    bool find_ace(){
        for(int i = 0; i < cards.size(); i++){
            if(cards[i] % 13 == 12){
                return true;
            }
        }
        return false;
    }

};

int main(){
    std::vector<int> deck;
    std::vector<int> deck_save;
    std::vector<player> players;
    int hit;
    int player_amount;
    for(int i = 0; i < 52; i++){
        deck.push_back(i + 1);
        deck_save.push_back(i + 1);
    }

    std::cout << "How many players?" << '\n';
    std::cin >> player_amount;

    for(int i = 0; i < player_amount; i++){
        player player;
        player.id = i;
        player.assign_card(deck, 2);
        players.push_back(player);
    }

    player dealer;
    dealer.assign_card(deck, 2);

    std::cout << "dealer: " << '\n';
    std::cout << number_to_card(dealer.cards[0]) << '\n';

    for(int i = 0; i < players.size(); i++){
        std::cout << "player#" << i + 1 << '\n';
        players[i].show_cards();
        std::cout << "sum = " << players[i].sum() << '\n';
        
    }

    
        for(int i = 0; i < players.size(); i++){
            while(true){
            std::cout << "player#" << i + 1 << " Hit or stand? press 1 for hit and 0 for stand";
            std::cin >> hit;
            if(hit == 1){
                players[i].assign_card(deck, 1); 
                players[i].show_cards();
                std::cout << "sum = " << players[i].sum() << '\n';
                if(players[i].bust()){ 
                    std::cout << "bust!";
                    break;
                }
            }

            else{
                break;
            }
            }
        }

    dealer.dealer_algorithm(deck);
    for(int i = 0; i < players.size(); i++){
    if(dealer.bust()){
           if(!players[i].isbust){
               std::cout << "player# " << i + 1 << " wins!" << '\n';
           }
    }
    else if(dealer.sum() < players[i].sum()){
        std::cout << "player# " << i + 1 << " wins!" << '\n';
    }
    else if(dealer.sum() == players[i].sum()){
        std::cout << "player# " << i + 1 << " draws!" << '\n';
    }
    else if(dealer.sum() > players[i].sum() || players[i].isbust){
        std::cout << "player# " << i + 1 << " loses!" << '\n';
    }
}

    return 0;
}

std::string number_to_card(int index){

    int color = index % 4;
    int number = index % 13;
    std::string card;
    switch(number){
        case 0:
            card += "two";
            break;
        case 1:
            card += "three";
            break;
        case 2:
            card += "four";
            break;
        case 3:
            card += "five";
            break;
        case 4:
            card += "six";
            break;
        case 5:
            card += "seven";
            break;
        case 6:
            card += "eight";
            break;
        case 7:
            card += "nine";
            break;
        case 8:
            card += "ten";
            break;
        case 9:
            card += "jack";
            break;
        case 10:
            card += "queen";
            break;
        case 11:
            card += "king";
            break;
        case 12:
            card += "ace";
            break;
        
    }
    switch(color){
    case 0:
        card += " of hearts";
        break;
    case 1:
        card += " of diamonds";
        break;
    case 2:
        card += " of spades";
        break;
    case 3:
        card += " of clubs";
        break;
    }

    return card;
}

int random_index(std::vector<int> &deck){
    int random_number;
    do{
    std::random_device rd; 
    std::mt19937 gen(std::random_device{}()); 

    std::uniform_int_distribution<> dist(1, 52); 

    random_number = dist(gen);
    }while(deck[random_number] == -1);

    return random_number;
}

int cardvalue(int index){
    int value;
    int puffer;
    value = ((index % 13) + 2);

    if (value == 14){
        return 11;
    }
    
    if (value > 10){
        value -= value % 10;
    }

    return value;
}
