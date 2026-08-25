#include "sigrid/utilities/Image/Image.h"

#include <sstream>
#include <iomanip>

void sigrid::Image::set(sf::Image&& image){
    m_image = std::move(image);
}

sf::Image sigrid::Image::getSfImage() const{
    return m_image;
}

int sigrid::Image::getWidth() const{
    return m_image.getSize().x;
}

int sigrid::Image::getHeight() const{
    return m_image.getSize().y;
}

sigrid::String sigrid::Image::getAsciiHexStream() const{

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for(unsigned int y = 0; y < m_image.getSize().y; y++){
        for(unsigned int x = 0; x < m_image.getSize().x; x++){
            const auto& pixel = m_image.getPixel({x,y});
            const auto& red = pixel.r;
            const auto& green = pixel.g;
            const auto& blue = pixel.b;

            ss << std::hex << std::setw(2) << static_cast<int>(red);
            ss << std::hex << std::setw(2) << static_cast<int>(green);
            ss << std::hex << std::setw(2) << static_cast<int>(blue);
        }
    }

    sigrid::String out;
    out.set(std::move(ss.str()));
    return out;
}

bool sigrid::Image::loadFromFile(const sigrid::String& filename){
    return m_image.loadFromFile(filename.getStdString());
}

bool sigrid::Image::saveToFile(const sigrid::String& filename) const{
    return m_image.saveToFile(filename.getStdString());
}

void sigrid::Image::modifyColor(const sf::Color& lightModifier, const sf::Color& darkModifier){

    for(unsigned int x = 0; x < m_image.getSize().x; x++){
        for(unsigned int y = 0; y < m_image.getSize().y; y++){
            sf::Color color = m_image.getPixel({x,y});
            color.r = (color.r * lightModifier.r) / 255;
            color.g = (color.g * lightModifier.g) / 255;
            color.b = (color.b * lightModifier.b) / 255;

            color.r = color.r + (darkModifier.r * (255-color.r)) / 255;
            color.g = color.g + (darkModifier.g * (255-color.g)) / 255;
            color.b = color.b + (darkModifier.b * (255-color.b)) / 255;

            m_image.setPixel({x,y},color);
        }
    }
}