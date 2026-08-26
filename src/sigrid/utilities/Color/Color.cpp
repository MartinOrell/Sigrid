#include "sigrid/utilities/Color/Color.h"

#include <sstream>
#include <iomanip>

void sigrid::Color::setRGB(const std::uint32_t& rgb){

    this->r = (static_cast<std::uint8_t>((rgb & 0x00'ff'00'00) >> 16));
    this->g = (static_cast<std::uint8_t>((rgb & 0x00'00'ff'00) >> 8));
    this->b = (static_cast<std::uint8_t>((rgb & 0x00'00'00'ff) >> 0));
}

void sigrid::Color::setRGBA(const std::uint32_t& rgba){
    
    this->r = (static_cast<std::uint8_t>((rgba & 0xff'00'00'00) >> 24));
    this->g = (static_cast<std::uint8_t>((rgba & 0x00'ff'00'00) >> 16));
    this->b = (static_cast<std::uint8_t>((rgba & 0x00'00'ff'00) >> 8));
    this->a = (static_cast<std::uint8_t>((rgba & 0x00'00'00'ff) >> 0));
}

std::uint32_t sigrid::Color::getRGBInteger() const{

    return static_cast<std::uint32_t>(
        this->r << 16 |
        this->g << 8 |
        this->b
    );
}

sigrid::String sigrid::Color::getRGBString() const{

    std::stringstream ss;
    ss << std::hex << std::setw(6) << std::setfill('0') << getRGBInteger();

    sigrid::String out;
    out.set(std::move(ss.str()));

    return out;
}

sf::Color sigrid::Color::getSfColor() const{
    return sf::Color(this->r, this->g, this->b, this->a);
}

sf::Color sigrid::Color::getSolidSfColor() const{
    return sf::Color(this->r, this->g, this->b, 255);
}