#include "ColorContainer.h"

#include <iostream>

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

    auto inputHex_o = sigrid_config::stringToHex(s);
    if(inputHex_o == std::nullopt){
        return false;
    }
    uint32_t inputHex = inputHex_o.value();

    value = inputHex * 0x100 + 0xff;
    return true;
}