#pragma once

#include <map>
#include <optional>
#include <memory>
#include "../Coord/Coord.h"
#include "LogicEntity.h"
#include "GraphicEntity.h"
#include "Piece/GraphicPiece.h"
#include "Shape/Circle/GraphicCircle.h"

namespace sigrid{

    class PieceManager;
    class ColorManager;
    class IconManager;

    class GraphicEntities: public sf::Drawable{
        public:
            GraphicEntities();

            void addPieceManager(PieceManager* const pieceManagerPtr);
            void addColorManager(ColorManager* const colorManagerPtr);
            void addIconManager(IconManager* const iconManagerPtr);
            void setPieceSize(const sf::Vector2f& pieceSize);
            void setCircleDiameter(const float& diameter);

            void addEntity(const Coord& coord, const sf::Vector2f position, const LogicEntity& entity);
            void removeEntity(const Coord& coord);
            void moveEntity(const Coord& fromCoord, const Coord& toCoord, const sf::Vector2f& newPosition);

            void clear();

            std::optional<GraphicEntity> getEntityAt(const Coord& coord) const;

            void removeColumn(const int& columnId);
            void removeRow(const int& rowId);

            void moveEntitiesRight(const float& tileWidth, const bool& isLeftToRight);
            void moveEntitiesLeft(const float& tileWidth, const bool& isLeftToRight);
            void moveEntitiesUp(const float& tileHeight, const bool& isTopToBottom);
            void moveEntitiesDown(const float& tileHeight, const bool& isTopToBottom);

            void move(const sf::Vector2f& offset);
            void setEntityPosition(const Coord& coord, const sf::Vector2f& position);

        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::map<Coord, GraphicPiece> m_pieces;
            std::map<Coord, GraphicCircle> m_circles;
            std::map<Coord, GraphicArrow> m_arrows;
            std::map<Coord, Icon> m_icons;

            sf::Vector2f m_pieceSize = {0.f, 0.f};
            float m_circleDiameter = 0.f;
            
            PieceManager* m_pieceManagerPtr = nullptr;
            ColorManager* m_arrowColorManagerPtr = nullptr;
            IconManager* m_iconManagerPtr = nullptr;
    };
}