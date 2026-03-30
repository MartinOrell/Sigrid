#include "GraphicBoard.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include "LogicBoard.h"
#include "../Entity/Piece/PieceManager.h"


using namespace sigrid;

GraphicBoard::GraphicBoard()
: m_scale{1.f}
, m_backgroundColor{sf::Color{255,255,255,255}}
, m_leftEdgeWidth{0}
, m_rightEdgeWidth{0}
, m_topEdgeWidth{0}
, m_bottomEdgeWidth{0}
, m_isLeftToRight{true}
, m_isTopToBottom{false}{}

void GraphicBoard::init(const LogicBoard& logicBoard, const BoardDesignContainer& config, PieceManager* const pieceManagerPtr, ColorManager* const tileColorManagerPtr, ColorManager* const arrowColorManagerPtr){

    m_arrowColorManagerPtr = arrowColorManagerPtr;
    m_showLabels = config.labelsInside || config.labelsOutside;

    m_isCoordinateLabelsInside = config.labelsInside;
    m_insideLabelSizeFactor = config.insideLabelSize;
    m_outsideLabelSizeFactor = config.outsideLabelSize;
    m_borderWidth = config.borderWidth;
    m_showPlayerToMoveToken = config.playerToMoveToken;
    m_tileLayerPtr = std::make_unique<GraphicTiles>();
    m_tileLayerPtr->init(logicBoard.getNumColumns(), logicBoard.getNumRows(), {config.tileWidth, config.tileHeight}, tileColorManagerPtr, arrowColorManagerPtr, {(float)m_leftEdgeWidth, (float)m_topEdgeWidth},m_isLeftToRight,m_isTopToBottom);
    m_pieceLayerPtr = std::make_unique<GraphicEntities>();
    m_pieceLayerPtr->init({config.tileWidth, config.tileHeight}, config.circleDiameter, pieceManagerPtr, arrowColorManagerPtr);
    m_arrowLayerPtr = std::make_unique<GraphicArrows>();
    m_arrowLayerPtr->init(config.arrowThickness, config.arrowHeadSize, arrowColorManagerPtr);

    if(!m_font.openFromFile(config.labelFont)){
        std::cout << "GraphicBoard: Failed to open font: " << config.labelFont << std::endl;
    }

    for(int y = 0; y < logicBoard.getNumRows(); y++){
        for(int x = 0; x < logicBoard.getNumColumns(); x++){

            auto tile_o = logicBoard.getTile({x,y});
            if(tile_o.has_value()){
                int colorId = tile_o->getColorId();
                m_tileLayerPtr->setTileColor({x,y},colorId);
            }

            auto entity_o = logicBoard.getEntityAt({x,y});
            if(entity_o != std::nullopt){
                auto position_o = m_tileLayerPtr->getTileCentrePosition({x,y});
                m_pieceLayerPtr->addEntity({x,y},position_o.value(),entity_o.value());
            }
        }
    }

    if(m_showLabels){
        if(m_isCoordinateLabelsInside){
            addInsideLabels();
        }
        else{
            unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileWidth();
            unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileHeight();

            setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);
            addOutsideLabels();
        }
    }

    if(m_showPlayerToMoveToken){
        m_rightEdgeWidth = (unsigned int)(0.5*m_tileLayerPtr->getTileHeight());
        initPlayerToMoveToken();
    }

    if(config.border){

        m_borderPtr = std::make_unique<RectangleBorder>();
        sf::Vector2f boardArea;
        boardArea.x = config.tileWidth* logicBoard.getNumColumns();
        boardArea.y = config.tileHeight* logicBoard.getNumRows();
        m_borderPtr->init(config.border, config.borderWidth, {(float)m_leftEdgeWidth, (float)m_topEdgeWidth},boardArea);
    }

    if(m_borderPtr && m_borderPtr->isVisible()){
        moveTiles({m_borderPtr->getWidth(), m_borderPtr->getWidth()});
    }
    
    m_texturePtr = std::make_unique<sf::RenderTexture>();
    resizeTexture();
    redrawTexture();

}

