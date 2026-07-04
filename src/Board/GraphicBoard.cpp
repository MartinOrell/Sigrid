#include "GraphicBoard.h"

#include "LogicBoard.h"
#include "BoardDesignContainer.h"
#include "../Color/ColorManager.h"

#include "../Entity/Tile/GraphicTiles.h"
#include "../Entity/GraphicEntities.h"
#include "../Entity/Shape/Arrow/GraphicArrows.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Image.hpp>

#include <iostream>

using namespace sigrid;

GraphicBoard::GraphicBoard()
: m_leftEdgeWidth{0.f}
, m_rightEdgeWidth{0.f}
, m_topEdgeWidth{0.f}
, m_bottomEdgeWidth{0.f}
, m_isLeftToRight{true}
, m_isTopToBottom{false}{
    m_texture.setBackgroundColor(sf::Color{255,255,255,255});
}

void GraphicBoard::setPieceManagerPtr(PieceManager* const managerPtr){
    if(!m_pieceLayerPtr){
        m_pieceLayerPtr = std::make_unique<GraphicEntities>();
    }
    m_pieceLayerPtr->setPieceManagerPtr(managerPtr);
}

void GraphicBoard::setTileColorManagerPtr(ColorManager* const managerPtr){
    if(!m_tileLayerPtr){
        m_tileLayerPtr = std::make_unique<GraphicTiles>();
    }
    m_tileLayerPtr->setColorManagerPtr(managerPtr);
}

void GraphicBoard::setArrowColorManagerPtr(ColorManager* const managerPtr){
    m_arrowColorManagerPtr = managerPtr;
}

void GraphicBoard::setFontManagerPtr(FontManager* const managerPtr){
    m_labels.setFontManagerPtr(managerPtr);
}

void GraphicBoard::setIconManagerPtr(IconManager* const managerPtr){
    if(!m_pieceLayerPtr){
        m_pieceLayerPtr = std::make_unique<GraphicEntities>();
    }
    m_pieceLayerPtr->setIconManagerPtr(managerPtr);
}

void GraphicBoard::setLeftToRight(){
    m_isLeftToRight = true;
}

void GraphicBoard::setRightToLeft(){
    m_isLeftToRight = false;
}

void GraphicBoard::setTopToBottom(){
    m_isTopToBottom = true;
}

void GraphicBoard::setBottomToTop(){
    m_isTopToBottom = false;
}

