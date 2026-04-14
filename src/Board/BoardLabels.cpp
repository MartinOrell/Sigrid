#include "BoardLabels.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include "../Font/FontManager.h"

#include <iostream>

using namespace sigrid;

BoardLabels::BoardLabels(){}

void BoardLabels::init(const bool& isInside, const bool& isOutside, const float& insideLabelSizeFactor, const float& outsideLabelSizeFactor, const std::string& fontFilename, FontManager* const fontManagerPtr){

    m_fontManagerPtr = fontManagerPtr;
    m_fontFilename = fontFilename;

    m_isInside = isInside;
    m_isVisible = isInside || isOutside;

    m_insideLabelSizeFactor = insideLabelSizeFactor;
    m_outsideLabelSizeFactor = outsideLabelSizeFactor;
}

bool BoardLabels::isVisible() const{
    return m_isVisible;
}

bool BoardLabels::isInsideLabelsVisible() const{
    return m_isVisible && m_isInside;
}

bool BoardLabels::isOutsideLabelsVisible() const{
    return m_isVisible && !m_isInside;
}

float BoardLabels::getInsideLabelSizeFactor() const{
    return m_insideLabelSizeFactor;
}

float BoardLabels::getOutsideLabelSizeFactor() const{
    return m_outsideLabelSizeFactor;
}

bool BoardLabels::addInsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor){

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cout << "BoardLabels: Failed to add inside bottom label" << std::endl;
        std::cout << "Font " << m_fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_bottomInsideCoordinateLabels.size();
    std::string s = std::to_string(i);
    s[0] = s[0] + 'a' - '0';
    unsigned int labelSize = m_insideLabelSizeFactor* tileSize.x;
    sf::Text label{*(fontPtr_o.value()), s, labelSize};

    sf::Vector2f position;
    position.x =
        tilePosition.x +
        tileSize.x -
        label.getLocalBounds().size.x*5/4;

    position.y =
        tilePosition.y +
        tileSize.y -
        labelSize*5/4;

    label.setPosition(position);

    label.setFillColor(sf::Color(100,100,100,255));
    label.setOutlineColor(tileColor);
    label.setOutlineThickness(2);

    m_bottomInsideCoordinateLabels.push_back(label);
    return true;
}

bool BoardLabels::addInsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor){

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cout << "BoardLabels: Failed to add inside left label" << std::endl;
        std::cout << "Font " << m_fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_leftInsideCoordinateLabels.size() + 1;
    std::string s = std::to_string(i);
    unsigned int labelSize = m_insideLabelSizeFactor* tileSize.y;
    sf::Text label{*(fontPtr_o.value()), s, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;

    //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
    position.x += tilePosition.x + (float)labelSize/16.f;
    position.y = tilePosition.y - (float)labelSize/4.f;
    
    label.setPosition(position);

    label.setFillColor(sf::Color(100,100,100,255));
    label.setOutlineColor(tileColor);
    
    label.setOutlineThickness(2);

    m_leftInsideCoordinateLabels.push_back(label);
    return true;
}

bool BoardLabels::addOutsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize){

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cout << "BoardLabels: Failed to add outside bottom label" << std::endl;
        std::cout << "Font " << m_fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_bottomOutsideCoordinateLabels.size();
    std::string s = std::to_string(i);
    s[0] = s[0] + 'a' - '0';
    unsigned int labelSize = m_outsideLabelSizeFactor*tileSize.x;
    sf::Text label{*(fontPtr_o.value()), s, labelSize};

    sf::Vector2f position;
    position.x =
        tilePosition.x +
        tileSize.x/2.f -
        label.getLocalBounds().size.x/2.f;

    position.y =
        tilePosition.y +
        tileSize.y -
        labelSize/4.f +
        5.f;
    
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);

    m_bottomOutsideCoordinateLabels.push_back(label);
    return true;
}

bool BoardLabels::addOutsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const float& edgeWidth){

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cout << "BoardLabels: Failed to add outside left label" << std::endl;
        std::cout << "Font " << m_fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_leftOutsideCoordinateLabels.size() + 1;
    std::string s = std::to_string(i);
    unsigned int labelSize = m_outsideLabelSizeFactor* tileSize.y;
    sf::Text label{*(fontPtr_o.value()), s, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;

    //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
    position.x = (edgeWidth-(float)labelSize/2.f)/2.f;
    position.y = tilePosition.y + tileSize.y/2.f - (float)labelSize*9.f/14.f;
    
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);

    m_leftOutsideCoordinateLabels.push_back(label);
    return true;
}

void BoardLabels::removeInsideLabels(){
    m_bottomInsideCoordinateLabels.clear();
    m_leftInsideCoordinateLabels.clear();
}

