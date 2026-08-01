#include "sigrid/Color/ColorContainer.h"

#include <iostream>

#include "sigrid/Config/IO.h"

bool sigrid::ColorContainer::load(InputStream& is){

    auto inputHex_o = is.readHex();
    if(inputHex_o == std::nullopt){

        std::cerr << "ColorContainer: Failed to read hex value."
            << " Failed to load ColorContainer" << std::endl;
        return false;
    }
    uint32_t inputHex = inputHex_o.value();
    
    value = inputHex * 0x100 + 0xff;
    return true;
}


bool sigrid::ColorContainer::setValue(const std::string& s){

    auto inputHex_o = sigrid_config::stringToHex(s);
    if(inputHex_o == std::nullopt){

        std::cerr << "ColorContainer: Failed to convert \"" << s << "\"."
            << " Failed to set ColorContainer from string" << std::endl;
        return false;
    }
    uint32_t inputHex = inputHex_o.value();

    value = inputHex * 0x100 + 0xff;
    return true;
}