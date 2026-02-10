#include "ToolPickerWindow.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;


ToolPickerWindow::ToolPickerWindow(const MainWindowConfigContainer& wConfig, PieceManager* pieceManagerPtr, ToolManager* toolManagerPtr, const std::vector<sf::Color> squareColors)
: m_pieceManagerPtr{pieceManagerPtr}
, m_toolManagerPtr{toolManagerPtr}
, m_numPieceColors{0}
, m_colorDisplay{ColorDisplay::Piece}
, m_showColors{wConfig.colorTools}
, m_colorColumns{2}
, m_show{wConfig.toolWindow}
, m_backgroundColor{255,255,255,0}
, m_arrowColorId{-1}
, m_pieceNotation{"P"}{

    m_numArrowColors = 12;

    m_boardPtr = std::make_unique<GraphicToolPicker>(squareColors);

    m_displayedPieceColorIds.push_back(0);
    m_displayedPieceColorIds.push_back(1);

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

void ToolPickerWindow::addArrowTool(){
    m_arrowColorId = 0;
}

void ToolPickerWindow::addPieceTool(std::string notation){
    m_pieceNotations.push_back(notation);
}

void ToolPickerWindow::addPieceColorTools(const int numColors){
    m_numPieceColors = numColors;
}

void ToolPickerWindow::setPosition(sf::Vector2f position){
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
    if(m_showColors){
        return 4;
    }
    return 2;
}

unsigned int ToolPickerWindow::getNumRows() const{
    return 7;
}

bool ToolPickerWindow::contains(sf::Vector2i point) const{
    
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

void ToolPickerWindow::setAddArrowTool(const int colorId){

    m_arrowColorId = colorId;

    redrawTexture();
}

void ToolPickerWindow::hideColorTools(){

    if(!m_texture){
        return;
    }

    if(!m_showColors){
        return;
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

    m_showColors = true;

    if(m_colorDisplay == ColorDisplay::Piece){
        setPieceColorTools(m_pieceNotation);
    }
    else if(m_colorDisplay == ColorDisplay::Arrow){
        setArrowColors();
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
    int x = 0;
    int y = 0;
    for(int i = 0; i < m_miscTools.size(); i++){
        m_boardPtr->addTool(m_miscTools.at(i).texturePtr, {x,y});
        m_clickActions.insert_or_assign({x,y}, m_miscTools.at(i).action);
        x++;
    }

    //Arrow tool
    if(m_arrowColorId >= 0){
        auto drawArrowTexture_o = m_toolManagerPtr->getArrowTexturePtr(m_arrowColorId);
        if(drawArrowTexture_o != std::nullopt){
            m_boardPtr->addTool(drawArrowTexture_o.value(), {x,y});
            ActionType::PickArrow action{m_arrowColorId};
            m_clickActions.insert_or_assign({x,y}, action);
            x++;
        }
    }
    

    //Colors
    if(m_showColors){
        x = 0;
        y = 1;

        if(m_colorDisplay == ColorDisplay::Arrow){
            for(int colorId = 0; colorId < m_numArrowColors; colorId++){
                auto arrowPtr_o = m_toolManagerPtr->getArrowTexturePtr(colorId);

                if(arrowPtr_o == std::nullopt){
                    continue;
                }

                m_boardPtr->addTool(arrowPtr_o.value(), {x,y});
                ActionType::PickArrowColor action{colorId};
                m_clickActions.insert_or_assign({x,y}, action);

                if(x < 1){
                    x++;
                }
                else{
                    x = 0;
                    y++;
                }
            }
        }
        else{ //ColorDisplay::Piece
            for(int colorId = 0; colorId < m_numPieceColors; colorId++){

                LogicPiece logicPiece{m_pieceNotation, colorId};
                auto piece_o = m_pieceManagerPtr->getPiece(logicPiece);

                if(piece_o == std::nullopt){
                    continue;
                }

                m_boardPtr->addTool(piece_o.value().graphic().getTexturePtr(), {x,y});

                ActionType::PickPieceColor action{piece_o.value()};

                m_clickActions.insert_or_assign({x,y}, action);

                if(x < 1){
                    x++;
                }
                else{
                    x = 0;
                    y++;
                }
            }
        }
    }

    //Pieces
    int startPieceColumn;
    int startPieceRow = 1;
    if(m_showColors){
        startPieceColumn = 2;
    }
    else{
        startPieceColumn = 0;
    }
    
    y = startPieceRow;
    x = startPieceColumn;
    for(int notationId = 0; notationId < m_pieceNotations.size(); notationId++){
        for(int i = 0; i < m_displayedPieceColorIds.size(); i++){
            LogicPiece logicPiece{m_pieceNotations.at(notationId), m_displayedPieceColorIds.at(i)};
            auto piece_o = m_pieceManagerPtr->getPiece(logicPiece);

            if(piece_o == std::nullopt){
                continue;
            }

            m_boardPtr->addTool(piece_o.value().graphic().getTexturePtr(), {x,y});

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
