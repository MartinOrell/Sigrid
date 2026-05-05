#include "GraphicEntities.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include "Piece/PieceManager.h"
#include "../Color/ColorManager.h"

using namespace sigrid;

GraphicEntities::GraphicEntities(){}

GraphicEntities& GraphicEntities::operator =(const GraphicEntities& rhs){
    m_pieces = rhs.m_pieces;
    m_circles = rhs.m_circles;
    m_arrows = rhs.m_arrows;

    m_icons.clear();//Temp fix since texture is saved in this class (should be saved elsewhere)

    m_pieceSize = rhs.m_pieceSize;
    m_circleDiameter = rhs.m_circleDiameter;
    
    m_pieceManagerPtr = rhs.m_pieceManagerPtr;
    m_arrowColorManagerPtr = rhs.m_arrowColorManagerPtr;

    return *this;
}

void GraphicEntities::addPieceManager(PieceManager* const pieceManagerPtr){
    m_pieceManagerPtr = pieceManagerPtr;
}

void GraphicEntities::addColorManager(ColorManager* const colorManagerPtr){
    m_arrowColorManagerPtr = colorManagerPtr;
}

void GraphicEntities::setPieceSize(const sf::Vector2f& pieceSize){
    m_pieceSize = pieceSize;
}

void GraphicEntities::setCircleDiameter(const float& diameter){
    m_circleDiameter = diameter;
}

void GraphicEntities::addEntity(const Coord& coord, const sf::Vector2f position, const LogicEntity& entity){
    if(std::holds_alternative<LogicPiece>(entity)){
        if(m_pieceManagerPtr == nullptr){
            std::cerr << "GraphicEntities: Failed to add piece" << std::endl;
            std::cerr << "PieceManagerPtr is null" << std::endl;
            return;
        }
        if(m_pieceSize.x == 0.f){
            std::cerr << "GraphicEntities: Failed to add piece" << std::endl;
            std::cerr << "Piece width is 0" << std::endl;
            return;
        }
        if(m_pieceSize.y == 0.f){
            std::cerr << "GraphicEntities: Failed to add piece" << std::endl;
            std::cerr << "Piece height is 0" << std::endl;
            return;
        }

        auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(std::get<LogicPiece>(entity));

        if(graphicPiece_o == std::nullopt){
            std::cerr << "GraphicEntities: Failed to add piece \""
                << std::get<LogicPiece>(entity).getNotation() << "\"" << std::endl;
            std::cerr << "Piece not found in pieceManager" << std::endl;
            return;
        }

        GraphicPiece newPiece{graphicPiece_o.value()};
        newPiece.resize(m_pieceSize);
        newPiece.setPosition(position);
        m_pieces.insert({coord, newPiece});
    }
    else if(std::holds_alternative<LogicCircle>(entity)){
        if(m_arrowColorManagerPtr == nullptr){
            std::cerr << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cerr << "ColorManager does not exist to assign color" << std::endl;
            return;
        }
        if(m_circleDiameter == 0.f){
            std::cerr << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cerr << "circle diameter is 0" << std::endl;
            return;
        }

        int colorId = std::get<LogicCircle>(entity).getColorId();
        auto color_o = m_arrowColorManagerPtr->getSolidColor(colorId);
        if(color_o == std::nullopt){
            std::cerr << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cerr << "Color of colorId " << colorId << " not found" << std::endl;
            return;
        }

        GraphicCircle newCircle(color_o.value(), m_circleDiameter);
        newCircle.setPosition(position);
        m_circles.insert({coord, newCircle});
    }
    else if(std::holds_alternative<LogicArrow>(entity)){

        sf::Color color;
        int colorId = std::get<LogicArrow>(entity).getColorId();
        auto color_o = m_arrowColorManagerPtr->getSolidColor(colorId);
        if(color_o == std::nullopt){
            color = sf::Color::Black;
        }
        else{
            color = color_o.value();
        }

        sf::Vector2f from = position;
        from.y += m_pieceSize.y*0.3f;
        sf::Vector2f to = position;
        to.y -= m_pieceSize.y*0.4f;

        GraphicArrow newArrow{};
        newArrow.setFromPosition(from);
        newArrow.setToPosition(to);
        newArrow.setColor(color);
        newArrow.setThickness(30);
        newArrow.setHeadSize(60);
        newArrow.init();
        m_arrows.insert({coord, newArrow});

    }
    else if(std::holds_alternative<LogicIcon>(entity)){

        if(!m_selectTexturePtr){
            m_selectTexturePtr = std::make_unique<sf::Texture>("res/icons/select_object.png");
        }

        sf::Vector2f iconPosition = position;
        iconPosition.x -= m_pieceSize.x/2.f;
        iconPosition.y -= m_pieceSize.y/2.f;

        Icon newIcon;
        newIcon.setSize(m_pieceSize);
        newIcon.setPosition(iconPosition);
        newIcon.setTexture(m_selectTexturePtr.get());
        m_icons.insert({coord, newIcon});
    }
    else{
        std::cerr << "GraphicEntities: Unable to add unknown entity" << std::endl;
        return;
    }
}

