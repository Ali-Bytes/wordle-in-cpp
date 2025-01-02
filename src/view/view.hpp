#include "../headers/constants.h"

namespace C = Constants;

namespace View{
    #ifndef VIEW
    #define VIEW
    class View{
        public:
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

            void hello(){
                std::cout << "Welcome to a Wordle clone!\n";
                std::cout << "2=Word is in the right place.\n1=Character is in the word, but in the wrong place.\n0=Character is not in the word.\n";
            }
    };
    #endif
}