GraphicBoard& GraphicBoard::operator=(const GraphicBoard& rhs){
    
    if(rhs.m_texturePtr){
        if(!m_texturePtr){
            m_texturePtr = std::make_unique<sf::RenderTexture>();
        }
        if(!(m_texturePtr->resize(rhs.m_texturePtr->getSize()))){
            std::cout << "GraphicBoard: Failed to resize texture during assignment operation" << std::endl;
        }
    }

    m_position = rhs.m_position;
    m_scale = rhs.m_scale;

    m_leftEdgeWidth = rhs.m_leftEdgeWidth;
    m_rightEdgeWidth = rhs.m_rightEdgeWidth;
    m_topEdgeWidth = rhs.m_topEdgeWidth;
    m_bottomEdgeWidth = rhs.m_bottomEdgeWidth;

    m_backgroundColor = rhs.m_backgroundColor;

    if(rhs.m_tileLayerPtr){
        if(!m_tileLayerPtr){
            m_tileLayerPtr = std::make_unique<GraphicTiles>();
        }
        *m_tileLayerPtr = *(rhs.m_tileLayerPtr);
    }

    if(rhs.m_pieceLayerPtr){
        if(!m_pieceLayerPtr){
            m_pieceLayerPtr = std::make_unique<GraphicEntities>();
        }
        *m_pieceLayerPtr = *(rhs.m_pieceLayerPtr);
    }

    if(rhs.m_arrowLayerPtr){
        if(!m_arrowLayerPtr){
            m_arrowLayerPtr = std::make_unique<GraphicArrows>();
        }
        *m_arrowLayerPtr = *(rhs.m_arrowLayerPtr);
    }

    if(rhs.m_dragArrowPtr){
        if(!m_dragArrowPtr){
            m_dragArrowPtr = std::make_unique<GraphicArrow>();
        }
        *m_dragArrowPtr = *(rhs.m_dragArrowPtr);
    }

    if(rhs.m_selectHighlight){
        if(!m_selectHighlight){
            m_selectHighlight = std::make_unique<GraphicTile>();
        }
        *m_selectHighlight = *(rhs.m_selectHighlight);
    }

    m_arrowColorManagerPtr = rhs.m_arrowColorManagerPtr;

    m_showLabels = rhs.m_showLabels;
    m_isCoordinateLabelsInside = rhs.m_isCoordinateLabelsInside;
    m_font = rhs.m_font;
    m_leftOutsideCoordinateLabels = rhs.m_leftOutsideCoordinateLabels;
    m_bottomOutsideCoordinateLabels = rhs.m_bottomOutsideCoordinateLabels;
    m_bottomInsideCoordinateLabels = rhs.m_bottomInsideCoordinateLabels;
    m_leftInsideCoordinateLabels = rhs.m_leftInsideCoordinateLabels;

    m_borderWidth = rhs.m_borderWidth;

    if(rhs.m_borderPtr){
        if(!m_borderPtr){
            m_borderPtr = std::make_unique<RectangleBorder>();
        }
        *m_borderPtr = *(rhs.m_borderPtr);
    }

    m_insideLabelSizeFactor = rhs.m_insideLabelSizeFactor;
    m_outsideLabelSizeFactor = rhs.m_outsideLabelSizeFactor;

    m_showPlayerToMoveToken = rhs.m_showPlayerToMoveToken;

    if(rhs.m_playerToMoveToken){
        if(!m_playerToMoveToken){
            m_playerToMoveToken = std::make_unique<sf::CircleShape>();
        }
        *m_playerToMoveToken = *(rhs.m_playerToMoveToken);
    }

    m_isLeftToRight = rhs.m_isLeftToRight;
    m_isTopToBottom = rhs.m_isTopToBottom;

    redrawTexture();

    return *this;
}

sf::Vector2f GraphicBoard::getTileSize() const{
    if(m_tileLayerPtr){
        return m_tileLayerPtr->getTileSize();
    }
    return {0.0, 0.0};
}

void GraphicBoard::setPosition(sf::Vector2f position){
    m_position = position;
}

void GraphicBoard::setPositionX(float x){
    m_position.x = x;
}

void GraphicBoard::setScale(const float scale){
    m_scale = scale;
}

unsigned int GraphicBoard::getImageWidth() const{
    return m_texturePtr->getSize().x;
}

unsigned int GraphicBoard::getImageHeight() const{
    return m_texturePtr->getSize().y;
}

float GraphicBoard::getDisplayWidth() const{
    return (float)m_texturePtr->getSize().x*m_scale;
}

float GraphicBoard::getDisplayHeight() const{
    return (float)m_texturePtr->getSize().y*m_scale;
}

