#pragma once

#include <optional>

#include "List/Vector.h"
#include "List/Map.h"
#include "Coord/CoordPair.h"
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

    void setFromXCoord(const int& id, const int& x);
    void setFromYCoord(const int& id, const int& y);
    void setToXCoord(const int& id, const int& x);
    void setToYCoord(const int& id, const int& y);

    std::optional<float> getPx(const int& x) const;
    std::optional<float> getPy(const int& y) const;

    std::optional<sf::Vector2f> getTopLeftPosition(const int& id) const;
    std::optional<sf::Vector2f> getCenterPosition(const int& id) const;
    std::optional<sf::Vector2f> getSize(const int& id) const;

    std::optional<float> getWidth(const int& fromX, const int& toX) const;
    std::optional<float> getHeight(const int& fromY, const int& toY) const;

  private:

    sigrid_list::Vector<float> m_xCoords;
    sigrid_list::Vector<float> m_yCoords;
    sigrid_list::Map<int, CoordPair> m_objects;
};

}  // namespace sigrid