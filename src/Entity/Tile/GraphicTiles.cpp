#include "GraphicTiles.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include "../../Color/ColorManager.h"

using namespace sigrid;

GraphicTiles::GraphicTiles(){}

void GraphicTiles::init(const int& columns, const int& rows, const sf::Vector2f& tileSize, ColorManager* const tileColorManagerPtr, ColorManager* const highlightColorManagerPtr, const sf::Vector2f& topLeftPosition, const bool& isLeftToRight, const bool& isTopToBottom){
    m_columns = columns;
    m_rows = rows;
    m_tileSize = tileSize;
    m_tileColorManagerPtr = tileColorManagerPtr;
    m_highlightColorManagerPtr = highlightColorManagerPtr;

    for(int y = 0; y < m_rows; y++){
        for(int x = 0; x < m_columns; x++){
            
            sf::Vector2f position;
            if(isLeftToRight){
                position.x = (float)(x*m_tileSize.x);
            }
            else{
                position.x = (float)((m_columns-x-1)*m_tileSize.x);
            }
            position.x += topLeftPosition.x;
            if(isTopToBottom){
                position.y = (float)(y*m_tileSize.y);
            }
            else{
                position.y = (float)((m_rows-y-1)*m_tileSize.y);
            }
            position.y += topLeftPosition.y;

            GraphicTile newTile;
            newTile.init(m_tileSize, sf::Color::White);
            newTile.setPosition(position);
            m_tiles.insert({{x,y}, newTile});
        }
    }
}

void GraphicTiles::setTilePosition(const Coord& coord, const sf::Vector2f& position){
    m_tiles.at(coord).setPosition(position);
}

void GraphicTiles::setTileColor(const Coord& coord, const int& colorId){
    
    auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);

    if(color_o != std::nullopt){
        m_tiles.at(coord).setTileColor(color_o.value());
    }
}

void GraphicTiles::setHighlightColor(const Coord& coord, const int& colorId){

    auto color_o = m_highlightColorManagerPtr->getTransparentColor(colorId);

    if(color_o != std::nullopt){
        m_tiles.at(coord).setHighlightColor(color_o.value());
    }
}

void GraphicTiles::removeHighlight(const Coord& coord){
    m_tiles.at(coord).removeHighlight();
}

void GraphicTiles::addColumnRight(const std::vector<int>& repeatTileColorIds, const bool& isLeftToRight){

    m_columns++;
    int x = m_columns-1;
    for(int y = 0; y < m_rows; y++){
        auto leftIt = m_tiles.find({x-1,y});
        if(leftIt != m_tiles.end()){

            sf::Vector2f position = leftIt->second.getTopLeftPosition();
            if(isLeftToRight){
                position.x += m_tileSize.x;
            }

            sf::Color color;
            if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
                color = sf::Color::White;
            }
            else{
                auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
                if(color_o == std::nullopt){
                    color = sf::Color::White;
                }
                else{
                    color = color_o.value();
                }
            }

            GraphicTile newTile;
            newTile.init(m_tileSize, color);
            newTile.setPosition(position);
            m_tiles.insert({{x,y}, newTile});

        }
    }
    if(!isLeftToRight){
        for(int x = 0; x < m_columns-1; x++){
            for(int y = 0; y < m_rows; y++){
                auto it = m_tiles.find({x,y});
                if(it != m_tiles.end()){
                    it->second.move(sf::Vector2f{m_tileSize.x, 0.f});
                }
            }
        }
    }
}

