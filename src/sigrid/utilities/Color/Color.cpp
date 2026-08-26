#include "sigrid/utilities/Color/Color.h"

void sigrid::Color::setRGBA(const std::uint32_t& colorHex){
    
    this->r = (static_cast<std::uint8_t>((colorHex & 0xff'00'00'00) >> 24));
    this->g = (static_cast<std::uint8_t>((colorHex & 0x00'ff'00'00) >> 16));
    this->b = (static_cast<std::uint8_t>((colorHex & 0x00'00'ff'00) >> 8));
    this->a = (static_cast<std::uint8_t>((colorHex & 0x00'00'00'ff) >> 0));
}

std::uint32_t sigrid::Color::getRGBInteger() const{

    return static_cast<std::uint32_t>(
        this->r << 16 |
        this->g << 8 |
        this->a
    );
}

sf::Color sigrid::Color::getSfColor() const{

    return sf::Color(this->r, this->g, this->b, this->a);
}

sf::Color sigrid::Color::getSolidSfColor() const{

    return sf::Color(this->r, this->g, this->b, 255);
}