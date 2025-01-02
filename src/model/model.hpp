#include "../headers/wordleDictionary.h"
#include "../headers/constants.h"

namespace C = Constants;
namespace WD = WordleDictionary;

namespace Model{
    #ifndef MODEL
    #define MODEL
    class Model{
        enum class ATTEMPT_OUTCOMES{
            NOT_IN_WORD = 0,
            IN_WORD_WRONG_SPOT = 1,
            IN_WORD_RIGHT_SPOT = 2
        };

        public:
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

                for(std::string word : WD::ALLOWED){
                    if(input.compare(word) == 0){
                        return true;
                    }
                }

                for(std::string word : WD::CORRECT){
                    if(input.compare(word) == 0){
                        return true;
                    }
                }

                std::cout << "Word is not valid (i.e. not in the answers list nor in the allowed wordle list.\n";
                return false;
            }

            std::string getRandomWord(){
                srand(time(0)); // give new seed (here it is the current time)
                
                int numOfElements = sizeof(WD::CORRECT) / sizeof(*WD::CORRECT);
                int r_int = std::rand() % numOfElements;

                return WD::CORRECT[r_int];
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
    };
    #endif
}