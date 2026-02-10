#include "Coord.h"

using namespace sigrid;

Coord::Coord(int x, int y)
: x(x)
, y(y){}

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