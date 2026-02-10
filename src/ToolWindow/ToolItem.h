#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Action/Action.h"

namespace sigrid{

    class ToolItem: public sf::Drawable{
        public:

            ToolItem(const Action&);

            void setSize(const sf::Vector2f& size);
            void setPosition(const sf::Vector2f& position);
            void setTexture(const sf::Texture* texturePtr, bool resetRect = false);
            bool isWithin(const sf::Vector2i& point);

            float getPositionRight();
            Action getAction();
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            sf::RectangleShape m_boxShape;
            sf::RectangleShape m_shape;
            Action m_action;
    };

}