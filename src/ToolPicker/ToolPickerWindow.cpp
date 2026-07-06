#include "ToolPicker/ToolPickerWindow.h"

#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>

#include "ToolPicker/ToolPickerContainer.h"
#include "Board/BoardDataContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Entity/Tile/GraphicTiles.h"
#include "Entity/GraphicEntities.h"
#include "Entity/Shape/Arrow/GraphicArrows.h"
#include "Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "Board/BoardLabels.h"
#include "Entity/TurnToken/TurnToken.h"

using namespace sigrid;


ToolPickerWindow::ToolPickerWindow()
: m_colorDisplay{ColorDisplay::Piece}
, m_arrowColorId{-1}
, m_circleColorId{-1}{}

void ToolPickerWindow::setTileColorManagerPtr(ColorManager* const managerPtr){
    m_board.setTileColorManagerPtr(managerPtr);
}

void ToolPickerWindow::setPieceManagerPtr(PieceManager* const managerPtr){
    m_board.setPieceManagerPtr(managerPtr);
}

void ToolPickerWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){
    m_board.setArrowColorManagerPtr(managerPtr);
}

void ToolPickerWindow::setIconManagerPtr(IconManager* const managerPtr){
    m_board.setIconManagerPtr(managerPtr); 
}

void ToolPickerWindow::init(const ToolPickerContainer& data){

    m_columns = data.columns;
    m_rows = data.rows;
    m_showColors = data.showColors;
    m_colorIds = data.colorToolIds;
    m_pieceNotation = data.defaultPieceNotation;
    m_miscBlock = data.miscToolBlock;
    m_colorBlock = data.colorBlock;
    m_pieceBlocks = data.pieceBlocks;
    m_defaultArrowColorId = data.defaultArrowColorId;
    m_defaultCircleColorId = data.defaultCircleColorId;

    if(data.show){
        m_texture.show();
    }
    else{
        m_texture.hide();
    }

    m_board.setLeftToRight();
    m_board.setTopToBottom();

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
    boardDesign.border = false;
    boardDesign.turnToken = false;

    m_board.init(boardData, boardDesign);

    m_board.setPosition({0.f,0.f});

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
            std::cerr << "ToolPickerWindow: Unknown tool: " << toolName << std::endl;
        }
    }
    for(const auto& pieceNotation: data.pieceNotations){
        addPieceTool(pieceNotation);
    }
}

void ToolPickerWindow::createGraphic(const sf::Vector2f& size){

    m_texture.setSize(size);

    unsigned int boardWidth = m_board.getImageWidth();
    unsigned int boardHeight = m_board.getImageHeight();
    float widthRatio = (float)size.x/(float)boardWidth;
    float heightRatio = (float)size.y/(float)boardHeight;
    float boardScale;
    if(widthRatio < heightRatio){
        boardScale = widthRatio;
    }
    else{
        boardScale = heightRatio;
    }
    m_board.setScale(boardScale);

    float posX = ((float)(size.x)-float(m_board.getDisplayWidth()))/2.f;
    float posY = ((float)(size.y)-float(m_board.getDisplayHeight()))/2.f;
    m_board.setPosition({posX, posY});

    redrawTexture();
}

void ToolPickerWindow::addSelectTool(){

    ToolStruct tool;
    LogicIcon icon;
    icon.setFilename("res/icons/select_object.png");
    tool.icon = icon;
    ActionType::SetTool action{sf::Mouse::Button::Left, ToolSelection::Select};
    tool.action = action;
    m_miscTools.push_back(tool);
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
    m_texture.setPosition(position);
    m_texture.display();
}

bool ToolPickerWindow::isVisible() const{
    return m_texture.isVisible();
}

bool ToolPickerWindow::isHidden() const{
    return m_texture.isHidden();
}

sf::Vector2f ToolPickerWindow::getSize() const{
    return m_texture.getTextureSize();
}

unsigned int ToolPickerWindow::getNumColumns() const{
    return m_columns;
}

unsigned int ToolPickerWindow::getNumRows() const{
    return m_rows;
}

bool ToolPickerWindow::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}


std::optional<Action> ToolPickerWindow::clicked(const sigrid::Tool& tool, const sf::Vector2f& position){

    if(m_texture.isHidden()){
        return std::nullopt;
    }

    sf::Vector2f point = position - m_texture.getPosition();

    auto coord_o = m_board.getTileCoord(point);

    if(coord_o == std::nullopt){
        return std::nullopt;
    }

    if(m_clickActions.find(coord_o.value()) != m_clickActions.end()){
        return m_clickActions.at(coord_o.value());
    }

    return std::nullopt;
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

    if(!m_texture.isInitialized()){
        return;
    }

    if(!m_showColors){
        return;
    }

    m_columns -= m_colorBlock.columns;

    for(int i = 0; i < m_colorBlock.columns; i++){
        m_board.removeLeftTileColumn();
    }

    int imageWidth = m_board.getImageWidth();
    float scale = m_texture.getDisplaySize().x/(float)imageWidth;
    m_board.setScale(scale);

    for(auto& pieceBlock : m_pieceBlocks){
        pieceBlock.coord.x -= m_colorBlock.columns;
    }

    m_showColors = false;

    redrawTexture();
}

void ToolPickerWindow::showColorTools(){

    if(!m_texture.isInitialized()){
        return;
    }

    if(m_showColors){
        return;
    }

    m_columns += m_colorBlock.columns;
    for(int i = 0; i < m_colorBlock.columns; i++){
        m_board.addTileColumnLeft();
    }

    int imageWidth = m_board.getImageWidth();
    float scale = m_texture.getDisplaySize().x/(float)imageWidth;
    m_board.setScale(scale);

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
    m_texture.hide();
}

void ToolPickerWindow::show(){
    m_texture.show();
}

void ToolPickerWindow::redrawTexture(){

    m_board.clearEntities();

    //Tools
    int x = m_miscBlock.coord.x;
    int y = m_miscBlock.coord.y;
    int i;
    for(i = 0; i < m_miscTools.size(); i++){

        m_board.addEntity({x,y}, m_miscTools.at(i).icon);

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

        sigrid::LogicArrow logicArrow{m_arrowColorId};
        m_board.addEntity({x,y}, logicArrow);

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
    
    //Circle tool
    if(m_circleColorId >= 0){
        sigrid::LogicCircle logicCircle{m_circleColorId};
        m_board.addEntity({x,y}, logicCircle);
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

    //Colors
    if(m_showColors){
        x = m_colorBlock.coord.x;
        y = m_colorBlock.coord.y;

        switch(m_colorDisplay){
            case ColorDisplay::Piece:
                for(int colorId = 0; colorId < m_colorIds.size(); colorId++){

                    LogicPiece logicPiece{m_pieceNotation, colorId};

                    m_board.addEntity({x,y}, logicPiece);

                    ActionType::PickPieceColor action{logicPiece};

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

                    sigrid::LogicArrow logicArrow{colorId};
                    m_board.addEntity({x,y}, logicArrow);

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

                    sigrid::LogicCircle logicCircle{colorId};
                    m_board.addEntity({x,y}, logicCircle);
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

            m_board.addEntity({x,y}, logicPiece);

            ActionType::PickEntity action{logicPiece};

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

    m_texture.clear();
    m_texture.draw(m_board);
    m_texture.display();
}

void ToolPickerWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_texture);
}
