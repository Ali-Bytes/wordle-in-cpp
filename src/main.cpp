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

#include "controller/controller.hpp"
#include "headers/constants.h"

namespace C = Constants;


int main(){
    Controller::Controller controller = Controller::Controller();

    const std::string WORD { controller.requestWordFromModel() };

    int current = 1;
    while(current <= C::NUM_OF_ATTEMPTS){
        int now = controller.iterate(current, WORD);
        current = now;
    }

    std::cout << "\n\n\nBetter luck next time! The word was " << WORD << ".\n";
}
