#include "Coord/Coord.h"

#include <iostream>

#include "Config/IO.h"

using namespace sigrid_coord;

Coord::Coord()
: x(0)
, y(0){}

Coord::Coord(const int x, const int y)
: x(x)
, y(y){}

Coord::Coord(const std::string& notation){
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

bool Coord::set(const std::string& notation){

    int nx = 0; // character notation where 'a' = 1, 'z' = 26, 'aa' = 27
    int ny = 0;

    int i;
    for(i = 0; i < notation.length(); i++){
        if(std::isdigit(notation.at(i))){
            break;
        }
        nx = nx*('z'-'a'+1) + notation.at(i)-'a'+1;
    }
    
    if(i == 0){
        std::cerr << "Coord: Invalid coordinate: " << notation << std::endl;
        return false;
    }
    if(i == notation.length()){
        std::cerr << "Coord: Invalid coordinate: " << notation << std::endl;
        return false;
    }

    ny = std::stoi(notation.substr(i));

    x = nx - 1;
    y = ny - 1;
    return true;
}

std::string Coord::getNotation() const{

    std::string notation;
    notation.append(getColumnNotation(x));
    notation.append(getRowNotation(y));
    
    return notation;
}

bool Coord::load(std::istream& is){

    const auto positionString_o = sigrid_config::readString(is);
    if(positionString_o == std::nullopt){
        return false;
    }
    const std::string& positionString = positionString_o.value();

    return set(positionString);
}

std::string sigrid_coord::getColumnNotation(const int& x){
    std::string notation = "";

    int base = 'z' - 'a'+1;
    for(int i{x}; i>=0; i = i / base-1){
        notation.insert(0,1,(i%base + 'a'));
    }
    return notation;
}

std::string sigrid_coord::getRowNotation(const int& y){
    return std::to_string(y+1);
}