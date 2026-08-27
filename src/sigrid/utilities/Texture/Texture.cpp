#include "sigrid/utilities/Texture/Texture.h"

bool sigrid::Texture::loadFromFile(const sigrid::String& filename){
    return m_texture.loadFromFile(filename.getStdString());
}

bool sigrid::Texture::loadFromImage(const sigrid::Image& image){
    return m_texture.loadFromImage(image.getSfImage());
}

const sf::Texture& sigrid::Texture::getSfTexture() const{
    return m_texture;
}