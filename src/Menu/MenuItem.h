#pragma once

#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../Action/Action.h"

namespace sigrid{

    class MenuItem: public sf::Drawable{

        public:
            MenuItem(std::string name, const sf::Font& font, const Action);

            void createGraphic(const unsigned int height);

            void setPosition(sf::Vector2f position);
            void setAction(const Action& action);
            void setText(const std::string& text);
            float getPositionLeft();
            float getPositionRight();
            float getPositionTop();
            bool isWithin(sf::Vector2i point, float maxYPos, float minYPos);
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
            sf::Vector2u m_textOffset;

            bool m_isToggled;
            std::string m_toggledName;
            Action m_toggledAction;
    };

}