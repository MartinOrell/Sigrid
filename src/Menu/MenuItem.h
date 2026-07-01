#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "../Action/Action.h"

namespace sf{
    class RectangleShape;
}

namespace sigrid{

    class MenuItem: public sf::Drawable{

        public:
            MenuItem();
            MenuItem(const MenuItem& src);
            MenuItem& operator=(const MenuItem& rhs);

            void createGraphic(const unsigned int height);

            void setName(const std::string& name);
            void setFont(const sf::Font& font);
            void setPosition(const sf::Vector2f& position);
            void setAction(const Action& action);
            void setText(const std::string& text);
            float getPositionLeft();
            float getPositionRight();
            float getPositionTop();
            bool isWithin(const sf::Vector2f& point, const float& maxYPos, const float& minYPos);
            Action getAction();
            std::string getName();
            void addToggle(const std::string& text, const Action&);
            void toggle();
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::string m_name = "";
            sf::RectangleShape m_shape;
            Action m_action;

            std::unique_ptr<sf::Text> m_textPtr;
            sf::Vector2f m_textOffset = {15.f,5.f};

            bool m_isToggled = false;
            std::string m_toggledName = "";
            Action m_toggledAction;
    };

}