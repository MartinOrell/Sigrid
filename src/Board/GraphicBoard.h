#pragma once

#include <optional>

#include "Coord/Coord.h"
#include "Coord/CoordPair.h"

#include "Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "Board/BoardLabels.h"
#include "Entity/TurnToken/TurnToken.h"

#include "Entity/Tile/GraphicTile.h"
#include "Entity/Tile/GraphicTiles.h"

#include "Entity/LogicEntity.h"
#include "Entity/GraphicEntity.h"
#include "Entity/GraphicEntities.h"

#include "Entity/Shape/Arrow/LogicArrow.h"
#include "Entity/Shape/Arrow/GraphicArrow.h"
#include "Entity/Shape/Arrow/GraphicArrows.h"

#include "Font/FontManager.h"

#include "SigridRenderTexture/SigridRenderTexture.h"

namespace sigrid{

class LogicBoard;
class BoardDesignContainer;
class PieceManager;
class ColorManager;
class IconManager;

class GraphicBoard: public sf::Drawable{

  public:
    
    GraphicBoard() = default;
    GraphicBoard(const GraphicBoard&) = default;
    GraphicBoard(GraphicBoard&&) = default;
    GraphicBoard& operator=(const GraphicBoard&);
    GraphicBoard& operator=(GraphicBoard&&) = default;
    
    void setPieceManagerPtr(PieceManager* const managerPtr);
    void setTileColorManagerPtr(ColorManager* const managerPtr);
    void setArrowColorManagerPtr(ColorManager* const managerPtr);
    void setFontManagerPtr(FontManager* const managerPtr);
    void setIconManagerPtr(IconManager* const managerPtr);
    void setLeftToRight();
    void setRightToLeft();
    void setTopToBottom();
    void setBottomToTop();

    void loadDesign(const BoardDesignContainer& config);
    void loadBoardState(const LogicBoard& logicBoard);

    sf::Vector2f getTileSize() const;

    void setPosition(const sf::Vector2f& position);

    void setPositionX(float x);

    void setScale(const float scale);

    float getImageWidth() const;

    float getImageHeight() const;

    sf::Image getImage(const int maxWidth, const int maxHeight) const;

    const sf::Vector2f& getTopLeftPosition() const;

    sf::Vector2f getDisplaySize() const;
    float getDisplayWidth() const;
    float getDisplayHeight() const;

    bool contains(const sf::Vector2f& point) const;

    bool isLeftToRight() const;

    bool isTopToBottom() const;

    bool isCoordinatesOutside() const;

    bool isWithinTurnToken(const sf::Vector2f& point) const;

    std::optional<sigrid_coord::Coord> getTileCoord(const sf::Vector2f& point);

    void addEntity(const sigrid_coord::Coord& coord, const LogicEntity& logicEntity);
    void removeEntity(const sigrid_coord::Coord& coord);
    void moveEntity(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord);

    void addTileHighlight(const sigrid_coord::Coord& coord, const int& colorId);
    void removeTileHighlight(const sigrid_coord::Coord& coord);

    void addArrow(const sigrid_coord::CoordPair& coordPair, const LogicArrow& arrow);
    void removeArrow(const sigrid_coord::CoordPair& coordPair);

    void updateDragArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const int& colorId);
    void removeDragArrow();

    void highlightTile(const sigrid_coord::Coord& coord);

    void unhighlight();
    

    void saveImage(const std::string& fileName);

    void clearEntities();
    void clearArrows();

    void addTileColumnRight(const std::vector<int>& repeatTileColorIds);
    void addTileColumnLeft(const std::vector<int>& repeatTileColorIds);
    void removeRightTileColumn();
    void removeLeftTileColumn();

    void addTileRowUp(const std::vector<int>& repeatTileColorIds);
    void addTileRowDown(const std::vector<int>& repeatTileColorIds);
    void removeTopTileRow();
    void removeBottomTileRow();

    void flip();

    void addLeftInsideLabels();
    void addBottomInsideLabels();
    void addLeftOutsideLabels();
    void addRightOutsideLabels();
    void addTopOutsideLabels();
    void addBottomOutsideLabels();

    void removeLeftInsideLabels();
    void removeBottomInsideLabels();
    void removeLeftOutsideLabels();
    void removeRightOutsideLabels();
    void removeTopOutsideLabels();
    void removeBottomOutsideLabels();

    void setCoordinateSize(const float& size);

    void addBorder();

    void removeBorder();

    void addTurnToken(const int& turnToMove);

    void removeTurnToken();

    void setTurnToMove(const int& turnToMove);

  private:

    void initTileLayer(const BoardDesignContainer& config);
    void initPieceLayer(const BoardDesignContainer& config);
    void initArrowLayer(const BoardDesignContainer& config);
    void initLabels(const BoardDesignContainer& config);
    void initTurnToken(const BoardDesignContainer& config);
    void initBorder(const BoardDesignContainer& config);

    void loadBoardState_tileLayer(const LogicBoard& logicBoard);
    void loadBoardState_pieceLayer(const LogicBoard& logicBoard);
    void loadBoardState_turnToken(const LogicBoard& logicBoard);
    void updateBorder();
    void updateLabels();

    void initTurnToken(const int& turnToMove);

    const sf::Color& getBackgroundColor() const;
    sf::Vector2f getTextureSize() const;
    const float& getScale() const;

    float calcTextureWidth() const;
    float calcTextureHeight() const;
    sf::Vector2f calcTextureSize() const;

    void resizeTexture();

    void redrawTexture();

    void updateLeftEdgeWidth();
    void updateRightEdgeWidth();
    void updateTopEdgeWidth();
    void updateBottomEdgeWidth();

    void addLeftInsideLabel_h(const int& row);
    void addLeftInsideLabels_h();
    void addBottomInsideLabel_h(const int& column);
    void addBottomInsideLabels_h();
    void addLeftOutsideLabel_h(const int& row);
    void addLeftOutsideLabels_h();
    void addRightOutsideLabel_h(const int& row);
    void addRightOutsideLabels_h();
    void addTopOutsideLabel_h(const int& column);
    void addTopOutsideLabels_h();
    void addBottomOutsideLabel_h(const int& column);
    void addBottomOutsideLabels_h();

    void moveTiles(const sf::Vector2f& offset);
    void moveTurnToken(const sf::Vector2f& offset);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    SigridRenderTexture m_texture;

    float m_leftEdgeWidth = 0.f;
    float m_rightEdgeWidth = 0.f;
    float m_topEdgeWidth = 0.f;
    float m_bottomEdgeWidth = 0.f;

    RectangleBorder m_border;

    BoardLabels m_labels;

    TurnToken m_turnToken;

    GraphicTiles m_tileLayer;
    GraphicEntities m_pieceLayer;
    GraphicArrows m_arrowLayer;

    bool m_isDragArrowVisible = false;
    GraphicArrow m_dragArrow;

    bool m_isSelectHighlightVisible = false;
    GraphicTile m_selectHighlight;

    ColorManager* m_arrowColorManagerPtr = nullptr;

    bool m_isLeftToRight = true;
    bool m_isTopToBottom = false;
};

}  // namespace sigrid