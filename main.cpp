#include <iostream>
#include <string>
#include <algorithm>

#include "constants.h"

namespace Const = constants;


void displayBoard(std::string_view board[][Const::NUM_OF_ATTEMPTS]);
std::string getInput();
void parseInput(std::string_view input);
int* checkAttempt(std::string_view attempt, std::string_view word);

int main(){
    std::string word {"arise"};

    std::cout << "\n";
    std::string_view input = getInput();
    parseInput(input);
    int* map = checkAttempt(input, word);
    for(int i = 0; i<Const::WORD_LENGTH; i++){
        std::cout << map[i] << "\n";
    }

    return 0;
}

void displayBoard(std::string_view board[][Const::NUM_OF_ATTEMPTS]){
    for(int i = 0; i < Const::WORD_LENGTH; i++){
        for(int j = 0; j < Const::NUM_OF_ATTEMPTS; j++){
            std::cout << board[i][j];
        }
        std::cout << '\n';
    }
}

std::string getInput(){
    std::string input;
    std::cin >> input;
    return input;
}

void parseInput(std::string_view input){
    int lo = 1;
    int hi = 5;

    if(input.size() != Const::WORD_LENGTH){
        std::cout << "inputSize is invalid. Please, enter an input of length=" << WORD_LENGTH << ".\n";
    }

    lo = 97;
    hi = 123;
    for(char c: input){
        int charToInt = std::tolower(c);
        // std::clamp returns first arg if it is within bounds
        if(charToInt != std::clamp(charToInt, lo, hi)){
            std::cout << "Invalid character found in your input: " << c << ".\n";
        }
    }
}

int* checkAttempt(std::string_view attempt, std::string_view word){
    static int map[Const::WORD_LENGTH] {}; // zero-initiliazation
    for(int i = 0; i < Const::WORD_LENGTH; i++){
        char c = attempt[i];
        if(word.find(c) == std::string::npos)
            map[i] = 0;
        else if(word.find(c) != attempt.find(c) && word.find(c) != std::string::npos)
            map[i] = 1;
        else
            map[i] = 2;
    }
    return map;
}
