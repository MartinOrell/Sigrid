#include "sigrid/Board/BoardLabels.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

#include "sigrid/Font/FontManager.h"
#include "sigrid/utilities/Coord/Coord.h"

sigrid_list::Vector<sigrid::BoardLabelContainer> sigrid::BoardLabels::getContainer() const{

    sigrid_list::Vector<BoardLabelContainer> containers;

    {
        sigrid::BoardLabelContainer container = m_leftOutsideCoordLabels.getContainer();
        container.location.isInside = false;
        container.location.orientation = sigrid_coord::Orientation::LEFT;
        containers.push_back(container);
    }

    {
        sigrid::BoardLabelContainer container = m_rightOutsideCoordLabels.getContainer();
        container.location.isInside = false;
        container.location.orientation = sigrid_coord::Orientation::RIGHT;
        containers.push_back(container);
    }

    {
        sigrid::BoardLabelContainer container = m_topOutsideCoordLabels.getContainer();
        container.location.isInside = false;
        container.location.orientation = sigrid_coord::Orientation::TOP;
        containers.push_back(container);
    }

    {
        sigrid::BoardLabelContainer container = m_bottomOutsideCoordLabels.getContainer();
        container.location.isInside = false;
        container.location.orientation = sigrid_coord::Orientation::BOTTOM;
        containers.push_back(container);
    }

    {
        sigrid::BoardLabelContainer container = m_leftInsideCoordLabels.getContainer();
        container.location.isInside = true;
        container.location.orientation = sigrid_coord::Orientation::LEFT;
        containers.push_back(container);
    }

    {
        sigrid::BoardLabelContainer container = m_bottomInsideCoordLabels.getContainer();
        container.location.isInside = true;
        container.location.orientation = sigrid_coord::Orientation::BOTTOM;
        containers.push_back(container);
    }

    return containers;
}

void sigrid::BoardLabels::showLeftInside(){
    m_leftInsideCoordLabels.isVisible = true;
}

void sigrid::BoardLabels::showBottomInside(){
    m_bottomInsideCoordLabels.isVisible = true;
}

void sigrid::BoardLabels::showLeftOutside(){
    m_leftOutsideCoordLabels.isVisible = true;
}

void sigrid::BoardLabels::showRightOutside(){
    m_rightOutsideCoordLabels.isVisible = true;
}

void sigrid::BoardLabels::showTopOutside(){
    m_topOutsideCoordLabels.isVisible = true;
}

void sigrid::BoardLabels::showBottomOutside(){
    m_bottomOutsideCoordLabels.isVisible = true;
}

void sigrid::BoardLabels::hideLeftInside(){
    m_leftInsideCoordLabels.isVisible = false;
}

void sigrid::BoardLabels::hideBottomInside(){
    m_bottomInsideCoordLabels.isVisible = false;
}

void sigrid::BoardLabels::hideLeftOutside(){
    m_leftOutsideCoordLabels.isVisible = false;
}

void sigrid::BoardLabels::hideRightOutside(){
    m_rightOutsideCoordLabels.isVisible = false;
}

void sigrid::BoardLabels::hideTopOutside(){
    m_topOutsideCoordLabels.isVisible = false;
}

void sigrid::BoardLabels::hideBottomOutside(){
    m_bottomOutsideCoordLabels.isVisible = false;
}

void sigrid::BoardLabels::setLeftInsideSize(const float& size){
    m_leftInsideCoordLabels.labelSizeFactor = size;
}

void sigrid::BoardLabels::setBottomInsideSize(const float& size){
    m_bottomInsideCoordLabels.labelSizeFactor = size;
}

void sigrid::BoardLabels::setLeftOutsideSize(const float& size){
    m_leftOutsideCoordLabels.labelSizeFactor = size;
}

void sigrid::BoardLabels::setRightOutsideSize(const float& size){
    m_rightOutsideCoordLabels.labelSizeFactor = size;
}

void sigrid::BoardLabels::setTopOutsideSize(const float& size){
    m_topOutsideCoordLabels.labelSizeFactor = size;
}

