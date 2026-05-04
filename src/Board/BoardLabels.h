#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

namespace sigrid{

    class FontManager;

    class BoardLabels: public sf::Drawable{

        public:
            BoardLabels();

            void setInside();
            void setOutside();
            void setInsideLabelSizeFactor(const float& size);
            void setOutsideLabelSizeFactor(const float& size);
            void setFont(const std::string& fontFilename);
            void setFontManagerPtr(FontManager* const fontManagerPtr);

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

            void addHorizontalLabel(const float& tileWidth, const bool& isLeftToRight);
            void removeHorizontalLabel();
            void addVerticalLabel(const float& tileHeight, const bool& isTopToBottom);
            void removeVerticalLabel();

            void show();
            void hide();

            void showInsideLabels();
            void showOutsideLabels();
            void hideInsideLabels();
            void hideOutsideLabels();

            void moveLeftInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            FontManager* m_fontManagerPtr = nullptr;
            bool m_isVisible = false;
            bool m_isInside = false;
            std::string m_fontFilename = "";
            float m_insideLabelSizeFactor = 0.f;
            float m_outsideLabelSizeFactor = 0.f;

            std::vector<sf::Text> m_leftOutsideCoordinateLabels;
            std::vector<sf::Text> m_bottomOutsideCoordinateLabels;
            std::vector<sf::Text> m_bottomInsideCoordinateLabels;
            std::vector<sf::Text> m_leftInsideCoordinateLabels;
    };
}