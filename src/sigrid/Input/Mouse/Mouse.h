#pragma once

#include <optional>
#include <functional> //Reference wrapper

#include <SFML/Window/Mouse.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/lists/Map.h"

namespace sigrid{

class Mouse{

  public:

    Mouse() = default;
    Mouse(const Mouse&) = default;
    Mouse(Mouse&&) = default;
    Mouse& operator=(const Mouse&) = default;
    Mouse& operator=(Mouse&&) = default;

    const std::optional<std::reference_wrapper<const sigrid::Position_f>> getPressPosition(const sf::Mouse::Button& button) const;
    bool isPressed(const sf::Mouse::Button& button) const;

    void press(const sf::Mouse::Button& button, const sigrid::Position_f& position);
    void release(const sf::Mouse::Button& button);

  private:

    sigrid_list::Map<sf::Mouse::Button, std::optional<sigrid::Position_f>> m_pressedPositions;
};

}  // namespace sigrid