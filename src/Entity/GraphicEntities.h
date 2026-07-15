#pragma once

#include <optional>
#include <memory>

#include "List/Map.h"
#include "Coord/Coord.h"
#include "Entity/LogicEntity.h"
#include "Entity/GraphicEntity.h"
#include "Entity/Piece/GraphicPiece.h"
#include "Entity/Shape/Circle/GraphicCircle.h"

namespace sigrid{

class PieceManager;
class ColorManager;
class IconManager;

class GraphicEntities: public sf::Drawable{

  public:

    GraphicEntities();

    void setPieceManagerPtr(PieceManager* const managerPtr);
    void setColorManagerPtr(ColorManager* const managerPtr);
    void setIconManagerPtr(IconManager* const managerPtr);
    void setPieceSize(const sf::Vector2f& pieceSize);
    void setCircleDiameter(const float& diameter);

    void addEntity(const sigrid_coord::Coord& coord, const sf::Vector2f position, const LogicEntity& entity);
    void removeEntity(const sigrid_coord::Coord& coord);
    void moveEntity(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const sf::Vector2f& newPosition);

    void clear();

    std::optional<GraphicEntity> getEntityAt(const sigrid_coord::Coord& coord) const;

    void removeColumn(const int& columnId);
    void removeRow(const int& rowId);

    void moveEntitiesRight(const float& tileWidth, const bool& isLeftToRight);
    void moveEntitiesLeft(const float& tileWidth, const bool& isLeftToRight);
    void moveEntitiesUp(const float& tileHeight, const bool& isTopToBottom);
    void moveEntitiesDown(const float& tileHeight, const bool& isTopToBottom);

    void move(const sf::Vector2f& offset);
    void setEntityPosition(const sigrid_coord::Coord& coord, const sf::Vector2f& position);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sigrid_list::Map<sigrid_coord::Coord, GraphicPiece> m_pieces;
    sigrid_list::Map<sigrid_coord::Coord, GraphicCircle> m_circles;
    sigrid_list::Map<sigrid_coord::Coord, GraphicArrow> m_arrows;
    sigrid_list::Map<sigrid_coord::Coord, Icon> m_icons;

    sf::Vector2f m_pieceSize = {0.f, 0.f};
    float m_circleDiameter = 0.f;
    
    PieceManager* m_pieceManagerPtr = nullptr;
    ColorManager* m_arrowColorManagerPtr = nullptr;
    IconManager* m_iconManagerPtr = nullptr;
};

}  // namespace sigrid