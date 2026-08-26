#pragma once

#include <memory>
#include <vector>
#include <optional>

#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "sigrid/Window/ToolWindow/ToolWindowContainer.h"

#include "sigrid/Action/Action.h"
#include "sigrid/Board/Board.h"

#include "sigrid/utilities/RenderTexture/RenderTexture.h"

namespace sigrid{

class ToolWindow: public sf::Drawable{

  public:

    ToolWindow() = default;
    ToolWindow(const ToolWindow&) = default;
    ToolWindow(ToolWindow&&) = default;
    ToolWindow& operator=(const ToolWindow&) = default;
    ToolWindow& operator=(ToolWindow&&) = default;

    void setTileColorManagerPtr(ColorManager* const managerPtr);

    void setIconManagerPtr(IconManager* const managerPtr);

    void setPieceManagerPtr(PieceManager* const managerPtr);

    void setArrowColorManagerPtr(ColorManager* const managerPtr);

    bool load(const ToolWindowContainer& container);
    ToolWindowContainer getContainer() const;

    void createGraphic(const sf::Vector2f& size);

    virtual void setPosition(const sf::Vector2f& position);

    bool isVisible() const;
    bool isHidden() const;

    bool contains(const sf::Vector2f& point) const;

    void setSetPieceTool(const LogicPiece& logicPiece);

    void setSelectTool(const sf::Mouse::Button button, const ToolSelection selection);

    void setAddArrowTool(const int colorId);

    void setAddCircleTool(const int colorId);

    void show();

    void hide();

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void redrawTexture();

    sigrid::RenderTexture m_texture;

    Board m_board;
};

}  // namespace sigrid