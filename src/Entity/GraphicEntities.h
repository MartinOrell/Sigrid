#pragma once

#include <map>
#include <optional>
#include "../Coord/Coord.h"
#include "LogicEntity.h"
#include "GraphicEntity.h"
#include "Piece/GraphicPiece.h"
#include "Shape/Circle/GraphicCircle.h"

namespace sigrid{

    class PieceManager;
    class ColorManager;

    class GraphicEntities: public sf::Drawable{
        public:
            GraphicEntities();

            void init(const sf::Vector2f& pieceSize, const float& circleDiameter, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr);

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

            sf::Vector2f m_pieceSize;
            float m_circleDiameter;
            
            PieceManager* m_pieceManagerPtr;
            ColorManager* m_arrowColorManagerPtr;
    };
}