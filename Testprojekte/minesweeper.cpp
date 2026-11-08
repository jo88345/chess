#include <iostream>
#include <ctime>

void createfield(int (&board)[8][8], int (&trueboard)[8][8]);
int randomnumb();
void distance(int (&board)[8][8]);
void displayboard(int board[8][8]);
void chardisplayboard(char board[8][8]);
int input_row();
int input_column();
void expansion(int trueboard[8][8], char (&publicboard)[8][8], int a, int b);
void cleanup(char (&board)[8][8]);
bool ncheck(char board[8][8]);
void flag(char (&publicboard)[8][8]);
void removeflag(char (&board)[8][8]);
bool wincheck(char board[8][8]);

int main(){
    srand(time(0));

    int board[8][8];
    char publicboard[8][8];
    int trueboard[8][8];
    int a;
    int b;

    createfield(board, trueboard);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            publicboard[i][j] = '*';
        }
    }
    distance(trueboard);
    while(true){
    chardisplayboard(publicboard);
    flag(publicboard);
    removeflag(publicboard);
    do{
    a = input_row();
    b = input_column();
    }while((a < 0 || a > 7 || b < 0 || b > 7) || publicboard[a][b] != '*');
    
    if(trueboard[a][b] == 0){
        publicboard[a][b] = trueboard[a][b] + 48;
        chardisplayboard(publicboard);
        std::cout << "you lose";
        break;
    }
    else if(trueboard[a][b] == 9){
        expansion(trueboard, publicboard, a, b);  
        while(ncheck(publicboard)){
        for(int i = 0; i < 8; i++){
           for(int j = 0; j < 8; j++){
               if(publicboard[i][j] == '9'){
                    expansion(trueboard, publicboard, i, j);  
               }
            }
        }
    }
    cleanup(publicboard);
    }
    else{
        publicboard[a][b] = trueboard[a][b] + 48;
    }
    if(wincheck(publicboard)){
        chardisplayboard(publicboard);
        std::cout << "you win!";
        return false;
    }
    
}


    return 0;
}

void createfield(int (&board)[8][8], int (&trueboard)[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = 1;
            trueboard[i][j] = 2;
        }
    }
    for(int i = 0; i < 11; i++){
        do{
        int a = randomnumb();
        if(board[a / 8][a % 8] == 1){
        trueboard[a / 8][a % 8] = 0;
        board[a / 8][a % 8] = 0;
        break;
        }
        }while(true);
    }
}

int randomnumb(){
    int num = rand() % 64;
    return num;
}

void distance(int (&board)[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != 0){
            int tempcounter = 0;

            if (board[i+1][j] == 0 && i != 7){
                tempcounter += 1;
            }
            if(board[i-1][j] == 0 && i != 0){
                tempcounter += 1;
            }
            if(board[i][j-1] == 0 && j != 0){
                tempcounter += 1;
            }
            if(board[i][j+1] == 0 && j != 7){
                tempcounter += 1;
            }
            if(board[i+1][j+1] == 0 && i != 7 && j != 7){
                tempcounter += 1;
            }
            if(board[i-1][j-1] == 0 && i != 0 && j != 0){
                tempcounter += 1;
            }
            if(board[i-1][j+1] == 0 && i != 0 && j != 7){
                tempcounter += 1;
            }
            if(board[i+1][j-1] == 0 && i != 7 && j != 0){
                tempcounter += 1;
            }

            if (tempcounter != 0){
            board[i][j] = tempcounter;
            }
            else{
                board[i][j] = 9;
            }
            } 

            

        }
    }
}

void displayboard(int board[8][8]){
    for(int i = 0; i < 8; i++){
        std::cout << '\n';
        for(int j = 0; j < 8; j++){
            std::cout  << board[i][j] << " ";
        }
    }
}

void chardisplayboard(char board[8][8]){
    for(int i = 0; i < 8; i++){
        std::cout << '\n';
        for(int j = 0; j < 8; j++){
            std::cout  << board[i][j] << " ";
        }
    }
    std::cout << '\n';
}

int input_column(){
    int column;
    std::cout << "1-8, column: " << '\n';
    std::cin >> column;
    return column - 1;
}

int input_row(){
    int row;
    std::cout << "1-8, row: " << '\n';
    std::cin >> row;
    return row - 1;
}

void expansion(int trueboard[8][8], char (&publicboard)[8][8], int a, int b){
    publicboard[a][b] = 'O';
    if(a != 7){
        publicboard[a+1][b] = trueboard[a+1][b] + 48;
    }
    if(a != 7 && b != 7){
        publicboard[a+1][b+1] = trueboard[a+1][b+1] + 48;
    }
    if(b != 7){
        publicboard[a][b+1] = trueboard[a][b+1] + 48;
    }
    if(a != 0){
        publicboard[a-1][b] = trueboard[a-1][b] + 48;
    }
    if(b != 0){
        publicboard[a][b-1] = trueboard[a][b-1] + 48;
    }
    if(a != 7 && b != 0){
        publicboard[a+1][b-1] = trueboard[a+1][b-1] + 48;
    }    
    if(a != 0 && b != 0){
        publicboard[a-1][b-1] = trueboard[a-1][b-1] + 48;
    }    
    if(a != 0 && b != 7){
        publicboard[a-1][b+1] = trueboard[a-1][b+1] + 48;
    } 
}

void cleanup(char (&board)[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '9'){
                board[i][j] = 'O';
            }
        }
    }
}

bool ncheck(char board[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '9' && ((board[i+1][j] == '*' && i != 7) || (board[i+1][j+1] == '*' && i != 7 && j != 7) || (board[i+1][j-1] == '*' && i != 7 && j != 0) || (board[i][j+1] == '*' && j != 7)|| (board[i][j-1] == '*' && j != 0) || (board[i-1][j] == '*' && i != 0) || (board[i-1][j+1] == '*' && i != 0 && j != 7) || (board[i-1][j-1] == '*' && i != 0 && j != 0))){
                return true;
            }
        }
    }
    return false;
}

void flag(char (&board)[8][8]){
    bool isflag = true;
    int a;
    int b;
    while(isflag){
    std::cout << "Do you want to place a flag? 1 for yes, 0 for no";
    std::cin >> isflag;
    if(isflag){
        do{
        a = input_row(); 
        b = input_column();
        }while(board[a][b] != '*');
        board[a][b] = '@';
        chardisplayboard(board);
    }
}
}

void removeflag(char (&board)[8][8]){
    bool isflag = true;
    while(isflag){
    std::cout << "Do you want to remove a flag? 1 for yes, 0 for no";
    std::cin >> isflag;
    if(isflag){
        board[input_row()][input_column()] = '*';
        chardisplayboard(board);
    }
}
}

bool wincheck(char board[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '*'){
                return false;
            }
        }
    }
    return true;
}
