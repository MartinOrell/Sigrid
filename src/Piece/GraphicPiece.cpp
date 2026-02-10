#include "GraphicPiece.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

using namespace sigrid;

GraphicPiece::GraphicPiece(sf::Vector2u size, const sf::Texture* texturePtr)
: m_sprite(*texturePtr)
, m_texturePtr(texturePtr){
    sf::FloatRect rect(m_sprite.getLocalBounds());
    m_sprite.setOrigin({rect.size.x/2.f, rect.size.y/2.f});
    m_sprite.setPosition({size.x/2.f, size.y/2.f});
    float scale = 0.8;
    m_sprite.scale({scale,scale});

    m_offset = {size.x/2.f, size.y/2.f};
}

GraphicPiece::GraphicPiece(const GraphicPiece& p)
: m_sprite(p.m_sprite)
, m_offset(p.m_offset)
, m_texturePtr(p.m_texturePtr){
}

GraphicPiece& GraphicPiece::operator =(const GraphicPiece& p){
    m_sprite = p.m_sprite;
    m_offset = p.m_offset;
    m_texturePtr = p.m_texturePtr;
    return *this;
}

void GraphicPiece::setPosition(sf::Vector2f position){
    sf::Vector2f newPosition;
    newPosition.x = position.x + m_offset.x;
    newPosition.y = position.y + m_offset.y;
    m_sprite.setPosition(newPosition);
}

bool GraphicPiece::contains(sf::Vector2i point) const{
    sf::FloatRect rect = m_sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

void GraphicPiece::resize(sf::Vector2f size){

    auto rect = m_sprite.getTextureRect();
    float scaleX = size.x/rect.size.x;
    float scaleY = size.y/rect.size.y;

    m_sprite.setScale({scaleX, scaleY});

    auto oldOffset = m_offset;
    sf::Vector2f newOffset = {size.x/2.f, size.y/2.f};
    m_sprite.move(newOffset - oldOffset);
    m_offset = newOffset;
}

const sf::Texture GraphicPiece::getTexture() const{
    return m_sprite.getTexture();
}

const sf::Texture* GraphicPiece::getTexturePtr() const{
    return m_texturePtr;
}

void GraphicPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}