void BoardLabels::removeOutsideLabels(){
    m_bottomOutsideCoordinateLabels.clear();
    m_leftOutsideCoordinateLabels.clear();
}

void BoardLabels::addHorizontalLabel(const float& tileWidth, const bool& isLeftToRight){
    //currently not taking textWidth into consideration
    //currently not taking coordinates after z into consideration
    if(m_bottomInsideCoordinateLabels.size() > 0){
        sf::Text label{m_bottomInsideCoordinateLabels.back()};
        if(isLeftToRight){
            label.move({tileWidth, 0.f});
        }
        else{
            label.move({-tileWidth, 0.f});
        }
        std::string s = label.getString();
        s.at(0)++;
        label.setString(s);
        m_bottomInsideCoordinateLabels.push_back(label);
    }
    if(m_bottomOutsideCoordinateLabels.size() > 0){
        sf::Text label{m_bottomOutsideCoordinateLabels.back()};
        if(isLeftToRight){
            label.move({tileWidth, 0.f});
        }
        else{
            label.move({-tileWidth, 0.f});
        }
        std::string s = label.getString();
        s.at(0)++;
        label.setString(s);
        m_bottomOutsideCoordinateLabels.push_back(label);
    }
}

void BoardLabels::removeHorizontalLabel(){
    if(m_bottomInsideCoordinateLabels.size() > 0){
        m_bottomInsideCoordinateLabels.pop_back();
    }
    if(m_bottomOutsideCoordinateLabels.size() > 0){
        m_bottomOutsideCoordinateLabels.pop_back();
    }
}

void BoardLabels::addVerticalLabel(const float& tileHeight, const bool& isTopToBottom){
    //currently not taking textWidth into consideration

    if(m_leftInsideCoordinateLabels.size() > 0){
        sf::Text label{m_leftInsideCoordinateLabels.back()};
        if(isTopToBottom){
            label.move({0.f, tileHeight});
        }
        else{
            label.move({0.f, -tileHeight});
        }
        std::string s = label.getString();
        int i = stoi(s);
        i++;
        s = std::to_string(i);
        label.setString(s);
        m_leftInsideCoordinateLabels.push_back(label);
    }
    if(m_leftOutsideCoordinateLabels.size() > 0){
        sf::Text label{m_leftOutsideCoordinateLabels.back()};
        if(isTopToBottom){
            label.move({0.f, tileHeight});
        }
        else{
            label.move({0.f, -tileHeight});
        }
        std::string s = label.getString();
        int i = stoi(s);
        i++;
        s = std::to_string(i);
        label.setString(s);
        m_leftOutsideCoordinateLabels.push_back(label);
    }
}

void BoardLabels::removeVerticalLabel(){

    if(m_leftInsideCoordinateLabels.size() > 0){
        m_leftInsideCoordinateLabels.pop_back();
    }
    if(m_leftOutsideCoordinateLabels.size() > 0){
        m_leftOutsideCoordinateLabels.pop_back();
    }
}

void BoardLabels::show(){
    m_isVisible = true;
}

void BoardLabels::hide(){
    m_isVisible = false;
}

void BoardLabels::showInsideLabels(){
    m_isInside = true;
    m_isVisible = true;
}

void BoardLabels::showOutsideLabels(){
    m_isInside = false;
    m_isVisible = true;
}

void BoardLabels::hideInsideLabels(){
    if(m_isInside){
        m_isVisible = false;
    }
}

void BoardLabels::hideOutsideLabels(){
    if(!m_isInside){
        m_isVisible = false;
    }
}

void BoardLabels::setOutsideLabelSizeFactor(const float& size){
    m_outsideLabelSizeFactor = size;
}

void BoardLabels::moveLeftInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftInsideCoordinateLabels){
        label.move(offset);
    }
}

void BoardLabels::moveBottomInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomInsideCoordinateLabels){
        label.move(offset);
    }
}

void BoardLabels::moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftOutsideCoordinateLabels){
        label.move(offset);
    }
}

void BoardLabels::moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomOutsideCoordinateLabels){
        label.move(offset);
    }
}

void BoardLabels::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(!m_isVisible){
        return;
    }

    if(m_isInside){

        for(auto& label : m_bottomInsideCoordinateLabels){
            target.draw(label);
        }
        
        for(auto& label : m_leftInsideCoordinateLabels){
            target.draw(label);
        }
    }
    else{

        for(auto& label : m_bottomOutsideCoordinateLabels){
            target.draw(label);
        }
        
        for(auto& label : m_leftOutsideCoordinateLabels){
            target.draw(label);
        }
    }
}