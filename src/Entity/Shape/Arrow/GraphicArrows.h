#pragma once

#include <map>
#include <optional>
#include <vector>

#include "../../../Coord/CoordPair.h"
#include "GraphicArrow.h"

namespace sigrid{
    class GraphicArrows: public sf::Drawable{
        public:
            GraphicArrows();

            void init(const float& arrowThickness, const float& arrowHeadSize);

            std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator begin();
            std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator end();

            void addArrow(const CoordPair& coordPair, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const sf::Color& color);
            void removeArrow(const CoordPair& coordPair);

            float getThickness() const;
            float getHeadSize() const;

            std::optional<GraphicArrow> getArrow(const CoordPair& coordPair) const;

            void move(const sf::Vector2f& offset);

        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::map<CoordPair, GraphicArrow> m_arrows;
            std::vector<CoordPair> m_drawOrder;

            float m_arrowThickness;
            float m_arrowHeadSize;
    };
}