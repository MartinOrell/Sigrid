#include "sigrid/Entity/Icon/Icon.h"

#include <SFML/Graphics/RenderTarget.hpp>

void sigrid::Icon::setSize(const sf::Vector2f& size){
    m_shape.setSize(size);
}

void sigrid::Icon::setPosition(const sf::Vector2f& position){
    m_shape.setPosition(position);
}

void sigrid::Icon::setTexture(const sigrid::Texture* texturePtr){
    m_shape.setTexture(&(texturePtr->getSfTexture()));
}

void sigrid::Icon::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void sigrid::Icon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}