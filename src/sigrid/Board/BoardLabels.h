#pragma once

#include <SFML/Graphics/Text.hpp>

#include "sigrid/utilities/Size/Size_f.h"
#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Offset/Offset_f.h"
#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/Color/Color.h"

#include "sigrid/Board/BoardLabelContainer.h"
#include "sigrid/Board/SideLabels.h"

namespace sigrid{

class FontManager;

class BoardLabels: public sf::Drawable{

  public:

    BoardLabels() = default;
    BoardLabels(const BoardLabels&) = default;
    BoardLabels(BoardLabels&&) = default;
    BoardLabels& operator=(const BoardLabels&) = default;
    BoardLabels& operator=(BoardLabels&&) = default;

    sigrid_list::Vector<BoardLabelContainer> getContainer() const;

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

    void setLeftInsideFont(const sigrid::String& fontFilename);
    void setBottomInsideFont(const sigrid::String& fontFilename);
    void setLeftOutsideFont(const sigrid::String& fontFilename);
    void setRightOutsideFont(const sigrid::String& fontFilename);
    void setTopOutsideFont(const sigrid::String& fontFilename);
    void setBottomOutsideFont(const sigrid::String& fontFilename);

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

    bool addLeftInsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize, const sigrid::Color& tileColor);
    bool addBottomInsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize, const sigrid::Color& tileColor);
    bool addLeftOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize);
    bool addRightOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize);
    bool addTopOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize);
    bool addBottomOutsideLabel(const sigrid::Position_f& tilePosition, const sigrid::Size_f& tileSize);

    void removeLeftInsideLabels();
    void removeBottomInsideLabels();
    void removeLeftOutsideLabels();
    void removeRightOutsideLabels();
    void removeTopOutsideLabels();
    void removeBottomOutsideLabels();

    void removeHorizontalLabel();
    void removeVerticalLabel();

    void moveLeftInsideLabels(const sigrid::Offset_f& offset);
    void moveBottomInsideLabels(const sigrid::Offset_f& offset);
    void moveLeftOutsideLabels(const sigrid::Offset_f& offset);
    void moveRightOutsideLabels(const sigrid::Offset_f& offset);
    void moveTopOutsideLabels(const sigrid::Offset_f& offset);
    void moveBottomOutsideLabels(const sigrid::Offset_f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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