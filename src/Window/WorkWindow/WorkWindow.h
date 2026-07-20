#pragma once

#include <optional>

#include "SigridRenderTexture/SigridRenderTexture.h"
#include "Layout/LayoutGrid.h"
#include "Board/Board.h"
#include "Action/Action.h"

#include "Entity/Shape/RectangleBorder/RectangleBorder.h"

#include "PdfHandler.h"

#include "List/VectorWithDisplayGrid.h"

namespace sigrid{

class BoardDataContainer;
class Tool;

class WorkWindow: public sf::Drawable{

  public:

    WorkWindow() = default;
    WorkWindow(const WorkWindow&) = default;
    WorkWindow(WorkWindow&&) = default;
    WorkWindow& operator=(const WorkWindow&) = default;
    WorkWindow& operator=(WorkWindow&&) = default;

    void setBoardFilename(const std::string& filename);

    void setResetBoardFilename(const std::string& filename);

    void setDefaultBoardImageFilename(const std::string& filename);

    void setTileColorManagerPtr(ColorManager* const managerPtr);

    void setPieceManagerPtr(PieceManager* const managerPtr);

    void setArrowColorManagerPtr(ColorManager* const managerPtr);

    void setFontManagerPtr(FontManager* const managerPtr);

    void loadGraphicData(const BoardDesignContainer& graphicData);
    void loadBoardData(const BoardDataContainer& boardData);

    void createGraphic(const sf::Vector2f& size);

    void loadFen(const std::string& fen);

    std::string getName() const;

    std::string getSaveFilename() const;

    std::string getFen() const;
    
    void setPosition(const sf::Vector2f& position);

    int getNumColumns() const;

    bool contains(const sf::Vector2f& point) const;

    bool isCoordinatesOutside() const;

    void mousePress(const sf::Vector2f& position);
    std::optional<sigrid_action::Action> clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition);
    void dragMouse(const Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& currentPosition);

    void reset();

    void clear();

    void print();

    void newBoard();

    void addBoardColumn();
    void removeBoardColumn();
    void addBoardRow();
    void removeBoardRow();

    void shiftBoardsLeft();
    void shiftBoardsRight();

    void gotoRightBoard();
    void gotoLeftBoard();
    void gotoUpBoard();
    void gotoDownBoard();

    void saveBoard();
    void savePdf();

    void flipBoard();

    void addLeftInsideLabels();
    void addBottomInsideLabels();
    void addLeftOutsideLabels();
    void addRightOutsideLabels();
    void addTopOutsideLabels();
    void addBottomOutsideLabels();
    
    void removeLeftInsideLabels();
    void removeBottomInsideLabels();
    void removeLeftOutsideLabels();
    void removeRightOutsideLabels();
    void removeTopOutsideLabels();
    void removeBottomOutsideLabels();

    void setCoordinateSize(const float& size);

    void addTileColumnRight();

    void addTileColumnLeft();

    void removeRightTileColumn();

    void removeLeftTileColumn();

    void addTileRowUp();

    void addTileRowDown();

    void removeTopTileRow();

    void removeBottomTileRow();

    void addBoardBorder();

    void removeBoardBorder();

    void addTurnToken();

    void removeTurnToken();

    void useAddEntityTool(const sigrid_coord::Coord& coord, const LogicEntity& newEntity);
    void useAddEntityAtSelectionTool(const LogicEntity& newEntity);

    void updateTexture();

  private:

    std::string getUniqueName(const std::string& name);

    void useAddTileHighlightTool(const sigrid_coord::Coord& coord, const int& colorId);
    void useAddArrowTool(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const int& colorId);

    void updateBoardLayout();

    void updateSelectionHighlight();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    typedef unsigned int LayoutItem;

    SigridRenderTexture m_texture;
    LayoutGrid m_layout;

    sigrid_list::VectorWithDisplayGrid<sigrid::Board> m_boards;

    RectangleBorder m_boardSelectHighlight;

    PdfHandler m_pdfHandler;

    std::string m_resetBoardFilename = "";
    std::string m_defaultBoardImageFilename = "";
};

}  // namespace sigrid