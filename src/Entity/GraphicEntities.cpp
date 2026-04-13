#include "GraphicEntities.h"

#include <iostream>

using namespace sigrid;

GraphicEntities::GraphicEntities(){}

void GraphicEntities::init(const sf::Vector2f& pieceSize, const float& circleDiameter, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr){

    m_pieceSize = pieceSize;
    m_circleDiameter = circleDiameter;
    m_pieceManagerPtr = pieceManagerPtr;
    m_arrowColorManagerPtr = arrowColorManagerPtr;

}

void GraphicEntities::addEntity(const Coord& coord, const sf::Vector2f position, const LogicEntity& entity){
    if(std::holds_alternative<LogicPiece>(entity)){
        if(m_pieceManagerPtr == nullptr){
            std::cout << "GraphicEntities: Failed to add piece" << std::endl;
            std::cout << "PieceManagerPtr is null" << std::endl;
            return;
        }

        auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(std::get<LogicPiece>(entity));

        if(graphicPiece_o == std::nullopt){
            std::cout << "GraphicEntities: Failed to add piece \""
                << std::get<LogicPiece>(entity).getNotation() << "\"" << std::endl;
            std::cout << "Piece not found in pieceManager" << std::endl;
            return;
        }

        GraphicPiece newPiece{graphicPiece_o.value()};
        newPiece.resize(m_pieceSize);
        newPiece.setPosition(position);
        m_pieces.insert({coord, newPiece});
    }
    else if(std::holds_alternative<LogicCircle>(entity)){
        if(m_arrowColorManagerPtr == nullptr){
            std::cout << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cout << "ColorManager does not exist to assign color" << std::endl;
            return;
        }

        int colorId = std::get<LogicCircle>(entity).getColorId();
        auto color_o = m_arrowColorManagerPtr->getSolidColor(colorId);
        if(color_o == std::nullopt){
            std::cout << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cout << "Color of colorId " << colorId << " not found" << std::endl;
            return;
        }

        GraphicCircle newCircle(color_o.value(), m_circleDiameter);
        newCircle.setPosition(position);
        m_circles.insert({coord, newCircle});
    }
}

void GraphicEntities::removeEntity(const Coord& coord){
    m_pieces.erase(coord);
    m_circles.erase(coord);
}

template<typename T> bool moveEntity_h(T& list, const Coord& fromCoord, const Coord& toCoord, const sf::Vector2f& newPosition){

    auto it = list.find(fromCoord);
    if(it == list.end()){
        return false;
    }
    it->second.setPosition(newPosition);
    list.insert({toCoord, it->second});
    list.erase(it);
    return true;
}

void GraphicEntities::moveEntity(const Coord& fromCoord, const Coord& toCoord, const sf::Vector2f& newPosition){
    
    if(moveEntity_h<std::map<Coord, GraphicPiece>>(m_pieces, fromCoord, toCoord, newPosition)){
        return;
    }
    moveEntity_h<std::map<Coord, GraphicCircle>>(m_circles, fromCoord, toCoord, newPosition);
}

void GraphicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
}

std::optional<GraphicEntity> GraphicEntities::getEntityAt(const Coord& coord) const{
    {
        auto it = m_pieces.find(coord);
        if(it != m_pieces.end()){
            return it->second;
        }
    }
    {
        auto it = m_circles.find(coord);
        if(it != m_circles.end()){
            return it->second;
        }
    }
    return std::nullopt;
}

template <typename T> void removeColumn_h(T& list, const int& columnId){

    for(auto it = list.begin(); it != list.end();){
        if(it->first.x == columnId){
            it = list.erase(it);
        }
        else{
            it++;
        }
    }
}

void GraphicEntities::removeColumn(const int& columnId){
    removeColumn_h<std::map<Coord, GraphicPiece>>(m_pieces, columnId);
    removeColumn_h<std::map<Coord, GraphicCircle>>(m_circles, columnId);
}

template <typename T> void removeRow_h(T& list, const int& rowId){

    for(auto it = list.begin(); it != list.end();){
        if(it->first.y == rowId){
            it = list.erase(it);
        }
        else{
            it++;
        }
    }
}

void GraphicEntities::removeRow(const int& rowId){
    removeRow_h<std::map<Coord, GraphicPiece>>(m_pieces, rowId);
    removeRow_h<std::map<Coord, GraphicCircle>>(m_circles, rowId);
}

template <typename T> void moveEntitiesRight_h(T& list, const float& tileWidth, const bool& isLeftToRight){

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(auto& entity: list){
        if(entity.first.x < minX){
            minX = entity.first.x;
        }
        if(entity.first.x > maxX){
            maxX = entity.first.x;
        }
        if(entity.first.y < minY){
            minY = entity.first.y;
        }
        if(entity.first.y > maxY){
            maxY = entity.first.y;
        }
    }

    for(int x = maxX; x >= minX; x--){
        for(int y = minY; y <= maxY; y++){
            auto it = list.find({x,y});
            if(it != list.end()){
                list.insert({{x+1,y},it->second});
                if(isLeftToRight){
                    list.at({x+1,y}).move({tileWidth, 0.f});
                }
                list.erase(it);
            }
        }
    }
}

