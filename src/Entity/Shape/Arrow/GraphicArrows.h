#pragma once

#include <map>
#include <optional>
#include <vector>

#include "../../../Coord/CoordPair.h"
#include "GraphicArrow.h"

namespace sigrid{

    class LogicArrow;
    class ColorManager;

    class GraphicArrows: public sf::Drawable{
        public:
            GraphicArrows();

            void setThickness(const float& thickness);
            void setHeadSize(const float& headSize);
            void setColorManagerPtr(ColorManager* const managerPtr);
            
            std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator begin();
            std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator end();

            void addArrow(const CoordPair& coordPair, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const LogicArrow& logicArrow);
            void removeArrow(const CoordPair& coordPair);

            float getThickness() const;
            float getHeadSize() const;

            std::optional<GraphicArrow> getArrow(const CoordPair& coordPair) const;

            void clear();

            void removeColumn(const int& columnId);
            void removeRow(const int& rowId);

            void moveArrowsRight(const float& tileWidth, const bool& isLeftToRight);
            void moveArrowsLeft(const float& tileWidth, const bool& isLeftToRight);
            void moveArrowsUp(const float& tileHeight, const bool& isTopToBottom);
            void moveArrowsDown(const float& tileHeight, const bool& isTopToBottom);

            void move(const sf::Vector2f& offset);

        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            ColorManager* m_colorManagerPtr = nullptr;

            std::map<CoordPair, GraphicArrow> m_arrows;
            std::vector<CoordPair> m_drawOrder;

            float m_arrowThickness = 0.f;
            float m_arrowHeadSize = 0.f;
    };
}