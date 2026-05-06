#include "ToolPickerWindow.h"

#include "ToolPickerContainer.h"
#include "../Entity/Piece/PieceManager.h"
#include "../Tool/ToolManager.h"
#include "../Board/BoardDataContainer.h"
#include "../Board/BoardDesignContainer.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

using namespace sigrid;


ToolPickerWindow::ToolPickerWindow(const ToolPickerContainer& data, ColorManager* const tileColorManagerPtr, PieceManager* pieceManagerPtr, ToolManager* toolManagerPtr, ColorManager* arrowColorManagerPtr)
: m_pieceManagerPtr{pieceManagerPtr}
, m_toolManagerPtr{toolManagerPtr}
, m_columns{data.columns}
, m_rows{data.rows}
, m_colorDisplay{ColorDisplay::Piece}
, m_showColors{data.showColors}
, m_show{data.show}
, m_backgroundColor{255,255,255,0}
, m_arrowColorId{-1}
, m_circleColorId{-1}
, m_colorIds{data.colorToolIds}
, m_pieceNotation{data.defaultPieceNotation}
, m_miscBlock{data.miscToolBlock}
, m_colorBlock{data.colorBlock}
, m_pieceBlocks{data.pieceBlocks}
, m_defaultArrowColorId{data.defaultArrowColorId}
, m_defaultCircleColorId{data.defaultCircleColorId}{

    m_boardPtr = std::make_unique<Board>();
    m_boardPtr->addTileColorManagerPtr(tileColorManagerPtr);
    m_boardPtr->addArrowColorManagerPtr(arrowColorManagerPtr);
    m_boardPtr->addPieceManagerPtr(pieceManagerPtr);
    m_boardPtr->setLeftToRight();
    m_boardPtr->setTopToBottom();

    BoardDataContainer boardData;
    boardData.columns = data.columns;
    boardData.rows = data.rows;
    boardData.repeatTileColorIds = data.tileColorIds;

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
    boardDesign.labelsInside = false;
    boardDesign.labelsOutside = false;
    boardDesign.border = false;
    boardDesign.turnToken = false;

    m_boardPtr->init(boardData, boardDesign);

    m_boardPtr->setPosition({0.f,0.f});

    m_displayedPieceColorIds.push_back(0);
    m_displayedPieceColorIds.push_back(1);

    for(const auto& toolName: data.toolNames){
        if(toolName == "Select"){
            addSelectTool();
        }
        else if(toolName == "Arrow"){
            addArrowTool(m_defaultArrowColorId);
        }
        else if(toolName == "Circle"){
            addCircleTool(m_defaultCircleColorId);
        }
        else{
            std::cout << "ToolPickerWindow: Unknown tool: " << toolName << std::endl;
        }
    }
    for(const auto& pieceNotation: data.pieceNotations){
        addPieceTool(pieceNotation);
    }

}

void ToolPickerWindow::addIconManager(IconManager* const managerPtr){
    if(m_boardPtr){
        m_boardPtr->addIconManagerPtr(managerPtr); 
    }
}

void ToolPickerWindow::createGraphic(const sf::Vector2u& size){
    m_texture = std::make_unique<sf::RenderTexture>(size);

    int imageWidth = m_boardPtr->getImageWidth();
    float scale = (float)size.x/(float)imageWidth;
    m_boardPtr->setScale(scale);

    redrawTexture();
}

void ToolPickerWindow::addSelectTool(){

    if(m_toolManagerPtr == nullptr){
        std::cout << "Unable to add select tool, toolManager is missing" << std::endl;
        return;
    }

    auto selectTexture_o = m_toolManagerPtr->getTexturePtr(ToolSelection::Select);
    if(selectTexture_o != std::nullopt){
        ToolStruct tool;
        tool.texturePtr = selectTexture_o.value();
        ActionType::SetTool action{sf::Mouse::Button::Left, ToolSelection::Select};
        tool.action = action;

        m_miscTools.push_back(tool);
    }
}

void ToolPickerWindow::addArrowTool(const int colorId){
    m_arrowColorId = colorId;
}

void ToolPickerWindow::addCircleTool(const int colorId){
    m_circleColorId = colorId;
}

void ToolPickerWindow::addPieceTool(const std::string& notation){
    m_pieceNotations.push_back(notation);
}

void ToolPickerWindow::setPosition(const sf::Vector2f& position){
    m_position = position;
}

bool ToolPickerWindow::isHidden() const{
    return !m_show;
}

sf::Vector2u ToolPickerWindow::getSize() const{

    if(!m_show){
        return {0,0};
    }

    if(!m_texture){
        return {0,0};
    }

    return m_texture->getSize();
}

unsigned int ToolPickerWindow::getNumColumns() const{
    return m_columns;
}

