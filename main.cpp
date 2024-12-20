#include <iostream>
#include <algorithm>
#include <cctype>

#include "constants.h"

namespace C = constants;

class guessStore;
enum class ATTEMPT_OUTCOMES;
void displayBoard(std::string_view board[][C::NUM_OF_ATTEMPTS]);
std::string getInput();
void parseInput(std::string_view input);
int* checkAttempt(std::string_view attempt, std::string_view word);

class guessStore{
    std::string attempts[C::NUM_OF_ATTEMPTS];
};

enum class ATTEMPT_OUTCOMES{
    NOT_IN_WORD = 0,
    IN_WORD_WRONG_SPOT = 1,
    IN_WORD_RIGHT_SPOT = 2
};

int main(){
    std::string word {"arise"};

    std::string_view input = getInput();
    parseInput(input);
    int* map = checkAttempt(input, word);
    for(int i = 0; i < C::WORD_LENGTH; i++){
        std::cout << map[i] << "\n";
    }
            
    return 0;
}

void displayBoard(std::string_view board[][C::NUM_OF_ATTEMPTS]){
    for(int i = 0; i < C::WORD_LENGTH; i++){
        for(int j = 0; j < C::NUM_OF_ATTEMPTS; j++){
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

    if(input.size() != C::WORD_LENGTH){
        std::cout << "inputSize is invalid. Please, enter an input of length=" << C::WORD_LENGTH << ".\n";
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
    static int map[C::WORD_LENGTH] {}; // zero-initiliazation
    for(int i = 0; i < C::WORD_LENGTH; i++){
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
