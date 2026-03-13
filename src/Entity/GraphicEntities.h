#pragma once

#include <map>
#include <optional>
#include "../Coord/Coord.h"
#include "GraphicEntity.h"
#include "../Piece/GraphicPiece.h"
#include "../Shape/Circle/GraphicCircle.h"

namespace sigrid{
    class GraphicEntities: public sf::Drawable{
        public:
            GraphicEntities();

            void addPiece(const Coord& coord, const GraphicPiece& piece);
            void addCircle(const Coord& coord, const GraphicCircle& circle);
            void removeEntity(const Coord& coord);

            void clear();

            std::optional<GraphicEntity> getEntityAt(const Coord& coord) const;

            void move(const sf::Vector2f& offset);
            void setEntityPosition(const Coord& coord, const sf::Vector2f& position);

        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::map<Coord, GraphicPiece> m_pieces;
            std::map<Coord, GraphicCircle> m_circles;

    };
}