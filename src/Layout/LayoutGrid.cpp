#include "LayoutGrid.h"

using namespace sigrid;

LayoutGrid::LayoutGrid(){}

void LayoutGrid::setPx(const unsigned int& x, const float& px){

    while(x >= m_xCoords.size()){
        m_xCoords.push_back(0.f);
    }
    auto& xCoord = m_xCoords.at(x).value().get();

    xCoord = px;
}

void LayoutGrid::setPy(const unsigned int& y, const float& py){

    while(y >= m_yCoords.size()){
        m_yCoords.push_back(0.f);
    }
    auto& yCoord = m_yCoords.at(y).value().get();
    
    yCoord = py;
}

void LayoutGrid::setPxIfLess(const unsigned int& x, const float& px){

    while(x >= m_xCoords.size()){
        m_xCoords.push_back(0.f);
    }
    auto& xCoord = m_xCoords.at(x).value().get();

    if(px < xCoord){
        xCoord = px;
    }
}

void LayoutGrid::setPyIfLess(const unsigned int& y, const float& py){

    while(y >= m_yCoords.size()){
        m_yCoords.push_back(0.f);
    }
    auto& yCoord = m_yCoords.at(y).value().get();

    if(py < yCoord){
        yCoord = py;
    }
}

void LayoutGrid::setPxIfGreater(const unsigned int& x, const float& px){

    while(x >= m_xCoords.size()){
        m_xCoords.push_back(0.f);
    }
    auto& xCoord = m_xCoords.at(x).value().get();

    if(px > xCoord){
        xCoord = px;
    }
}

void LayoutGrid::setPyIfGreater(const unsigned int& y, const float& py){

    while(y >= m_yCoords.size()){
        m_yCoords.push_back(0.f);
    }
    auto& yCoord = m_yCoords.at(y).value().get();

    if(py > yCoord){
        yCoord = py;
    }
}

void LayoutGrid::setFromXCoord(const unsigned int& id, const int& x){

    auto it = m_objects.find(id);
    if(it != m_objects.end()){
        it->second.from.x = x;
        return;
    }
    
    CoordPair pair;
    pair.from.x = x;
    m_objects.insert({id, pair});
}

void LayoutGrid::setFromYCoord(const unsigned int& id, const int& y){

    auto it = m_objects.find(id);
    if(it != m_objects.end()){
        it->second.from.y = y;
        return;
    }
    
    CoordPair pair;
    pair.from.y = y;
    m_objects.insert({id, pair});
}

void LayoutGrid::setToXCoord(const unsigned int& id, const int& x){

    auto it = m_objects.find(id);
    if(it != m_objects.end()){
        it->second.to.x = x;
        return;
    }

    CoordPair pair;
    pair.to.x = x;
    m_objects.insert({id, pair});
}

void LayoutGrid::setToYCoord(const unsigned int& id, const int& y){

    auto it = m_objects.find(id);
    if(it != m_objects.end()){
        it->second.to.y = y;
        return;
    }

    CoordPair pair;
    pair.to.y = y;
    m_objects.insert({id, pair});
}

std::optional<float> LayoutGrid::getPx(const int& x) const{

    auto xCoord_o = m_xCoords.at(x);
    if(xCoord_o == std::nullopt){
        return std::nullopt;
    }
    return xCoord_o.value().get();
}

std::optional<float> LayoutGrid::getPy(const int& y) const{

    auto yCoord_o = m_yCoords.at(y);
    if(yCoord_o == std::nullopt){
        return std::nullopt;
    }
    return yCoord_o.value().get();
}

std::optional<sf::Vector2f> LayoutGrid::getTopLeftPosition(const unsigned int& id) const{

    auto it = m_objects.find(id);
    if(it == m_objects.end()){
        return std::nullopt;
    }

    int fromX = it->second.from.x;
    auto fromPx_o = m_xCoords.at(fromX);
    if(fromPx_o == std::nullopt){
        return std::nullopt;
    }

    int fromY = it->second.from.y;
    auto fromPy_o = m_yCoords.at(fromY);
    if(fromPy_o == std::nullopt){
        return std::nullopt;
    }

    const float& fromPx = fromPx_o.value().get();
    const float& fromPy = fromPy_o.value().get();

    return sf::Vector2f{fromPx, fromPy};
}

std::optional<sf::Vector2f> LayoutGrid::getCenterPosition(const unsigned int& id) const{

    auto it = m_objects.find(id);
    if(it == m_objects.end()){
        return std::nullopt;
    }

    int fromX = it->second.from.x;
    auto fromPx_o = m_xCoords.at(fromX);
    if(fromPx_o == std::nullopt){
        return std::nullopt;
    }

    int fromY = it->second.from.y;
    auto fromPy_o = m_yCoords.at(fromY);
    if(fromPy_o == std::nullopt){
        return std::nullopt;
    }

    int toX = it->second.to.x;
    auto toPx_o = m_xCoords.at(toX);
    if(toPx_o == std::nullopt){
        return std::nullopt;
    }

    int toY = it->second.to.y;
    auto toPy_o = m_yCoords.at(toY);
    if(toPy_o == std::nullopt){
        return std::nullopt;
    }

    const float& fromPx = fromPx_o.value().get();
    const float& fromPy = fromPy_o.value().get();
    const float& toPx = toPx_o.value().get();
    const float& toPy = toPy_o.value().get();

    float px = fromPx + (toPx - fromPx)/2.f;
    float py = fromPy + (toPy - fromPy)/2.f;

    return sf::Vector2f{px, py};
}

std::optional<sf::Vector2f> LayoutGrid::getSize(const unsigned int& id) const{

    auto it = m_objects.find(id);
    if(it == m_objects.end()){
        return std::nullopt;
    }

    int fromX = it->second.from.x;
    int toX = it->second.to.x;

    auto width_o = getWidth(fromX, toX);
    if(width_o == std::nullopt){
        return std::nullopt;
    }
    const float width = width_o.value();

    int fromY = it->second.from.y;
    int toY = it->second.to.y;

    auto height_o = getHeight(fromY, toY);
    if(height_o == std::nullopt){
        return std::nullopt;
    }
    const float height = height_o.value();

    return sf::Vector2f{width, height};
}

std::optional<sf::Vector2u> LayoutGrid::getSizeU(const unsigned int& id) const{

    auto size_o = getSize(id);
    if(size_o == std::nullopt){
        return std::nullopt;
    }
    return sf::Vector2u{(unsigned int)size_o.value().x, (unsigned int)size_o.value().y};
}

std::optional<float> LayoutGrid::getWidth(const int& fromX, const int& toX) const{

    auto fromPx_o = m_xCoords.at(fromX);
    if(fromPx_o == std::nullopt){
        return std::nullopt;
    }

    auto toPx_o = m_xCoords.at(toX);
    if(toPx_o == std::nullopt){
        return std::nullopt;
    }

    const float& fromPx = fromPx_o.value().get();
    const float& toPx = toPx_o.value().get();

    const float width = toPx - fromPx;

    if(width < 0.f){
        return std::nullopt;
    }

    return width;
}

std::optional<float> LayoutGrid::getHeight(const int& fromY, const int& toY) const{

    auto fromPy_o = m_yCoords.at(fromY);
    if(fromPy_o == std::nullopt){
        return std::nullopt;
    }

    auto toPy_o = m_yCoords.at(toY);
    if(toPy_o == std::nullopt){
        return std::nullopt;
    }

    const float& fromPy = fromPy_o.value().get();
    const float& toPy = toPy_o.value().get();

    const float height = toPy - fromPy;

    if(height < 0.f){
        return std::nullopt;
    }

    return height;
}