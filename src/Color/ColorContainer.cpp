#include "ColorContainer.h"

#include <iostream>

bool sigrid::ColorContainer::load(std::istream& is){

    uint32_t inputHex;
    try{
        is >> std::hex >> inputHex >> std::ws;
    }
    catch(...){
        std::cerr << "ColorContainer: Failed to load color" << std::endl;
        return false;
    }
    value = inputHex * 0x100 + 0xff;
    return true;
}