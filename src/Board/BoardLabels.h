#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

namespace sigrid{

    class FontManager;

    class BoardLabels: public sf::Drawable{

        public:
            BoardLabels();

            void showLeftInside();
            void showBottomInside();
            void showLeftOutside();
            void showBottomOutside();

            void hideLeftInside();
            void hideBottomInside();
            void hideLeftOutside();
            void hideBottomOutside();

            void setLeftInsideSize(const float& size);
            void setBottomInsideSize(const float& size);
            void setLeftOutsideSize(const float& size);
            void setBottomOutsideSize(const float& size);

            void setLeftInsideFont(const std::string& fontFilename);
            void setBottomInsideFont(const std::string& fontFilename);
            void setLeftOutsideFont(const std::string& fontFilename);
            void setBottomOutsideFont(const std::string& fontFilename);

            void setFontManagerPtr(FontManager* const managerPtr);

            bool isLeftInsideVisible() const;
            bool isBottomInsideVisible() const;
            bool isLeftOutsideVisible() const;
            bool isBottomOutsideVisible() const;

            float getLeftInsideLabelSize() const;
            float getBottomInsideLabelSize() const;
            float getLeftOutsideLabelSize() const;
            float getBottomOutsideLabelSize() const;

            bool addInsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor);
            bool addInsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor);
            bool addOutsideBottomLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize);
            bool addOutsideLeftLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const float& edgeWidth);

            void removeLeftInsideLabels();
            void removeBottomInsideLabels();
            void removeLeftOutsideLabels();
            void removeBottomOutsideLabels();

            void removeHorizontalLabel();
            void addVerticalLabel(const float& tileHeight, const bool& isTopToBottom);
            void removeVerticalLabel();

            void moveLeftInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            struct SideLabels{
                std::vector<sf::Text> labels;
                bool isVisible = false;
                std::string fontFilename = "";
                float size = 0.f;
            };

            FontManager* m_fontManagerPtr = nullptr;
            SideLabels m_leftOutsideCoordLabels;
            SideLabels m_bottomOutsideCoordLabels;
            SideLabels m_leftInsideCoordLabels;
            SideLabels m_bottomInsideCoordLabels;
    };
}