#include "sigrid/utilities/Coord/Coord.h"

#include <iostream>

using namespace sigrid_coord;

Coord::Coord()
: x(0)
, y(0){}

Coord::Coord(const int x, const int y)
: x(x)
, y(y){}

Coord::Coord(const sigrid::String& notation){
    set(notation);
}

Coord& Coord::operator=(const Coord& rhs){
    x = rhs.x;
    y = rhs.y;
    
    return *this;
}

bool Coord::operator<(const Coord& rhs) const{
    if(y < rhs.y){
        return true;
    }
    if(y > rhs.y){
        return false;
    }
    if(x < rhs.x){
        return true;
    }
    return false;
}

bool Coord::operator==(const Coord& rhs) const{
    if(x != rhs.x){
        return false;
    }
    if(y != rhs.y){
        return false;
    }
    return true;
}

bool Coord::operator!=(const Coord& rhs) const{
    if(x != rhs.x){
        return true;
    }
    if(y != rhs.y){
        return true;
    }
    return false;
}

bool Coord::set(const sigrid::String& notation){

    int nx = 0; // character notation where 'a' = 1, 'z' = 26, 'aa' = 27
    int ny = 0;

    int i;
    for(i = 0; i < notation.length(); i++){
        auto xChar_o = notation.at(i);
        if(xChar_o == std::nullopt){
            std::cerr << "Coord: Failed to read char from \""
                << notation << "\" at position " << i << "."
                << " Failed to set Coord" << std::endl;
            return false;
        } 
        char xChar = xChar_o.value().get();

        if(std::isdigit(xChar)){
            break;
        }
        nx = nx*('z'-'a'+1) + xChar-'a'+1;
    }
    
    if(i == 0){
        std::cerr << "Coord: Invalid coordinate: " << notation
            << ". Failed to set Coord" << std::endl;
        return false;
    }
    if(i == notation.length()){
        std::cerr << "Coord: Invalid coordinate: " << notation
            << ". Failed to set Coord" << std::endl;
        return false;
    }

    auto yString_o = notation.substr(i);
    if(yString_o == std::nullopt){
        std::cerr << "Coord: Failed to get yString from \""
            << notation << "\" at position " << i << "."
            << " Failed to set Coord" << std::endl;
        return false;
    }
    sigrid::String yString = yString_o.value();
    if(yString.length() == 0){
        std::cerr << "Coord: yString is empty after getting substring from \""
            << notation << "\" at position " << i << "."
            << " Failed to set Coord" << std::endl;
        return false;
    }
    
    auto y_o = yString.toInt();
    if(y_o == std::nullopt){
        std::cerr << "Coord: Failed to convert yString \""
            << yString << "\" to int."
            << " Failed to set Coord" << std::endl;
        return false;
    }
    ny = y_o.value();

    x = nx - 1;
    y = ny - 1;
    return true;
}

sigrid::String Coord::getNotation() const{

    sigrid::String notation;
    notation.append(getColumnNotation(x));
    notation.append(getRowNotation(y));
    
    return notation;
}

bool Coord::load(sigrid::InputStream& is){

    const auto positionString_o = is.readString();
    if(positionString_o == std::nullopt){

        std::cerr << "Coord: Failed to read string."
            << " Failed to load Coord" << std::endl;
        return false;
    }
    const sigrid::String& positionString = positionString_o.value();

    if(!set(positionString)){

        std::cerr << "Coord: Failed to set from string \"" << positionString << "\"."
            << " Failed to load Coord" << std::endl;
        return false;
    }
    return true;
}

sigrid::String sigrid_coord::getColumnNotation(const int& x){

    sigrid::String notation = "";

    int base = 'z' - 'a'+1;
    for(int i{x}; i>=0; i = i / base-1){
        notation.insert(0,1,(i%base + 'a'));
    }
    return notation;
}

sigrid::String sigrid_coord::getRowNotation(const int& y){

    std::string stdString = std::to_string(y+1);
    sigrid::String sigridString;
    sigridString.set(std::move(stdString));
    return sigridString;
}