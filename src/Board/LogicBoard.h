#pragma once

#include <optional>

#include "Entity/Tile/LogicTiles.h"
#include "Entity/LogicEntities.h"
#include "Entity/Shape/Arrow/LogicArrows.h"

namespace sigrid{

class BoardDataContainer;

class LogicBoard{

  public:

    LogicBoard() = default;
    LogicBoard(const LogicBoard&) = default;
    LogicBoard(LogicBoard&&) = default;
    LogicBoard& operator=(const LogicBoard&) = default;
    LogicBoard& operator=(LogicBoard&&) = default;

    bool load(const BoardDataContainer& data);

    const int getNumColumns() const;
    const int getNumRows() const;

    bool isWithinBoard(const sigrid_coord::Coord& coord) const;
    bool isEmptyTile(const sigrid_coord::Coord& coord) const;
    std::optional<LogicTile> getTile(const sigrid_coord::Coord& coord) const;
    std::optional<LogicEntity> getEntityAt(const sigrid_coord::Coord& coord) const;
    std::optional<LogicArrow> getArrowAt(const sigrid_coord::CoordPair& coordPair) const;
    std::string getFen() const;
    int getTurnToMove() const;
    std::vector<int> getRepeatColorIds() const;

    void setTurnToMove(const int& turnToMove);

    bool addEntity(const sigrid_coord::Coord& coord, const LogicEntity& entity);
    bool removeEntity(const sigrid_coord::Coord& coord);
    bool moveEntity(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord);

    bool addTileHighlight(const sigrid_coord::Coord& coord, const int& highlightColorId);
    bool removeTileHighlight(const sigrid_coord::Coord& coord);

    bool addArrow(const sigrid_coord::CoordPair& coordPair, const LogicArrow& arrow);
    bool removeArrow(const sigrid_coord::CoordPair& coordPair);

    bool addTileColumnRight();
    bool addTileColumnLeft();
    bool removeRightTileColumn();
    bool removeLeftTileColumn();
    bool addTileRowUp();
    bool addTileRowDown();
    bool removeTopTileRow();
    bool removeBottomTileRow();

    void print();
    void clearEntities();
    void clearArrows();

    friend std::ostream& operator<<(std::ostream& out, const LogicBoard& board);

  private:
    
    LogicTiles m_tileLayer;
    LogicEntities m_pieceLayer;
    LogicArrows m_arrowLayer;
    int m_turnToMove = 0; //0 = white to move, 1 = black to move

};

}  // namespace sigrid