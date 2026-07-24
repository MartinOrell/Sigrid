#include "ColorContainer.h"

#include <iostream>
#include <sstream>

#include "Config/IO.h"

bool sigrid::ColorContainer::load(std::istream& is){

    auto inputHex_o = sigrid_config::readHex(is);
    if(inputHex_o == std::nullopt){
        return false;
    }
    uint32_t inputHex = inputHex_o.value();
    
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