void GraphicTiles::addColumnLeft(const std::vector<int>& repeatTileColorIds, const bool& isLeftToRight){

    m_columns++;
    {
        int x = m_columns-1;
        for(int y = 0; y < m_rows; y++){
            auto leftIt = m_tiles.find({x-1,y});
            if(leftIt != m_tiles.end()){
                GraphicTile newTile = leftIt->second;
                if(isLeftToRight){
                    newTile.move(sf::Vector2f{m_tileSize.x,0.f});
                }
                m_tiles.insert({{x,y},newTile});
            }
        }
    }

    for(int x = m_columns-2; x > 0; x--){
        for(int y = 0; y < m_rows; y++){
            auto currentIt = m_tiles.find({x,y});
            auto leftIt = m_tiles.find({x-1,y});
            if(leftIt != m_tiles.end()){
                if(currentIt == m_tiles.end()){
                    GraphicTile tile = leftIt->second;
                    if(isLeftToRight){
                        tile.move(sf::Vector2f{m_tileSize.x,0.f});
                    }
                    m_tiles.insert({{x,y}, tile});
                }
                else{
                    currentIt->second = leftIt->second;
                    if(isLeftToRight){
                        currentIt->second.move(sf::Vector2f{m_tileSize.x,0.f});
                    }
                }
            }
        }
    }
    
    
    {
        int x = 0;
        for(int y = 0; y < m_rows; y++){
            auto currentIt = m_tiles.find({x,y});
            if(currentIt != m_tiles.end()){
                sf::Vector2f position = currentIt->second.getTopLeftPosition();
                if(!isLeftToRight){
                    position.x += m_tileSize.x;
                }

                sf::Color color;
                if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
                    color = sf::Color::White;
                }
                else{
                    auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
                    if(color_o == std::nullopt){
                        color = sf::Color::White;
                    }
                    else{
                        color = color_o.value();
                    }
                }
                
                GraphicTile newTile;
                newTile.init(m_tileSize, color);
                newTile.setPosition(position);
                currentIt->second = newTile;
            }
        }
    }
}

void GraphicTiles::removeColumnRight(const bool& isLeftToRight){
    m_columns--;

    int x = m_columns;
    for(int y = 0; y < m_rows; y++){
        m_tiles.erase({x,y});
    }

    if(!isLeftToRight){
        for(auto& tile: m_tiles){
            tile.second.move(sf::Vector2f{-m_tileSize.x, 0.f});
        }
    }
}

void GraphicTiles::removeColumnLeft(const bool& isLeftToRight){

    m_columns--;
    for(int x = 0; x < m_columns; x++){
        for(int y=0; y<m_rows; y++){
            auto currentIt = m_tiles.find({x,y});
            auto rightIt = m_tiles.find({x+1,y});

            if(rightIt != m_tiles.end()){
                if(currentIt == m_tiles.end()){
                    GraphicTile tile = rightIt->second;
                    if(isLeftToRight){
                        tile.move(sf::Vector2f{-m_tileSize.x,0.f});
                    }
                    m_tiles.insert({{x,y},tile});
                }
                else{
                    currentIt->second = rightIt->second;
                    if(isLeftToRight){
                        currentIt->second.move(sf::Vector2f{-m_tileSize.x,0.f});
                    }
                }
            }
        }
    }

    {
        int x = m_columns;
        for(int y = 0; y < m_rows; y++){
            m_tiles.erase({x,y});
        }
    }
}

void GraphicTiles::addRowUp(const std::vector<int>& repeatTileColorIds, const bool& isTopToBottom){

    m_rows++;
    {
        int y = m_rows-1;
        for(int x = 0; x < m_columns; x++){
            auto topIt = m_tiles.find({x,y-1});
            if(topIt != m_tiles.end()){
                GraphicTile newTile = topIt->second;
                if(isTopToBottom){
                    newTile.move(sf::Vector2f{0.f, m_tileSize.y});
                }
                m_tiles.insert({{x,y},newTile});
            }
        }
    }

    for(int y = m_rows-2; y > 0; y--){
        for(int x = 0; x < m_columns; x++){
            auto currentIt = m_tiles.find({x,y});
            auto topIt = m_tiles.find({x,y-1});
            if(topIt != m_tiles.end()){
                if(currentIt == m_tiles.end()){
                    GraphicTile tile = topIt->second;
                    if(isTopToBottom){
                        tile.move(sf::Vector2f{0.f, m_tileSize.y});
                    }
                    m_tiles.insert({{x,y}, tile});
                }
                else{
                    currentIt->second = topIt->second;
                    if(isTopToBottom){
                        currentIt->second.move(sf::Vector2f{0.f, m_tileSize.y});
                    }
                }
            }
        }
    }
    
    
    {
        int y = 0;
        for(int x = 0; x < m_columns; x++){
            auto currentIt = m_tiles.find({x,y});
            if(currentIt != m_tiles.end()){
                sf::Vector2f position = currentIt->second.getTopLeftPosition();
                if(!isTopToBottom){
                    position.y += m_tileSize.y;
                }

                sf::Color color;
                if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
                    color = sf::Color::White;
                }
                else{
                    auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
                    if(color_o == std::nullopt){
                        color = sf::Color::White;
                    }
                    else{
                        color = color_o.value();
                    }
                }
                
                GraphicTile newTile;
                newTile.init(m_tileSize, color);
                newTile.setPosition(position);
                currentIt->second = newTile;
            }
        }
    }
}

