#include "Icon.h"

using namespace sigrid;

Icon::Icon(){}

void Icon::setSize(const sf::Vector2f& size){
    m_shape.setSize(size);
}

void Icon::setPosition(const sf::Vector2f& position){
    m_shape.setPosition(position);
}

void Icon::setTexture(const sf::Texture* texturePtr){
    m_shape.setTexture(texturePtr);
}

void Icon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}