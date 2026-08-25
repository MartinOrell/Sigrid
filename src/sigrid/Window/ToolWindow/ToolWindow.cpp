#include "sigrid/Window/ToolWindow/ToolWindow.h"

#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>

#include "sigrid/Board/BoardStateContainer.h"
#include "sigrid/Board/BoardDesignContainer.h"
#include "sigrid/Entity/Tile/GraphicTiles.h"
#include "sigrid/Entity/GraphicEntities.h"
#include "sigrid/Entity/Shape/Arrow/GraphicArrows.h"
#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "sigrid/Board/BoardLabels.h"
#include "sigrid/Entity/TurnToken/TurnToken.h"

void sigrid::ToolWindow::setTileColorManagerPtr(ColorManager* const managerPtr){
    m_board.setTileColorManagerPtr(managerPtr);
}

void sigrid::ToolWindow::setIconManagerPtr(IconManager* const managerPtr){
    m_board.setIconManagerPtr(managerPtr);
}

void sigrid::ToolWindow::setPieceManagerPtr(PieceManager* const managerPtr){
    m_board.setPieceManagerPtr(managerPtr);
}

void sigrid::ToolWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){
    m_board.setArrowColorManagerPtr(managerPtr);
}

bool sigrid::ToolWindow::load(const ToolWindowContainer& container){

    m_board.setLeftToRight();
    m_board.setTopToBottom();

    BoardStateContainer boardStateData;
    boardStateData.columns = 1;
    boardStateData.rows = 1;
    boardStateData.repeatTileColorIds.clear();
    boardStateData.repeatTileColorIds.push_back(0);

    BoardDesignContainer boardDesign;
    {
        int tileWidth = 255;
        int tileHeight = 255;
        if(tileWidth < tileHeight){
            tileHeight = tileWidth;
        }
        else{
            tileWidth = tileHeight;
        }
        boardDesign.tile.width = tileWidth;
        boardDesign.tile.height = tileHeight;
    }
    boardDesign.arrow.thickness = 40;
    boardDesign.arrow.headSize = 80;
    boardDesign.circle.diameter = 100;
    boardDesign.border.isVisible = false;
    boardDesign.turnToken.isVisible = false;

    m_board.loadGraphicData(boardDesign);
    m_board.loadBoardState(boardStateData);

    LogicIcon selectIcon;
    selectIcon.setFilename("res/icons/select_object.png");
    m_board.addEntity({0,0}, selectIcon);

    if(!container.isVisible){
        hide();
    }

    return true;
}

sigrid::ToolWindowContainer sigrid::ToolWindow::getContainer() const{

    ToolWindowContainer container;
    container.isVisible = m_texture.isVisible();

    return container;
}

void sigrid::ToolWindow::createGraphic(const sf::Vector2f& size){

    m_texture.setSize(size);

    int boardWidth = m_board.getImageWidth();
    int boardHeight = m_board.getImageHeight();
    float widthRatio = size.x/(float)boardWidth;
    float heightRatio = size.y/(float)boardHeight;
    float boardScale;
    if(widthRatio < heightRatio){
        boardScale = widthRatio;
    }
    else{
        boardScale = heightRatio;
    }
    m_board.setScale(boardScale);

    float posX = (size.x-m_board.getDisplayWidth())/2.f;
    float posY = (size.y-m_board.getDisplayHeight())/2.f;
    m_board.setPosition({posX, posY});

    redrawTexture();
}

void sigrid::ToolWindow::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
    m_texture.display();
}

bool sigrid::ToolWindow::isVisible() const{
    return m_texture.isVisible();
}

bool sigrid::ToolWindow::isHidden() const{
    return m_texture.isHidden();
}

bool sigrid::ToolWindow::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

void sigrid::ToolWindow::setSetPieceTool(const LogicPiece& logicPiece){
    m_board.removeEntity({0,0});
    m_board.addEntity({0,0},logicPiece);
    redrawTexture();
}

void sigrid::ToolWindow::setSelectTool(const sf::Mouse::Button button, const ToolSelection selection){

    m_board.removeEntity({0,0});
    switch(selection){
        case ToolSelection::Select:
        {
            LogicIcon selectIcon;
            selectIcon.setFilename("res/icons/select_object.png");
            m_board.addEntity({0,0}, selectIcon);
            break;
        }
        default:
            std::cerr << "ToolWindow: failed to set select Tool" << std::endl;
            break;
    }
    redrawTexture();
}

void sigrid::ToolWindow::setAddArrowTool(const int colorId){

    LogicArrow arrow;
    arrow.setColor(colorId);
    m_board.removeEntity({0,0});
    m_board.addEntity({0,0}, arrow);

    redrawTexture();
}

void sigrid::ToolWindow::setAddCircleTool(const int colorId){

    LogicCircle circle;
    circle.setColor(colorId);
    m_board.removeEntity({0,0});
    m_board.addEntity({0,0}, std::move(circle));

    redrawTexture();
}

void sigrid::ToolWindow::show(){
    m_texture.show();
}

void sigrid::ToolWindow::hide(){
    m_texture.hide();
}

void sigrid::ToolWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_texture);
}

void sigrid::ToolWindow::redrawTexture(){

    if(!m_texture.isInitialized()){
        return;
    }

    m_texture.clear();
    m_texture.draw(m_board);
    m_texture.display();
}