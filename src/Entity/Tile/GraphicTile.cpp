#include "GraphicTile.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sigrid;

GraphicTile::GraphicTile(){}

GraphicTile::GraphicTile(const GraphicTile& src){
    m_shape = src.m_shape;

    if(src.m_highlightPtr){
        m_highlightPtr = std::make_unique<sf::RectangleShape>(src.m_highlightPtr->getSize());
        m_highlightPtr->setFillColor(src.m_highlightPtr->getFillColor());
        m_highlightPtr->setPosition(src.m_highlightPtr->getPosition());
    }
}

void GraphicTile::init(const sf::Vector2f& size, const sf::Color& color){
    m_shape.setSize(size);
    m_shape.setFillColor(color);
}

void GraphicTile::setPosition(const sf::Vector2f& topLeftPosition){
    m_shape.setPosition(topLeftPosition);
    if(m_highlightPtr){
        m_highlightPtr->setPosition(topLeftPosition);
    }
}

void GraphicTile::setTileColor(const sf::Color& color){
    m_shape.setFillColor(color);
}

void GraphicTile::setHighlightColor(const sf::Color& color){
    if(!m_highlightPtr){
        m_highlightPtr = std::make_unique<sf::RectangleShape>(m_shape.getSize());
        m_highlightPtr->setPosition(m_shape.getPosition());
    }
    m_highlightPtr->setFillColor(color);
}

void GraphicTile::removeHighlight(){
    m_highlightPtr.reset();
}

sf::Vector2f GraphicTile::getSize() const{
    return m_shape.getSize();
}

sf::Vector2f GraphicTile::getTopLeftPosition() const{
    return m_shape.getPosition();
}

sf::Vector2f GraphicTile::getCentrePosition() const{
    return m_shape.getPosition() + m_shape.getSize()/2.f;
}

float GraphicTile::getRightPosition() const{
    return m_shape.getPosition().x + m_shape.getSize().x;
}

float GraphicTile::getTopPosition() const{
    return m_shape.getPosition().y;
}

sf::Color GraphicTile::getColor() const{
    return m_shape.getFillColor();
}

GraphicTile& GraphicTile::operator =(const GraphicTile& rhs){
    m_shape = rhs.m_shape;
    if(rhs.m_highlightPtr){
        if(!m_highlightPtr){
            m_highlightPtr = std::make_unique<sf::RectangleShape>();
        }
        m_highlightPtr->setSize(rhs.m_highlightPtr->getSize());
        m_highlightPtr->setFillColor(rhs.m_highlightPtr->getFillColor());
        m_highlightPtr->setPosition(rhs.m_highlightPtr->getPosition());
    }
    else{
        if(m_highlightPtr){
            m_highlightPtr.reset();
        }
    }
    return *this;
}

void GraphicTile::move(const sf::Vector2f& offset){
    m_shape.move(offset);
    if(m_highlightPtr){
        m_highlightPtr->move(offset);
    }
}

void GraphicTile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
    if(m_highlightPtr){
        target.draw(*m_highlightPtr);
    }
}