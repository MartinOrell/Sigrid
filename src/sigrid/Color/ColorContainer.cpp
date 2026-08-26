#include "sigrid/Color/ColorContainer.h"

#include <iostream>
#include <iomanip>
#include <sstream>

bool sigrid::ColorContainer::load(InputStream& is){

    auto rgb_o = is.readHex();
    if(rgb_o == std::nullopt){

        std::cerr << "ColorContainer: Failed to read hex value."
            << " Failed to load ColorContainer" << std::endl;
        return false;
    }
    this->rgb = rgb_o.value();
    
    return true;
}

sigrid::String sigrid::ColorContainer::getString(const unsigned int& indentLevel) const{

    std::stringstream ss;
    ss << std::hex << std::setw(6) << std::setfill('0') << this->rgb;

    sigrid::String out;
    out.set(std::move(ss.str()));

    return out;
}

bool sigrid::ColorContainer::setValue(const sigrid::String& rgbString){
    return setRGB(rgbString);
}

bool sigrid::ColorContainer::setRGB(const sigrid::String& rgbString){

    auto rgb_o = rgbString.toHex();
    if(rgb_o == std::nullopt){

        std::cerr << "ColorContainer: Failed to convert \"" << rgbString << "\"."
            << " Failed to set ColorContainer from string" << std::endl;
        return false;
    }
    this->rgb = rgb_o.value();
    return true;
}