#include "BoardLabels.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

#include "Font/FontManager.h"
#include "Coord/Coord.h"

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

void BoardLabels::showRightOutside(){
    m_rightOutsideCoordLabels.isVisible = true;
}

void BoardLabels::showTopOutside(){
    m_topOutsideCoordLabels.isVisible = true;
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

void BoardLabels::hideRightOutside(){
    m_rightOutsideCoordLabels.isVisible = false;
}

void BoardLabels::hideTopOutside(){
    m_topOutsideCoordLabels.isVisible = false;
}

void BoardLabels::hideBottomOutside(){
    m_bottomOutsideCoordLabels.isVisible = false;
}

void BoardLabels::setLeftInsideSize(const float& size){
    m_leftInsideCoordLabels.labelSizeFactor = size;
}

void BoardLabels::setBottomInsideSize(const float& size){
    m_bottomInsideCoordLabels.labelSizeFactor = size;
}

void BoardLabels::setLeftOutsideSize(const float& size){
    m_leftOutsideCoordLabels.labelSizeFactor = size;
}

void BoardLabels::setRightOutsideSize(const float& size){
    m_rightOutsideCoordLabels.labelSizeFactor = size;
}

void BoardLabels::setTopOutsideSize(const float& size){
    m_topOutsideCoordLabels.labelSizeFactor = size;
}

void BoardLabels::setBottomOutsideSize(const float& size){
    m_bottomOutsideCoordLabels.labelSizeFactor = size;
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

void BoardLabels::setRightOutsideFont(const std::string& fontFilename){
    m_rightOutsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setTopOutsideFont(const std::string& fontFilename){
    m_topOutsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setBottomOutsideFont(const std::string& fontFilename){
    m_bottomOutsideCoordLabels.fontFilename = fontFilename;
}

void BoardLabels::setLeftOutsideWorkWidth(const float& width){
    m_leftWorkWidth = width;
}

void BoardLabels::setRightOutsideWorkWidth(const float& width){
    m_rightWorkWidth = width;
}

void BoardLabels::setTopOutsideWorkHeight(const float& height){
    m_topWorkHeight = height;
}

void BoardLabels::setBottomOutsideWorkHeight(const float& height){
    m_bottomWorkHeight = height;
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

bool BoardLabels::isRightOutsideVisible() const{
    return m_rightOutsideCoordLabels.isVisible;
}

bool BoardLabels::isTopOutsideVisible() const{
    return m_topOutsideCoordLabels.isVisible;
}

bool BoardLabels::isBottomOutsideVisible() const{
    return m_bottomOutsideCoordLabels.isVisible;
}

float BoardLabels::getLeftInsideLabelSize() const{
    return m_leftInsideCoordLabels.labelSizeFactor;
}

float BoardLabels::getBottomInsideLabelSize() const{
    return m_bottomInsideCoordLabels.labelSizeFactor;
}

float BoardLabels::getLeftOutsideLabelSize() const{
    return m_leftOutsideCoordLabels.labelSizeFactor;
}

float BoardLabels::getRightOutsideLabelSize() const{
    return m_rightOutsideCoordLabels.labelSizeFactor;
}

float BoardLabels::getTopOutsideLabelSize() const{
    return m_topOutsideCoordLabels.labelSizeFactor;
}

float BoardLabels::getBottomOutsideLabelSize() const{
    return m_bottomOutsideCoordLabels.labelSizeFactor;
}

float BoardLabels::getRightOutsideWorkWidth() const{
    return m_rightWorkWidth;
}

bool BoardLabels::addLeftInsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor){

    if(m_leftInsideCoordLabels.labelSizeFactor == 0.f){
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
    std::string notation = sigrid_coord::getRowNotation(i);
    unsigned int labelSize = m_leftInsideCoordLabels.labelSizeFactor * tileSize.y;
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

bool BoardLabels::addBottomInsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor){

    if(m_bottomInsideCoordLabels.labelSizeFactor == 0.f){
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
    std::string notation = sigrid_coord::getColumnNotation(i);
    unsigned int labelSize = m_bottomInsideCoordLabels.labelSizeFactor * tileSize.x;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

    sf::Vector2f position;
    position.x =
        tilePosition.x +
        tileSize.x -
        label.getLocalBounds().size.x*5/4;
    if(notation == "i" || notation == "l"){
        position.x -= label.getLocalBounds().size.x*2.f;
    }

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

bool BoardLabels::addLeftOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize){

    if(m_leftOutsideCoordLabels.labelSizeFactor == 0.f){
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
    std::string notation = sigrid_coord::getRowNotation(i);
    unsigned int labelSize = m_leftOutsideCoordLabels.labelSizeFactor * tileSize.y;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;
    position.x = (m_leftWorkWidth-(float)label.getLocalBounds().size.x*5.f/4.f)/2.f;
    if(notation == "1"){
        position.x -= (float)label.getLocalBounds().size.x/2.f;
    }
    position.y = tilePosition.y + tileSize.y/2.f - (float)labelSize*9.f/14.f;
    
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);

    m_leftOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool BoardLabels::addRightOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize){

    if(m_rightOutsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add right outside label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_rightOutsideCoordLabels.fontFilename.size() == 0){
        std::cerr << "BoardLabels: Failed to add right outside label" << std::endl;
        std::cerr << "Font file name not set" << std::endl;
        return false;
    }

    if(!m_fontManagerPtr){
        std::cerr << "BoardLabels: Failed to add right outside label" << std::endl;
        std::cerr << "Font Manager is nullptr" << std::endl;
        return false;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_rightOutsideCoordLabels.fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cerr << "BoardLabels: Failed to add right outside label" << std::endl;
        std::cerr << "Font " << m_rightOutsideCoordLabels.fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_rightOutsideCoordLabels.labels.size();
    std::string notation = sigrid_coord::getRowNotation(i);
    unsigned int labelSize = m_rightOutsideCoordLabels.labelSizeFactor * tileSize.y;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;
    position.x = tilePosition.x + tileSize.x + (m_rightWorkWidth-(float)label.getLocalBounds().size.x*5.f/4.f)/2.f + 5.f;
    if(notation == "1"){
        position.x -= (float)label.getLocalBounds().size.x/2.f;
    }
    position.y = tilePosition.y + tileSize.y/2.f - (float)labelSize*9.f/14.f;
    
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);

    m_rightOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool BoardLabels::addTopOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize){

    if(m_topOutsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add top outside label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_topOutsideCoordLabels.fontFilename.size() == 0){
        std::cerr << "BoardLabels: Failed to add top outside label" << std::endl;
        std::cerr << "Font file name not set" << std::endl;
        return false;
    }

    if(!m_fontManagerPtr){
        std::cerr << "BoardLabels: Failed to add top outside label" << std::endl;
        std::cerr << "Font Manager is nullptr" << std::endl;
        return false;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_topOutsideCoordLabels.fontFilename);
    if(fontPtr_o == std::nullopt){
        std::cerr << "BoardLabels: Failed to add top outside label" << std::endl;
        std::cerr << "Font " << m_topOutsideCoordLabels.fontFilename << " not found" << std::endl;
        return false;
    }

    int i = m_topOutsideCoordLabels.labels.size();
    std::string notation = sigrid_coord::getColumnNotation(i);
    unsigned int labelSize = m_topOutsideCoordLabels.labelSizeFactor * tileSize.x;
    sf::Text label{*(fontPtr_o.value()), notation, labelSize};

    label.setOrigin({0.f,0.f});

    sf::Vector2f position;
    position.x =
        tilePosition.x +
        tileSize.x/2.f -
        label.getLocalBounds().size.x/2.f;

    position.y =
        tilePosition.y -
        m_topWorkHeight -
        labelSize/4.f;
    
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);

    m_topOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool BoardLabels::addBottomOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize){

    if(m_bottomOutsideCoordLabels.labelSizeFactor == 0.f){
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
    std::string notation = sigrid_coord::getColumnNotation(i);
    unsigned int labelSize = m_bottomOutsideCoordLabels.labelSizeFactor * tileSize.x;
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

void BoardLabels::removeLeftInsideLabels(){
    m_leftInsideCoordLabels.labels.clear();
}

void BoardLabels::removeBottomInsideLabels(){
    m_bottomInsideCoordLabels.labels.clear();
}

void BoardLabels::removeLeftOutsideLabels(){
    m_leftOutsideCoordLabels.labels.clear();
}

void BoardLabels::removeRightOutsideLabels(){
    m_rightOutsideCoordLabels.labels.clear();
}

void BoardLabels::removeTopOutsideLabels(){
    m_topOutsideCoordLabels.labels.clear();
}

void BoardLabels::removeBottomOutsideLabels(){
    m_bottomOutsideCoordLabels.labels.clear();
}

void BoardLabels::removeHorizontalLabel(){
    if(m_bottomInsideCoordLabels.labels.size() > 0){
        m_bottomInsideCoordLabels.labels.pop_back();
    }
    if(m_topOutsideCoordLabels.labels.size() > 0){
        m_topOutsideCoordLabels.labels.pop_back();
    }
    if(m_bottomOutsideCoordLabels.labels.size() > 0){
        m_bottomOutsideCoordLabels.labels.pop_back();
    }
}

void BoardLabels::removeVerticalLabel(){

    if(m_leftInsideCoordLabels.labels.size() > 0){
        m_leftInsideCoordLabels.labels.pop_back();
    }
    if(m_leftOutsideCoordLabels.labels.size() > 0){
        m_leftOutsideCoordLabels.labels.pop_back();
    }
    if(m_rightOutsideCoordLabels.labels.size() > 0){
        m_rightOutsideCoordLabels.labels.pop_back();
    }
}

void BoardLabels::moveLeftInsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftInsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveBottomInsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomInsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveLeftOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveRightOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_rightOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveTopOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_topOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void BoardLabels::moveBottomOutsideLabels(const sf::Vector2f& offset){
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

    if(m_rightOutsideCoordLabels.isVisible){
        for(auto& label : m_rightOutsideCoordLabels.labels){
            target.draw(label);
        }
    }

    if(m_topOutsideCoordLabels.isVisible){
        for(auto& label : m_topOutsideCoordLabels.labels){
            target.draw(label);
        }
    }

    if(m_bottomOutsideCoordLabels.isVisible){
        for(auto& label : m_bottomOutsideCoordLabels.labels){
            target.draw(label);
        }
    }
}