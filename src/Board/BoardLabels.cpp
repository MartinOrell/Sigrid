#include "BoardLabels.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include "../Font/FontManager.h"
#include "../Coord/Coord.h"

#include <iostream>

using namespace sigrid;

BoardLabels::BoardLabels(){}

void BoardLabels::showLeftInside(){
    m_leftInsideCoordLabels.isVisible = true;
}

void BoardLabels::showBottomInside(){
    m_bottomInsideCoordLabels.isVisible = true;
}

void BoardLabels::showLeftOutside(){
    m_leftOutsideCoordLabels.isVisible = true;
}

void BoardLabels::showBottomOutside(){
    m_bottomOutsideCoordLabels.isVisible = true;
}

void BoardLabels::hideLeftInside(){
    m_leftInsideCoordLabels.isVisible = false;
}

void BoardLabels::hideBottomInside(){
    m_bottomInsideCoordLabels.isVisible = false;
}

void BoardLabels::hideLeftOutside(){
    m_leftOutsideCoordLabels.isVisible = false;
}

void BoardLabels::hideBottomOutside(){
    m_bottomOutsideCoordLabels.isVisible = false;
}

void BoardLabels::setLeftInsideSize(const float& size){
    m_leftInsideCoordLabels.size = size;
}

void BoardLabels::setBottomInsideSize(const float& size){
    m_bottomInsideCoordLabels.size = size;
}

void BoardLabels::setLeftOutsideSize(const float& size){
    m_leftOutsideCoordLabels.size = size;
}

void BoardLabels::setBottomOutsideSize(const float& size){
    m_bottomOutsideCoordLabels.size = size;
}

