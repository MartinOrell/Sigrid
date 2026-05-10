#include "ToolWindow.h"

#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>

#include "../../Board/BoardDataContainer.h"
#include "../../Board/BoardDesignContainer.h"
#include "../../Entity/Tile/GraphicTiles.h"
#include "../../Entity/GraphicEntities.h"
#include "../../Entity/Shape/Arrow/GraphicArrows.h"
#include "../../Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "../../Board/BoardLabels.h"
#include "../../Entity/TurnToken/TurnToken.h"

using namespace sigrid;

ToolWindow::ToolWindow()
: m_show{true}
, m_backgroundColor{255,255,255,0}{}

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

void ToolWindow::createGraphic(const sf::Vector2u& size){
    m_texture = std::make_unique<sf::RenderTexture>(size);

    float itemWidth = (float)size.y;
    float itemHeight = (float)size.y;

    int imageHeight = m_board.getImageHeight();
    int imageWidth = m_board.getImageWidth();

    float scale = itemHeight/imageHeight;
    float x = itemWidth/2.f;

    m_board.setScale(scale);
    m_board.setPosition({x,0.f});

    redrawTexture();
}

void ToolWindow::setPosition(const sf::Vector2f& position){
    m_position = position;
}

bool ToolWindow::isHidden() const{
    return !m_show;
}

bool ToolWindow::contains(const sf::Vector2f& point) const{
    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point);
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
    m_show = true;
}

void ToolWindow::hide(){
    m_show = false;
}

void ToolWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    if(!m_texture || !m_show){
        return;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}

void ToolWindow::redrawTexture(){
    if(!m_texture){
        return;
    }

    m_texture->clear(m_backgroundColor);
    m_texture->draw(m_board);
}