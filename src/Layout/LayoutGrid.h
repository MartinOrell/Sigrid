#pragma once

#include <optional>
#include <vector>
#include <map>
#include "../Coord/CoordPair.h"
#include <SFML/System/Vector2.hpp>

namespace sigrid{

    class LayoutGrid{

        public:
            LayoutGrid();

            void setPx(const int& x, const float& px);
            void setPy(const int& y, const float& px);

            void setPxIfLess(const int& x, const float& px);
            void setPyIfLess(const int& y, const float& py);
            void setPxIfGreater(const int& x, const float& px);
            void setPyIfGreater(const int& y, const float& py);

            void setFromXCoord(const unsigned int& id, const int& x);
            void setFromYCoord(const unsigned int& id, const int& y);
            void setToXCoord(const unsigned int& id, const int& x);
            void setToYCoord(const unsigned int& id, const int& y);

            float getPx(const int& x);
            float getPy(const int& y);

            std::optional<sf::Vector2f> getPosition(const unsigned int& id);
            std::optional<sf::Vector2u> getSizeU(const unsigned int& id);

            std::optional<float> getWidth(const int& fromX, const int& toX);
            std::optional<float> getHeight(const int& fromY, const int& toY);

        private:
            std::vector<float> m_xCoords;
            std::vector<float> m_yCoords;
            std::map<unsigned int, CoordPair> m_objects;
    };

}