#include "ToolPickerWindow.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;


ToolPickerWindow::ToolPickerWindow(const ToolPickerContainer& data, const std::vector<uint32_t>& squareColors, PieceManager* pieceManagerPtr, ToolManager* toolManagerPtr)
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

    m_boardPtr = std::make_unique<GraphicToolPicker>(squareColors);

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

void ToolPickerWindow::createGraphic(const sf::Vector2u& size){
    m_texture = std::make_unique<sf::RenderTexture>(size);

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

bool ToolPickerWindow::contains(const sf::Vector2i& point) const{
    
    if(!m_show){
        return false;
    }

    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}


Action ToolPickerWindow::clicked(const sigrid::Tool& tool, const sf::Vector2i& position){

    if(!m_show){
        return ActionType::None();
    }

    int x = position.x-(int)m_position.x;
    int y = position.y-(int)m_position.y;

    auto coord_o = m_boardPtr->getSquareCoord({x,y});

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

    m_boardPtr->clear();

    //Tools
    int x = m_miscBlock.coord.x;
    int y = m_miscBlock.coord.y;
    int i;
    for(i = 0; i < m_miscTools.size(); i++){
        m_boardPtr->addTool({x,y}, m_miscTools.at(i).texturePtr);
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
            m_boardPtr->addTool({x,y}, drawArrowTexture_o.value());
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
            m_boardPtr->addTool({x,y}, drawCircleTexture_o.value());
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
                    auto piece_o = m_pieceManagerPtr->getPiece(logicPiece);

                    if(piece_o == std::nullopt){
                        continue;
                    }

                    m_boardPtr->addTool({x,y}, piece_o.value().graphic().getTexturePtr());

                    ActionType::PickPieceColor action{piece_o.value()};

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

                    m_boardPtr->addTool({x,y}, arrowPtr_o.value());
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

                    m_boardPtr->addTool({x,y}, circlePtr_o.value());
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
            auto piece_o = m_pieceManagerPtr->getPiece(logicPiece);

            if(piece_o == std::nullopt){
                continue;
            }

            m_boardPtr->addTool({x,y}, piece_o.value().graphic().getTexturePtr());

            ActionType::PickPiece action{piece_o.value()};

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

    m_boardPtr->createGraphic(m_texture->getSize());
    m_boardPtr->setPosition({0.f,0.f});

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
