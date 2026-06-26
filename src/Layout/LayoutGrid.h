#pragma once

#include <optional>
#include <map>

#include "../List/SigridVector.h"
#include "../Coord/CoordPair.h"
#include <SFML/System/Vector2.hpp>

namespace sigrid{

    class LayoutGrid{

        public:
            LayoutGrid();

            void setPx(const unsigned int& x, const float& px);
            void setPy(const unsigned int& y, const float& px);

            void setPxIfLess(const unsigned int& x, const float& px);
            void setPyIfLess(const unsigned int& y, const float& py);
            void setPxIfGreater(const unsigned int& x, const float& px);
            void setPyIfGreater(const unsigned int& y, const float& py);

            void setFromXCoord(const unsigned int& id, const int& x);
            void setFromYCoord(const unsigned int& id, const int& y);
            void setToXCoord(const unsigned int& id, const int& x);
            void setToYCoord(const unsigned int& id, const int& y);

            std::optional<float> getPx(const int& x) const;
            std::optional<float> getPy(const int& y) const;

            std::optional<sf::Vector2f> getTopLeftPosition(const unsigned int& id) const;
            std::optional<sf::Vector2f> getCenterPosition(const unsigned int& id) const;
            std::optional<sf::Vector2f> getSize(const unsigned int& id) const;
            std::optional<sf::Vector2u> getSizeU(const unsigned int& id) const;

            std::optional<float> getWidth(const int& fromX, const int& toX) const;
            std::optional<float> getHeight(const int& fromY, const int& toY) const;

        private:
            SigridVector<float> m_xCoords;
            SigridVector<float> m_yCoords;
            std::map<unsigned int, CoordPair> m_objects;
    };

}