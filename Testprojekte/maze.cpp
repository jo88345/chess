#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>

void fillmaze(std::vector<std::vector<char>> &maze, int a, char carc);
void printmaze(std::vector<std::vector<char>> &maze, int a);
int random_square(int a);
void random_start(std::vector<std::vector<char>> &maze, int a);
void expansion(std::vector<std::vector<char>> &maze, int a,  std::vector<int> &visited, int tempocounter, int amount, std::vector<std::vector<char>> &legalmaze);
int ocounter(std::vector<std::vector<char>> &maze, int a);
bool edger(std::vector<std::vector<char>> &maze, int a);
bool findvalue(std::vector<int> list, int element);
bool charfindvalue(std::vector<std::vector<char>> list, int x, int y, char target);
bool borders(std::vector<std::vector<char>> &list, int x, int y, int a, int zlatan);
bool finisher(std::vector<std::vector<char>> &maze, int a, int x, int y, int zlatan);
int legal_expansion(std::vector<std::vector<char>> &maze, int a, std::vector<std::vector<char>> &legaltable);
int charcounter(std::vector<std::vector<char>> &maze, int a, char character);
void filllegaltable(std::vector<std::vector<char>> &maze, int a, std::vector<std::vector<char>> &legaltable);


int main(){
    srand(time(0));
    int a = 10;
    std::vector<std::vector<char>> legalmaze(a,std::vector<char>(a));
    std::vector<std::vector<char>> maze(a,std::vector<char>(a));
    std::vector<int> visited;
    int x;
    int y;
    int temp;
    char temo = 0;

    fillmaze(maze, a, '*');
    fillmaze(legalmaze, a, '1');
    printmaze(maze, a);

    random_start(maze, a);

    printmaze(maze, a);


    expansion(maze, a, visited, 0, 0, legalmaze);
    visited.clear();
    printmaze(maze, a);
    filllegaltable(maze, a, legalmaze);
    legal_expansion(maze, a, legalmaze);

    printmaze(legalmaze, a);

    while(legal_expansion(maze, a, legalmaze) > 0){
        visited.clear();
        expansion(maze, a, visited, ocounter(maze, a), 1, legalmaze);
        printmaze(maze, a);
    } 
    std::cout << "A";


    legal_expansion(maze, a, legalmaze);

    std::cout << legal_expansion(maze, a, legalmaze);
    
    printmaze(legalmaze, a);

    return 0;
}

void fillmaze(std::vector<std::vector<char>> &maze, int a, char carc){
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            maze[i][j] = carc;
        }
    }
}

void printmaze(std::vector<std::vector<char>> &maze, int a){
    for(int i = 0; i < a; i++){
        std::cout << '\n';
        for(int j = 0; j < a; j++){
            std::cout << maze[i][j];
        }
    }
    std::cout << '\n';
}

int random_square(int a){
    int num = rand() % a;
    return num;
}

void random_start(std::vector<std::vector<char>> &maze, int a){
    int index;
    int edge;

    do{
    index = random_square(a);
    edge = random_square(4);
    }while(((index == 0 || index == a-1) && edge == 0) ||((index == 0 || index == a-1)  && edge == 1) || ((index == 0 || index == a-1) && edge == 2) || ((index == a-1 || index == 0) && edge == 3));

    switch(edge){
        case 0:
        maze[edge][index] = '@';
        maze[edge + 1][index] = 'O';
        break;
        case 1:
        edge = 0;
        maze[index][edge] = '@';
        maze[index][edge + 1] = 'O';
        break;
        case 2:
        edge = a;
        maze[edge - 1][index] = '@';
        maze[edge - 2][index] = 'O';
        break;
        case 3:
        edge = a;
        maze[index][edge - 1] = '@';
        maze[index][edge - 2] = 'O';
        break;
    }
}

void expansion(std::vector<std::vector<char>> &maze, int a, std::vector<int> &visited,  int tempocounter, int amount, std::vector<std::vector<char>> &legalmaze){
    int counter = 0;
    bool breaker = false;
    int num = 0;
    int x;
    int y;
    for(int i = 0; i < a && !breaker; i++){
        for(int j = 0; j < a && !breaker; j++){
            if(maze[i][j] == 'O' && !findvalue(visited, a*i + j) && legalmaze[i][j] == '1'){
                counter = 0;
                do{
                num = random_square(4);
                counter++;
                if(counter > 20){
                    counter = 0; 
                    break; //Da stand einmal return, was grosse Probleme machte da das Programm der Reihe nach die 'O' durchgeht und es die Expansion einfach beenden würde, wenn auch nur ein einziges nicht geht.
                }
                }while((((num == 0 && (maze[i+1][j] == 'O' || maze[i+1][j] == '@')) || (num == 1 && (maze[i-1][j] == 'O' || maze[i-1][j] == '@')) || (num == 2 && (maze[i][j+1] == 'O' || maze[i][j+1] == '@')) || (num == 3 && (maze[i][j-1] == 'O' || maze[i][j-1] == '@'))) || !finisher(maze, a, i, j, num)) || (edger(maze, a) && ((num == 0 && i == a-2) || (num == 1 && i == 1) || (num == 2 && j == a-2) || (num == 3 && j == 1))) || ((num == 0 && borders(maze, i, j, a, 1)) || (num == 1 && borders(maze, i, j, a, 2)) || (num == 2 && borders(maze, i, j, a, 3)) || (num == 3 && borders(maze, i, j, a, 4))));
                switch(num){
                    case 0:
                   
                    maze[i+1][j] = 'O';
                    visited.push_back(a*i + j);
                    break;
                    case 1:

                    
                    maze[i-1][j] = 'O';
                    visited.push_back(a*i + j);
                    break;
                    case 2:
                    
                    
                    maze[i][j+1] = 'O';
                    visited.push_back(a*i + j);
                    
                    break;
                    case 3:
                   
                    
                    maze[i][j-1] = 'O';
                    visited.push_back(a*i + j);
                    
                    break;
                }
            }
        }
    }
    /*
    printmaze(maze, a);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Aus ChatGPT
    system("cls");
    */
    if(!edger(maze, a) || ocounter(maze, a)-tempocounter < amount){
        printmaze(maze, a);
        filllegaltable(maze, a, legalmaze);
        expansion(maze, a, visited, tempocounter, amount, legalmaze);
        std::cout << "A";
        return;
    }
}