void BoardLabels::setLeftInsideFont(const std::string& fontFilename){
    m_leftInsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setBottomInsideFont(const std::string& fontFilename){
    m_bottomInsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setLeftOutsideFont(const std::string& fontFilename){
    m_leftOutsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setBottomOutsideFont(const std::string& fontFilename){
    m_bottomOutsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setFontManagerPtr(FontManager* const managerPtr){
    m_fontManagerPtr = managerPtr;
}

bool BoardLabels::isLeftInsideVisible() const{
    return m_leftInsideCoordLabels.isVisible;
}

bool BoardLabels::isBottomInsideVisible() const{
    return m_bottomInsideCoordLabels.isVisible;
}

bool BoardLabels::isLeftOutsideVisible() const{
    return m_leftOutsideCoordLabels.isVisible;
}

bool BoardLabels::isBottomOutsideVisible() const{
    return m_bottomOutsideCoordLabels.isVisible;
}

float BoardLabels::getLeftInsideLabelSize() const{
    return m_leftInsideCoordLabels.size;
}

float BoardLabels::getBottomInsideLabelSize() const{
    return m_bottomInsideCoordLabels.size;
}

float BoardLabels::getLeftOutsideLabelSize() const{
    return m_leftOutsideCoordLabels.size;
}

float BoardLabels::getBottomOutsideLabelSize() const{
    return m_bottomOutsideCoordLabels.size;
}

bool BoardLabels::addInsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor){

    if(m_bottomInsideCoordLabels.size == 0.f){
        std::cerr << "BoardLabels: Failed to add inside bottom label" << std::endl;
        std::cerr << "Inside label size factor is 0" << std::endl;
        return false;
    }

    if(m_bottomInsideCoordLabels.fontFilename.size() == 0){
        std::cerr << "BoardLabels: Failed to add inside bottom label" << std::endl;
        std::cerr << "Font file name not set" << std::endl;
        return false;
    }

    if(!m_fontManagerPtr){
        std::cerr << "BoardLabels: Failed to add inside bottom label" << std::endl;
        std::cerr << "Font Manager is nullptr" << std::endl;
        return false;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_bottomInsideCoordLabels.fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cerr << "BoardLabels: Failed to add inside bottom label" << std::endl;
        std::cerr << "Font " << m_bottomInsideCoordLabels.fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_bottomInsideCoordLabels.labels.size();
    std::string notation = notation::getColumnNotation(i);
    unsigned int labelSize = m_bottomInsideCoordLabels.size * tileSize.x;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

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

    m_bottomInsideCoordLabels.labels.push_back(label);
    return true;
}

bool BoardLabels::addInsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor){

    if(m_leftInsideCoordLabels.size == 0.f){
        std::cerr << "BoardLabels: Failed to add inside left label" << std::endl;
        std::cerr << "Inside label size factor is 0" << std::endl;
        return false;
    }

    if(m_leftInsideCoordLabels.fontFilename.size() == 0){
        std::cerr << "BoardLabels: Failed to add inside left label" << std::endl;
        std::cerr << "Font file name not set" << std::endl;
        return false;
    }

    if(!m_fontManagerPtr){
        std::cerr << "BoardLabels: Failed to add inside left label" << std::endl;
        std::cerr << "Font Manager is nullptr" << std::endl;
        return false;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_leftInsideCoordLabels.fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cerr << "BoardLabels: Failed to add inside left label" << std::endl;
        std::cerr << "Font " << m_leftInsideCoordLabels.fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_leftInsideCoordLabels.labels.size();
    std::string notation = notation::getRowNotation(i);
    unsigned int labelSize = m_leftInsideCoordLabels.size * tileSize.y;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;

    //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
    position.x += tilePosition.x + (float)labelSize/16.f;
    position.y = tilePosition.y - (float)labelSize/4.f;
    
    label.setPosition(position);

    label.setFillColor(sf::Color(100,100,100,255));
    label.setOutlineColor(tileColor);
    
    label.setOutlineThickness(2);

    m_leftInsideCoordLabels.labels.push_back(label);
    return true;
}

bool BoardLabels::addOutsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize){

    if(m_bottomOutsideCoordLabels.size == 0.f){
        std::cerr << "BoardLabels: Failed to add outside bottom label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_bottomOutsideCoordLabels.fontFilename.size() == 0){
        std::cerr << "BoardLabels: Failed to add outside bottom label" << std::endl;
        std::cerr << "Font file name not set" << std::endl;
        return false;
    }

    if(!m_fontManagerPtr){
        std::cerr << "BoardLabels: Failed to add outside bottom label" << std::endl;
        std::cerr << "Font Manager is nullptr" << std::endl;
        return false;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_bottomOutsideCoordLabels.fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cerr << "BoardLabels: Failed to add outside bottom label" << std::endl;
        std::cerr << "Font " << m_bottomOutsideCoordLabels.fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_bottomOutsideCoordLabels.labels.size();
    std::string notation = notation::getColumnNotation(i);
    unsigned int labelSize = m_bottomOutsideCoordLabels.size * tileSize.x;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

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

    m_bottomOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool BoardLabels::addOutsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const float& edgeWidth){

    if(m_leftOutsideCoordLabels.size == 0.f){
        std::cerr << "BoardLabels: Failed to add outside left label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_leftOutsideCoordLabels.fontFilename.size() == 0){
        std::cerr << "BoardLabels: Failed to add outside left label" << std::endl;
        std::cerr << "Font file name not set" << std::endl;
        return false;
    }

    if(!m_fontManagerPtr){
        std::cerr << "BoardLabels: Failed to add outside left label" << std::endl;
        std::cerr << "Font Manager is nullptr" << std::endl;
        return false;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_leftOutsideCoordLabels.fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cerr << "BoardLabels: Failed to add outside left label" << std::endl;
        std::cerr << "Font " << m_leftOutsideCoordLabels.fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_leftOutsideCoordLabels.labels.size();
    std::string notation = notation::getRowNotation(i);
    unsigned int labelSize = m_leftOutsideCoordLabels.size * tileSize.y;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;

    //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
    position.x = (edgeWidth-(float)labelSize/2.f)/2.f;
    position.y = tilePosition.y + tileSize.y/2.f - (float)labelSize*9.f/14.f;
    
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);

    m_leftOutsideCoordLabels.labels.push_back(label);
    return true;
}

void BoardLabels::removeLeftInsideLabels(){
    m_leftInsideCoordLabels.labels.clear();
}

void BoardLabels::removeBottomInsideLabels(){
    m_bottomInsideCoordLabels.labels.clear();
}

void BoardLabels::removeLeftOutsideLabels(){
    m_leftOutsideCoordLabels.labels.clear();
}

void BoardLabels::removeBottomOutsideLabels(){
    m_bottomOutsideCoordLabels.labels.clear();
}

void BoardLabels::addHorizontalLabel(const float& tileWidth, const bool& isLeftToRight){
    //currently not taking textWidth into consideration
    if(m_bottomInsideCoordLabels.labels.size() > 0){
        sf::Text label{m_bottomInsideCoordLabels.labels.back()};
        if(isLeftToRight){
            label.move({tileWidth, 0.f});
        }
        else{
            label.move({-tileWidth, 0.f});
        }
        int i = m_bottomInsideCoordLabels.labels.size();
        std::string notation = notation::getColumnNotation(i);
        label.setString(notation);
        m_bottomInsideCoordLabels.labels.push_back(label);
    }
    if(m_bottomOutsideCoordLabels.labels.size() > 0){
        sf::Text label{m_bottomOutsideCoordLabels.labels.back()};
        if(isLeftToRight){
            label.move({tileWidth, 0.f});
        }
        else{
            label.move({-tileWidth, 0.f});
        }
        int i = m_bottomOutsideCoordLabels.labels.size();
        std::string notation = notation::getColumnNotation(i);
        label.setString(notation);
        m_bottomOutsideCoordLabels.labels.push_back(label);
    }
}

void BoardLabels::removeHorizontalLabel(){
    if(m_bottomInsideCoordLabels.labels.size() > 0){
        m_bottomInsideCoordLabels.labels.pop_back();
    }
    if(m_bottomOutsideCoordLabels.labels.size() > 0){
        m_bottomOutsideCoordLabels.labels.pop_back();
    }
}

void BoardLabels::addVerticalLabel(const float& tileHeight, const bool& isTopToBottom){
    //currently not taking textWidth into consideration

    if(m_leftInsideCoordLabels.labels.size() > 0){
        sf::Text label{m_leftInsideCoordLabels.labels.back()};
        if(isTopToBottom){
            label.move({0.f, tileHeight});
        }
        else{
            label.move({0.f, -tileHeight});
        }
        int i = m_leftInsideCoordLabels.labels.size();
        std::string notation = notation::getRowNotation(i);
        label.setString(notation);
        m_leftInsideCoordLabels.labels.push_back(label);
    }
    if(m_leftOutsideCoordLabels.labels.size() > 0){
        sf::Text label{m_leftOutsideCoordLabels.labels.back()};
        if(isTopToBottom){
            label.move({0.f, tileHeight});
        }
        else{
            label.move({0.f, -tileHeight});
        }
        int i = m_leftOutsideCoordLabels.labels.size();
        std::string notation = notation::getRowNotation(i);
        label.setString(notation);
        m_leftOutsideCoordLabels.labels.push_back(label);
    }
}

void BoardLabels::removeVerticalLabel(){

    if(m_leftInsideCoordLabels.labels.size() > 0){
        m_leftInsideCoordLabels.labels.pop_back();
    }
    if(m_leftOutsideCoordLabels.labels.size() > 0){
        m_leftOutsideCoordLabels.labels.pop_back();
    }
}

void BoardLabels::moveLeftInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftInsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveBottomInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomInsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(m_leftInsideCoordLabels.isVisible){
        for(auto& label : m_leftInsideCoordLabels.labels){
            target.draw(label);
        }
    }

    if(m_bottomInsideCoordLabels.isVisible){
        for(auto& label : m_bottomInsideCoordLabels.labels){
            target.draw(label);
        }
    }

    if(m_leftOutsideCoordLabels.isVisible){
        for(auto& label : m_leftOutsideCoordLabels.labels){
            target.draw(label);
        }
    }

    if(m_bottomOutsideCoordLabels.isVisible){
        for(auto& label : m_bottomOutsideCoordLabels.labels){
            target.draw(label);
        }
    }
}