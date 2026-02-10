#include "ToolItem.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include "../Action/Action.h"

using namespace sigrid;

ToolItem::ToolItem(const Action& action)
: m_action(action){
    m_boxShape.setFillColor(sf::Color(100,100,100));

    m_boxShape.setOutlineColor(sf::Color(0,0,0));
    m_boxShape.setOutlineThickness(-2.f);

    m_boxShape.setScale({1.f,-1.f});

    m_shape.setScale({1.f,-1.f});
}

void ToolItem::setSize(const sf::Vector2f& size){
    m_boxShape.setSize(size);
    m_shape.setSize(size);

    m_boxShape.setOrigin({0, size.y});
    m_boxShape.setPosition({0, size.y/2.f});

    m_shape.setOrigin(m_boxShape.getOrigin());
    m_shape.setPosition(m_boxShape.getPosition());
}

void ToolItem::setPosition(const sf::Vector2f& position){
    m_boxShape.setPosition(position);
    m_shape.setPosition(position);
}

void ToolItem::setTexture(const sf::Texture* texturePtr, bool resetRect){
    m_shape.setTexture(texturePtr, true);
}

bool ToolItem::isWithin(const sf::Vector2i& point){
    //Currently only look at x values
    if(point.x < m_boxShape.getPosition().x){
        return false;
    }
    if(point.x > m_boxShape.getPosition().x + m_boxShape.getSize().x){
        return false;
    }
    return true;
}

float ToolItem::getPositionRight(){
    return m_boxShape.getPosition().x + m_boxShape.getSize().x;
}

Action ToolItem::getAction(){
    return m_action;
}

void ToolItem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_boxShape);
    target.draw(m_shape);
}