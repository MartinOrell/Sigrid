#pragma once

#include <optional>

#include "sigrid/utilities/String/String.h"
#include "sigrid/SigridRenderTexture/SigridRenderTexture.h"
#include "sigrid/utilities/Layout/LayoutGrid.h"
#include "sigrid/Board/Board.h"
#include "sigrid/Action/Action.h"

#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorder.h"

#include "sigrid/Window/WorkWindow/PdfHandler.h"

#include "sigrid/utilities/lists/VectorWithDisplayGrid.h"
#include "sigrid/Window/WorkWindow/WorkWindowContainer.h"
#include "sigrid/Board/BoardContainer.h"
#include "sigrid/Board/BoardStateContainer.h"
#include "sigrid/Board/BoardDesignContainer.h"

namespace sigrid{

class Tool;

class WorkWindow: public sf::Drawable{

  public:

    WorkWindow() = default;
    WorkWindow(const WorkWindow&) = default;
    WorkWindow(WorkWindow&&) = default;
    WorkWindow& operator=(const WorkWindow&) = default;
    WorkWindow& operator=(WorkWindow&&) = default;

    bool loadBoards(const sigrid_list::Vector<BoardContainer> boardContainers);

    void loadBoard(const int& id, const BoardContainer& container);

    void setResetBoardFilename(const sigrid::String& filename);
    const sigrid::String& getResetBoardFilename() const;

    void setDefaultBoardImageFilename(const sigrid::String& filename);
    const sigrid::String& getDefaultBoardImageFilename() const;

    void setTileColorManagerPtr(ColorManager* const managerPtr);

    void setPieceManagerPtr(PieceManager* const managerPtr);

    void setArrowColorManagerPtr(ColorManager* const managerPtr);

    void setFontManagerPtr(FontManager* const managerPtr);

    bool load(const WorkWindowContainer& container);
    WorkWindowContainer getContainer() const;

    void loadGraphicData(const BoardDesignContainer& graphicData);
    std::optional<BoardDesignContainer> getBoardStyleContainer() const;

    void loadBoardState(const int& id, const BoardStateContainer& boardStateData);

    sigrid_list::Vector<BoardContainer> getBoardContainers() const;

    void createGraphic(const sf::Vector2f& size);

    void loadFen(const sigrid::String& fen);

    sigrid::String getName() const;

    sigrid::String getSaveFilename() const;

    sigrid::String getFen() const;
    
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
    void addBoard(const sigrid::String& boardFilename);

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

    void saveBoards();
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

    sigrid::String getUniqueName(const sigrid::String& name);

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

    sigrid::String m_resetBoardFilename;
    sigrid::String m_defaultBoardImageFilename;
};

}  // namespace sigrid