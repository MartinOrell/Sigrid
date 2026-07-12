#include "Window/ToolWindow/ToolWindow.h"

#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>

#include "Board/BoardDataContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Entity/Tile/GraphicTiles.h"
#include "Entity/GraphicEntities.h"
#include "Entity/Shape/Arrow/GraphicArrows.h"
#include "Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "Board/BoardLabels.h"
#include "Entity/TurnToken/TurnToken.h"

using namespace sigrid;

ToolWindow::ToolWindow(){}

void ToolWindow::setTileColorManagerPtr(ColorManager* const managerPtr){
    m_board.setTileColorManagerPtr(managerPtr);
}

void ToolWindow::setIconManagerPtr(IconManager* const managerPtr){
    m_board.setIconManagerPtr(managerPtr);
}

void ToolWindow::setPieceManagerPtr(PieceManager* const managerPtr){
    m_board.setPieceManagerPtr(managerPtr);
}

void ToolWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){
    m_board.setArrowColorManagerPtr(managerPtr);
}

void ToolWindow::init(){

    m_board.setLeftToRight();
    m_board.setTopToBottom();

    BoardDataContainer boardData;
    boardData.columns = 1;
    boardData.rows = 1;
    boardData.repeatTileColorIds = std::vector<int>{0};

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
        boardDesign.tileWidth = tileWidth;
        boardDesign.tileHeight = tileHeight;
    }
    boardDesign.arrowThickness = 40;
    boardDesign.arrowHeadSize = 80;
    boardDesign.circleDiameter = 100;
    boardDesign.border = false;
    boardDesign.turnToken = false;

    m_board.init(boardData, boardDesign);

    LogicIcon selectIcon;
    selectIcon.setFilename("res/icons/select_object.png");
    m_board.addEntity({0,0}, selectIcon);
}

void ToolWindow::createGraphic(const sf::Vector2f& size){

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

void ToolWindow::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
    m_texture.display();
}

bool ToolWindow::isVisible() const{
    return m_texture.isVisible();
}

bool ToolWindow::isHidden() const{
    return m_texture.isHidden();
}

bool ToolWindow::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

void ToolWindow::setSetPieceTool(const LogicPiece& logicPiece){
    m_board.removeEntity({0,0});
    m_board.addEntity({0,0},logicPiece);
    redrawTexture();
}

void ToolWindow::setSelectTool(const sf::Mouse::Button button, const ToolSelection selection){

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

void ToolWindow::setAddArrowTool(const int colorId){

    LogicArrow arrow{colorId};
    m_board.removeEntity({0,0});
    m_board.addEntity({0,0}, arrow);

    redrawTexture();
}

void ToolWindow::setAddCircleTool(const int colorId){

    LogicCircle circle{colorId};
    m_board.removeEntity({0,0});
    m_board.addEntity({0,0}, circle);

    redrawTexture();
}

void ToolWindow::show(){
    m_texture.show();
}

void ToolWindow::hide(){
    m_texture.hide();
}

void ToolWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_texture);
}

void ToolWindow::redrawTexture(){

    if(!m_texture.isInitialized()){
        return;
    }

    m_texture.clear();
    m_texture.draw(m_board);
    m_texture.display();
}