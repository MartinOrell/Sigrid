#include "LayoutGrid.h"

using namespace sigrid;

LayoutGrid::LayoutGrid(){}

void LayoutGrid::setPx(const int& x, const float& px){

    while(x >= m_xCoords.size()){
        m_xCoords.push_back(0.f);
    }
    m_xCoords.at(x) = px;
}

void LayoutGrid::setPy(const int& y, const float& py){

    while(y >= m_yCoords.size()){
        m_yCoords.push_back(0.f);
    }
    m_yCoords.at(y) = py;
}

void LayoutGrid::setPxIfLess(const int& x, const float& px){

    while(x >= m_xCoords.size()){
        m_xCoords.push_back(0.f);
    }
    if(px < m_xCoords.at(x)){
        m_xCoords.at(x) = px;
    }
}

void LayoutGrid::setPyIfLess(const int& y, const float& py){

    while(y >= m_yCoords.size()){
        m_yCoords.push_back(0.f);
    }
    if(py < m_yCoords.at(y)){
        m_yCoords.at(y) = py;
    }
}

void LayoutGrid::setPxIfGreater(const int& x, const float& px){

    while(x >= m_xCoords.size()){
        m_xCoords.push_back(0.f);
    }
    if(px > m_xCoords.at(x)){
        m_xCoords.at(x) = px;
    }
}

void LayoutGrid::setPyIfGreater(const int& y, const float& py){

    while(y >= m_yCoords.size()){
        m_yCoords.push_back(0.f);
    }
    if(py > m_yCoords.at(y)){
        m_yCoords.at(y) = py;
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

float LayoutGrid::getPx(const int& x){

    if(x >= m_xCoords.size()){
        return 0.f;
    }
    return m_xCoords.at(x);
}

float LayoutGrid::getPy(const int& y){

    if(y >= m_yCoords.size()){
        return 0.f;
    }
    return m_yCoords.at(y);
}

std::optional<sf::Vector2f> LayoutGrid::getPosition(const unsigned int& id){

    auto it = m_objects.find(id);
    if(it == m_objects.end()){
        return std::nullopt;
    }

    int fromX = it->second.from.x;
    if(fromX >= m_xCoords.size()){
        return std::nullopt;
    }
    float fromPx = m_xCoords.at(fromX);

    int fromY = it->second.from.y;
    if(fromY >= m_yCoords.size()){
        return std::nullopt;
    }
    float fromPy = m_yCoords.at(fromY);

    return sf::Vector2f{fromPx, fromPy};
}

std::optional<sf::Vector2u> LayoutGrid::getSizeU(const unsigned int& id){

    auto it = m_objects.find(id);
    if(it == m_objects.end()){
        return std::nullopt;
    }

    int fromX = it->second.from.x;
    if(fromX >= m_xCoords.size()){
        return std::nullopt;
    }
    float fromPx = m_xCoords.at(fromX);

    int toX = it->second.to.x;
    if(toX >= m_xCoords.size()){
        return std::nullopt;
    }
    float toPx = m_xCoords.at(toX);

    float width = toPx - fromPx;

    if(width < 0){
        return std::nullopt;
    }

    int fromY = it->second.from.y;
    if(fromY >= m_yCoords.size()){
        return std::nullopt;
    }
    float fromPy = m_yCoords.at(fromY);

    int toY = it->second.to.y;
    if(toY >= m_yCoords.size()){
        return std::nullopt;
    }
    float toPy = m_yCoords.at(toY);

    float height = toPy - fromPy;

    if(height < 0){
        return std::nullopt;
    }

    return sf::Vector2u{(unsigned int)width, (unsigned int)height};
}

std::optional<float> LayoutGrid::getWidth(const int& fromX, const int& toX){

    if(fromX >= m_xCoords.size()){
        return std::nullopt;
    }
    if(toX >= m_xCoords.size()){
        return std::nullopt;
    }

    float fromPx = m_xCoords.at(fromX);
    float toPx = m_xCoords.at(toX);
    return toPx - fromPx;
}

std::optional<float> LayoutGrid::getHeight(const int& fromY, const int& toY){

    if(fromY >= m_yCoords.size()){
        return std::nullopt;
    }
    if(toY >= m_yCoords.size()){
        return std::nullopt;
    }

    float fromPy = m_yCoords.at(fromY);
    float toPy = m_yCoords.at(toY);
    return toPy - fromPy;
}