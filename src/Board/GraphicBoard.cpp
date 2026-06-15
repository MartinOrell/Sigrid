#include "GraphicBoard.h"

#include "LogicBoard.h"
#include "BoardDesignContainer.h"
#include "../Color/ColorManager.h"

#include "../Entity/Tile/GraphicTiles.h"
#include "../Entity/GraphicEntities.h"
#include "../Entity/Shape/Arrow/GraphicArrows.h"

#include "../Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "BoardLabels.h"
#include "../Entity/TurnToken/TurnToken.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Image.hpp>

#include <iostream>

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
    if(!m_labelsPtr){
        m_labelsPtr = std::make_unique<BoardLabels>();
    }
    m_labelsPtr->setFontManagerPtr(managerPtr);
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
    m_tileLayerPtr->move({float(m_leftEdgeWidth), (float)m_topEdgeWidth});
    if(m_borderPtr && m_borderPtr->isVisible()){
        m_tileLayerPtr->move({m_borderPtr->getWidth(), m_borderPtr->getWidth()});
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

    if(m_turnTokenPtr){
        m_turnTokenPtr->setTurnToMove(logicBoard.getTurnToMove());
    }

    if(m_borderPtr){;
        sf::Vector2f boardArea;
        boardArea.x = m_tileLayerPtr->getTileWidth() * logicBoard.getNumColumns();
        boardArea.y = m_tileLayerPtr->getTileHeight() * logicBoard.getNumRows();
        m_borderPtr->setEnclosedArea(boardArea);
        m_borderPtr->init(m_borderPtr->isVisible());
    }

    if(m_labelsPtr){
        if(m_labelsPtr->isLeftInsideVisible()){
            addLeftInsideLabels_h();
        }
        if(m_labelsPtr->isBottomInsideVisible()){
            addBottomInsideLabels_h();
        }
        if(m_labelsPtr->isLeftOutsideVisible()){
            updateLeftEdgeWidth();
            addLeftOutsideLabels_h();
        }
        if(m_labelsPtr->isRightOutsideVisible()){
            updateRightEdgeWidth();
            addRightOutsideLabels_h();
        }
        if(m_labelsPtr->isTopOutsideVisible()){
            updateTopEdgeWidth();
            addTopOutsideLabels_h();
        }
        if(m_labelsPtr->isBottomOutsideVisible()){
            updateBottomEdgeWidth();
            addBottomOutsideLabels_h();
        }
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::init(const LogicBoard& logicBoard, const BoardDesignContainer& config){

    m_borderWidth = config.borderWidth;
    
    if(!m_tileLayerPtr){
        m_tileLayerPtr = std::make_unique<GraphicTiles>();
    }
    
    m_tileLayerPtr->setNumColumns(logicBoard.getNumColumns());
    m_tileLayerPtr->setNumRows(logicBoard.getNumRows());
    m_tileLayerPtr->setTileSize({config.tileWidth, config.tileHeight});
    m_tileLayerPtr->setTopLeftPosition({(float)m_leftEdgeWidth, (float)m_topEdgeWidth});
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

    if(m_labelsPtr){
        for(auto& label: config.labels){
            if(label.isInside){
                if(label.position == 0){
                    if(label.isVisible){
                        m_labelsPtr->showLeftInside();
                    }
                    else{
                        m_labelsPtr->hideLeftInside();
                    }
                    m_labelsPtr->setLeftInsideSize(label.size);
                    m_labelsPtr->setLeftInsideFont(label.font);
                }
                else if(label.position == 3){
                    if(label.isVisible){
                        m_labelsPtr->showBottomInside();
                    }
                    else{
                        m_labelsPtr->hideBottomInside();
                    }
                    m_labelsPtr->setBottomInsideSize(label.size);
                    m_labelsPtr->setBottomInsideFont(label.font);
                }
                else{
                    std::cerr << "Unhandled label position: " << label.position << std::endl;
                }
            }
            else{ // outside
                if(label.position == 0){
                    if(label.isVisible){
                        m_labelsPtr->showLeftOutside();
                    }
                    else{
                        m_labelsPtr->hideLeftOutside();
                    }
                    m_labelsPtr->setLeftOutsideSize(label.size);
                    m_labelsPtr->setLeftOutsideFont(label.font);
                }
                else if(label.position == 1){
                    if(label.isVisible){
                        m_labelsPtr->showRightOutside();
                    }
                    else{
                        m_labelsPtr->hideRightOutside();
                    }
                    m_labelsPtr->setRightOutsideSize(label.size);
                    m_labelsPtr->setRightOutsideFont(label.font);
                }
                else if(label.position == 2){
                    if(label.isVisible){
                        m_labelsPtr->showTopOutside();
                    }
                    else{
                        m_labelsPtr->hideTopOutside();
                    }
                    m_labelsPtr->setTopOutsideSize(label.size);
                    m_labelsPtr->setTopOutsideFont(label.font);
                }
                else if(label.position == 3){
                    if(label.isVisible){
                        m_labelsPtr->showBottomOutside();
                    }
                    else{
                        m_labelsPtr->hideBottomOutside();
                    }
                    m_labelsPtr->setBottomOutsideSize(label.size);
                    m_labelsPtr->setBottomOutsideFont(label.font);
                }
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

    if(m_labelsPtr){
        if(m_labelsPtr->isLeftInsideVisible()){
            addLeftInsideLabels_h();
        }
        if(m_labelsPtr->isBottomInsideVisible()){
            addBottomInsideLabels_h();
        }
        if(m_labelsPtr->isLeftOutsideVisible()){
            updateLeftEdgeWidth();
            addLeftOutsideLabels_h();
        }
        if(m_labelsPtr->isRightOutsideVisible()){
            updateRightEdgeWidth();
            addRightOutsideLabels_h();
        }
        if(m_labelsPtr->isTopOutsideVisible()){
            updateTopEdgeWidth();
            addTopOutsideLabels_h();
        }
        if(m_labelsPtr->isBottomOutsideVisible()){
            updateBottomEdgeWidth();
            addBottomOutsideLabels_h();
        }
    }

    if(config.turnToken){
        m_turnTokenPtr = std::make_unique<TurnToken>();
        m_turnTokenPtr->show();
        updateRightEdgeWidth();
        initTurnToken(logicBoard.getTurnToMove());
    }

    if(config.border){

        m_borderPtr = std::make_unique<RectangleBorder>();
        sf::Vector2f boardArea;
        boardArea.x = config.tileWidth* logicBoard.getNumColumns();
        boardArea.y = config.tileHeight* logicBoard.getNumRows();
        m_borderPtr->setWidth(config.borderWidth);
        m_borderPtr->setTopLeftPosition({(float)m_leftEdgeWidth, (float)m_topEdgeWidth});
        m_borderPtr->setEnclosedArea(boardArea);
        m_borderPtr->init(config.border);
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
            std::cerr << "GraphicBoard: Failed to resize texture during assignment operation" << std::endl;
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

    if(rhs.m_labelsPtr){
        if(!m_labelsPtr){
            m_labelsPtr = std::make_unique<BoardLabels>();
        }
        *m_labelsPtr = *(rhs.m_labelsPtr);
    }

    m_borderWidth = rhs.m_borderWidth;

    if(rhs.m_borderPtr){
        if(!m_borderPtr){
            m_borderPtr = std::make_unique<RectangleBorder>();
        }
        *m_borderPtr = *(rhs.m_borderPtr);
    }

    if(rhs.m_turnTokenPtr){
        if(!m_turnTokenPtr){
            m_turnTokenPtr = std::make_unique<TurnToken>();
        }
        *m_turnTokenPtr = *(rhs.m_turnTokenPtr);
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

void GraphicBoard::setPosition(const sf::Vector2f& position){
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

sf::Image GraphicBoard::getImage(const unsigned int maxWidth, const unsigned int maxHeight) const{

    const auto& size = m_texturePtr->getTexture().getSize();
    unsigned int oldWidth = size.x;
    unsigned int oldHeight = size.y;

    float widthRatio = 1.f;
    if(oldWidth > maxWidth){
        widthRatio = (float)maxWidth/(float)oldWidth;
    }
    float heightRatio = 1.f;
    if(oldHeight > maxHeight){
        heightRatio = (float)maxHeight/(float)oldHeight;
    }

    float ratio;
    if(widthRatio < heightRatio){
        ratio = widthRatio;
    }
    else{
        ratio = heightRatio;
    }

    unsigned int newWidth = oldWidth * ratio;
    unsigned int newHeight = oldHeight * ratio;

    sf::Sprite sprite(m_texturePtr->getTexture());
    sprite.setPosition({0.f,0.f});
    sprite.setScale({ratio,ratio});

    sf::RenderTexture newRenderTexture{sf::Vector2u{newWidth, newHeight}};
    newRenderTexture.clear(sf::Color::White);
    newRenderTexture.draw(sprite);
    return newRenderTexture.getTexture().copyToImage();
}

const sf::Vector2f& GraphicBoard::getTopLeftPosition() const{
    return m_position;
}

sf::Vector2f GraphicBoard::getDisplaySize() const{

    if(!m_texturePtr){
        std::cerr << "GraphicBoard: Unable to get display size" << std::endl;
        std::cerr << "TexturePtr is null";
        return sf::Vector2f{0.f,0.f};
    }

    const auto& textureSize = m_texturePtr->getSize();
    const float& x = (float)textureSize.x * m_scale;
    const float& y = (float)textureSize.y * m_scale;
    return sf::Vector2f{x, y};
}

float GraphicBoard::getDisplayWidth() const{
    return (float)m_texturePtr->getSize().x*m_scale;
}

float GraphicBoard::getDisplayHeight() const{
    return (float)m_texturePtr->getSize().y*m_scale;
}


bool GraphicBoard::contains(const sf::Vector2f& point) const{
    sf::Sprite sprite(m_texturePtr->getTexture());
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains((point-m_position)/m_scale);
}

bool GraphicBoard::isLeftToRight() const{
    return m_isLeftToRight;
}

bool GraphicBoard::isTopToBottom() const{
    return m_isTopToBottom;
}

bool GraphicBoard::isCoordinatesOutside() const{
    if(!m_labelsPtr){
        return false;
    }
    return m_labelsPtr->isLeftOutsideVisible();
}

bool GraphicBoard::isWithinTurnToken(const sf::Vector2f& point) const{

    if(!m_turnTokenPtr){
        return false;
    }

    return m_turnTokenPtr->isWithin((point-m_position)/m_scale);
}

std::optional<Coord> GraphicBoard::getTileCoord(const sf::Vector2f& point){

    sf::Vector2f rect = (sf::Vector2f)m_texturePtr->getSize();
    rect.x = rect.x - (float)m_leftEdgeWidth - (float)m_rightEdgeWidth;
    rect.x *= m_scale;

    rect.y = rect.y - (float)m_topEdgeWidth - (float)m_bottomEdgeWidth;
    rect.y *= m_scale;

    float x = point.x - m_position.x;
    x = x - (float)m_leftEdgeWidth*m_scale;
    x = x *(float)m_tileLayerPtr->getNumColumns()/rect.x;

    float y = point.y - m_position.y;
    y = y - (float)m_topEdgeWidth*m_scale;
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

    if(!m_dragArrowPtr){

        if(!m_arrowLayerPtr){
            std::cerr << "GraphicBoard: Unable to update dragArrow position to "
                << toCoord.getNotation() << std::endl;
            std::cerr << "arrowLayer not found" << std::endl;
            return;
        }

        m_dragArrowPtr = std::make_unique<GraphicArrow>();
        m_dragArrowPtr->setFromPosition(fromPosition_o.value());
        m_dragArrowPtr->setToPosition(toPosition_o.value());
        m_dragArrowPtr->setColor(color_o.value());
        m_dragArrowPtr->setThickness(m_arrowLayerPtr->getThickness());
        m_dragArrowPtr->setHeadSize(m_arrowLayerPtr->getHeadSize());
        m_dragArrowPtr->init();
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
        std::cerr << "GraphicBoard: Unable to highlight tile at "
            << coord.getNotation() << std::endl;
        std::cerr << "Tile position not found" << std::endl;
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
    std::cerr << "Saving board image: " << fileName << std::endl;
    auto success = image.saveToFile(fileName);
    if(success && std::filesystem::exists(fileName)){
        std::cerr << "board image: " << fileName << " saved" << std::endl;
    }
    else{
        std::cerr << "Failed to save board image: " << fileName << std::endl;
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
    if(m_borderPtr){
        m_borderPtr->addWidth(m_tileLayerPtr->getTileSize().x);
    }
    if(m_turnTokenPtr){
        m_turnTokenPtr->move(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
    }
    if(m_labelsPtr){
        if(!m_isLeftToRight){
            m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
            m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        }
        m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        int column = m_tileLayerPtr->getNumColumns()-1;
        if(m_labelsPtr->isBottomInsideVisible()){
            addBottomInsideLabel_h(column);
        }
        if(m_labelsPtr->isTopOutsideVisible()){
            addTopOutsideLabel_h(column);
        }
        if(m_labelsPtr->isBottomOutsideVisible()){
            addBottomOutsideLabel_h(column);
        }
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
    if(m_borderPtr){
        m_borderPtr->addWidth(m_tileLayerPtr->getTileSize().x);
    }
    if(m_turnTokenPtr){
        m_turnTokenPtr->move(sf::Vector2f{m_tileLayerPtr->getTileSize().x, 0.f});
    }
    if(m_labelsPtr){
        if(!m_isLeftToRight){
            m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
            m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        }
        m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{m_tileLayerPtr->getTileSize().x,0.f});
        int column = m_tileLayerPtr->getNumColumns()-1;
        if(m_labelsPtr->isBottomInsideVisible()){
            addBottomInsideLabel_h(column);
        }
        if(m_labelsPtr->isTopOutsideVisible()){
            addTopOutsideLabel_h(column);
        }
        if(m_labelsPtr->isBottomOutsideVisible()){
            addBottomOutsideLabel_h(column);
        }
    }
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTileColumnRight(){
    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeColumnRight(m_isLeftToRight);
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
    if(m_turnTokenPtr){
        m_turnTokenPtr->move({-m_tileLayerPtr->getTileSize().x, 0.f});
    }
    if(m_borderPtr){
        m_borderPtr->addWidth(-m_tileLayerPtr->getTileSize().x);
    }
    if(m_labelsPtr){
        m_labelsPtr->removeHorizontalLabel();
        if(!m_isLeftToRight){
            m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
            m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
        }
        m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
    }
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTileColumnLeft(){
    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeColumnLeft(m_isLeftToRight);
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->removeColumn(0);
        m_pieceLayerPtr->moveEntitiesLeft(m_tileLayerPtr->getTileSize().x, m_isLeftToRight);
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->removeColumn(0);
        m_arrowLayerPtr->moveArrowsLeft(m_tileLayerPtr->getTileSize().x, m_isLeftToRight);
    }
    if(m_turnTokenPtr){
        m_turnTokenPtr->move({-m_tileLayerPtr->getTileSize().x, 0.f});
    }
    if(m_borderPtr){
        m_borderPtr->addWidth(-m_tileLayerPtr->getTileSize().x);
    }
    if(m_labelsPtr){
        m_labelsPtr->removeHorizontalLabel();
        if(!m_isLeftToRight){
            m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
            m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
        }
        m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{-m_tileLayerPtr->getTileSize().x,0.f});
    }
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
    if(m_borderPtr){
        m_borderPtr->addHeight(m_tileLayerPtr->getTileSize().y);
    }
    if(m_labelsPtr){
        if(!m_isTopToBottom){
            m_labelsPtr->moveLeftInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveLeftOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        }
        m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        
        int row = m_tileLayerPtr->getNumRows()-1;
        if(m_labelsPtr->isLeftInsideVisible()){
            addLeftInsideLabel_h(row);
        }
        if(m_labelsPtr->isLeftOutsideVisible()){
            addLeftOutsideLabel_h(row);
        }
        if(m_labelsPtr->isRightOutsideVisible()){
            addRightOutsideLabel_h(row);
        }
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
    if(m_borderPtr){
        m_borderPtr->addHeight(m_tileLayerPtr->getTileSize().y);
    }
    if(m_labelsPtr){
        if(!m_isTopToBottom){
            m_labelsPtr->moveLeftInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveLeftOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        }
        m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{0.f, m_tileLayerPtr->getTileSize().y});
        
        int row = m_tileLayerPtr->getNumRows()-1;
        if(m_labelsPtr->isLeftInsideVisible()){
            addLeftInsideLabel_h(row);
        }
        if(m_labelsPtr->isLeftOutsideVisible()){
            addLeftOutsideLabel_h(row);
        }
        if(m_labelsPtr->isRightOutsideVisible()){
            addRightOutsideLabel_h(row);
        }
    }
    updateLeftEdgeWidth();
    updateRightEdgeWidth();
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTileRowUp(){

    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeRowUp(m_isLeftToRight);
    if(m_pieceLayerPtr){
        m_pieceLayerPtr->removeRow(0);
        m_pieceLayerPtr->moveEntitiesUp(m_tileLayerPtr->getTileSize().y, m_isTopToBottom);
    }
    if(m_arrowLayerPtr){
        m_arrowLayerPtr->removeRow(0);
        m_arrowLayerPtr->moveArrowsUp(m_tileLayerPtr->getTileSize().y, m_isTopToBottom);
    }
    if(m_borderPtr){
        m_borderPtr->addHeight(-m_tileLayerPtr->getTileSize().y);
    }
    if(m_labelsPtr){
        m_labelsPtr->removeVerticalLabel();
        if(!m_isTopToBottom){
            m_labelsPtr->moveLeftInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveLeftOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        }
        m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
    }
    updateLeftEdgeWidth();
    updateRightEdgeWidth();
    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTileRowDown(){

    if(!m_tileLayerPtr){
        return;
    }
    m_tileLayerPtr->removeRowDown(m_isTopToBottom);
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
    if(m_borderPtr){
        m_borderPtr->addHeight(-m_tileLayerPtr->getTileSize().y);
    }
    if(m_labelsPtr){
        m_labelsPtr->removeVerticalLabel();
        if(!m_isTopToBottom){
            m_labelsPtr->moveLeftInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveLeftOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
            m_labelsPtr->moveRightOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        }
        m_labelsPtr->moveBottomInsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
        m_labelsPtr->moveBottomOutsideLabels(sf::Vector2f{0.f, -m_tileLayerPtr->getTileSize().y});
    }
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
            arrow.second.set(fromPos,toPos);
        }
    }
    
    if(m_labelsPtr){
        if(m_labelsPtr->isLeftInsideVisible()){
            addLeftInsideLabels();
        }
        if(m_labelsPtr->isBottomInsideVisible()){
            addBottomInsideLabels();
        }
        if(m_labelsPtr->isLeftOutsideVisible()){
            addLeftOutsideLabels();
        }
        if(m_labelsPtr->isRightOutsideVisible()){
            addRightOutsideLabels();
        }
        if(m_labelsPtr->isBottomOutsideVisible()){
            addBottomOutsideLabels();
        }
    }

    redrawTexture();//also called by addCoordinates
}

void GraphicBoard::addLeftInsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->showLeftInside();

    addLeftInsideLabels_h();

    redrawTexture();
}

void GraphicBoard::addBottomInsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->showBottomInside();

    addBottomInsideLabels_h();

    redrawTexture();
}

void GraphicBoard::addLeftOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->showLeftOutside();
    updateLeftEdgeWidth();
    addLeftOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addRightOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->showRightOutside();
    updateRightEdgeWidth();
    addRightOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addTopOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->showTopOutside();
    updateTopEdgeWidth();
    addTopOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::addBottomOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->showBottomOutside();
    updateBottomEdgeWidth();
    addBottomOutsideLabels_h();
    redrawTexture();
}

void GraphicBoard::removeLeftInsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(m_labelsPtr->isLeftInsideVisible()){
        m_labelsPtr->removeLeftInsideLabels();
    }
    m_labelsPtr->hideLeftInside();

    redrawTexture();
}

void GraphicBoard::removeBottomInsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(m_labelsPtr->isBottomInsideVisible()){
        m_labelsPtr->removeBottomInsideLabels();
    }
    m_labelsPtr->hideBottomInside();

    redrawTexture();
}

void GraphicBoard::removeLeftOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(m_labelsPtr->isLeftOutsideVisible()){
        m_labelsPtr->hideLeftOutside();
        updateLeftEdgeWidth();
        m_labelsPtr->removeLeftOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::removeRightOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(m_labelsPtr->isRightOutsideVisible()){
        m_labelsPtr->hideRightOutside();
        updateRightEdgeWidth();
        m_labelsPtr->removeRightOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::removeTopOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(m_labelsPtr->isTopOutsideVisible()){
        m_labelsPtr->hideTopOutside();
        updateTopEdgeWidth();
        m_labelsPtr->removeTopOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::removeBottomOutsideLabels(){

    if(!m_labelsPtr){
        return;
    }

    if(m_labelsPtr->isBottomOutsideVisible()){
        m_labelsPtr->hideBottomOutside();
        updateBottomEdgeWidth();
        m_labelsPtr->removeBottomOutsideLabels();
    }

    redrawTexture();
}

void GraphicBoard::setCoordinateSize(const float& size){

    if(!m_labelsPtr){
        return;
    }

    m_labelsPtr->setLeftOutsideSize(size);
    m_labelsPtr->setRightOutsideSize(size);
    m_labelsPtr->setTopOutsideSize(size);
    m_labelsPtr->setBottomOutsideSize(size);

    unsigned int leftEdgeWidth = size* m_tileLayerPtr->getTileWidth();
    unsigned int leftEdgeHeight = size* m_tileLayerPtr->getTileHeight();

    m_labelsPtr->showLeftOutside();
    updateLeftEdgeWidth();
    m_labelsPtr->showRightOutside();
    updateRightEdgeWidth();
    m_labelsPtr->showTopOutside();
    updateTopEdgeWidth();
    m_labelsPtr->showBottomOutside();
    updateBottomEdgeWidth();

    addLeftOutsideLabels_h();
    addRightOutsideLabels_h();
    addTopOutsideLabels_h();
    addBottomOutsideLabels_h();
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
        m_borderPtr->setWidth((float)m_borderWidth);
        m_borderPtr->setTopLeftPosition(topLeftPosition);
        m_borderPtr->setEnclosedArea(boardArea);
        m_borderPtr->init(isVisible);
    }
    else if(m_borderPtr->isVisible()){
        return;
    }

    sf::Vector2f topLeftPosition{(float)m_leftEdgeWidth, (float)m_topEdgeWidth};
    sf::Vector2f boardArea;
    boardArea.x = m_tileLayerPtr->getTileWidth()* m_tileLayerPtr->getNumColumns();
    boardArea.y = m_tileLayerPtr->getTileHeight()*m_tileLayerPtr->getNumRows();

    m_borderPtr->setEnclosedArea(boardArea);
    m_borderPtr->setTopLeftPosition(topLeftPosition);
    m_borderPtr->show();

    moveTiles({(float)m_borderWidth, (float)m_borderWidth});
    if(m_labelsPtr){
        m_labelsPtr->moveLeftInsideLabels({(float)m_borderWidth, (float)m_borderWidth});
        m_labelsPtr->moveBottomInsideLabels({(float)m_borderWidth, (float)m_borderWidth});
        m_labelsPtr->moveLeftOutsideLabels({0.f, (float)m_borderWidth});
        m_labelsPtr->moveBottomOutsideLabels({(float)m_borderWidth, 2.f*(float)m_borderWidth});
    }
    
    moveTurnToken({2.f*(float)m_borderWidth, (float)m_borderWidth});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeBorder(){

    if(!m_borderPtr || m_borderPtr->isHidden()){
        return;
    }

    m_borderPtr->hide();

    moveTiles({-(float)m_borderWidth, -(float)m_borderWidth});
    moveTurnToken({-2.f*(float)m_borderWidth, -(float)m_borderWidth});
    if(m_labelsPtr){
        m_labelsPtr->moveLeftInsideLabels({-(float)m_borderWidth, -(float)m_borderWidth});
        m_labelsPtr->moveBottomInsideLabels({-(float)m_borderWidth, -(float)m_borderWidth});
        m_labelsPtr->moveLeftOutsideLabels({0.f, -(float)m_borderWidth});
        m_labelsPtr->moveBottomOutsideLabels({-(float)m_borderWidth, -2.f*(float)m_borderWidth});
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addTurnToken(const int& turnToMove){

    if(m_turnTokenPtr && m_turnTokenPtr->isVisible()){
        return;
    }

    if(!m_turnTokenPtr){
        m_turnTokenPtr = std::make_unique<TurnToken>();
        m_turnTokenPtr->show();
        updateRightEdgeWidth();
        initTurnToken(turnToMove);
    }
    else{
        m_turnTokenPtr->show();
        updateRightEdgeWidth();
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeTurnToken(){

    if(!m_turnTokenPtr){
        return;
    }

    m_turnTokenPtr->hide();
    updateRightEdgeWidth();

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::setTurnToMove(const int& turnToMove){
    if(!m_turnTokenPtr){
        return;
    }

    m_turnTokenPtr->setTurnToMove(turnToMove);

    m_texturePtr->draw(*m_turnTokenPtr);
}

void GraphicBoard::initTurnToken(const int& turnToMove){
    float radius = 0.2* m_tileLayerPtr->getTileHeight();
    
    float x = m_leftEdgeWidth;
    if(m_borderPtr && m_borderPtr->isVisible()){
        x+= 2*m_borderWidth;
    }
    x += m_tileLayerPtr->getTileWidth()*m_tileLayerPtr->getNumColumns();

    float workWidth = m_rightEdgeWidth;
    if(m_labelsPtr && m_labelsPtr->isRightOutsideVisible()){
        workWidth -= m_labelsPtr->getRightOutsideWorkWidth();
        x += m_labelsPtr->getRightOutsideWorkWidth();
    }

    x += workWidth/2.f;
    float y = m_topEdgeWidth;
    y += m_tileLayerPtr->getTileHeight()/2.f;

    m_turnTokenPtr->setRadius(radius);
    m_turnTokenPtr->setCenterPosition({x,y});
    m_turnTokenPtr->setTurnToMove(turnToMove);
    m_turnTokenPtr->init();
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
        std::cerr << "GraphicWindow: Failed to resize texture" << std::endl;
        return;
    }
}

void GraphicBoard::redrawTexture(){
    if(!m_texturePtr){
        return;
    }

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

    if(m_labelsPtr){
        m_texturePtr->draw(*m_labelsPtr);
    }

    if(m_borderPtr){
        m_texturePtr->draw(*m_borderPtr);
    }

    if(m_turnTokenPtr){
        m_texturePtr->draw(*m_turnTokenPtr);
    }
}

void GraphicBoard::updateLeftEdgeWidth(){

    unsigned int newEdgeWidth = 0;
    if(m_labelsPtr && m_tileLayerPtr && m_labelsPtr->isLeftOutsideVisible()){
        int numDigits = notation::getRowNotation(m_tileLayerPtr->getNumRows()-1).length();
        float labelSize = m_labelsPtr->getLeftOutsideLabelSize();
        float tileWidth = m_tileLayerPtr->getTileWidth();

        newEdgeWidth = (float)numDigits*labelSize*tileWidth/2.f + tileWidth/5.f;
        m_labelsPtr->setLeftOutsideWorkWidth((float)newEdgeWidth);
    }

    if(newEdgeWidth == m_leftEdgeWidth){
        return;
    }

    float moveX = (float)newEdgeWidth - (float)m_leftEdgeWidth;
    m_leftEdgeWidth = newEdgeWidth;

    moveTiles({moveX, 0.f});
    if(m_borderPtr){
        m_borderPtr->move({moveX, 0.f});
    }
    moveTurnToken({moveX, 0.f});

    if(m_labelsPtr&& m_labelsPtr->isLeftOutsideVisible()){
        m_labelsPtr->moveLeftOutsideLabels({-moveX/2.f, 0.f});
    }

    if(m_texturePtr){
        resizeTexture();
    }
}

void GraphicBoard::updateRightEdgeWidth(){

    unsigned int newEdgeWidth = 0;

    if(m_labelsPtr && m_tileLayerPtr && m_labelsPtr->isRightOutsideVisible()){
        int numDigits = notation::getRowNotation(m_tileLayerPtr->getNumRows()-1).length();
        float labelSize = m_labelsPtr->getRightOutsideLabelSize();
        float tileWidth = m_tileLayerPtr->getTileWidth();

        float newWorkWidth = (float)numDigits*labelSize*tileWidth/2.f + tileWidth/5.f;
        float oldWorkWidth = m_labelsPtr->getRightOutsideWorkWidth();

        if(newWorkWidth != oldWorkWidth){
            m_labelsPtr->setRightOutsideWorkWidth(newWorkWidth);

            float moveX = newWorkWidth - oldWorkWidth;
            m_labelsPtr->moveRightOutsideLabels({moveX/2.f, 0.f});
            if(m_turnTokenPtr){
                m_turnTokenPtr->move({moveX, 0.f});
            }
        }

        newEdgeWidth += newWorkWidth;
    }

    if(m_turnTokenPtr && m_tileLayerPtr && m_turnTokenPtr->isVisible()){
        newEdgeWidth += (unsigned int)(m_tileLayerPtr->getTileWidth()/2.f);
    }

    if(newEdgeWidth == m_rightEdgeWidth){
        return;
    }

    m_rightEdgeWidth = newEdgeWidth;

    if(m_turnTokenPtr){   
        float x = m_leftEdgeWidth;
        if(m_borderPtr && m_borderPtr->isVisible()){
            x+= 2*m_borderWidth;
        }
        x += m_tileLayerPtr->getTileWidth()*m_tileLayerPtr->getNumColumns();

        float workWidth = m_rightEdgeWidth;
        if(m_labelsPtr && m_labelsPtr->isRightOutsideVisible()){
            workWidth -= m_labelsPtr->getRightOutsideWorkWidth();
            x += m_labelsPtr->getRightOutsideWorkWidth();
        }

        x += workWidth/2.f;
        float y = m_topEdgeWidth;
        y += m_tileLayerPtr->getTileHeight()/2.f;

        sf::Vector2f oldPosition = m_turnTokenPtr->getCenterPosition();
        sf::Vector2f newPosition{x,y};
        if(oldPosition != newPosition){
            m_turnTokenPtr->setCenterPosition({x,y});
        }
    }

    if(m_texturePtr){
        resizeTexture();
    }
}

void GraphicBoard::updateTopEdgeWidth(){

    unsigned int newEdgeWidth = 0;

    if(m_labelsPtr && m_labelsPtr->isTopOutsideVisible()){
        newEdgeWidth = m_labelsPtr->getTopOutsideLabelSize()* m_tileLayerPtr->getTileHeight();
        m_labelsPtr->setTopOutsideWorkHeight((float)newEdgeWidth);
    }

    if(newEdgeWidth == m_topEdgeWidth){
        return;
    }

    float moveY = (float)newEdgeWidth - (float)m_topEdgeWidth;
    m_topEdgeWidth = newEdgeWidth;
    

    moveTiles({0.f, moveY});
    if(m_borderPtr){
        m_borderPtr->move({0.f, moveY});
    }
    moveTurnToken({0.f, moveY});

    if(m_texturePtr){
        resizeTexture();
    }
}

void GraphicBoard::updateBottomEdgeWidth(){

    unsigned int newEdgeWidth = 0;
    if(m_labelsPtr && m_tileLayerPtr && m_labelsPtr->isBottomOutsideVisible()){
        newEdgeWidth =  m_labelsPtr->getBottomOutsideLabelSize()* m_tileLayerPtr->getTileHeight();
        m_labelsPtr->setBottomOutsideWorkHeight((float)newEdgeWidth);
    }

    if(newEdgeWidth == m_bottomEdgeWidth){
        return;
    }

    m_bottomEdgeWidth = newEdgeWidth;

    if(m_texturePtr){
        resizeTexture();
    }
}

void GraphicBoard::addLeftInsideLabel_h(const int& row){

    if(!m_labelsPtr){
        return;
    }

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
    m_labelsPtr->addLeftInsideLabel(tilePosition_o.value(), tileSize, tileColor_o.value());
}

void GraphicBoard::addLeftInsideLabels_h(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->removeLeftInsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        addLeftInsideLabel_h(i);
    }
}

void GraphicBoard::addBottomInsideLabel_h(const int& column){

    if(!m_labelsPtr){
        return;
    }

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
    m_labelsPtr->addBottomInsideLabel(tilePosition_o.value(), tileSize, tileColor_o.value());
}

void GraphicBoard::addBottomInsideLabels_h(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->removeBottomInsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumColumns(); i++){
        addBottomInsideLabel_h(i);
    }
}

void GraphicBoard::addLeftOutsideLabel_h(const int& row){

    if(!m_labelsPtr){
        return;
    }

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
    m_labelsPtr->addLeftOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addLeftOutsideLabels_h(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->removeLeftOutsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        addLeftOutsideLabel_h(i);
    }
}

void GraphicBoard::addRightOutsideLabel_h(const int& row){

    if(!m_labelsPtr){
        return;
    }

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
    m_labelsPtr->addRightOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addRightOutsideLabels_h(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->removeRightOutsideLabels();

    for(int i = 0; i < m_tileLayerPtr->getNumRows(); i++){
        addRightOutsideLabel_h(i);
    }
}

void GraphicBoard::addTopOutsideLabel_h(const int& column){

    if(!m_labelsPtr){
        return;
    }

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
    m_labelsPtr->addTopOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addTopOutsideLabels_h(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->removeTopOutsideLabels();

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
    m_labelsPtr->addBottomOutsideLabel(tilePosition_o.value(), tileSize);
}

void GraphicBoard::addBottomOutsideLabels_h(){

    if(!m_labelsPtr){
        return;
    }

    if(!m_tileLayerPtr){
        return;
    }

    m_labelsPtr->removeBottomOutsideLabels();

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

    if(m_labelsPtr){
        m_labelsPtr->moveLeftInsideLabels(offset);
        m_labelsPtr->moveBottomInsideLabels(offset);
        m_labelsPtr->moveLeftOutsideLabels(offset);
        m_labelsPtr->moveRightOutsideLabels(offset);
        m_labelsPtr->moveTopOutsideLabels(offset);
        m_labelsPtr->moveBottomOutsideLabels(offset);
    }
}

void GraphicBoard::moveTurnToken(const sf::Vector2f& offset){
    if(m_turnTokenPtr){
        m_turnTokenPtr->move(offset);
    }
}

void GraphicBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite sprite(m_texturePtr->getTexture());
    sprite.setPosition(m_position);
    sprite.move({0.f, m_scale*(float)m_texturePtr->getTexture().getSize().y});
    sprite.setScale({m_scale,-m_scale});
    target.draw(sprite);
}