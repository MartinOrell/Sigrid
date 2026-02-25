#include "Coord.h"

#include <cctype>
#include <iostream>

using namespace sigrid;

Coord::Coord(const int x, const int y)
: x(x)
, y(y){}

Coord::Coord(const std::string& notation){
    
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
        std::cout << "Invalid coordinate: " << notation << std::endl;
        return;
    }
    if(i == notation.length()){
        std::cout << "Invalid coordinate: " << notation << std::endl;
        return;
    }

    ny = std::stoi(notation.substr(i));

    x = nx - 1;
    y = ny - 1;
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

std::string Coord::getNotation() const{

    std::string notation;

    int base = 'z' - 'a'+1;
    for(int i{x}; i>=0; i = i / base-1){
        notation.insert(0,1,(i%base + 'a'));
    }

    notation.append(std::to_string(y+1));
    
    return notation;
}