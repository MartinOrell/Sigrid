#include "LogicEntities.h"

#include <iostream>

using namespace sigrid;

LogicEntities::LogicEntities(){}

void LogicEntities::addEntity(const Coord& coord, const LogicEntity& entity){
    if(std::holds_alternative<LogicPiece>(entity)){
        m_pieces.insert({coord, std::get<LogicPiece>(entity)});
    }
    else if(std::holds_alternative<LogicCircle>(entity)){
        m_circles.insert({coord, std::get<LogicCircle>(entity)});
    }
    else if(std::holds_alternative<LogicArrow>(entity)){
        m_arrows.insert({coord, std::get<LogicArrow>(entity)});
    }
    else if(std::holds_alternative<LogicIcon>(entity)){
        m_icons.insert({coord, std::get<LogicIcon>(entity)});
    }
    else{
        std::cout << "LogicEntities: Unable to add Entity" << std::endl;
        std::cout << "Unknown index of variant: " << entity.index() << std::endl;
    }
}

void LogicEntities::removeEntity(const Coord& coord){
    m_pieces.erase(coord);
    m_circles.erase(coord);
    m_arrows.erase(coord);
    m_icons.erase(coord);
}

void LogicEntities::moveEntity(const Coord& fromCoord, const Coord& toCoord){
    {
        auto it = m_pieces.find(fromCoord);
        if(it != m_pieces.end()){
            m_pieces.insert({toCoord, it->second});
            m_pieces.erase(fromCoord);
            return;
        }
    }
    {
        auto it = m_circles.find(fromCoord);
        if(it != m_circles.end()){
            m_circles.insert({toCoord, it->second});
            m_circles.erase(fromCoord);
            return;
        }
    }
    {
        auto it = m_arrows.find(fromCoord);
        if(it != m_arrows.end()){
            m_arrows.insert({toCoord, it->second});
            m_arrows.erase(fromCoord);
            return;
        }
    }
    {
        auto it = m_icons.find(fromCoord);
        if(it != m_icons.end()){
            m_icons.insert({toCoord, it->second});
            m_icons.erase(fromCoord);
            return;
        }
    }
}

void LogicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
    m_arrows.clear();
    m_icons.clear();
}

std::optional<LogicEntity> LogicEntities::getEntityAt(const Coord& coord) const{

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

void LogicEntities::removeColumn(const int& columnId){
    for(auto it = m_pieces.begin(); it != m_pieces.end();){
        if(it->first.x == columnId){
            it = m_pieces.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_circles.begin(); it != m_circles.end();){
        if(it->first.x == columnId){
            it = m_circles.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_arrows.begin(); it != m_arrows.end();){
        if(it->first.x == columnId){
            it = m_arrows.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_icons.begin(); it != m_icons.end();){
        if(it->first.x == columnId){
            it = m_icons.erase(it);
        }
        else{
            it++;
        }
    }
}

void LogicEntities::removeRow(const int& rowId){
    for(auto it = m_pieces.begin(); it != m_pieces.end();){
        if(it->first.y == rowId){
            it = m_pieces.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_circles.begin(); it != m_circles.end();){
        if(it->first.y == rowId){
            it = m_circles.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_arrows.begin(); it != m_arrows.end();){
        if(it->first.y == rowId){
            it = m_arrows.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_icons.begin(); it != m_icons.end();){
        if(it->first.y == rowId){
            it = m_icons.erase(it);
        }
        else{
            it++;
        }
    }
}

template <typename T> void moveEntitiesRight_h(T& list){

    if(list.size() < 1){
        return;
    }

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
                list.erase(it);
            }
        }
    }
}

void LogicEntities::moveEntitiesRight(){
    moveEntitiesRight_h<std::map<Coord, LogicPiece>>(m_pieces);
    moveEntitiesRight_h<std::map<Coord, LogicCircle>>(m_circles);
    moveEntitiesRight_h<std::map<Coord, LogicArrow>>(m_arrows);
    moveEntitiesRight_h<std::map<Coord, LogicIcon>>(m_icons);
}

template <typename T> void moveEntitiesLeft_h(T& list){

    if(list.size() < 1){
        return;
    }

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
                list.erase(it);
            }
        }
    }
}

void LogicEntities::moveEntitiesLeft(){
    moveEntitiesLeft_h<std::map<Coord, LogicPiece>>(m_pieces);
    moveEntitiesLeft_h<std::map<Coord, LogicCircle>>(m_circles);
    moveEntitiesLeft_h<std::map<Coord, LogicArrow>>(m_arrows);
    moveEntitiesLeft_h<std::map<Coord, LogicIcon>>(m_icons);
}


template <typename T> void moveEntitiesUp_h(T& list){
    
    if(list.size() < 1){
        return;
    }

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
                list.erase(it);
            }
        }
    }
}
void LogicEntities::moveEntitiesUp(){
    moveEntitiesUp_h<std::map<Coord, LogicPiece>>(m_pieces);
    moveEntitiesUp_h<std::map<Coord, LogicCircle>>(m_circles);
    moveEntitiesUp_h<std::map<Coord, LogicArrow>>(m_arrows);
    moveEntitiesUp_h<std::map<Coord, LogicIcon>>(m_icons);
}

template <typename T> void moveEntitiesDown_h(T& list){

    if(list.size() < 1){
        return;
    }

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
                list.erase(it);
            }
        }
    }
}

void LogicEntities::moveEntitiesDown(){
    moveEntitiesDown_h<std::map<Coord, LogicPiece>>(m_pieces);
    moveEntitiesDown_h<std::map<Coord, LogicCircle>>(m_circles);
    moveEntitiesDown_h<std::map<Coord, LogicArrow>>(m_arrows);
    moveEntitiesDown_h<std::map<Coord, LogicIcon>>(m_icons);
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicEntities &entities)
{
    for(const auto& piece: entities.m_pieces){
        out << "\nPiece: " << piece.second.getColorId()
            << " " << piece.second.getNotation()
            << " " << piece.first.getNotation();
    }
    for(const auto& circle: entities.m_circles){
        out << "\nCircle: " << circle.second.getColorId()
            << " " << circle.first.getNotation();
    }
    for(const auto& arrow: entities.m_arrows){
        out << "\nArrow: " << arrow.second.getColorId()
            << " " << arrow.first.getNotation();
    }
    for(const auto& icon: entities.m_icons){
        out << "\nIcon: " << icon.second.getFilename()
            << " " << icon.first.getNotation();
    }
    return out;
}
