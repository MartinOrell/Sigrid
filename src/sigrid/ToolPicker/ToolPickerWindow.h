#pragma once

#include <optional>
#include <memory>
#include <map>

#include <SFML/System/Vector2.hpp>

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Action/Action.h"
#include "sigrid/utilities/Coord/CoordBlock.h"
#include "sigrid/Color/ColorManager.h"
#include "sigrid/Tool/ToolStruct.h"
#include "sigrid/Board/Board.h"

#include "sigrid/SigridRenderTexture/SigridRenderTexture.h"
#include "sigrid/ToolPicker/ToolPickerContainer.h"

namespace sigrid{

class PieceManager;
class IconManager;

class Tool;

class ToolPickerWindow: public sf::Drawable{

  public:

    ToolPickerWindow() = default;
    ToolPickerWindow(const ToolPickerWindow&) = default;
    ToolPickerWindow(ToolPickerWindow&&) = default;
    ToolPickerWindow& operator=(const ToolPickerWindow&) = default;
    ToolPickerWindow& operator=(ToolPickerWindow&&) = default;

    void setTileColorManagerPtr(ColorManager* const managerPtr);

    void setPieceManagerPtr(PieceManager* const managerPtr);

    void setArrowColorManagerPtr(ColorManager* const managerPtr);

    void setIconManagerPtr(IconManager* const managerPtr);

    void load(const ToolPickerContainer& data);

    void createGraphic(const sf::Vector2f& size);

    void addSelectTool();

    void addArrowTool(const int colorId);

    void addCircleTool(const int colorId);

    void addPieceTool(const std::string& notation);

    virtual void setPosition(const sf::Vector2f& position);

    bool isVisible() const;
    bool isHidden() const;

    sf::Vector2f getSize() const;

    int getNumColumns() const;

    int getNumRows() const;

    bool contains(const sf::Vector2f& point) const;

    std::optional<sigrid_action::Action> clicked(const sigrid::Tool& tool, const sf::Vector2f& position);

    void setPieceColorTools(const std::string& pieceNotation);

    void setPieceTools(const int colorId);

    void setArrowColors();

    void setCircleColors();

    void setAddArrowTool(const int colorId);

    void setAddCircleTool(const int colorId);

    void hideColorTools();

    void showColorTools();

    void hide();

    void show();

  private:

    void redrawTexture();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    enum ColorDisplay{
        None,
        Piece,
        Arrow,
        Circle
    };

    int m_columns = 1;
    int m_rows = 1;

    sigrid_list::Vector<ToolStruct> m_miscTools;

    ColorDisplay m_colorDisplay{ColorDisplay::Piece};

    SigridRenderTexture m_texture;

    Board m_board;

    std::map<sigrid_coord::Coord, sigrid_action::Action> m_clickActions;

    sigrid_list::Vector<int> m_displayedPieceColorIds;
    int m_arrowColorId = -1;
    int m_circleColorId = -1;
    std::string m_pieceNotation = "";

    sigrid_list::Vector<std::string> m_pieceNotations;

    bool m_showColors = false;

    sigrid_list::Vector<int> m_colorIds;

    sigrid_coord::CoordBlock m_miscBlock;
    sigrid_coord::CoordBlock m_colorBlock;
    sigrid_list::Vector<sigrid_coord::CoordBlock> m_pieceBlocks;

    int m_defaultArrowColorId = 0;
    int m_defaultCircleColorId = 0;
};

}  // namespace sigrid