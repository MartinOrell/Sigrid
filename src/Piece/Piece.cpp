#include "Piece.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;

Piece::Piece(sf::Vector2u size, const sf::Texture* texturePtr, const int colorId, std::string notation)
: m_logicPiece(notation, colorId)
, m_graphicPiece(size, texturePtr){}

void Piece::setPosition(sf::Vector2f position){
    m_graphicPiece.setPosition(position);
}

bool Piece::contains(sf::Vector2i point) const{
    return m_graphicPiece.contains(point);
}

const LogicPiece& Piece::logic() const{
    return m_logicPiece;
}

const GraphicPiece& Piece::graphic() const{
    return m_graphicPiece;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_graphicPiece);
}

