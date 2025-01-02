#include "../model/model.hpp"
#include "../view/view.hpp"

#include "../headers/wordleDictionary.h"
#include "../headers/constants.h"

namespace C = Constants;

using namespace View;
using namespace Model;

namespace Controller{
    #ifndef CONTROLLER
    #define CONTROLLER
    class Controller{
        public:
            Controller(){
                this->view = View::View();
                this->model = Model::Model();
            }

            std::string requestWordFromModel(){
                std::string WORD = this->model.getRandomWord();
                return WORD;
            }

            int iterate(int current, std::string WORD){
                const std::string PROMPT_PHRASE { "\nEnter a word: " };
                std::string input { this->getInput(PROMPT_PHRASE) };
                
                if(!this->model.parseInput(input))
                    return current;

                int* map = this->model.checkAttempt(input, WORD);

                this->view.displayWordValidity(input, map);

                // stop game if latest guess was right
                if(strcmp(WORD.c_str(), input.c_str()) == 0){
                    std::cout << "\n\n\nGood job! The word is indeed " << WORD << ".\n";
                    this->waitForInput("\nPress enter to terminate.\n");
                    return C::NUM_OF_ATTEMPTS + 1;
                }

                return ++current;
            }

        private:
            View::View view;
            Model::Model model;

            std::string getInput(std::string_view prompt){
                std::string input;

                std::cout << prompt; 
                std::cin >> input;
                return input;
            }

            void waitForInput(std::string_view prompt){
                std::cout << prompt;
                std::cin.get();
            }
    };
    #endif
}