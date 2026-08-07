#include "sigrid/Color/ColorContainer.h"

#include <iostream>
#include <iomanip>

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

std::ostream& sigrid::operator<<(std::ostream& out, const ColorContainer& colorContainer){

    out << std::hex << std::setw(6) << std::setfill('0') << colorContainer.value;

    return out;
}

bool sigrid::ColorContainer::setValue(const sigrid::String& s){

    auto inputHex_o = s.toHex();
    if(inputHex_o == std::nullopt){

        std::cerr << "ColorContainer: Failed to convert \"" << s << "\"."
            << " Failed to set ColorContainer from string" << std::endl;
        return false;
    }
    uint32_t inputHex = inputHex_o.value();

    value = inputHex * 0x100 + 0xff;
    return true;
}