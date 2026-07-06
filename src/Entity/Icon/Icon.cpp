#include "Entity/Icon/Icon.h"

#include <SFML/Graphics/RenderTarget.hpp>

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

void Icon::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void Icon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}