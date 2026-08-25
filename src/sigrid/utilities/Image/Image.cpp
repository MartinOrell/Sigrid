#include "sigrid/utilities/Image/Image.h"

void sigrid::Image::set(sf::Image&& image){
    m_image = std::move(image);
}

sf::Image sigrid::Image::getSfImage() const{
    return m_image;
}

bool sigrid::Image::saveToFile(const sigrid::String& filename){
    return m_image.saveToFile(filename.getStdString());
}