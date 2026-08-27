#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/Color/Color.h"

namespace sigrid{

class RenderWindow{

  public:
    
    RenderWindow() = default;
    RenderWindow(const RenderWindow&) = default;
    RenderWindow(RenderWindow&&) = default;
    RenderWindow& operator=(const RenderWindow&) = default;
    RenderWindow& operator=(RenderWindow&&) = default;

    bool create(const int& width, const int& height);
    void setTitle(const sigrid::String& title);
    bool setFramerateLimit(const int& limit);
    void setView(const sf::Rect<float>& visibleArea);
    void setBackgroundColor(const sigrid::Color& backgroundColor);

    bool isOpen() const;
    std::optional<sf::Event> pollEvent();
    void close();

    void clear();
    void draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default);
    void display();

  private:

    sf::RenderWindow m_renderWindow;
    sigrid::Color m_backgroundColor;

};
    

}  // namespace sigrid