void GraphicEntities::removeEntity(const Coord& coord){
    m_pieces.erase(coord);
    m_circles.erase(coord);
    m_arrows.erase(coord);
    m_icons.erase(coord);
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
    else if(moveEntity_h<std::map<Coord, GraphicCircle>>(m_circles, fromCoord, toCoord, newPosition)){
        return;
    }
    else if(moveEntity_h<std::map<Coord, GraphicArrow>>(m_arrows, fromCoord, toCoord, newPosition)){
        return;
    }
    else{
        moveEntity_h<std::map<Coord, Icon>>(m_icons, fromCoord, toCoord, newPosition);
    }
}

void GraphicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
    m_arrows.clear();
    m_icons.clear();
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
    {
        auto it = m_arrows.find(coord);
        if(it != m_arrows.end()){
            return it->second;
        }
    }
    {
        auto it = m_icons.find(coord);
        if(it != m_icons.end()){
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
    removeColumn_h<std::map<Coord, GraphicArrow>>(m_arrows, columnId);
    removeColumn_h<std::map<Coord, Icon>>(m_icons, columnId);
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
    removeRow_h<std::map<Coord, GraphicArrow>>(m_arrows, rowId);
    removeRow_h<std::map<Coord, Icon>>(m_icons, rowId);
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
    moveEntitiesRight_h<std::map<Coord, GraphicArrow>>(m_arrows, tileWidth, isLeftToRight);
    moveEntitiesRight_h<std::map<Coord, Icon>>(m_icons, tileWidth, isLeftToRight);
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
    moveEntitiesLeft_h<std::map<Coord, GraphicArrow>>(m_arrows, tileWidth, isLeftToRight);
    moveEntitiesLeft_h<std::map<Coord, Icon>>(m_icons, tileWidth, isLeftToRight);
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
    moveEntitiesUp_h<std::map<Coord, GraphicArrow>>(m_arrows, tileHeight, isTopToBottom);
    moveEntitiesUp_h<std::map<Coord, Icon>>(m_icons, tileHeight, isTopToBottom);
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
    moveEntitiesDown_h<std::map<Coord, GraphicArrow>>(m_arrows, tileHeight, isTopToBottom);
    moveEntitiesDown_h<std::map<Coord, Icon>>(m_icons, tileHeight, isTopToBottom);
}

void GraphicEntities::move(const sf::Vector2f& offset){
    for(auto& piece : m_pieces){
        piece.second.move(offset);
    }

    for(auto& circle : m_circles){
        circle.second.move(offset);
    }

    for(auto& arrow : m_arrows){
        arrow.second.move(offset);
    }

    for(auto& icon : m_arrows){
        icon.second.move(offset);
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
    {
        auto it = m_arrows.find(coord);
        if(it != m_arrows.end()){
            it->second.setPosition(position);
            return;
        }
    }
    {
        auto it = m_icons.find(coord);
        if(it != m_icons.end()){
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

    for(auto& arrow : m_arrows){
        target.draw(arrow.second);
    }

    for(auto& icon : m_icons){
        target.draw(icon.second);
    }
}