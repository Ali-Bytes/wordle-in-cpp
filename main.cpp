#include <iostream>
#include <cctype>
#include <algorithm>

#include "constants.h"

using namespace constants;

void displayBoard(std::string_view wordsBoard[]){
    for(int i = 0; i < WORD_LENGTH; i++){
        std::cout << wordsBoard[i] << '\n';
    }
}

std::string getInput(){
    std::string input;
    std::cin >> input;
    return input;
}

void parseInput(std::string input){
    int lo = 1;
    int hi = 5;

    if(input.size() != WORD_LENGTH){
        std::cout << "inputSize is invalid. Enter an input of length=" << WORD_LENGTH << ".\n";
    }

    lo = 97;
    hi = 123;
    for(char c: input){
        int charToInt = tolower(c);
        // std::clamp returns first arg if it is within bounds
        if(charToInt != std::clamp(charToInt, lo, hi)){
            std::cout << "Invalid character found in your input: " << c << ".\n";
        }
    }
}

int main(){
    std::string_view word {"Arise"};

    std::string input = getInput();
    parseInput(input);

    return 0;
}