void GraphicTiles::addRowDown(const std::vector<int>& repeatTileColorIds, const bool& isTopToBottom){

    m_rows++;
    int y = m_rows-1;
    for(int x = 0; x < m_columns; x++){
        auto topIt = m_tiles.find({x,y-1});
        if(topIt != m_tiles.end()){

            sf::Vector2f position = topIt->second.getTopLeftPosition();
            if(isTopToBottom){
                position.y += m_tileSize.y;
            }

            sf::Color color;
            if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
                color = sf::Color::White;
            }
            else{
                auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
                if(color_o == std::nullopt){
                    color = sf::Color::White;
                }
                else{
                    color = color_o.value();
                }
            }

            GraphicTile newTile;
            newTile.init(m_tileSize, color);
            newTile.setPosition(position);
            m_tiles.insert({{x,y}, newTile});

        }
    }
    if(!isTopToBottom){
        for(int y = 0; y < m_rows-1; y++){
            for(int x = 0; x < m_columns; x++){
                auto it = m_tiles.find({x,y});
                if(it != m_tiles.end()){
                    it->second.move(sf::Vector2f{0.f, m_tileSize.y});
                }
            }
        }
    }
}

void GraphicTiles::removeRowUp(const bool& isTopToBottom){

    m_rows--;
    for(int y = 0; y < m_rows; y++){
        for(int x = 0; x < m_columns; x++){
            auto currentIt = m_tiles.find({x,y});
            auto downIt = m_tiles.find({x,y+1});

            if(downIt != m_tiles.end()){
                if(currentIt == m_tiles.end()){
                    GraphicTile tile = downIt->second;
                    if(!isTopToBottom){
                        tile.move(sf::Vector2f{0.f, -m_tileSize.y});
                    }
                    m_tiles.insert({{x,y},tile});
                }
                else{
                    currentIt->second = downIt->second;
                    if(!isTopToBottom){
                        currentIt->second.move(sf::Vector2f{0.f, -m_tileSize.y});
                    }
                }
            }
        }
    }

    {
        int y = m_rows;
        for(int x = 0; x < m_columns; x++){
            m_tiles.erase({x,y});
        }
    }
}

void GraphicTiles::removeRowDown(const bool& isTopToBottom){

    m_rows--;
    int y = m_rows;
    for(int x = 0; x < m_columns; x++){
        m_tiles.erase({x,y});
    }

    if(!isTopToBottom){
        for(auto& tile: m_tiles){
            tile.second.move(sf::Vector2f{0.f, -m_tileSize.y});
        }
    }
}

int GraphicTiles::getNumColumns() const{
    return m_columns;
}

int GraphicTiles::getNumRows() const{
    return m_rows;
}

float GraphicTiles::getTileWidth() const{
    return m_tileSize.x;
}

float GraphicTiles::getTileHeight() const{
    return m_tileSize.y;
}

sf::Vector2f GraphicTiles::getTileSize() const{
    return m_tileSize;
}

std::optional<sf::Vector2f> GraphicTiles::getTileTopLeftPosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getTopLeftPosition();
}

std::optional<sf::Vector2f> GraphicTiles::getTileCentrePosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getCentrePosition();
}

std::optional<float> GraphicTiles::getTileRightPosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getRightPosition();
}

std::optional<float> GraphicTiles::getTileTopPosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getTopPosition();
}

std::optional<sf::Color> GraphicTiles::getTileColor(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getColor();

}

void GraphicTiles::move(const sf::Vector2f& offset){
    for(auto& tile: m_tiles){
        tile.second.move(offset);
    }
}

void GraphicTiles::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(auto& tile: m_tiles){
        target.draw(tile.second);
    }
}