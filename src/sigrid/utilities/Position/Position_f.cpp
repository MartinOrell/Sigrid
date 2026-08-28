#include "sigrid/utilities/Position/Position_f.h"

sf::Vector2<float> sigrid::Position_f::getSfVector() const{
    return sf::Vector2<float>{this->x, this->y};
}

sigrid::Position_f sigrid::Position_f::operator+(const Position_f& rhs) const{
    
    sigrid::Position_f out;
    out.x = this->x + rhs.x;
    out.y = this->y + rhs.y;
    return out;
}

sigrid::Position_f sigrid::Position_f::operator-(const Position_f& rhs) const{
    
    sigrid::Position_f out;
    out.x = this->x - rhs.x;
    out.y = this->y - rhs.y;
    return out;
}

sigrid::Position_f sigrid::Position_f::operator*(const float& rhs) const{

    sigrid::Position_f out;
    out.x = this->x * rhs;
    out.y = this->y * rhs;
    return out;
}

sigrid::Position_f sigrid::Position_f::operator/(const float& rhs) const{

    sigrid::Position_f out;
    out.x = this->x / rhs;
    out.y = this->y / rhs;
    return out;
}

bool sigrid::Position_f::operator==(const Position_f& rhs) const{
    
    if(this->x != rhs.x){
        return false;
    }
    return this->y == rhs.y;
}

bool sigrid::Position_f::operator!=(const Position_f& rhs) const{
    
    if(this->x != rhs.x){
        return true;
    }
    return this->y != rhs.y;
}

void sigrid::Position_f::set(const sf::Vector2f& sfVector){

    this->x = sfVector.x;
    this->y = sfVector.y;
}