void GraphicEntities::moveEntitiesRight(const float& tileWidth, const bool& isLeftToRight){
    moveEntitiesRight_h<std::map<Coord, GraphicPiece>>(m_pieces, tileWidth, isLeftToRight);
    moveEntitiesRight_h<std::map<Coord, GraphicCircle>>(m_circles, tileWidth, isLeftToRight);
}

template<typename T> void moveEntitiesLeft_h(T& list, const float& tileWidth, const bool& isLeftToRight){

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(auto& entity: list){
        if(entity.first.x < minX){
            minX = entity.first.x;
        }
        if(entity.first.x > maxX){
            maxX = entity.first.x;
        }
        if(entity.first.y < minY){
            minY = entity.first.y;
        }
        if(entity.first.y > maxY){
            maxY = entity.first.y;
        }
    }

    for(int x = minX; x <= maxX; x++){
        for(int y = minY; y <= maxY; y++){
            auto it = list.find({x,y});
            if(it != list.end()){
                list.insert({{x-1,y},it->second});
                if(isLeftToRight){
                    list.at({x-1,y}).move({-tileWidth, 0.f});
                }
                list.erase(it);
            }
        }
    }
}

void GraphicEntities::moveEntitiesLeft(const float& tileWidth, const bool& isLeftToRight){
    moveEntitiesLeft_h<std::map<Coord, GraphicPiece>>(m_pieces, tileWidth, isLeftToRight);
    moveEntitiesLeft_h<std::map<Coord, GraphicCircle>>(m_circles, tileWidth, isLeftToRight);
}

template <typename T> void moveEntitiesUp_h(T& list, const float& tileHeight, const bool& isTopToBottom){

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(auto& entity: list){
        if(entity.first.x < minX){
            minX = entity.first.x;
        }
        if(entity.first.x > maxX){
            maxX = entity.first.x;
        }
        if(entity.first.y < minY){
            minY = entity.first.y;
        }
        if(entity.first.y > maxY){
            maxY = entity.first.y;
        }
    }

    for(int y = minY; y <= maxY; y++){
        for(int x = minX; x <= maxX; x++){
            auto it = list.find({x,y});
            if(it != list.end()){
                list.insert({{x,y-1},it->second});
                if(isTopToBottom){
                    list.at({x,y-1}).move({0.f, -tileHeight});
                }
                list.erase(it);
            }
        }
    }
}

void GraphicEntities::moveEntitiesUp(const float& tileHeight, const bool& isTopToBottom){
    moveEntitiesUp_h<std::map<Coord, GraphicPiece>>(m_pieces, tileHeight, isTopToBottom);
    moveEntitiesUp_h<std::map<Coord, GraphicCircle>>(m_circles, tileHeight, isTopToBottom);
}

template <typename T> void moveEntitiesDown_h(T& list, const float& tileHeight, const bool& isTopToBottom){
    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(auto& entity: list){
        if(entity.first.x < minX){
            minX = entity.first.x;
        }
        if(entity.first.x > maxX){
            maxX = entity.first.x;
        }
        if(entity.first.y < minY){
            minY = entity.first.y;
        }
        if(entity.first.y > maxY){
            maxY = entity.first.y;
        }
    }

    for(int y = maxY; y >= minY; y--){
        for(int x = minX; x <= maxX; x++){
            auto it = list.find({x,y});
            if(it != list.end()){
                list.insert({{x,y+1},it->second});
                if(isTopToBottom){
                    list.at({x,y+1}).move({0.f, tileHeight});
                }
                list.erase(it);
            }
        }
    }
}

void GraphicEntities::moveEntitiesDown(const float& tileHeight, const bool& isTopToBottom){
    moveEntitiesDown_h<std::map<Coord, GraphicPiece>>(m_pieces, tileHeight, isTopToBottom);
    moveEntitiesDown_h<std::map<Coord, GraphicCircle>>(m_circles, tileHeight, isTopToBottom);
}

void GraphicEntities::move(const sf::Vector2f& offset){
    for(auto& piece : m_pieces){
        piece.second.move(offset);
    }

    for(auto& circle : m_circles){
        circle.second.move(offset);
    }
}

void GraphicEntities::setEntityPosition(const Coord& coord, const sf::Vector2f& position){
    {
        auto it = m_pieces.find(coord);
        if(it != m_pieces.end()){
            it->second.setPosition(position);
            return;
        }
    }
    {
        auto it = m_circles.find(coord);
        if(it != m_circles.end()){
            it->second.setPosition(position);
            return;
        }
    }
}

void GraphicEntities::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(auto& piece : m_pieces){
        target.draw(piece.second);
    }

    for(auto& circle : m_circles){
        target.draw(circle.second);
    }
}