unsigned int ToolPickerWindow::getNumRows() const{
    return m_rows;
}

bool ToolPickerWindow::contains(const sf::Vector2f& point) const{
    
    if(!m_show){
        return false;
    }

    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point);
}


Action ToolPickerWindow::clicked(const sigrid::Tool& tool, const sf::Vector2f& position){

    if(!m_show){
        return ActionType::None();
    }

    sf::Vector2f point = position - m_position;

    auto coord_o = m_boardPtr->getTileCoord(point);

    if(coord_o == std::nullopt){
        return ActionType::None();
    }

    if(m_clickActions.find(coord_o.value()) != m_clickActions.end()){
        return m_clickActions.at(coord_o.value());
    }

    return ActionType::None();
}

void ToolPickerWindow::setPieceColorTools(const std::string& pieceNotation){

    if(!m_showColors){
        return;
    }

    m_pieceNotation = pieceNotation;

    m_colorDisplay = ColorDisplay::Piece;

    redrawTexture();
}

void ToolPickerWindow::setPieceTools(const int colorId){

    if(colorId == m_displayedPieceColorIds.back()){
        return;
    }

    m_displayedPieceColorIds.erase(m_displayedPieceColorIds.begin());
    m_displayedPieceColorIds.push_back(colorId);

    redrawTexture();
}

void ToolPickerWindow::setArrowColors(){

    if(!m_showColors){
        return;
    }

    m_colorDisplay = ColorDisplay::Arrow;

    redrawTexture();
}

void ToolPickerWindow::setCircleColors(){

    if(!m_showColors){
        return;
    }

    m_colorDisplay = ColorDisplay::Circle;

    redrawTexture();
}

void ToolPickerWindow::setAddArrowTool(const int colorId){

    m_arrowColorId = colorId;

    redrawTexture();
}

void ToolPickerWindow::setAddCircleTool(const int colorId){

    m_circleColorId = colorId;

    redrawTexture();
}

void ToolPickerWindow::hideColorTools(){

    if(!m_texture){
        return;
    }

    if(!m_showColors){
        return;
    }

    m_columns -= m_colorBlock.columns;

    for(int i = 0; i < m_colorBlock.columns; i++){
        m_boardPtr->removeSquareColumnLeft();
    }

    int imageWidth = m_boardPtr->getImageWidth();
    float scale = (float)m_texture->getSize().x/(float)imageWidth;
    m_boardPtr->setScale(scale);

    for(auto& pieceBlock : m_pieceBlocks){
        pieceBlock.coord.x -= m_colorBlock.columns;
    }

    m_showColors = false;

    redrawTexture();
}

void ToolPickerWindow::showColorTools(){

    if(!m_texture){
        return;
    }

    if(m_showColors){
        return;
    }

    m_columns += m_colorBlock.columns;
    for(int i = 0; i < m_colorBlock.columns; i++){
        m_boardPtr->addSquareColumnLeft();
    }

    int imageWidth = m_boardPtr->getImageWidth();
    float scale = (float)m_texture->getSize().x/(float)imageWidth;
    m_boardPtr->setScale(scale);

    for(auto& pieceBlock : m_pieceBlocks){
        pieceBlock.coord.x += m_colorBlock.columns;
    }

    m_showColors = true;

    switch(m_colorDisplay){
        case ColorDisplay::Piece:
            setPieceColorTools(m_pieceNotation);
            break;
        case ColorDisplay::Arrow:
            setArrowColors();
            break;
        case ColorDisplay::Circle:
            setCircleColors();
            break;
        default:
            break;
    }
    
    redrawTexture();
}


void ToolPickerWindow::hide(){
    m_show = false;
}

void ToolPickerWindow::show(){
    m_show = true;
}

