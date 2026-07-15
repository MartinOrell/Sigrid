#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>

namespace sigrid{

class FontManager;

class BoardLabels: public sf::Drawable{

  public:

    BoardLabels() = default;
    BoardLabels(const BoardLabels&) = default;
    BoardLabels(BoardLabels&&) = default;
    BoardLabels& operator=(const BoardLabels&) = default;
    BoardLabels& operator=(BoardLabels&&) = default;

    void showLeftInside();
    void showBottomInside();
    void showLeftOutside();
    void showRightOutside();
    void showTopOutside();
    void showBottomOutside();

    void hideLeftInside();
    void hideBottomInside();
    void hideLeftOutside();
    void hideRightOutside();
    void hideTopOutside();
    void hideBottomOutside();

    void setLeftInsideSize(const float& size);
    void setBottomInsideSize(const float& size);
    void setLeftOutsideSize(const float& size);
    void setRightOutsideSize(const float& size);
    void setTopOutsideSize(const float& size);
    void setBottomOutsideSize(const float& size);

    void setLeftInsideFont(const std::string& fontFilename);
    void setBottomInsideFont(const std::string& fontFilename);
    void setLeftOutsideFont(const std::string& fontFilename);
    void setRightOutsideFont(const std::string& fontFilename);
    void setTopOutsideFont(const std::string& fontFilename);
    void setBottomOutsideFont(const std::string& fontFilename);

    void setLeftOutsideWorkWidth(const float& width);
    void setRightOutsideWorkWidth(const float& width);
    void setTopOutsideWorkHeight(const float& height);
    void setBottomOutsideWorkHeight(const float& height);

    void setFontManagerPtr(FontManager* const managerPtr);

    bool isLeftInsideVisible() const;
    bool isBottomInsideVisible() const;
    bool isLeftOutsideVisible() const;
    bool isRightOutsideVisible() const;
    bool isTopOutsideVisible() const;
    bool isBottomOutsideVisible() const;

    float getLeftInsideLabelSize() const;
    float getBottomInsideLabelSize() const;
    float getLeftOutsideLabelSize() const;
    float getRightOutsideLabelSize() const;
    float getTopOutsideLabelSize() const;
    float getBottomOutsideLabelSize() const;

    float getRightOutsideWorkWidth() const;

    bool addLeftInsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor);
    bool addBottomInsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize, const sf::Color& tileColor);
    bool addLeftOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize);
    bool addRightOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize);
    bool addTopOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize);
    bool addBottomOutsideLabel(const sf::Vector2f& tilePosition, const sf::Vector2f& tileSize);

    void removeLeftInsideLabels();
    void removeBottomInsideLabels();
    void removeLeftOutsideLabels();
    void removeRightOutsideLabels();
    void removeTopOutsideLabels();
    void removeBottomOutsideLabels();

    void removeHorizontalLabel();
    void removeVerticalLabel();

    void moveLeftInsideLabels(const sf::Vector2f& offset);
    void moveBottomInsideLabels(const sf::Vector2f& offset);
    void moveLeftOutsideLabels(const sf::Vector2f& offset);
    void moveRightOutsideLabels(const sf::Vector2f& offset);
    void moveTopOutsideLabels(const sf::Vector2f& offset);
    void moveBottomOutsideLabels(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct SideLabels{
        std::vector<sf::Text> labels;
        bool isVisible = false;
        std::string fontFilename = "";
        float labelSizeFactor = 0.f; //fraction of tileHeight
    };

    FontManager* m_fontManagerPtr = nullptr;
    SideLabels m_leftInsideCoordLabels;
    SideLabels m_bottomInsideCoordLabels;
    SideLabels m_leftOutsideCoordLabels;
    SideLabels m_rightOutsideCoordLabels;
    SideLabels m_topOutsideCoordLabels;
    SideLabels m_bottomOutsideCoordLabels;
    float m_leftWorkWidth = 0.f;
    float m_rightWorkWidth = 0.f;
    float m_topWorkHeight = 0.f;
    float m_bottomWorkHeight = 0.f;
};

}  // namespace sigrid