int ocounter(std::vector<std::vector<char>> &maze, int a){
    int counter = 0;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            if(maze[i][j] == 'O'){
                counter++;
            }
        }
    }
    return counter;
}

bool edger(std::vector<std::vector<char>> &maze, int a){
    int counter = 0;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            if((i == 0 && ((maze[i][j] == 'O') || (maze[i][j] == '@'))) || (j == 0 && ((maze[i][j] == 'O') ||(maze[i][j] == '@'))) || (j == a-1 && ((maze[i][j] == 'O') || (maze[i][j] == '@'))) || (i == a-1 && ((maze[i][j] == 'O')||(maze[i][j] == '@')))){
                maze[i][j] = '@';
                counter++;
                if(counter == 2){
                return true;
                }
            }
        }
    }
    return false;
}

bool findvalue(std::vector<int> list, int element){
    for(int i = 0; i < list.size(); i++){
        if(list[i] == element){
            return true;
        }
    }
    return false;
}

bool borders(std::vector<std::vector<char>> &list, int x, int y, int a, int zlatan){

    switch(zlatan){
    case 1:
    
    if(x < a-2 && list[x+2][y] == 'O'){
        return true;
    }
    if(y > 0 && x < a-1 && list[x+1][y-1] == 'O'){
        return true;
    }
    if(y < a-1 && x < a-1 && list[x+1][y+1] == 'O'){
        return true;
    }
    return false;

    case 2:
    if(x > 1 && list[x-2][y] == 'O'){
        return true;
    }
    if(x > 0 && y < a-1 && list[x-1][y+1] == 'O'){
        return true;
    }
    if(x > 0 && y > 0 && list[x-1][y-1] == 'O'){
        return true;
    }
    return false;

    case 3:
    if(y < a-2 && list[x][y+2] == 'O'){
        return true;
    }
    if(x > 0 && y < a-1 && list[x-1][y+1] == 'O'){
        return true;
    }
    if(x < a-1 && y < a-1 && list[x+1][y+1] == 'O'){
        return true;
    }
    return false;

    case 4:
    if(y > 1 && list[x][y-2] == 'O'){
        return true;
    }
    if(x > 0 && y > 0 && list[x-1][y-1] == 'O'){
        return true;
    }
    if(x < a-1 && y > 0 && list[x+1][y-1] == 'O'){
        return true;
    }
    return false;
}
return false;
}

bool charfindvalue(std::vector<std::vector<char>> list, int x, int y, char target){
    if(list[x][y] == target){
        return true;
        }
    return false;
}

bool finisher(std::vector<std::vector<char>> &maze, int a, int x, int y, int zlatan){
        switch(zlatan){
            case 0:
            for(int i = 0; i < a; i++){
            if(x == a-2 && charfindvalue(maze, a-1, i, '@')){
                return false;
            }
            }
            break;
            case 1:
            for(int i = 0; i < a; i++){
            if(x == 1 && charfindvalue(maze, 0, i, '@')){
                return false;
            }
            }
            break;
            case 2:
            for(int i = 0; i < a; i++){
            if(y == a-2 && charfindvalue(maze, i, a-1, '@')){
                return false;
            }
            }
            break;
            case 3:
            for(int i = 0; i < a; i++){
            if(y == 1 && charfindvalue(maze, i, 0, '@')){
                return false;
            }
            }   
            break;
    }
    return true;
}

int legal_expansion(std::vector<std::vector<char>> &maze, int a, std::vector<std::vector<char>> &legaltable){
    int counter = 0;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            for(int k = 1; k < 5; k++){
                if(maze[i][j] == 'O' && !borders(maze, i, j, a, k)){
                    switch(k){
                        case 1:
                        if(maze[i+1][j] != 'O' && maze[i+1][j] != '@' && (i != a-2 && charcounter(maze, a, '@') == 2)){
                        legaltable[i][j] = '1';
                        counter++;
                        }
                        break;
                        case 2:
                        if(maze[i-1][j] != 'O' && maze[i-1][j] != '@'  && (i != 1 && charcounter(maze, a, '@') == 2)){
                        legaltable[i][j] = '1';
                        counter++;
                        }
                        break;
                       
                        case 3:
                        if(maze[i][j+1] != 'O' && maze[i][j+1] != '@'  && (j != a-2 && charcounter(maze, a, '@') == 2)){
                        legaltable[i][j] = '1';
                        counter++;
                        }
                        break;
                        
                        case 4:
                        if(maze[i][j-1] != 'O' && maze[i][j-1] != '@'  && (j != 1 && charcounter(maze, a, '@') == 2)){
                        legaltable[i][j] = '1';
                        counter++;
                        }
                        break;
                        
                    }
                    
                }
            }
        }
    }
    return counter;
}

int charcounter(std::vector<std::vector<char>> &maze, int a, char character){
    int counter = 0;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            if(maze[i][j] == character){
                counter++;
            }
        }
    }
    return counter;
}

void filllegaltable(std::vector<std::vector<char>> &maze, int a, std::vector<std::vector<char>> &legaltable){


    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            legaltable[i][j] = maze[i][j];
        }
    }
}
