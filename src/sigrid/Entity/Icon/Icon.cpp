#include "sigrid/Entity/Icon/Icon.h"

#include <SFML/Graphics/RenderTarget.hpp>

void sigrid::Icon::setSize(const sigrid::Size_f& size){
    m_shape.setSize(size.getSfVector());
}

void sigrid::Icon::setPosition(const sigrid::Position_f& position){
    m_shape.setPosition(position.getSfVector());
}

void sigrid::Icon::setTexture(const sigrid::Texture* texturePtr){
    m_shape.setTexture(&(texturePtr->getSfTexture()));
}

void sigrid::Icon::move(const sigrid::Offset_f& offset){
    m_shape.move(offset.getSfVector());
}

void sigrid::Icon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}