void sigrid::BoardLabels::setBottomOutsideSize(const float& size){
    m_bottomOutsideCoordLabels.labelSizeFactor = size;
}

void sigrid::BoardLabels::setLeftInsideFont(const sigrid::String& fontFilename){
    m_leftInsideCoordLabels.fontFilename = fontFilename;
}

void sigrid::BoardLabels::setBottomInsideFont(const sigrid::String& fontFilename){
    m_bottomInsideCoordLabels.fontFilename = fontFilename;
}

void sigrid::BoardLabels::setLeftOutsideFont(const sigrid::String& fontFilename){
    m_leftOutsideCoordLabels.fontFilename = fontFilename;
}

void sigrid::BoardLabels::setRightOutsideFont(const sigrid::String& fontFilename){
    m_rightOutsideCoordLabels.fontFilename = fontFilename;
}

void sigrid::BoardLabels::setTopOutsideFont(const sigrid::String& fontFilename){
    m_topOutsideCoordLabels.fontFilename = fontFilename;
}

void sigrid::BoardLabels::setBottomOutsideFont(const sigrid::String& fontFilename){
    m_bottomOutsideCoordLabels.fontFilename = fontFilename;
}

void sigrid::BoardLabels::setLeftOutsideWorkWidth(const float& width){
    m_leftWorkWidth = width;
}

void sigrid::BoardLabels::setRightOutsideWorkWidth(const float& width){
    m_rightWorkWidth = width;
}

void sigrid::BoardLabels::setTopOutsideWorkHeight(const float& height){
    m_topWorkHeight = height;
}

void sigrid::BoardLabels::setBottomOutsideWorkHeight(const float& height){
    m_bottomWorkHeight = height;
}

void sigrid::BoardLabels::setFontManagerPtr(FontManager* const managerPtr){
    m_fontManagerPtr = managerPtr;
}

bool sigrid::BoardLabels::isLeftInsideVisible() const{
    return m_leftInsideCoordLabels.isVisible;
}

bool sigrid::BoardLabels::isBottomInsideVisible() const{
    return m_bottomInsideCoordLabels.isVisible;
}

bool sigrid::BoardLabels::isLeftOutsideVisible() const{
    return m_leftOutsideCoordLabels.isVisible;
}

bool sigrid::BoardLabels::isRightOutsideVisible() const{
    return m_rightOutsideCoordLabels.isVisible;
}

bool sigrid::BoardLabels::isTopOutsideVisible() const{
    return m_topOutsideCoordLabels.isVisible;
}

bool sigrid::BoardLabels::isBottomOutsideVisible() const{
    return m_bottomOutsideCoordLabels.isVisible;
}

float sigrid::BoardLabels::getLeftInsideLabelSize() const{
    return m_leftInsideCoordLabels.labelSizeFactor;
}

float sigrid::BoardLabels::getBottomInsideLabelSize() const{
    return m_bottomInsideCoordLabels.labelSizeFactor;
}

float sigrid::BoardLabels::getLeftOutsideLabelSize() const{
    return m_leftOutsideCoordLabels.labelSizeFactor;
}

float sigrid::BoardLabels::getRightOutsideLabelSize() const{
    return m_rightOutsideCoordLabels.labelSizeFactor;
}

float sigrid::BoardLabels::getTopOutsideLabelSize() const{
    return m_topOutsideCoordLabels.labelSizeFactor;
}

float sigrid::BoardLabels::getBottomOutsideLabelSize() const{
    return m_bottomOutsideCoordLabels.labelSizeFactor;
}

float sigrid::BoardLabels::getRightOutsideWorkWidth() const{
    return m_rightWorkWidth;
}

