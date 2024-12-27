#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include <cstring>
#include <cstdlib>
#include <array>
#include <ios>
#include <limits>

#include "constants.h"
#include "words.h"
#include "answers.h"


namespace C = constants;
namespace W = words;
namespace A = answers;

enum class ATTEMPT_OUTCOMES;
void waitForInput();
std::string_view getRandomWord();
std::string getInput(std::string_view);
bool parseInput(std::string_view);
int* checkAttempt(std::string_view, std::string_view);
void displayWordValidity(std::string_view, int[]);

enum class ATTEMPT_OUTCOMES{
    NOT_IN_WORD = 0,
    IN_WORD_WRONG_SPOT = 1,
    IN_WORD_RIGHT_SPOT = 2
};

int main(){
    std::cout << "Welcome to a Wordle clone!\n";
    std::cout << "2=Word is in the right place.\n1=Character is in the word, but in the wrong place.\n0=Character is not in the word.\n";

    const std::string WORD { getRandomWord() };

    int current = 1;
    while(current <= C::NUM_OF_ATTEMPTS){
        std::string_view promptPhrase { "\nEnter a word: " };

        std::string input { getInput(promptPhrase) };
        
        if(!parseInput(input))
            continue;

        int* map = checkAttempt(input, WORD);

        displayWordValidity(input, map);

        // stop game if latest guess was right
        if(strcmp(WORD.c_str(), input.c_str()) == 0){
            std::cout << "\n\n\nGood job! The word is indeed " << WORD << ".\n";
            waitForInput();
            return 0;
        }

        current++;
        std::cout << "\n";
    }

    std::cout << "\n\n\nBetter luck next time! The word was " << WORD << ".\n";
}

void waitForInput(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //wait for newline
    std::cout << "\nPress enter to terminate.\n";
    std::cin.get();
}

std::string getInput(std::string_view prompt){
    std::string input;

    std::cout << prompt; 
    std::cin >> input;
    return input;
}

bool parseInput(std::string_view input){
    if(input.size() != C::WORD_LENGTH){
        std::cout << "inputSize is invalid. Please, enter an input of length=" << C::WORD_LENGTH << ".\n";
        return false;
    }

    const int lo = C::LOWER_CASE_A_ASCII;
    const int hi = C::LOWER_CASE_Z_ASCII;
    for(char c: input){
        int charToInt = std::tolower(c);
        // std::clamp returns first arg if it is within bounds
        if(charToInt != std::clamp(charToInt, lo, hi)){
            std::cout << "Invalid character found in your input: " << c << ".\n";
            return false;
        }
    }

    for(std::string word : A::POSSIBLE_ANSWERS){
        if(input.compare(word) == 0){
            return true;
        }
    }

    for(std::string word : W::WORDS_S){
        if(input.compare(word) == 0){
            return true;
        }
    }

    std::cout << "Word is not valid (i.e. not in the answers list nor in the allowed wordle list.\n";
    return false;
}

std::string_view getRandomWord(){
    srand(time(0)); // give new seed (here it is the current time)
    
    int numOfElements = sizeof(W::WORDS_S) / sizeof(*W::WORDS_S);
    int r_int = std::rand() % numOfElements;

    return W::WORDS_S[r_int];
}

int* checkAttempt(std::string_view attempt, std::string_view word){
    static int map[C::WORD_LENGTH] {}; // zero-initiliazation

    for(int i = 0; i < C::WORD_LENGTH; i++){
        char c = attempt[i];
        // this order is the right one
        if(attempt[i] == word[i])
            map[i] = 2;
        else if(word.find(c) != std::string::npos)
            map[i] = 1;
        else
            map[i] = 0;
    }
    
    return map;
}

void displayWordValidity(std::string_view attempt, int map[]){
    std::cout << "\n";
    for(int i = 0; i < C::WORD_LENGTH; i++){
        std::cout << attempt[i] << "  ";
    }

    std::cout << "\n";
    for(int i = 0; i < C::WORD_LENGTH; i++){
        std::cout << map[i] << "  ";
    }
}