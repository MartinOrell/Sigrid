#pragma once

#include <optional>
#include <string>

#include "Board/GraphicBoard.h"
#include "Board/LogicBoard.h"
#include "Entity/Piece/PieceManager.h"

namespace sigrid{

class BoardDataContainer;
class LogicTile;
class IconManager;

class Board: public sf::Drawable{

  public:

    Board() = default;
    Board(const Board&);
    Board(Board&&) = default;
    Board& operator=(const Board&) = default;
    Board& operator=(Board&&) = default;

    void setPieceManagerPtr(PieceManager* const managerPtr);
    void setTileColorManagerPtr(ColorManager* const managerPtr);
    void setArrowColorManagerPtr(ColorManager* const managerPtr);
    void setFontManagerPtr(FontManager* const managerPtr);
    void setIconManagerPtr(IconManager* const managerPtr);
    void setLeftToRight();
    void setRightToLeft();
    void setTopToBottom();
    void setBottomToTop();

    void loadBoardData(const BoardDataContainer& boardData);
    void init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData);

    void setPosition(const sf::Vector2f& position);

    void setPositionX(const float x);

    void setScale(const float scale);

    void setFilename(const std::string& filename);

    void setImageFilename(const std::string& filename);

    int getNumColumns() const;

    int getImageWidth() const;

    int getImageHeight() const;

    sf::Image getImage(const int maxWidth, const int maxHeight) const;

    const sf::Vector2f& getTopLeftPosition() const;

    sf::Vector2f getDisplaySize() const;
    float getDisplayWidth() const;
    float getDisplayHeight() const;

    std::string getName() const;

    std::string getFilename() const;

    std::string getImageFilename() const;

    bool contains(const sf::Vector2f& point) const;

    bool isEmptyTile(const sigrid_coord::Coord& coord) const;

    bool isCoordinatesOutside() const;

    bool isWithinTurnToken(const sf::Vector2f& point) const;

    bool isImageFilenameSet() const;

    std::optional<sigrid_coord::Coord> getTileCoord(const sf::Vector2f& point);

    std::optional<LogicTile> getTile(const sigrid_coord::Coord& coord);

    std::optional<LogicEntity> getLogicEntity(const sigrid_coord::Coord& coord);

    std::optional<LogicArrow> getLogicArrow(const sigrid_coord::CoordPair& coordPair);

    std::string getFen() const;

    void select(const sigrid_coord::Coord& coord);

    void deselect();

    void addEntity(const sigrid_coord::Coord& coord, const LogicEntity& newEntity);
    void removeEntity(const sigrid_coord::Coord& coord);

    void addEntityAtSelection(const LogicEntity& newEntity);
    void dragAndDrop(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord);

    void addArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const LogicArrow& newArrow);
    void removeArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord);

    void addTileHighlight(const sigrid_coord::Coord& coord, const int& colorId);
    void removeTileHighlight(const sigrid_coord::Coord& coord);

    void updateDragArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const int& colorId);
    void removeDragArrow();

    void loadFen(const std::string& fen);

    void save();

    void clearEntities();
    void clearArrows();
    void print();

    void flipBoard();

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

    void addTileColumnRight();

    void addTileColumnLeft();

    void removeRightTileColumn();

    void removeLeftTileColumn();

    void addTileRowUp();

    void addTileRowDown();

    void removeTopTileRow();

    void removeBottomTileRow();

    void addBorder();

    void removeBorder();

    void addTurnToken();

    void removeTurnToken();

    void toggleTurnToken();

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    LogicBoard m_logicBoard;

    GraphicBoard m_graphicBoard;

    std::optional<sigrid_coord::Coord> m_selection_o = std::nullopt;

    std::string m_filename;
    std::string m_imageFilename;
};

}  // Namespace sigrid