void ToolPickerWindow::redrawTexture(){

    m_boardPtr->clearEntities();

    //Tools
    int x = m_miscBlock.coord.x;
    int y = m_miscBlock.coord.y;
    int i;
    for(i = 0; i < m_miscTools.size(); i++){

        LogicIcon logicIcon;
        logicIcon.setName("Select");
        m_boardPtr->addEntity({x,y}, logicIcon);

        m_clickActions.insert_or_assign({x,y}, m_miscTools.at(i).action);
        if((i+1)%m_miscBlock.columns == 0){
            x = m_miscBlock.coord.x;
            y++;
        }
        else{
            x++;
        }
    }

    //Arrow tool
    if(m_arrowColorId >= 0){
        auto drawArrowTexture_o = m_toolManagerPtr->getArrowTexturePtr(m_arrowColorId);
        if(drawArrowTexture_o != std::nullopt){

            sigrid::LogicArrow logicArrow{m_arrowColorId};
            m_boardPtr->addEntity({x,y}, logicArrow);

            ActionType::PickArrow action{m_arrowColorId};
            m_clickActions.insert_or_assign({x,y}, action);
            if((i+1)%m_miscBlock.columns == 0){
                x = m_miscBlock.coord.x;
                y++;
            }
            else{
                x++;
            }
            i++;
        }
    }
    
    //Circle tool
    if(m_circleColorId >= 0){
        auto drawCircleTexture_o = m_toolManagerPtr->getCircleTexturePtr(m_circleColorId);
        if(drawCircleTexture_o != std::nullopt){
            sigrid::LogicCircle logicCircle{m_circleColorId};
            m_boardPtr->addEntity({x,y}, logicCircle);
            ActionType::PickCircle action{m_circleColorId};
            m_clickActions.insert_or_assign({x,y}, action);
            if((i+1)%m_miscBlock.columns == 0){
                x = m_miscBlock.coord.x;
                y++;
            }
            else{
                x++;
            }
            i++;
        }
    }

    //Colors
    if(m_showColors){
        x = m_colorBlock.coord.x;
        y = m_colorBlock.coord.y;

        switch(m_colorDisplay){
            case ColorDisplay::Piece:
                for(int colorId = 0; colorId < m_colorIds.size(); colorId++){

                    LogicPiece logicPiece{m_pieceNotation, colorId};
                    auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(logicPiece);

                    if(graphicPiece_o == std::nullopt){
                        continue;
                    }

                    m_boardPtr->addEntity({x,y}, logicPiece);

                    ActionType::PickPieceColor action{logicPiece, graphicPiece_o.value()};

                    m_clickActions.insert_or_assign({x,y}, action);

                    if(x < m_colorBlock.coord.x + m_colorBlock.columns-1){
                        x++;
                    }
                    else{
                        x = m_colorBlock.coord.x;
                        y++;
                    }
                }
                break;
            case ColorDisplay::Arrow:
                for(int colorId = 0; colorId < m_colorIds.size(); colorId++){
                    auto arrowPtr_o = m_toolManagerPtr->getArrowTexturePtr(colorId);

                    if(arrowPtr_o == std::nullopt){
                        continue;
                    }

                    sigrid::LogicArrow logicArrow{colorId};
                    m_boardPtr->addEntity({x,y}, logicArrow);

                    ActionType::PickArrowColor action{colorId};
                    m_clickActions.insert_or_assign({x,y}, action);

                    if(x < m_colorBlock.coord.x + m_colorBlock.columns-1){
                        x++;
                    }
                    else{
                        x = m_colorBlock.coord.x;
                        y++;
                    }
                }
                break;
            case ColorDisplay::Circle:
                for(int colorId = 0; colorId < m_colorIds.size(); colorId++){
                    auto circlePtr_o = m_toolManagerPtr->getCircleTexturePtr(colorId);

                    if(circlePtr_o == std::nullopt){
                        continue;
                    }

                    sigrid::LogicCircle logicCircle{colorId};
                    m_boardPtr->addEntity({x,y}, logicCircle);
                    ActionType::PickCircleColor action{colorId};
                    m_clickActions.insert_or_assign({x,y}, action);

                    if(x < m_colorBlock.coord.x + m_colorBlock.columns-1){
                        x++;
                    }
                    else{
                        x = m_colorBlock.coord.x;
                        y++;
                    }
                }
                break;
        }
    }

    //Pieces
    int startPieceColumn = m_pieceBlocks.at(0).coord.x;
    int startPieceRow = m_pieceBlocks.at(0).coord.y;
    
    y = startPieceRow;
    x = startPieceColumn;
    for(int notationId = 0; notationId < m_pieceNotations.size(); notationId++){
        for(int i = 0; i < m_displayedPieceColorIds.size(); i++){
            LogicPiece logicPiece{m_pieceNotations.at(notationId), m_displayedPieceColorIds.at(i)};
            auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(logicPiece);

            if(graphicPiece_o == std::nullopt){
                continue;
            }

            m_boardPtr->addEntity({x,y}, logicPiece);

            ActionType::PickEntity action{logicPiece, graphicPiece_o.value()};

            m_clickActions.insert_or_assign({x,y}, action);

            if(i == m_displayedPieceColorIds.size()-1){
                y++;
                x = startPieceColumn;
            }
            else{
                x++;
            }
        }
    }
}

void ToolPickerWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_texture){
        return;
    }

    if(!m_show){
        return;
    }
    
    sf::Vector2u textureSize = m_texture->getSize();

    if(textureSize == sf::Vector2u{0,0}){
        return;
    }

    sf::RenderTexture texture(textureSize);
    texture.clear(m_backgroundColor);
    if(m_boardPtr != nullptr){
        texture.draw(*m_boardPtr);
    }
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}
