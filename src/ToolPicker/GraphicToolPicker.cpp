#include "GraphicToolPicker.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include "../Board/LogicBoard.h"
#include "../Piece/PieceManager.h"


using namespace sigrid;

GraphicToolPicker::GraphicToolPicker(const std::vector<sf::Color> squareColors)
{
    m_backgroundColor = sf::Color{255,255,255,0};

    for(int i = 0; i < squareColors.size(); i++){
        m_squareColors.push_back(squareColors.at(i));
    }
}

void GraphicToolPicker::createGraphic(const sf::Vector2u& size){

    unsigned int numRows = m_squares.size();

    if(numRows == 0){
        return;
    }

    unsigned int numColumns = m_squares.at(0).size();
    
    if(numColumns == 0){
        return;
    }

    m_squareSize.x = size.x/numColumns;
    m_squareSize.y = size.y/numRows;

    if(m_squareSize.x < m_squareSize.y){
        m_squareSize.y = m_squareSize.x;
    }
    else{
        m_squareSize.x = m_squareSize.y;
    }

    m_offsetY = ((float)size.y-(float)numRows*m_squareSize.y)/2.f;

    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < numColumns; x++){

            m_squares.at(y).at(x) = std::make_unique<sf::RectangleShape>(m_squareSize);
            sf::Color squareColor = m_squareColors.at((x+y)%m_squareColors.size());
            m_squares.at(y).at(x)->setFillColor(squareColor);
            m_squares.at(y).at(x)->setPosition(sf::Vector2f(x*m_squareSize.x, y*m_squareSize.y+m_offsetY));

            auto toolIt = m_tools.find({x,y});
            if(toolIt != m_tools.end()){
                toolIt->second.setSize(m_squares.at(y).at(x)->getSize());
                toolIt->second.setPosition(m_squares.at(y).at(x)->getPosition());
            }
        }
    }

    bool success = m_texture.resize(size);
    assert(success);
    redrawTexture();
}

void GraphicToolPicker::setPosition(const sf::Vector2f& position){
    m_position = position;
}

bool GraphicToolPicker::contains(sf::Vector2i point) const{
    sf::Sprite sprite(m_texture.getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

sf::Vector2u GraphicToolPicker::getSize() const{
    return m_texture.getSize();
}

unsigned int GraphicToolPicker::getNumColumns() const{
    if(m_squares.size() == 0){
        return 0;
    }
    return m_squares.at(0).size();
}

unsigned int GraphicToolPicker::getNumRows() const{
    return m_squares.size();
}

std::optional<Coord> GraphicToolPicker::getSquareCoord(sf::Vector2i point){

    int columns = m_squares.at(0).size();
    int rows = m_squares.size();
    float width = (float)columns*m_squareSize.x;
    float height = (float)rows*m_squareSize.y;
    float x = (float)(point.x - m_position.x)*(float)columns/width;
    float y = (float)(point.y - m_position.y - m_offsetY)*(float)rows/height;

    if(x < 0.f){
        return std::nullopt;
    }
    if(x >= (float)columns){
        return std::nullopt;
    }
    if(y < 0.f){
        return std::nullopt;
    }
    if(y >= (float)rows){
        return std::nullopt;
    }
    return std::make_optional<Coord>((int)x,(int)y);
}

void GraphicToolPicker::addTool(const sf::Texture* texturePtr, const Coord& coord){

    bool addedSquares = false;
    while((int)m_squares.size() - 1 < coord.y){
        addSquareRow();
        addedSquares = true;
    }

    while((int)m_squares.at(0).size() - 1 < coord.x){
        addSquareColumn();
        addedSquares = true;
    }

    sf::RectangleShape tool;
    tool.setTexture(texturePtr);

    if(m_squares.at(coord.y).at(coord.x)){
        tool.setSize(m_squares.at(coord.y).at(coord.x)->getSize());
        tool.setPosition(m_squares.at(coord.y).at(coord.x)->getPosition());
    }

    m_tools.insert_or_assign(coord, tool);
}

void GraphicToolPicker::removeTool(const Coord& coord){
    m_tools.erase(coord);
    redrawTexture();
}

void GraphicToolPicker::moveTool(const Coord& fromCoord, const Coord& toCoord){

    auto it = m_tools.find(fromCoord);
    if(it == m_tools.end()){
        return;
    }

    bool addedSquares = false;
    while((int)m_squares.size() - 1 < toCoord.y){
        addSquareRow();
        addedSquares = true;
    }

    while((int)m_squares.at(0).size() - 1 < toCoord.x){
        addSquareColumn();
        addedSquares = true;
    }
    
    if(!m_squares.at(toCoord.y).at(toCoord.x)){
        std::cout << "Failed to move tool, square does not exist" << std::endl;
        return;
    }
    it->second.setPosition(m_squares.at(toCoord.y).at(toCoord.x)->getPosition());

    m_tools.insert_or_assign(toCoord, it->second);
    m_tools.erase(it);
    redrawTexture();
}

void GraphicToolPicker::removeLastColumn(){
    for(int y = 0; y < m_squares.size(); y++){
        m_squares.at(y).pop_back();
    }
    redrawTexture();
}

void GraphicToolPicker::redrawTexture(){

    m_texture.clear(m_backgroundColor);

    for(int y = 0; y < m_squares.size(); y++){
        for(int x = 0; x < m_squares.at(y).size(); x++){
            m_texture.draw(*m_squares[y][x]);
        }
    }

    for(auto& tool : m_tools){
        m_texture.draw(tool.second);
    }
    
}

void GraphicToolPicker::clear(){
    m_squares.clear();
    m_tools.clear();
}

void GraphicToolPicker::addSquareRow(){
    std::vector<std::unique_ptr<sf::RectangleShape>> row;

    int y = m_squares.size();

    if(y == 0){
        m_squares.push_back(std::move(row));
        return;
    }

    for(int x = 0; x < m_squares.at(0).size(); x++){

        std::unique_ptr<sf::RectangleShape> squarePtr;
        
        squarePtr = std::make_unique<sf::RectangleShape>(m_squareSize);
        sf::Color squareColor = m_squareColors.at((x+y)%m_squareColors.size());
        squarePtr->setFillColor(squareColor);
        squarePtr->setPosition(sf::Vector2f(x*m_squareSize.x, y*m_squareSize.y));

        row.push_back(std::move(squarePtr));
    }
    m_squares.push_back(std::move(row));
}

void GraphicToolPicker::addSquareColumn(){

    if(m_squares.size() == 0){
        return;
    }

    int x = m_squares.at(0).size();

    for(int y = 0; y < m_squares.size(); y++){
        std::unique_ptr<sf::RectangleShape> squarePtr;
                
        squarePtr = std::make_unique<sf::RectangleShape>(m_squareSize);
        sf::Color squareColor = m_squareColors.at((x+y)%m_squareColors.size());
        squarePtr->setFillColor(squareColor);
        squarePtr->setPosition(sf::Vector2f(x*m_squareSize.x, y*m_squareSize.y));

        m_squares.at(y).push_back(std::move(squarePtr));
    }

}

void GraphicToolPicker::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite sprite(m_texture.getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}