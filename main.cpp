#include <iostream>

#include <constants.h>

using namespace CONSTANTS;

void displayBoard(std::string_view wordsBoard[]){
    for(int i = 0; i < BOARD_SIZE; i++){
        std::cout << wordsBoard[i] << '\n';
    }
}

int main(){
    std::string_view wordsBoard[5] {"Arise", "Notes", "Panel", "Crane", "Blame"};
    displayBoard(wordsBoard);

    return 0;
}