#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../Font/FontManager.h"

namespace sigrid{

    class BoardLabels: public sf::Drawable{

        public:
            BoardLabels();

            void init(const bool& isInside, const bool& isOutside, const float& insideLabelSizeFactor, const float& outsideLabelSizeFactor, const std::string& fontFilename, FontManager* const fontManagerPtr);

            bool isVisible() const;
            bool isInsideLabelsVisible() const;
            bool isOutsideLabelsVisible() const;

            float getInsideLabelSizeFactor() const;
            float getOutsideLabelSizeFactor() const;

            bool addInsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor);
            bool addInsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor);
            bool addOutsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize);
            bool addOutsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const float& edgeWidth);

            void removeInsideLabels();
            void removeOutsideLabels();

            void show();
            void hide();

            void showInsideLabels();
            void showOutsideLabels();
            void hideInsideLabels();
            void hideOutsideLabels();

            void setOutsideLabelSizeFactor(const float& size);

            void moveLeftInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            FontManager* m_fontManagerPtr;
            bool m_isVisible;
            bool m_isInside;
            std::string m_fontFilename;
            float m_insideLabelSizeFactor;
            float m_outsideLabelSizeFactor;

            std::vector<sf::Text> m_leftOutsideCoordinateLabels;
            std::vector<sf::Text> m_bottomOutsideCoordinateLabels;
            std::vector<sf::Text> m_bottomInsideCoordinateLabels;
            std::vector<sf::Text> m_leftInsideCoordinateLabels;
    };
}