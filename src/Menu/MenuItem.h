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
            MenuItem(const std::string& name, const sf::Font& font, const Action);

            void createGraphic(const unsigned int height);

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

            std::string m_name;
            std::unique_ptr<sf::RectangleShape> m_shapePtr;
            Action m_action;

            sf::Text m_text;
            sf::Vector2f m_textOffset;

            bool m_isToggled;
            std::string m_toggledName;
            Action m_toggledAction;
    };

}