bool sigrid::BoardLabels::addLeftInsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize, const sigrid::Color& tileColor){

    if(m_leftInsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add inside left label" << std::endl;
        std::cerr << "Inside label size factor is 0" << std::endl;
        return false;
    }

    if(m_leftInsideCoordLabels.fontFilename.length() == 0){
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
    sigrid::String notation = sigrid_coord::getRowNotation(i);
    unsigned int labelSize = m_leftInsideCoordLabels.labelSizeFactor * tileSize.y;

    sigrid::GraphicText label;
    label.setFont(*(fontPtr_o.value()));
    label.setString(notation);
    label.setCharacterSize(labelSize);

    label.setOrigin({0.f,0.f});

    sigrid::Position_f position;

    //using labelSize instead of label.getLocalWidth() because localBounds has a weird gap
    position.x = tilePosition.x + (float)labelSize/16.f;
    position.y = tilePosition.y - (float)labelSize/4.f;
    
    label.setPosition(position);

    sigrid::Color fillColor;
    fillColor.setRGB(0x646464);
    label.setFillColor(fillColor);
    label.setOutlineColor(tileColor);
    
    label.setOutlineThickness(2);

    m_leftInsideCoordLabels.labels.push_back(label);
    return true;
}

bool sigrid::BoardLabels::addBottomInsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize, const sigrid::Color& tileColor){

    if(m_bottomInsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add inside bottom label" << std::endl;
        std::cerr << "Inside label size factor is 0" << std::endl;
        return false;
    }

    if(m_bottomInsideCoordLabels.fontFilename.length() == 0){
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
    sigrid::String notation = sigrid_coord::getColumnNotation(i);
    unsigned int labelSize = m_bottomInsideCoordLabels.labelSizeFactor * tileSize.x;

    sigrid::GraphicText label;
    label.setFont(*(fontPtr_o.value()));
    label.setString(notation);
    label.setCharacterSize(labelSize);

    sigrid::Position_f position;
    position.x =
        tilePosition.x +
        tileSize.x -
        label.getLocalWidth()*5/4;
    if(notation == "i" || notation == "l"){
        position.x -= label.getLocalWidth()*2.f;
    }

    position.y =
        tilePosition.y +
        tileSize.y -
        labelSize*5/4;

    label.setPosition(position);

    sigrid::Color fillColor;
    fillColor.setRGB(0x646464);
    label.setFillColor(fillColor);
    label.setOutlineColor(tileColor);
    label.setOutlineThickness(2);

    m_bottomInsideCoordLabels.labels.push_back(label);
    return true;
}

bool sigrid::BoardLabels::addLeftOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize){

    if(m_leftOutsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add outside left label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_leftOutsideCoordLabels.fontFilename.length() == 0){
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
    sigrid::String notation = sigrid_coord::getRowNotation(i);
    unsigned int labelSize = m_leftOutsideCoordLabels.labelSizeFactor * tileSize.y;

    sigrid::GraphicText label;
    label.setFont(*(fontPtr_o.value()));
    label.setString(notation);
    label.setCharacterSize(labelSize);

    label.setOrigin({0.f,0.f});

    sigrid::Position_f position;
    position.x = (m_leftWorkWidth-label.getLocalWidth()*5.f/4.f)/2.f;
    if(notation == "1"){
        position.x -= (float)label.getLocalWidth()/2.f;
    }
    position.y = tilePosition.y + tileSize.y/2.f - (float)labelSize*9.f/14.f;
    
    label.setPosition(position);

    sigrid::Color fillColor;
    fillColor.setRGB(0x000000);
    label.setFillColor(fillColor);

    m_leftOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool sigrid::BoardLabels::addRightOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize){

    if(m_rightOutsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add right outside label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_rightOutsideCoordLabels.fontFilename.length() == 0){
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
    sigrid::String notation = sigrid_coord::getRowNotation(i);
    unsigned int labelSize = m_rightOutsideCoordLabels.labelSizeFactor * tileSize.y;

    sigrid::GraphicText label;
    label.setFont(*(fontPtr_o.value()));
    label.setString(notation);
    label.setCharacterSize(labelSize);

    label.setOrigin({0.f,0.f});

    sigrid::Position_f position;
    position.x = tilePosition.x + tileSize.x + (m_rightWorkWidth-(float)label.getLocalWidth()*5.f/4.f)/2.f + 5.f;
    if(notation == "1"){
        position.x -= (float)label.getLocalWidth()/2.f;
    }
    position.y = tilePosition.y + tileSize.y/2.f - (float)labelSize*9.f/14.f;
    
    label.setPosition(position);
    sigrid::Color fillColor;
    fillColor.setRGB(0x000000);
    label.setFillColor(fillColor);

    m_rightOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool sigrid::BoardLabels::addTopOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize){

    if(m_topOutsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add top outside label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_topOutsideCoordLabels.fontFilename.length() == 0){
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
    sigrid::String notation = sigrid_coord::getColumnNotation(i);
    unsigned int labelSize = m_topOutsideCoordLabels.labelSizeFactor * tileSize.x;

    sigrid::GraphicText label;
    label.setFont(*(fontPtr_o.value()));
    label.setString(notation);
    label.setCharacterSize(labelSize);

    label.setOrigin({0.f,0.f});

    sigrid::Position_f position;
    position.x =
        tilePosition.x +
        tileSize.x/2.f -
        label.getLocalWidth()/2.f;

    position.y =
        tilePosition.y -
        m_topWorkHeight -
        labelSize/4.f;
    
    label.setPosition(position);
    sigrid::Color fillColor;
    fillColor.setRGB(0x000000);
    label.setFillColor(fillColor);

    m_topOutsideCoordLabels.labels.push_back(label);
    return true;
}

bool sigrid::BoardLabels::addBottomOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Position_f& tileSize){

    if(m_bottomOutsideCoordLabels.labelSizeFactor == 0.f){
        std::cerr << "BoardLabels: Failed to add outside bottom label" << std::endl;
        std::cerr << "Outside label size factor is 0" << std::endl;
        return false;
    }

    if(m_bottomOutsideCoordLabels.fontFilename.length() == 0){
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
    sigrid::String notation = sigrid_coord::getColumnNotation(i);
    unsigned int labelSize = m_bottomOutsideCoordLabels.labelSizeFactor * tileSize.x;

    sigrid::GraphicText label;
    label.setFont(*(fontPtr_o.value()));
    label.setString(notation);
    label.setCharacterSize(labelSize);

    sigrid::Position_f position;
    position.x =
        tilePosition.x +
        tileSize.x/2.f -
        label.getLocalWidth()/2.f;

    position.y =
        tilePosition.y +
        tileSize.y -
        labelSize/4.f +
        5.f;
    
    label.setPosition(position);
    sigrid::Color fillColor;
    fillColor.setRGB(0x000000);
    label.setFillColor(fillColor);

    m_bottomOutsideCoordLabels.labels.push_back(label);
    return true;
}

void sigrid::BoardLabels::removeLeftInsideLabels(){
    m_leftInsideCoordLabels.labels.clear();
}

void sigrid::BoardLabels::removeBottomInsideLabels(){
    m_bottomInsideCoordLabels.labels.clear();
}

void sigrid::BoardLabels::removeLeftOutsideLabels(){
    m_leftOutsideCoordLabels.labels.clear();
}

void sigrid::BoardLabels::removeRightOutsideLabels(){
    m_rightOutsideCoordLabels.labels.clear();
}

void sigrid::BoardLabels::removeTopOutsideLabels(){
    m_topOutsideCoordLabels.labels.clear();
}

void sigrid::BoardLabels::removeBottomOutsideLabels(){
    m_bottomOutsideCoordLabels.labels.clear();
}

void sigrid::BoardLabels::removeHorizontalLabel(){
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

void sigrid::BoardLabels::removeVerticalLabel(){

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

void sigrid::BoardLabels::moveLeftInsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftInsideCoordLabels.labels){
        label.move(offset);
    }
}

void sigrid::BoardLabels::moveBottomInsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomInsideCoordLabels.labels){
        label.move(offset);
    }
}

void sigrid::BoardLabels::moveLeftOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void sigrid::BoardLabels::moveRightOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_rightOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void sigrid::BoardLabels::moveTopOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_topOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void sigrid::BoardLabels::moveBottomOutsideLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomOutsideCoordLabels.labels){
        label.move(offset);
    }
}

void sigrid::BoardLabels::draw(sf::RenderTarget& target, sf::RenderStates states) const{

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