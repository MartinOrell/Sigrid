#include "ColorContainer.h"

#include <iostream>
#include <sstream>

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

bool sigrid::ColorContainer::setValue(const std::string& s){

    uint32_t colorHex;
    std::stringstream ss;
    try{
        ss << std::hex << s;
        ss >> colorHex;
    }
    catch(...){
        std::cerr << "ColorContainer: Failed setting value from string " << s << std::endl;
        return false;
    }
    
    value = colorHex * 0x100 + 0xff;
    return true;
}