std::optional<GraphicEntity> GraphicBoard::getEntityAt(const Coord& coord) const{
    return m_pieceLayerPtr->getEntityAt(coord);
}

bool GraphicBoard::contains(sf::Vector2i point) const{
    sf::Sprite sprite(m_texturePtr->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

bool GraphicBoard::isCoordinatesOutside() const{
    return !m_isCoordinateLabelsInside;
}

bool GraphicBoard::isWithinPlayerToMoveToken(sf::Vector2i point) const{
    if(!m_showPlayerToMoveToken){
        return false;
    }
    if(!m_playerToMoveToken){
        return false;
    }

    float x = (float)point.x - m_position.x;
    float y = (float)point.y - m_position.y;

    float radius = m_playerToMoveToken->getRadius()*m_scale;
    float centerX = m_playerToMoveToken->getPosition().x*m_scale+radius;
    float centerY = m_playerToMoveToken->getPosition().y*m_scale+radius;

    return (x-centerX)*(x-centerX)+(y-centerY)*(y-centerY) < radius*radius;
}

std::optional<Coord> GraphicBoard::getTileCoord(sf::Vector2i point){

    sf::Vector2u rect = m_texturePtr->getSize();
    rect.x = rect.x - m_leftEdgeWidth - m_rightEdgeWidth;
    rect.x *= m_scale;

    rect.y = rect.y - m_topEdgeWidth - m_bottomEdgeWidth;
    rect.y *= m_scale;

    float x = (float)point.x - m_position.x;
    x = x - (float)m_leftEdgeWidth*m_scale;
    x = x *(float)m_tileLayerPtr->getNumColumns()/(float)rect.x;

    float y = (float)point.y - m_position.y;
    y = y - (float)(m_topEdgeWidth*m_scale);
    y = y * (float)m_tileLayerPtr->getNumRows() / (float)rect.y;

    if(x < 0.f){
        return std::nullopt;
    }
    if(x >= m_tileLayerPtr->getNumColumns()){
        return std::nullopt;
    }
    if(y < 0.f){
        return std::nullopt;
    }
    if(y >= m_tileLayerPtr->getNumRows()){
        return std::nullopt;
    }

    if(!m_isLeftToRight){
        x = m_tileLayerPtr->getNumColumns()-x;
    }
    if(!m_isTopToBottom){
        y = m_tileLayerPtr->getNumRows()-y;
    }
    return std::make_optional<Coord>((int)x,(int)y);
}

void GraphicBoard::addEntity(const Coord& coord, const LogicEntity& entity){
    
    auto position_o = m_tileLayerPtr->getTileCentrePosition(coord);

    if(position_o == std::nullopt){
        std::cout << "GraphicBoard: Failed to add entity at "
            << coord.getNotation() << std::endl;
        std::cout << "Position for coordinate not found" << std::endl;
        return;
    }

    if(m_pieceLayerPtr->getEntityAt(coord) != std::nullopt){
        std::cout << "GraphicBoard: Failed to add entity at "
            << coord.getNotation() << std::endl;
        std::cout << "There is already an entity there" << std::endl;
        return;
    }

    m_pieceLayerPtr->addEntity(coord,position_o.value(),entity);
    redrawTexture();
}

void GraphicBoard::removeEntity(const Coord& coord){

    if(m_pieceLayerPtr->getEntityAt(coord) == std::nullopt){
        std::cout << "GraphicBoard: Failed to remove entity at "
            << coord.getNotation() << std::endl;
        std::cout << "There is no entity there" << std::endl;
        return;
    }

    m_pieceLayerPtr->removeEntity(coord);
    redrawTexture();
}

void GraphicBoard::moveEntity(const Coord& fromCoord, const Coord& toCoord){
    
    if(fromCoord == toCoord){
        std::cout << "GraphicBoard: Failed to move entity from "
            << fromCoord.getNotation() << " to "
            << toCoord.getNotation() << std::endl;
        std::cout << "Starting tile and destination tile are the same" << std::endl;
        return; 
    }

    auto toPosition_o = m_tileLayerPtr->getTileCentrePosition(toCoord);

    if(toPosition_o == std::nullopt){
        std::cout << "GraphicBoard: Failed to move entity from "
            << fromCoord.getNotation() << " to "
            << toCoord.getNotation() << std::endl;
        std::cout << "Destination tile position not found" << std::endl;
        return;
    }

    if(m_pieceLayerPtr->getEntityAt(toCoord) != std::nullopt){
        m_pieceLayerPtr->removeEntity(toCoord);
    }

    if(m_pieceLayerPtr->getEntityAt(fromCoord) != std::nullopt){
        m_pieceLayerPtr->moveEntity(fromCoord, toCoord,toPosition_o.value());
    }

    redrawTexture();
}

void GraphicBoard::addTileHighlight(const Coord& coord, const int& colorId){

    m_tileLayerPtr->setHighlightColor(coord, colorId);

    redrawTexture();
}

void GraphicBoard::removeTileHighlight(const Coord& coord){

    m_tileLayerPtr->removeHighlight(coord);

    redrawTexture();
}

void GraphicBoard::addArrow(const CoordPair& coordPair, const LogicArrow& logicArrow){

    auto fromPosition_o = m_tileLayerPtr->getTileCentrePosition(coordPair.from);

    if(fromPosition_o == std::nullopt){
        std::cout << "GraphicBoard: Failed to add arrow from "
            << coordPair.from.getNotation() << std::endl;
        std::cout << "Starting tile position not found" << std::endl;
        return;
    }

    auto toPosition_o = m_tileLayerPtr->getTileCentrePosition(coordPair.to);

    if(toPosition_o == std::nullopt){
        std::cout << "GraphicBoard: Failed to add arrow to "
            << coordPair.to.getNotation() << std::endl;
        std::cout << "Destination tile position not found" << std::endl;
        return;
    }

    if(!m_arrowLayerPtr){
        std::cout << "GraphicBoard: Failed to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "arrow layer not found" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_arrowLayerPtr->getArrow(coordPair);

    if(occupyingArrow_o != std::nullopt){
        std::cout << "GraphicBoard: Failed to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "There is already an arrow there" << std::endl;
        return;
    }

    m_arrowLayerPtr->addArrow(coordPair, fromPosition_o.value(), toPosition_o.value(), logicArrow);

    redrawTexture();
}

void GraphicBoard::removeArrow(const CoordPair& coordPair){

    if(!m_arrowLayerPtr){
        std::cout << "GraphicBoard: Failed to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "ArrowLayer not found" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_arrowLayerPtr->getArrow(coordPair);

    if(occupyingArrow_o == std::nullopt){
        std::cout << "GraphicBoard: Failed to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "There is no arrow there" << std::endl;
        return;
    }

    m_arrowLayerPtr->removeArrow(coordPair);
    
    redrawTexture();
}

void GraphicBoard::updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId){
    
    auto color_o = m_arrowColorManagerPtr->getSolidColor(colorId);

    if(color_o == std::nullopt){
        std::cout << "GraphicBoard: Failed to update drag arrow" << std::endl;
        std::cout << "Failed to receive color with id " << colorId << std::endl;
        return;
    }

    auto fromPosition_o = m_tileLayerPtr->getTileCentrePosition(fromCoord);
        
    if(fromPosition_o == std::nullopt){
        std::cout << "GraphicBoard: Unable to update dragArrow position from "
            << fromCoord.getNotation() << std::endl;
        std::cout << "Starting tile position not found" << std::endl;
        return;
    }

    auto toPosition_o = m_tileLayerPtr->getTileCentrePosition(toCoord);

    if(toPosition_o == std::nullopt){
        std::cout << "GraphicBoard: Unable to update dragArrow position to "
            << toCoord.getNotation() << std::endl;
        std::cout << "Destination tile position not found" << std::endl;
        return;
    }

    if(!m_dragArrowPtr){

        if(!m_arrowLayerPtr){
            std::cerr << "GraphicBoard: Unable to update dragArrow position to "
                << toCoord.getNotation() << std::endl;
            std::cerr << "arrowLayer not found" << std::endl;
            return;
        }

        m_dragArrowPtr = std::make_unique<GraphicArrow>();
        m_dragArrowPtr->init(fromPosition_o.value(), toPosition_o.value(), color_o.value(), m_arrowLayerPtr->getThickness(), m_arrowLayerPtr->getHeadSize());
    }
    else{
        m_dragArrowPtr->set(fromPosition_o.value(), toPosition_o.value());
        m_dragArrowPtr->setColor(color_o.value());
    }
    
    redrawTexture();
}

void GraphicBoard::removeDragArrow(){
    if(m_dragArrowPtr){
        m_dragArrowPtr = nullptr;
        redrawTexture();
    }
}

void GraphicBoard::highlightTile(const Coord& coord){

    auto position_o = m_tileLayerPtr->getTileTopLeftPosition(coord);

    if(position_o == std::nullopt){
        std::cout << "GraphicBoard: Unable to highlight tile at "
            << coord.getNotation() << std::endl;
        std::cout << "Tile position not found" << std::endl;
    }

    if(!m_selectHighlight){
        m_selectHighlight = std::make_unique<GraphicTile>();
        sf::Color color{255,255,0,100};
        m_selectHighlight->init(m_tileLayerPtr->getTileSize(), color);
    }

    m_selectHighlight->setPosition(position_o.value());

    redrawTexture();
}

void GraphicBoard::unhighlight(){
    if(m_selectHighlight){
        m_selectHighlight = nullptr;
        redrawTexture();
    }
}

void GraphicBoard::saveImage(const std::string& fileName){
    auto image = m_texturePtr->getTexture().copyToImage();
    image.flipVertically();
    std::cout << "Saving board image: " << fileName << std::endl;
    auto success = image.saveToFile(fileName);
    if(success && std::filesystem::exists(fileName)){
        std::cout << "board image: " << fileName << " saved" << std::endl;
    }
    else{
        std::cout << "Failed to save board image: " << fileName << std::endl;
    }
}

void GraphicBoard::clearEntities(){
    m_pieceLayerPtr->clear();
    redrawTexture();
}

void GraphicBoard::clearArrows(){
    m_arrowLayerPtr->clear();
    redrawTexture();
}

void GraphicBoard::flip(){
    m_isLeftToRight = !m_isLeftToRight;
    m_isTopToBottom = !m_isTopToBottom;

    int tileWidth = m_tileLayerPtr->getTileWidth();
    int tileHeight = m_tileLayerPtr->getTileHeight();

    for(int y = 0; y < m_tileLayerPtr->getNumRows(); y++){
        for(int x = 0; x < m_tileLayerPtr->getNumColumns(); x++){
            sf::Vector2f position;
            if(m_isLeftToRight){
                position.x = (float)(x*tileWidth);
            }
            else{
                position.x = (float)((m_tileLayerPtr->getNumColumns()-x-1)*tileWidth);
            }
            position.x += m_leftEdgeWidth;
            if(m_isTopToBottom){
                position.y = (float)(y*tileHeight);
            }
            else{
                position.y = (float)((m_tileLayerPtr->getNumRows()-y-1)*tileHeight);
            }
            position.y += m_topEdgeWidth;
            m_tileLayerPtr->setTilePosition({x,y},position);

            auto entity_o = m_pieceLayerPtr->getEntityAt({x,y});

            if(entity_o != std::nullopt){
                auto position_o = m_tileLayerPtr->getTileCentrePosition({x,y});
                m_pieceLayerPtr->setEntityPosition({x,y}, position_o.value());
            }
        }
    }

    if(m_arrowLayerPtr){
        for(auto& arrow : *m_arrowLayerPtr){
            sf::Vector2f fromPos = m_tileLayerPtr->getTileCentrePosition(arrow.first.from).value();
            sf::Vector2f toPos = m_tileLayerPtr->getTileCentrePosition(arrow.first.to).value();
            arrow.second.set(fromPos,toPos);
        }
    }
    

    if(m_showLabels){
        addCoordinates();
    }

    redrawTexture();//also called by addCoordinates
}

void GraphicBoard::addCoordinates(){

    m_showLabels = true;
    if(m_isCoordinateLabelsInside){
        addInsideLabels();
        redrawTexture();
        return;
    }

    unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileWidth();
    unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileHeight();

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    addOutsideLabels();
    redrawTexture();
}

void GraphicBoard::removeCoordinates(){
    
    m_showLabels = false;
    if(m_isCoordinateLabelsInside){
        m_leftInsideCoordinateLabels.clear();
        m_bottomInsideCoordinateLabels.clear();
        redrawTexture();
        return;
    }

    setLeftAndBottomEdgeWidth(0,0);

    m_leftOutsideCoordinateLabels.clear();
    m_bottomOutsideCoordinateLabels.clear();
    redrawTexture();
}

void GraphicBoard::moveCoordinatesOutside(){
    if(!m_isCoordinateLabelsInside){
        return;
    }
    m_isCoordinateLabelsInside = false;
    m_showLabels = true;

    unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileWidth();
    unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileHeight();

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    m_leftInsideCoordinateLabels.clear();
    m_bottomInsideCoordinateLabels.clear();
    addOutsideLabels();
    redrawTexture();
}

void GraphicBoard::moveCoordinatesInside(){
    if(m_isCoordinateLabelsInside){
        return;
    }
    m_isCoordinateLabelsInside = true;
    m_showLabels = true;

    setLeftAndBottomEdgeWidth(0,0);

    m_leftOutsideCoordinateLabels.clear();
    m_bottomOutsideCoordinateLabels.clear();
    addInsideLabels();
    redrawTexture();
}

void GraphicBoard::setCoordinateSize(const float& size){

    m_outsideLabelSizeFactor = size;

    unsigned int leftEdgeWidth = size* m_tileLayerPtr->getTileWidth();
    unsigned int leftEdgeHeight = size* m_tileLayerPtr->getTileHeight();

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    addOutsideLabels();
    redrawTexture();

}

void GraphicBoard::addBorder(){

    if(!m_borderPtr){
        m_borderPtr = std::make_unique<RectangleBorder>();
        bool isVisible = true;
        sf::Vector2f topLeftPosition{(float)m_leftEdgeWidth, (float)m_topEdgeWidth};
        sf::Vector2f boardArea;
        boardArea.x = m_tileLayerPtr->getTileWidth()* m_tileLayerPtr->getNumColumns();
        boardArea.y = m_tileLayerPtr->getTileHeight()*m_tileLayerPtr->getNumRows();
        m_borderPtr->init(isVisible, (float)m_borderWidth, topLeftPosition, boardArea);
    }
    else if(m_borderPtr->isVisible()){
        return;
    }

    sf::Vector2f topLeftPosition{(float)m_leftEdgeWidth, (float)m_topEdgeWidth};
    sf::Vector2f boardArea;
    boardArea.x = m_tileLayerPtr->getTileWidth()* m_tileLayerPtr->getNumColumns();
    boardArea.y = m_tileLayerPtr->getTileHeight()*m_tileLayerPtr->getNumRows();

    m_borderPtr->show(topLeftPosition, boardArea);

    moveTiles({(float)m_borderWidth, (float)m_borderWidth});
    moveLeftInsideCoordinateLabels({(float)m_borderWidth, (float)m_borderWidth});
    moveBottomInsideCoordinateLabels({(float)m_borderWidth, (float)m_borderWidth});
    moveLeftOutsideCoordinateLabels({0.f, (float)m_borderWidth});
    moveBottomOutsideCoordinateLabels({(float)m_borderWidth, 2.f*(float)m_borderWidth});
    movePlayerToMoveToken({2.f*(float)m_borderWidth, (float)m_borderWidth});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeBorder(){

    if(!m_borderPtr || !m_borderPtr->isVisible()){
        return;
    }

    m_borderPtr->hide();

    moveTiles({-(float)m_borderWidth, -(float)m_borderWidth});
    movePlayerToMoveToken({-2.f*(float)m_borderWidth, -(float)m_borderWidth});
    moveLeftInsideCoordinateLabels({-(float)m_borderWidth, -(float)m_borderWidth});
    moveBottomInsideCoordinateLabels({-(float)m_borderWidth, -(float)m_borderWidth});
    moveLeftOutsideCoordinateLabels({0.f, -(float)m_borderWidth});
    moveBottomOutsideCoordinateLabels({-(float)m_borderWidth, -2.f*(float)m_borderWidth});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addPlayerToMoveToken(){

    if(m_showPlayerToMoveToken){
        return;
    }

    m_showPlayerToMoveToken = true;

    m_rightEdgeWidth = (unsigned int)(0.5* m_tileLayerPtr->getTileWidth());

    if(!m_playerToMoveToken){
        initPlayerToMoveToken();
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removePlayerToMoveToken(){

    if(!m_showPlayerToMoveToken){
        return;
    }

    m_showPlayerToMoveToken = false;

    m_rightEdgeWidth = 0;

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::togglePlayerToMoveToken(){
    if(!m_playerToMoveToken){
        std::cout << "GraphicBoard: Unable to toggle player-to-move token. It does not exist" << std::endl;
        return;
    }

    if(m_playerToMoveToken->getFillColor().toInteger() == sf::Color{255,255,255,255}.toInteger()){
        m_playerToMoveToken->setFillColor(sf::Color{0,0,0,255});
    }
    else{
        m_playerToMoveToken->setFillColor(sf::Color{255,255,255,255});
    }

    m_texturePtr->draw(*m_playerToMoveToken);
}

void GraphicBoard::initPlayerToMoveToken(){
    float radius = 0.2* m_tileLayerPtr->getTileHeight();
    std::size_t pointCount = 30;
    m_playerToMoveToken = std::make_unique<sf::CircleShape>(radius, pointCount);
    float x = m_leftEdgeWidth;
    if(m_borderPtr && m_borderPtr->isVisible()){
        x+= 2*m_borderWidth;
    }
    x += m_tileLayerPtr->getTileWidth()*m_tileLayerPtr->getNumColumns();
    x += m_rightEdgeWidth/2.f;
    x -= radius;
    float y = m_topEdgeWidth;
    y += m_tileLayerPtr->getTileHeight()/2.f;
    y -= radius;
    m_playerToMoveToken->setPosition({x,y});

    m_playerToMoveToken->setFillColor(sf::Color{255,255,255,255});
    m_playerToMoveToken->setOutlineColor(sf::Color{0,0,0,255});
    m_playerToMoveToken->setOutlineThickness(-6.f);
}

unsigned int GraphicBoard::getTextureWidth() const{

    unsigned int boardWidth = (unsigned int)(m_tileLayerPtr->getTileWidth()* m_tileLayerPtr->getNumColumns());
    boardWidth += m_leftEdgeWidth+m_rightEdgeWidth;
    if(m_borderPtr && m_borderPtr->isVisible()){
        boardWidth += 2*m_borderWidth;
    }

    return boardWidth;

}

unsigned int GraphicBoard::getTextureHeight() const{
    unsigned int boardHeight = (unsigned int)(m_tileLayerPtr->getTileHeight()*(unsigned int)m_tileLayerPtr->getNumRows());
    boardHeight += m_topEdgeWidth+m_bottomEdgeWidth;
    if(m_borderPtr && m_borderPtr->isVisible()){
        boardHeight += 2*m_borderWidth;
    }

    return boardHeight;
}

void GraphicBoard::resizeTexture(){

    bool success;
    success = m_texturePtr->resize({getTextureWidth(), getTextureHeight()});
    if(!success){
        std::cout << "GraphicWindow: Failed to resize texture" << std::endl;
        return;
    }
}

void GraphicBoard::redrawTexture(){
    m_texturePtr->clear(m_backgroundColor);

    if(m_tileLayerPtr){
        m_texturePtr->draw(*m_tileLayerPtr);
    }

    if(m_selectHighlight){
        m_texturePtr->draw(*m_selectHighlight);
    }

    if(m_pieceLayerPtr){
        m_texturePtr->draw(*m_pieceLayerPtr);
    }

    if(m_arrowLayerPtr){
        m_texturePtr->draw(*m_arrowLayerPtr);
    }

    if(m_dragArrowPtr){
        m_texturePtr->draw(*m_dragArrowPtr);
    }

    for(const auto& label : m_leftOutsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    for(const auto& label : m_bottomOutsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    for(const auto& label : m_leftInsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    for(const auto& label : m_bottomInsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    if(m_borderPtr){
        m_texturePtr->draw(*m_borderPtr);
    }

    if(m_playerToMoveToken && m_showPlayerToMoveToken){
        m_texturePtr->draw(*m_playerToMoveToken);
    }
}

void GraphicBoard::setLeftAndBottomEdgeWidth(const unsigned int leftWidth, const unsigned int bottomWidth){
    
    float moveX = (float)leftWidth - (float)m_leftEdgeWidth;
    m_leftEdgeWidth = leftWidth;
    m_bottomEdgeWidth = bottomWidth;

    moveTiles({moveX, 0.f});
    if(m_borderPtr){
        m_borderPtr->move({moveX, 0.f});
    }
    movePlayerToMoveToken({moveX, 0.f});

    if(m_texturePtr){
        resizeTexture();
    }
    
}

void GraphicBoard::addOutsideLabels(){

    m_bottomOutsideCoordinateLabels.clear();
    m_leftOutsideCoordinateLabels.clear();

    for(int i = 0; i < m_tileLayerPtr->getNumColumns(); i++){
        std::string s = std::to_string(i);
        s[0] = s[0] + 'a' - '0';
        unsigned int labelSize = m_outsideLabelSizeFactor*m_tileLayerPtr->getTileWidth();
        sf::Text label{m_font, s, labelSize};

        sf::Vector2f position;
        position.x =
            m_tileLayerPtr->getTileCentrePosition({i,0}).value().x -
            label.getLocalBounds().size.x/2;

        position.y =
            getTextureHeight() -
            m_bottomEdgeWidth -
            labelSize/4;
        
        label.setPosition(position);
        label.setFillColor(sf::Color::Black);

        m_bottomOutsideCoordinateLabels.push_back(label);
    }

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        std::string s = std::to_string(m_tileLayerPtr->getNumRows() -i);
        unsigned int labelSize = m_outsideLabelSizeFactor* m_tileLayerPtr->getTileHeight();
        sf::Text label{m_font, s, labelSize};

        label.setOrigin({0.f,0.f});

        sf::Vector2f position;

        //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
        position.x = ((float)m_leftEdgeWidth-(float)labelSize/2.f)/2.f;

        int j = m_tileLayerPtr->getNumRows()-i-1;
        position.y = m_tileLayerPtr->getTileCentrePosition({0,j}).value().y -
            (float)labelSize*9.f/14.f;
        
        label.setPosition(position);
        label.setFillColor(sf::Color::Black);

        m_leftOutsideCoordinateLabels.push_back(label);
    }
}

void GraphicBoard::addInsideLabels(){

    m_bottomInsideCoordinateLabels.clear();
    m_leftInsideCoordinateLabels.clear();

    for(int i = 0; i < m_tileLayerPtr->getNumColumns(); i++){
        std::string s = std::to_string(i);
        s[0] = s[0] + 'a' - '0';
        unsigned int labelSize = m_insideLabelSizeFactor* m_tileLayerPtr->getTileWidth();
        sf::Text label{m_font, s, labelSize};

        sf::Vector2f position;
        position.x =
            m_tileLayerPtr->getTileRightPosition({i,0}).value() -
            label.getLocalBounds().size.x*5/4;
        
        position.y = getTextureHeight() - labelSize*5/4;
        
        position.y -= (float)m_bottomEdgeWidth;

        label.setPosition(position);

        label.setFillColor(sf::Color(100,100,100,255));

        auto outlineColor_o = m_tileLayerPtr->getTileColor({i,0});
        if(outlineColor_o.has_value()){
            label.setOutlineColor(outlineColor_o.value());
        }

        label.setOutlineThickness(2);

        m_bottomInsideCoordinateLabels.push_back(label);
    }

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        std::string s = std::to_string(m_tileLayerPtr->getNumRows() -i);
        unsigned int labelSize = m_insideLabelSizeFactor* m_tileLayerPtr->getTileHeight();
        sf::Text label{m_font, s, labelSize};

        label.setOrigin({0.f,0.f});

        sf::Vector2f position;

        //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
        position.x = (float)labelSize/16.f;
        position.x += (float)m_leftEdgeWidth;

        int j = m_tileLayerPtr->getNumRows()-i-1;
        position.y = m_tileLayerPtr->getTileTopPosition({0,j}).value() - (float)labelSize/4.f;
        
        label.setPosition(position);

        label.setFillColor(sf::Color(100,100,100,255));

        auto outlineColor_o = m_tileLayerPtr->getTileColor({0,j});
        if(outlineColor_o.has_value()){
            label.setOutlineColor(outlineColor_o.value());
        }
        
        label.setOutlineThickness(2);

        m_leftInsideCoordinateLabels.push_back(label);
    }
}

void GraphicBoard::moveTiles(const sf::Vector2f& offset){
    
    if(m_tileLayerPtr){
        m_tileLayerPtr->move(offset);
    }

    if(m_pieceLayerPtr){
        m_pieceLayerPtr->move(offset);
    }
    
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->move(offset);
    }
}

void GraphicBoard::moveLeftInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftInsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::moveBottomInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomInsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftOutsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomOutsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::movePlayerToMoveToken(const sf::Vector2f& offset){
    if(m_playerToMoveToken){
        m_playerToMoveToken->move(offset);
    }
}


void GraphicBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite sprite(m_texturePtr->getTexture());
    sprite.setPosition(m_position);
    sprite.setScale({m_scale,m_scale});
    target.draw(sprite);
}