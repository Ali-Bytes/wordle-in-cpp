#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

#include "constants.h"


namespace C = constants;

enum class ATTEMPT_OUTCOMES;
std::string getInput(std::string_view prompt);
void parseInput(std::string_view input);
int* checkAttempt(std::string_view attempt, std::string_view word);
void displayWordValidity(std::string_view attempt, int map[]);

enum class ATTEMPT_OUTCOMES{
    NOT_IN_WORD = 0,
    IN_WORD_WRONG_SPOT = 1,
    IN_WORD_RIGHT_SPOT = 2
};

int main(){
    std::string_view word { "arise" };

    std::string_view input { getInput("Enter a word: ") };
    parseInput(input);
    int* map = checkAttempt(input, word);
    displayGameState(input, map);
}

std::string getInput(std::string_view prompt){
    std::string input;

    std::cout << prompt; 
    std::cin >> input;
    return input;
}

void parseInput(std::string_view input){
    if(input.size() != C::WORD_LENGTH){
        std::cout << "inputSize is invalid. Please, enter an input of length=" << C::WORD_LENGTH << ".\n";
        return;
    }

    int lo { 97 };
    int hi { 123 };
    for(char c: input){
        int charToInt = std::tolower(c);
        // std::clamp returns first arg if it is within bounds
        if(charToInt != std::clamp(charToInt, lo, hi)){
            std::cout << "Invalid character found in your input: " << c << ".\n";
            return;
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

void displayWordValidity(std::string_view attempt, int map[]){
    for(int i = 0; i < C::WORD_LENGTH; i++){
        std::cout << attempt[i] << " (" << map[i] << ") ";
    }
}