void GraphicBoard::load(const LogicBoard& logicBoard){

    if(!m_tileLayerPtr){
        m_tileLayerPtr = std::make_unique<GraphicTiles>();
    }

    m_tileLayerPtr->clear();

    if(m_pieceLayerPtr){
        m_pieceLayerPtr->clear();
    }

    if(m_arrowLayerPtr){
        m_arrowLayerPtr->clear();
    }
    
    m_tileLayerPtr->setNumColumns(logicBoard.getNumColumns());
    m_tileLayerPtr->setNumRows(logicBoard.getNumRows());
    m_tileLayerPtr->init(m_isLeftToRight, m_isTopToBottom);
    m_tileLayerPtr->move({m_leftEdgeWidth, m_topEdgeWidth});

    if(m_border.isVisible()){
        m_tileLayerPtr->move({m_border.getThickness(), m_border.getThickness()});
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
                if(!m_pieceLayerPtr){
                    m_pieceLayerPtr = std::make_unique<GraphicEntities>();
                }
                auto position_o = m_tileLayerPtr->getTileCentrePosition({x,y});
                if(position_o != std::nullopt){
                    m_pieceLayerPtr->addEntity({x,y},position_o.value(),entity_o.value());
                }
            }
        }
    }

    if(m_turnToken.isVisible()){
        m_turnToken.setTurnToMove(logicBoard.getTurnToMove());
    }

    {
        sf::Vector2f boardArea;
        boardArea.x = m_tileLayerPtr->getTileWidth() * logicBoard.getNumColumns();
        boardArea.y = m_tileLayerPtr->getTileHeight() * logicBoard.getNumRows();
        
        m_border.setEnclosedArea(boardArea);
    }

    if(m_labels.isLeftInsideVisible()){
        addLeftInsideLabels_h();
    }
    if(m_labels.isBottomInsideVisible()){
        addBottomInsideLabels_h();
    }
    if(m_labels.isLeftOutsideVisible()){
        updateLeftEdgeWidth();
        addLeftOutsideLabels_h();
    }
    if(m_labels.isRightOutsideVisible()){
        updateRightEdgeWidth();
        addRightOutsideLabels_h();
    }
    if(m_labels.isTopOutsideVisible()){
        updateTopEdgeWidth();
        addTopOutsideLabels_h();
    }
    if(m_labels.isBottomOutsideVisible()){
        updateBottomEdgeWidth();
        addBottomOutsideLabels_h();
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::init(const LogicBoard& logicBoard, const BoardDesignContainer& config){
    
    if(!m_tileLayerPtr){
        m_tileLayerPtr = std::make_unique<GraphicTiles>();
    }
    
    m_tileLayerPtr->setNumColumns(logicBoard.getNumColumns());
    m_tileLayerPtr->setNumRows(logicBoard.getNumRows());
    m_tileLayerPtr->setTileSize({config.tileWidth, config.tileHeight});
    m_tileLayerPtr->setTopLeftPosition({m_leftEdgeWidth, m_topEdgeWidth});
    if(m_arrowColorManagerPtr){
        m_tileLayerPtr->setHighlightColorManagerPtr(m_arrowColorManagerPtr);
    }
    m_tileLayerPtr->init(m_isLeftToRight,m_isTopToBottom);
    
    if(!m_pieceLayerPtr){
        m_pieceLayerPtr = std::make_unique<GraphicEntities>();
    }
    
    if(m_arrowColorManagerPtr){
        m_pieceLayerPtr->setColorManagerPtr(m_arrowColorManagerPtr);
    }
    m_pieceLayerPtr->setPieceSize({config.tileWidth, config.tileHeight});
    m_pieceLayerPtr->setCircleDiameter(config.circleDiameter);

    m_arrowLayerPtr = std::make_unique<GraphicArrows>();
    m_arrowLayerPtr->setThickness(config.arrowThickness);
    m_arrowLayerPtr->setHeadSize(config.arrowHeadSize);
    if(m_arrowColorManagerPtr){
        m_arrowLayerPtr->setColorManagerPtr(m_arrowColorManagerPtr);
    }

    for(auto& label: config.labels){
        if(label.isInside){
            if(label.position == 0){
                if(label.isVisible){
                    m_labels.showLeftInside();
                }
                else{
                    m_labels.hideLeftInside();
                }
                m_labels.setLeftInsideSize(label.size);
                m_labels.setLeftInsideFont(label.font);
            }
            else if(label.position == 3){
                if(label.isVisible){
                    m_labels.showBottomInside();
                }
                else{
                    m_labels.hideBottomInside();
                }
                m_labels.setBottomInsideSize(label.size);
                m_labels.setBottomInsideFont(label.font);
            }
            else{
                std::cerr << "GraphicBoard: Unhandled label position: " << label.position << std::endl;
            }
        }
        else{ // outside
            if(label.position == 0){
                if(label.isVisible){
                    m_labels.showLeftOutside();
                }
                else{
                    m_labels.hideLeftOutside();
                }
                m_labels.setLeftOutsideSize(label.size);
                m_labels.setLeftOutsideFont(label.font);
            }
            else if(label.position == 1){
                if(label.isVisible){
                    m_labels.showRightOutside();
                }
                else{
                    m_labels.hideRightOutside();
                }
                m_labels.setRightOutsideSize(label.size);
                m_labels.setRightOutsideFont(label.font);
            }
            else if(label.position == 2){
                if(label.isVisible){
                    m_labels.showTopOutside();
                }
                else{
                    m_labels.hideTopOutside();
                }
                m_labels.setTopOutsideSize(label.size);
                m_labels.setTopOutsideFont(label.font);
            }
            else if(label.position == 3){
                if(label.isVisible){
                    m_labels.showBottomOutside();
                }
                else{
                    m_labels.hideBottomOutside();
                }
                m_labels.setBottomOutsideSize(label.size);
                m_labels.setBottomOutsideFont(label.font);
            }
        }
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

    if(m_labels.isLeftInsideVisible()){
        addLeftInsideLabels_h();
    }
    if(m_labels.isBottomInsideVisible()){
        addBottomInsideLabels_h();
    }
    if(m_labels.isLeftOutsideVisible()){
        updateLeftEdgeWidth();
        addLeftOutsideLabels_h();
    }
    if(m_labels.isRightOutsideVisible()){
        updateRightEdgeWidth();
        addRightOutsideLabels_h();
    }
    if(m_labels.isTopOutsideVisible()){
        updateTopEdgeWidth();
        addTopOutsideLabels_h();
    }
    if(m_labels.isBottomOutsideVisible()){
        updateBottomEdgeWidth();
        addBottomOutsideLabels_h();
    }

    if(config.turnToken){
        initTurnToken(logicBoard.getTurnToMove());
        m_turnToken.show();
        updateRightEdgeWidth();
    }
    else{
        m_turnToken.hide();
    }

    m_border.setThickness(config.borderThickness);
    m_border.setColor(sf::Color{0,0,0});
    if(config.border){

        sf::Vector2f boardArea;
        boardArea.x = config.tileWidth* logicBoard.getNumColumns();
        boardArea.y = config.tileHeight* logicBoard.getNumRows();

        m_border.setTopLeftPosition({m_leftEdgeWidth, m_topEdgeWidth});
        m_border.setEnclosedArea(boardArea);
        
        m_border.show();
    }
    else{
        m_border.hide();
    }

    if(m_border.isVisible()){
        moveTiles({m_border.getThickness(), m_border.getThickness()});
    }
    
    resizeTexture();
    redrawTexture();
}

GraphicBoard& GraphicBoard::operator=(const GraphicBoard& rhs){

    if(rhs.m_texture.isInitialized()){
        m_texture.setSize(rhs.getTextureSize());
    }

    m_texture.setPosition(rhs.getTopLeftPosition());
    m_texture.setBackgroundColor(rhs.getBackgroundColor());
    m_texture.setScale(rhs.getScale());

    m_leftEdgeWidth = rhs.m_leftEdgeWidth;
    m_rightEdgeWidth = rhs.m_rightEdgeWidth;
    m_topEdgeWidth = rhs.m_topEdgeWidth;
    m_bottomEdgeWidth = rhs.m_bottomEdgeWidth;

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

    m_dragArrow = rhs.m_dragArrow;

    m_isSelectHighlightVisible = rhs.m_isSelectHighlightVisible;
    m_selectHighlight = rhs.m_selectHighlight;

    m_arrowColorManagerPtr = rhs.m_arrowColorManagerPtr;

    m_labels = rhs.m_labels;
    m_border = rhs.m_border;
    m_turnToken = rhs.m_turnToken;

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

void GraphicBoard::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
    m_texture.display();
}

void GraphicBoard::setPositionX(float x){
    sf::Vector2f position = m_texture.getPosition();
    position.x = x;
    m_texture.setPosition(position);
    m_texture.display();
}

void GraphicBoard::setScale(const float scale){
    m_texture.setScale(scale);
    m_texture.display();
}

float GraphicBoard::getImageWidth() const{
    return m_texture.getTextureSize().x;
}

float GraphicBoard::getImageHeight() const{
    return m_texture.getTextureSize().y;
}

sf::Image GraphicBoard::getImage(const unsigned int maxWidth, const unsigned int maxHeight) const{
    return m_texture.getImage(maxWidth, maxHeight);
}

const sf::Vector2f& GraphicBoard::getTopLeftPosition() const{
    return m_texture.getPosition();
}

sf::Vector2f GraphicBoard::getDisplaySize() const{
    return m_texture.getDisplaySize();
}

float GraphicBoard::getDisplayWidth() const{
    return m_texture.getDisplaySize().x;
}

float GraphicBoard::getDisplayHeight() const{
    return m_texture.getDisplaySize().y;
}

bool GraphicBoard::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

bool GraphicBoard::isLeftToRight() const{
    return m_isLeftToRight;
}

bool GraphicBoard::isTopToBottom() const{
    return m_isTopToBottom;
}

bool GraphicBoard::isCoordinatesOutside() const{
    return m_labels.isLeftOutsideVisible();
}

bool GraphicBoard::isWithinTurnToken(const sf::Vector2f& point) const{
    return m_turnToken.isWithin((point-m_texture.getPosition())/m_texture.getScale());
}

std::optional<Coord> GraphicBoard::getTileCoord(const sf::Vector2f& point){

    const float& scale = m_texture.getScale();
    const sf::Vector2f& position = m_texture.getPosition();

    sf::Vector2f rect = m_texture.getTextureSize();
    rect.x = rect.x - m_leftEdgeWidth - m_rightEdgeWidth;
    rect.x *= scale;

    rect.y = rect.y - m_topEdgeWidth - m_bottomEdgeWidth;
    rect.y *= scale;

    float x = point.x - position.x;
    x = x - m_leftEdgeWidth*scale;
    x = x *(float)m_tileLayerPtr->getNumColumns()/rect.x;

    float y = point.y - position.y;
    y = y - m_topEdgeWidth*scale;
    y = y * (float)m_tileLayerPtr->getNumRows() /rect.y;

    if(x < 0.f){
        return std::nullopt;
    }
    if(x >= (float)m_tileLayerPtr->getNumColumns()){
        return std::nullopt;
    }
    if(y < 0.f){
        return std::nullopt;
    }
    if(y >= (float)m_tileLayerPtr->getNumRows()){
        return std::nullopt;
    }

    if(!m_isLeftToRight){
        x = (float)m_tileLayerPtr->getNumColumns()-x;
    }
    if(!m_isTopToBottom){
        y = (float)m_tileLayerPtr->getNumRows()-y;
    }
    return std::make_optional<Coord>((int)x,(int)y);
}

void GraphicBoard::addEntity(const Coord& coord, const LogicEntity& entity){
    
    auto position_o = m_tileLayerPtr->getTileCentrePosition(coord);

    if(position_o == std::nullopt){
        std::cerr << "GraphicBoard: Failed to add entity at "
            << coord.getNotation() << std::endl;
        std::cerr << "Position for coordinate not found" << std::endl;
        return;
    }

    if(m_pieceLayerPtr->getEntityAt(coord) != std::nullopt){
        std::cerr << "GraphicBoard: Failed to add entity at "
            << coord.getNotation() << std::endl;
        std::cerr << "There is already an entity there" << std::endl;
        return;
    }

    m_pieceLayerPtr->addEntity(coord,position_o.value(),entity);
    redrawTexture();
}

void GraphicBoard::removeEntity(const Coord& coord){

    if(m_pieceLayerPtr->getEntityAt(coord) == std::nullopt){
        std::cerr << "GraphicBoard: Failed to remove entity at "
            << coord.getNotation() << std::endl;
        std::cerr << "There is no entity there" << std::endl;
        return;
    }

    m_pieceLayerPtr->removeEntity(coord);
    redrawTexture();
}

void GraphicBoard::moveEntity(const Coord& fromCoord, const Coord& toCoord){
    
    if(fromCoord == toCoord){
        std::cerr << "GraphicBoard: Failed to move entity from "
            << fromCoord.getNotation() << " to "
            << toCoord.getNotation() << std::endl;
        std::cerr << "Starting tile and destination tile are the same" << std::endl;
        return; 
    }

    auto toPosition_o = m_tileLayerPtr->getTileCentrePosition(toCoord);

    if(toPosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Failed to move entity from "
            << fromCoord.getNotation() << " to "
            << toCoord.getNotation() << std::endl;
        std::cerr << "Destination tile position not found" << std::endl;
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
        std::cerr << "GraphicBoard: Failed to add arrow from "
            << coordPair.from.getNotation() << std::endl;
        std::cerr << "Starting tile position not found" << std::endl;
        return;
    }

    auto toPosition_o = m_tileLayerPtr->getTileCentrePosition(coordPair.to);

    if(toPosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Failed to add arrow to "
            << coordPair.to.getNotation() << std::endl;
        std::cerr << "Destination tile position not found" << std::endl;
        return;
    }

    if(!m_arrowLayerPtr){
        std::cerr << "GraphicBoard: Failed to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "arrow layer not found" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_arrowLayerPtr->getArrow(coordPair);

    if(occupyingArrow_o != std::nullopt){
        std::cerr << "GraphicBoard: Failed to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "There is already an arrow there" << std::endl;
        return;
    }

    m_arrowLayerPtr->addArrow(coordPair, fromPosition_o.value(), toPosition_o.value(), logicArrow);

    redrawTexture();
}

void GraphicBoard::removeArrow(const CoordPair& coordPair){

    if(!m_arrowLayerPtr){
        std::cerr << "GraphicBoard: Failed to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "ArrowLayer not found" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_arrowLayerPtr->getArrow(coordPair);

    if(occupyingArrow_o == std::nullopt){
        std::cerr << "GraphicBoard: Failed to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "There is no arrow there" << std::endl;
        return;
    }

    m_arrowLayerPtr->removeArrow(coordPair);
    
    redrawTexture();
}

void GraphicBoard::updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId){
    
    if(!m_arrowColorManagerPtr){
        std::cerr << "GraphicBoard: Failed to update drag arrow" << std::endl;
        std::cerr << "arrowColorManagerPtr is null" << std::endl;
        return;
    }

    auto color_o = m_arrowColorManagerPtr->getSolidColor(colorId);

    if(color_o == std::nullopt){
        std::cerr << "GraphicBoard: Failed to update drag arrow" << std::endl;
        std::cerr << "Failed to receive color with id " << colorId << std::endl;
        return;
    }

    auto fromPosition_o = m_tileLayerPtr->getTileCentrePosition(fromCoord);
        
    if(fromPosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Unable to update dragArrow position from "
            << fromCoord.getNotation() << std::endl;
        std::cerr << "Starting tile position not found" << std::endl;
        return;
    }

    auto toPosition_o = m_tileLayerPtr->getTileCentrePosition(toCoord);

    if(toPosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Unable to update dragArrow position to "
            << toCoord.getNotation() << std::endl;
        std::cerr << "Destination tile position not found" << std::endl;
        return;
    }

    if(!m_isDragArrowVisible){

        if(!m_arrowLayerPtr){
            std::cerr << "GraphicBoard: Unable to update dragArrow position to "
                << toCoord.getNotation() << std::endl;
            std::cerr << "arrowLayer not found" << std::endl;
            return;
        }
        m_dragArrow.setThickness(m_arrowLayerPtr->getThickness());
        m_dragArrow.setHeadSize(m_arrowLayerPtr->getHeadSize());
    }
    
    m_dragArrow.setPosition(fromPosition_o.value(), toPosition_o.value());
    m_dragArrow.setColor(color_o.value());
    m_isDragArrowVisible = true;
    
    redrawTexture();
}

void GraphicBoard::removeDragArrow(){
    if(!m_isDragArrowVisible){
        return;
    }
    m_isDragArrowVisible = false;
    redrawTexture();
}

void GraphicBoard::highlightTile(const Coord& coord){

    auto position_o = m_tileLayerPtr->getTileTopLeftPosition(coord);

    if(position_o == std::nullopt){
        std::cerr << "GraphicBoard: Unable to highlight tile at "
            << coord.getNotation() << std::endl;
        std::cerr << "Tile position not found" << std::endl;
    }
    auto& position = position_o.value();

    m_isSelectHighlightVisible = true;
    sf::Color color{255,255,0,100};
    m_selectHighlight.setSize(m_tileLayerPtr->getTileSize());
    m_selectHighlight.setTileColor(color);
    m_selectHighlight.setPosition(position);

    redrawTexture();
}

void GraphicBoard::unhighlight(){
    
    if(!m_isSelectHighlightVisible){
        return;
    }
    m_isSelectHighlightVisible = false;
    redrawTexture();
}

void GraphicBoard::saveImage(const std::string& fileName){
    std::cout << "Saving board image: " << fileName << std::endl;
    auto success = m_texture.getImage().saveToFile(fileName);
    if(success && std::filesystem::exists(fileName)){
        std::cout << "board image: " << fileName << " saved" << std::endl;
    }
    else{
        std::cerr << "GraphicBoard: Failed to save board image: " << fileName << std::endl;
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

void GraphicBoard::addTileColumnRight(const std::vector<int>& repeatTileColorIds){
    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->addColumnRight(repeatTileColorIds, m_isLeftToRight);
    if(m_pieceLayerPtr){
        if(!m_isLeftToRight){
            m_pieceLayerPtr->move(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        }
    }
    if(m_arrowLayerPtr){
        if(!m_isLeftToRight){
            m_arrowLayerPtr->move(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        }
    }

    m_border.addWidth(m_tileLayerPtr->getTileSize().x);

    m_turnToken.move(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});

    if(!m_isLeftToRight){
        m_labels.moveBottomInsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        m_labels.moveBottomOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
    }
    m_labels.moveRightOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
    int column = m_tileLayerPtr->getNumColumns()-1;
    if(m_labels.isBottomInsideVisible()){
        addBottomInsideLabel_h(column);
    }
    if(m_labels.isTopOutsideVisible()){
        addTopOutsideLabel_h(column);
    }
    if(m_labels.isBottomOutsideVisible()){
        addBottomOutsideLabel_h(column);
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addTileColumnLeft(const std::vector<int>& repeatTileColorIds){
    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->addColumnLeft(repeatTileColorIds, m_isLeftToRight);
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->moveEntitiesRight(m_tileLayerPtr->getTileSize().x, m_isLeftToRight);
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->moveArrowsRight(m_tileLayerPtr->getTileSize().x, m_isLeftToRight);
    }

    m_border.addWidth(m_tileLayerPtr->getTileSize().x);
    
    m_turnToken.move(sf::Vector2f{m_tileLayerPtr->getTileSize().x, 0.f});

    if(!m_isLeftToRight){
        m_labels.moveBottomInsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        m_labels.moveBottomOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
    }
    m_labels.moveRightOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
    int column = m_tileLayerPtr->getNumColumns()-1;
    if(m_labels.isBottomInsideVisible()){
        addBottomInsideLabel_h(column);
    }
    if(m_labels.isTopOutsideVisible()){
        addTopOutsideLabel_h(column);
    }
    if(m_labels.isBottomOutsideVisible()){
        addBottomOutsideLabel_h(column);
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeRightTileColumn(){
    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeRightColumn(m_isLeftToRight);
    int columnId = m_tileLayerPtr->getNumColumns();
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->removeColumn(columnId);
        if(!m_isLeftToRight){
            m_pieceLayerPtr->move(sf::Vector2f{-m_tileLayerPtr->getTileSize().x, 0.f});
        }
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->removeColumn(columnId);
        if(!m_isLeftToRight){
            m_arrowLayerPtr->move(sf::Vector2f{-m_tileLayerPtr->getTileSize().x, 0.f});
        }
    }
    m_turnToken.move({-m_tileLayerPtr->getTileSize().x, 0.f});

    m_border.addWidth(-m_tileLayerPtr->getTileSize().x);

    m_labels.removeHorizontalLabel();
    if(!m_isLeftToRight){
        m_labels.moveBottomInsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
        m_labels.moveBottomOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
    }
    m_labels.moveRightOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeLeftTileColumn(){
    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeLeftColumn(m_isLeftToRight);
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->removeColumn(0);
        m_pieceLayerPtr->moveEntitiesLeft(m_tileLayerPtr->getTileSize().x, m_isLeftToRight);
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->removeColumn(0);
        m_arrowLayerPtr->moveArrowsLeft(m_tileLayerPtr->getTileSize().x, m_isLeftToRight);
    }

    m_turnToken.move({-m_tileLayerPtr->getTileSize().x, 0.f});

    m_border.addWidth(-m_tileLayerPtr->getTileSize().x);

    m_labels.removeHorizontalLabel();
    if(!m_isLeftToRight){
        m_labels.moveBottomInsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
        m_labels.moveBottomOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
    }
    m_labels.moveRightOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addTileRowUp(const std::vector<int>& repeatTileColorIds){

    if(!m_tileLayerPtr){
        return;
    }

    m_tileLayerPtr->addRowUp(repeatTileColorIds, m_isTopToBottom);
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->moveEntitiesDown(m_tileLayerPtr->getTileSize().y, m_isTopToBottom);
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->moveArrowsDown(m_tileLayerPtr->getTileSize().y, m_isTopToBottom);
    }

    m_border.addHeight(m_tileLayerPtr->getTileSize().y);

    if(!m_isTopToBottom){
        m_labels.moveLeftInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        m_labels.moveLeftOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        m_labels.moveRightOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
    }
    m_labels.moveBottomInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
    m_labels.moveBottomOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
    
    int row = m_tileLayerPtr->getNumRows()-1;
    if(m_labels.isLeftInsideVisible()){
        addLeftInsideLabel_h(row);
    }
    if(m_labels.isLeftOutsideVisible()){
        addLeftOutsideLabel_h(row);
    }
    if(m_labels.isRightOutsideVisible()){
        addRightOutsideLabel_h(row);
    }

    updateLeftEdgeWidth();
    updateRightEdgeWidth();
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addTileRowDown(const std::vector<int>& repeatTileColorIds){

    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->addRowDown(repeatTileColorIds, m_isTopToBottom);
    if(m_pieceLayerPtr){
        if(!m_isTopToBottom){
            m_pieceLayerPtr->move(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        }
    }
    if(m_arrowLayerPtr){
        if(!m_isTopToBottom){
            m_arrowLayerPtr->move(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        }
    }

    m_border.addHeight(m_tileLayerPtr->getTileSize().y);

    if(!m_isTopToBottom){
        m_labels.moveLeftInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        m_labels.moveLeftOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        m_labels.moveRightOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
    }
    m_labels.moveBottomInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
    m_labels.moveBottomOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
    
    int row = m_tileLayerPtr->getNumRows()-1;
    if(m_labels.isLeftInsideVisible()){
        addLeftInsideLabel_h(row);
    }
    if(m_labels.isLeftOutsideVisible()){
        addLeftOutsideLabel_h(row);
    }
    if(m_labels.isRightOutsideVisible()){
        addRightOutsideLabel_h(row);
    }

    updateLeftEdgeWidth();
    updateRightEdgeWidth();
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTopTileRow(){

    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeTopRow(m_isLeftToRight);
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->removeRow(0);
        m_pieceLayerPtr->moveEntitiesUp(m_tileLayerPtr->getTileSize().y, m_isTopToBottom);
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->removeRow(0);
        m_arrowLayerPtr->moveArrowsUp(m_tileLayerPtr->getTileSize().y, m_isTopToBottom);
    }

    m_border.addHeight(-m_tileLayerPtr->getTileSize().y);

    m_labels.removeVerticalLabel();
    if(!m_isTopToBottom){
        m_labels.moveLeftInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        m_labels.moveLeftOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        m_labels.moveRightOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
    }
    m_labels.moveBottomInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
    m_labels.moveBottomOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});

    updateLeftEdgeWidth();
    updateRightEdgeWidth();
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeBottomTileRow(){

    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeBottomRow(m_isTopToBottom);
    int rowId = m_tileLayerPtr->getNumRows();
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->removeRow(rowId);
        if(!m_isTopToBottom){
            m_pieceLayerPtr->move(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        }
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->removeRow(rowId);
        if(!m_isTopToBottom){
            m_arrowLayerPtr->move(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        }
    }

    m_border.addHeight(-m_tileLayerPtr->getTileSize().y);

    m_labels.removeVerticalLabel();
    if(!m_isTopToBottom){
        m_labels.moveLeftInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        m_labels.moveLeftOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        m_labels.moveRightOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
    }
    m_labels.moveBottomInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
    m_labels.moveBottomOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});

    updateLeftEdgeWidth();
    updateRightEdgeWidth();
    resizeTexture();
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
            arrow.second.setPosition(fromPos,toPos);
        }
    }
    
    if(m_labels.isLeftInsideVisible()){
        addLeftInsideLabels();
    }
    if(m_labels.isBottomInsideVisible()){
        addBottomInsideLabels();
    }
    if(m_labels.isLeftOutsideVisible()){
        addLeftOutsideLabels();
    }
    if(m_labels.isRightOutsideVisible()){
        addRightOutsideLabels();
    }
    if(m_labels.isBottomOutsideVisible()){
        addBottomOutsideLabels();
    }

    redrawTexture();//also called by addCoordinates
}

void GraphicBoard::addLeftInsideLabels(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.showLeftInside();

    addLeftInsideLabels_h();

    redrawTexture();
}

void GraphicBoard::addBottomInsideLabels(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.showBottomInside();

    addBottomInsideLabels_h();

    redrawTexture();
}

void GraphicBoard::addLeftOutsideLabels(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.showLeftOutside();
    updateLeftEdgeWidth();
    addLeftOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addRightOutsideLabels(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.showRightOutside();
    updateRightEdgeWidth();
    addRightOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addTopOutsideLabels(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.showTopOutside();
    updateTopEdgeWidth();
    addTopOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addBottomOutsideLabels(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.showBottomOutside();
    updateBottomEdgeWidth();
    addBottomOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::removeLeftInsideLabels(){

    if(m_labels.isLeftInsideVisible()){
        m_labels.removeLeftInsideLabels();
    }
    m_labels.hideLeftInside();

    redrawTexture();
}

void GraphicBoard::removeBottomInsideLabels(){

    if(m_labels.isBottomInsideVisible()){
        m_labels.removeBottomInsideLabels();
    }
    m_labels.hideBottomInside();

    redrawTexture();
}

void GraphicBoard::removeLeftOutsideLabels(){

    if(m_labels.isLeftOutsideVisible()){
        m_labels.hideLeftOutside();
        updateLeftEdgeWidth();
        m_labels.removeLeftOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::removeRightOutsideLabels(){

    if(m_labels.isRightOutsideVisible()){
        m_labels.hideRightOutside();
        updateRightEdgeWidth();
        m_labels.removeRightOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::removeTopOutsideLabels(){

    if(m_labels.isTopOutsideVisible()){
        m_labels.hideTopOutside();
        updateTopEdgeWidth();
        m_labels.removeTopOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::removeBottomOutsideLabels(){

    if(m_labels.isBottomOutsideVisible()){
        m_labels.hideBottomOutside();
        updateBottomEdgeWidth();
        m_labels.removeBottomOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::setCoordinateSize(const float& size){

    m_labels.setLeftOutsideSize(size);
    m_labels.setRightOutsideSize(size);
    m_labels.setTopOutsideSize(size);
    m_labels.setBottomOutsideSize(size);

    m_labels.showLeftOutside();
    updateLeftEdgeWidth();
    m_labels.showRightOutside();
    updateRightEdgeWidth();
    m_labels.showTopOutside();
    updateTopEdgeWidth();
    m_labels.showBottomOutside();
    updateBottomEdgeWidth();

    addLeftOutsideLabels_h();
    addRightOutsideLabels_h();
    addTopOutsideLabels_h();
    addBottomOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addBorder(){

    if(m_border.isVisible()){
        return;
    }

    sf::Vector2f topLeftPosition{m_leftEdgeWidth, m_topEdgeWidth};
    sf::Vector2f boardArea;
    boardArea.x = m_tileLayerPtr->getTileWidth()* m_tileLayerPtr->getNumColumns();
    boardArea.y = m_tileLayerPtr->getTileHeight()*m_tileLayerPtr->getNumRows();

    m_border.setEnclosedArea(boardArea);
    m_border.setTopLeftPosition(topLeftPosition);
    m_border.show();

    float dx = m_border.getThickness();
    float dy = m_border.getThickness();
    moveTiles({dx, dy});
    m_labels.moveLeftInsideLabels({dx, dy});
    m_labels.moveBottomInsideLabels({dx, dy});
    m_labels.moveLeftOutsideLabels({0.f, dy});
    m_labels.moveBottomOutsideLabels({dx, 2.f*dy});
    
    moveTurnToken({2.f*dx, dy});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeBorder(){

    if(m_border.isHidden()){
        return;
    }

    m_border.hide();

    float dx = m_border.getThickness();
    float dy = m_border.getThickness();
    moveTiles({-dx, -dy});
    moveTurnToken({-2.f*dx, -dy});
    m_labels.moveLeftInsideLabels({-dx, -dy});
    m_labels.moveBottomInsideLabels({-dx, -dy});
    m_labels.moveLeftOutsideLabels({0.f, -dy});
    m_labels.moveBottomOutsideLabels({-dx, -2.f*dy});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addTurnToken(const int& turnToMove){

    if(m_turnToken.isVisible()){
        return;
    }

    initTurnToken(turnToMove);
    m_turnToken.show();
    updateRightEdgeWidth();

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTurnToken(){

    if(m_turnToken.isHidden()){
        return;
    }

    m_turnToken.hide();
    updateRightEdgeWidth();

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::setTurnToMove(const int& turnToMove){
    
    if(m_turnToken.isHidden()){
        return;
    }
    
    m_turnToken.setTurnToMove(turnToMove);

    redrawTexture();
}

void GraphicBoard::initTurnToken(const int& turnToMove){

    float radius = 0.2* m_tileLayerPtr->getTileHeight();
    
    float x = m_leftEdgeWidth;
    if(m_border.isVisible()){
        x+= 2*m_border.getThickness();
    }
    
    x += m_tileLayerPtr->getTileWidth()*m_tileLayerPtr->getNumColumns();

    float workWidth = m_rightEdgeWidth;
    if(m_labels.isRightOutsideVisible()){
        workWidth -= m_labels.getRightOutsideWorkWidth();
        x += m_labels.getRightOutsideWorkWidth();
    }

    x += workWidth/2.f;
    float y = m_topEdgeWidth;
    y += m_tileLayerPtr->getTileHeight()/2.f;

    m_turnToken.setRadius(radius);
    m_turnToken.setCenterPosition({x,y});
    m_turnToken.setTurnToMove(turnToMove);
}

sf::Vector2f GraphicBoard::getTextureSize() const{
    return m_texture.getTextureSize();
}

const float& GraphicBoard::getScale() const{
    return m_texture.getScale();
}

float GraphicBoard::calcTextureWidth() const{

    float boardWidth = (m_tileLayerPtr->getTileWidth()* (float)m_tileLayerPtr->getNumColumns());
    boardWidth += m_leftEdgeWidth + m_rightEdgeWidth;
    if(m_border.isVisible()){
        boardWidth += 2.f*m_border.getThickness();
    }

    return boardWidth;
}

float GraphicBoard::calcTextureHeight() const{

    float boardHeight = (m_tileLayerPtr->getTileHeight()*(float)m_tileLayerPtr->getNumRows());
    boardHeight += m_topEdgeWidth + m_bottomEdgeWidth;
    if(m_border.isVisible()){
        boardHeight += 2.f*m_border.getThickness();
    }

    return boardHeight;
}

sf::Vector2f GraphicBoard::calcTextureSize() const{
    return sf::Vector2f{calcTextureWidth(), calcTextureHeight()};
}

const sf::Color& GraphicBoard::getBackgroundColor() const{
    return m_texture.getBackgroundColor();
}

void GraphicBoard::resizeTexture(){

    bool success;
    success = m_texture.setSize(calcTextureSize());
    if(!success){
        std::cerr << "GraphicBoard: Failed to resize texture" << std::endl;
        return;
    }
}

void GraphicBoard::redrawTexture(){
    if(!m_texture.isInitialized()){
        return;
    }

    m_texture.clear();

    if(m_tileLayerPtr){
        m_texture.draw(*m_tileLayerPtr);
    }

    if(m_isSelectHighlightVisible){
        m_texture.draw(m_selectHighlight);
    }

    if(m_pieceLayerPtr){
        m_texture.draw(*m_pieceLayerPtr);
    }

    if(m_arrowLayerPtr){
        m_texture.draw(*m_arrowLayerPtr);
    }

    if(m_isDragArrowVisible){
        m_texture.draw(m_dragArrow);
    }

    m_texture.draw(m_labels);

    if(m_border.isVisible()){
        m_texture.draw(m_border);
    }

    if(m_turnToken.isVisible()){
        m_texture.draw(m_turnToken);
    }

    m_texture.display();
}

void GraphicBoard::updateLeftEdgeWidth(){

    float newEdgeWidth = 0.f;
    if(m_tileLayerPtr && m_labels.isLeftOutsideVisible()){
        int numDigits = notation::getRowNotation(m_tileLayerPtr->getNumRows()-1).length();
        float labelSize = m_labels.getLeftOutsideLabelSize();
        float tileWidth = m_tileLayerPtr->getTileWidth();

        newEdgeWidth = (float)numDigits*labelSize*tileWidth/2.f + tileWidth/5.f;
        m_labels.setLeftOutsideWorkWidth(newEdgeWidth);
    }

    if(newEdgeWidth == m_leftEdgeWidth){
        return;
    }

    float moveX = newEdgeWidth - m_leftEdgeWidth;
    m_leftEdgeWidth = newEdgeWidth;

    moveTiles({moveX, 0.f});
    m_border.move({moveX, 0.f});
    moveTurnToken({moveX, 0.f});

    if(m_labels.isLeftOutsideVisible()){
        m_labels.moveLeftOutsideLabels({-moveX/2.f, 0.f});
    }

    if(m_texture.isInitialized()){
        resizeTexture();
    }
}

void GraphicBoard::updateRightEdgeWidth(){

    float newEdgeWidth = 0.f;

    if(m_tileLayerPtr && m_labels.isRightOutsideVisible()){
        int numDigits = notation::getRowNotation(m_tileLayerPtr->getNumRows()-1).length();
        float labelSize = m_labels.getRightOutsideLabelSize();
        float tileWidth = m_tileLayerPtr->getTileWidth();

        float newWorkWidth = (float)numDigits*labelSize*tileWidth/2.f + tileWidth/5.f;
        float oldWorkWidth = m_labels.getRightOutsideWorkWidth();

        if(newWorkWidth != oldWorkWidth){
            m_labels.setRightOutsideWorkWidth(newWorkWidth);

            float moveX = newWorkWidth - oldWorkWidth;
            m_labels.moveRightOutsideLabels({moveX/2.f, 0.f});
            m_turnToken.move({moveX, 0.f});
        }

        newEdgeWidth += newWorkWidth;
    }

    if(m_tileLayerPtr && m_turnToken.isVisible()){
        newEdgeWidth += m_tileLayerPtr->getTileWidth()/2.f;
    }

    if(newEdgeWidth == m_rightEdgeWidth){
        return;
    }

    m_rightEdgeWidth = newEdgeWidth;

    {   
        float x = m_leftEdgeWidth;
        if(m_border.isVisible()){
            x+= 2*m_border.getThickness();
        }
        x += m_tileLayerPtr->getTileWidth()*m_tileLayerPtr->getNumColumns();

        float workWidth = m_rightEdgeWidth;
        if(m_labels.isRightOutsideVisible()){
            workWidth -= m_labels.getRightOutsideWorkWidth();
            x += m_labels.getRightOutsideWorkWidth();
        }

        x += workWidth/2.f;
        float y = m_topEdgeWidth;
        y += m_tileLayerPtr->getTileHeight()/2.f;

        sf::Vector2f oldPosition = m_turnToken.getCenterPosition();
        sf::Vector2f newPosition{x,y};
        if(oldPosition != newPosition){
            m_turnToken.setCenterPosition({x,y});
        }
    }

    if(m_texture.isInitialized()){
        resizeTexture();
    }
}

void GraphicBoard::updateTopEdgeWidth(){

    float newEdgeWidth = 0.f;

    if(m_labels.isTopOutsideVisible()){
        newEdgeWidth = m_labels.getTopOutsideLabelSize()* m_tileLayerPtr->getTileHeight();
        m_labels.setTopOutsideWorkHeight(newEdgeWidth);
    }

    if(newEdgeWidth == m_topEdgeWidth){
        return;
    }

    float moveY = newEdgeWidth - m_topEdgeWidth;
    m_topEdgeWidth = newEdgeWidth;
    

    moveTiles({0.f, moveY});
    m_border.move({0.f, moveY});
    moveTurnToken({0.f, moveY});

    if(m_texture.isInitialized()){
        resizeTexture();
    }
}

void GraphicBoard::updateBottomEdgeWidth(){

    float newEdgeWidth = 0.f;
    if(m_tileLayerPtr && m_labels.isBottomOutsideVisible()){
        newEdgeWidth =  m_labels.getBottomOutsideLabelSize()* m_tileLayerPtr->getTileHeight();
        m_labels.setBottomOutsideWorkHeight(newEdgeWidth);
    }

    if(newEdgeWidth == m_bottomEdgeWidth){
        return;
    }

    m_bottomEdgeWidth = newEdgeWidth;

    if(m_texture.isInitialized()){
        resizeTexture();
    }
}

void GraphicBoard::addLeftInsideLabel_h(const int& row){

    if(!m_tileLayerPtr){
        return;
    }

    Coord coord;
    if(!m_isLeftToRight){
        coord.x = m_tileLayerPtr->getNumColumns()-1;
    }
    coord.y = row;

    auto tilePosition_o = m_tileLayerPtr->getTileTopLeftPosition(coord);
    if(tilePosition_o == std::nullopt){
        return;
    }
    sf::Vector2f tileSize = m_tileLayerPtr->getTileSize();
    auto tileColor_o = m_tileLayerPtr->getTileColor(coord);
    if(tileColor_o == std::nullopt){
        return;
    }
    m_labels.addLeftInsideLabel(tilePosition_o.value(), tileSize, tileColor_o.value());
}

void GraphicBoard::addLeftInsideLabels_h(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.removeLeftInsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        addLeftInsideLabel_h(i);
    }
}

void GraphicBoard::addBottomInsideLabel_h(const int& column){

    if(!m_tileLayerPtr){
        return;
    }

    Coord coord;
    coord.x = column;
    if(m_isTopToBottom){
        coord.y = m_tileLayerPtr->getNumRows() - 1;
    }

    auto tilePosition_o = m_tileLayerPtr->getTileTopLeftPosition(coord);
    if(tilePosition_o == std::nullopt){
        return;
    }
    sf::Vector2f tileSize = m_tileLayerPtr->getTileSize();
    auto tileColor_o = m_tileLayerPtr->getTileColor(coord);
    if(tileColor_o == std::nullopt){
        return;
    }
    m_labels.addBottomInsideLabel(tilePosition_o.value(), tileSize, tileColor_o.value());
}

void GraphicBoard::addBottomInsideLabels_h(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.removeBottomInsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumColumns(); i++){
        addBottomInsideLabel_h(i);
    }
}

void GraphicBoard::addLeftOutsideLabel_h(const int& row){

    if(!m_tileLayerPtr){
        return;
    }

    Coord coord;
    if(!m_isLeftToRight){
        coord.x = m_tileLayerPtr->getNumColumns()-1;
    }
    coord.y = row;
    auto tilePosition_o = m_tileLayerPtr->getTileTopLeftPosition(coord);
    if(tilePosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Tile "
            << coord.getNotation() << " not found for label" << std::endl;
        return;
    }
    sf::Vector2f tileSize = m_tileLayerPtr->getTileSize();
    m_labels.addLeftOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addLeftOutsideLabels_h(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.removeLeftOutsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        addLeftOutsideLabel_h(i);
    }
}

void GraphicBoard::addRightOutsideLabel_h(const int& row){

    if(!m_tileLayerPtr){
        return;
    }

    Coord coord;
    if(m_isLeftToRight){
        coord.x = m_tileLayerPtr->getNumColumns()-1;
    }
    coord.y = row;
    auto tilePosition_o = m_tileLayerPtr->getTileTopLeftPosition(coord);
    if(tilePosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Tile "
            << coord.getNotation() << " not found for label" << std::endl;
        return;
    }
    sf::Vector2f tileSize = m_tileLayerPtr->getTileSize();
    m_labels.addRightOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addRightOutsideLabels_h(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.removeRightOutsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        addRightOutsideLabel_h(i);
    }
}

void GraphicBoard::addTopOutsideLabel_h(const int& column){

    if(!m_tileLayerPtr){
        return;
    }

    Coord coord;
    coord.x = column;
    if(!m_isTopToBottom){
        coord.y = m_tileLayerPtr->getNumRows()-1;
    }
    auto tilePosition_o = m_tileLayerPtr->getTileTopLeftPosition(coord);
    if(tilePosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Tile "
            << coord.getNotation() << " not found for label" << std::endl;
        return;
    }
    sf::Vector2f tileSize = m_tileLayerPtr->getTileSize();
    m_labels.addTopOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addTopOutsideLabels_h(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.removeTopOutsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumColumns(); i++){
        addTopOutsideLabel_h(i);
    }
}

void GraphicBoard::addBottomOutsideLabel_h(const int& column){

    Coord coord;
    coord.x = column;
    if(m_isTopToBottom){
        coord.y = m_tileLayerPtr->getNumRows() - 1;
    }
    auto tilePosition_o = m_tileLayerPtr->getTileTopLeftPosition(coord);
    if(tilePosition_o == std::nullopt){
        std::cerr << "GraphicBoard: Tile "
            << coord.getNotation() << " not found for label" << std::endl;
        return;
    }
    sf::Vector2f tileSize = m_tileLayerPtr->getTileSize();
    m_labels.addBottomOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addBottomOutsideLabels_h(){

    if(!m_tileLayerPtr){
        return;
    }

    m_labels.removeBottomOutsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumColumns(); i++){
        addBottomOutsideLabel_h(i);
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

    m_labels.moveLeftInsideLabels(offset);
    m_labels.moveBottomInsideLabels(offset);
    m_labels.moveLeftOutsideLabels(offset);
    m_labels.moveRightOutsideLabels(offset);
    m_labels.moveTopOutsideLabels(offset);
    m_labels.moveBottomOutsideLabels(offset);
}

void GraphicBoard::moveTurnToken(const sf::Vector2f& offset){
    m_turnToken.move(offset);
}

void GraphicBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_texture);
}