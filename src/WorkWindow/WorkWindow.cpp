#include "WorkWindow.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;


WorkWindow::WorkWindow()
: m_backgroundColor{255,255,255,0}{}

void WorkWindow::createGraphic(const sf::Vector2u& size)
{
    m_texture = std::make_unique<sf::RenderTexture>(size);

    if(m_boardPtr){
        unsigned int boardWidth = m_boardPtr->getImageWidth();
        unsigned int boardHeight = m_boardPtr->getImageHeight();
        float widthRatio = (float)size.x/(float)boardWidth;
        float heightRatio = (float)size.y/(float)boardHeight;
        float boardScale;
        if(widthRatio < heightRatio){
            boardScale = widthRatio;
        }
        else{
            boardScale = heightRatio;
        }
        m_boardPtr->setScale(boardScale);

        float posX = ((float)(size.x)-float(m_boardPtr->getDisplayWidth()))/2.f;
        float posY = ((float)(size.y)-float(m_boardPtr->getDisplayHeight()))/2.f;
        m_boardPtr->setPosition({posX, posY});
    }
}

void WorkWindow::addBoard(std::unique_ptr<sigrid::Board> board){
    m_boardPtr = std::move(board);
}

void WorkWindow::setPosition(sf::Vector2f position){
    m_position = position;
}

unsigned int WorkWindow::getNumColumns() const{
    if(!m_boardPtr){
        return 0;
    }
    return m_boardPtr->getNumColumns();
}

bool WorkWindow::contains(sf::Vector2i point) const{

    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

bool WorkWindow::isCoordinatesOutside() const{
    return m_boardPtr->isCoordinatesOutside();
}

void WorkWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_texture){
        return;
    }

    sf::RenderTexture texture(m_texture->getSize());
    texture.clear(m_backgroundColor);
    texture.draw(*m_boardPtr);
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}



Action WorkWindow::clicked(const sigrid::Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& releasePosition){
    
    m_boardPtr->removeDragArrow();

    int fromX = pressPosition.x-(int)m_position.x;
    int fromY = pressPosition.y-(int)m_position.y;

    int toX = releasePosition.x-(int)m_position.x;
    int toY = releasePosition.y-(int)m_position.y;


    if(m_boardPtr->isWithinPlayerToMoveToken({fromX, fromY}) &&
    m_boardPtr->isWithinPlayerToMoveToken({toX, toY})){
        m_boardPtr->togglePlayerToMoveToken();
    }

    auto fromCoord_o = m_boardPtr->getSquareCoord({fromX,fromY});
    auto toCoord_o = m_boardPtr->getSquareCoord({toX, toY});

    
    if(fromCoord_o == std::nullopt){
        return ActionType::None();
    }

    if(toCoord_o == std::nullopt){
        switch(tool.selection()){
            case ToolSelection::Select:
                m_boardPtr->deselect();
                break;
            default:
                break;
        }
        return ActionType::None();
    }

    auto fromCoord = fromCoord_o.value();
    auto toCoord = toCoord_o.value();

    switch(tool.selection()){
        case ToolSelection::Select:
            if(fromCoord == toCoord){
                m_boardPtr->select(toCoord);
            }
            else{
                m_boardPtr->movePiece(fromCoord_o.value(), toCoord_o.value());
            }
            return ActionType::None();
        case ToolSelection::PieceAdder:
            m_boardPtr->addPiece(tool.piece(), toCoord);
            return ActionType::None();
        case ToolSelection::PiecePicker:
            {
                auto piece_o = m_boardPtr->getPiece(toCoord);
                if(piece_o == std::nullopt){
                    return ActionType::None();
                }
                ActionType::PickPiece action{piece_o.value()};
                return action;
            }
        case ToolSelection::DrawArrow:
            if(fromCoord == toCoord){
                m_boardPtr->addSquareHighlight(tool.arrowColorId(), toCoord);
                return ActionType::None();
            }
            m_boardPtr->addArrow(tool.arrowColorId(), fromCoord, toCoord);
            return ActionType::None();
        default:
            return ActionType::None();
    }
    return ActionType::None();
}

void WorkWindow::dragMouse(const Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& currentPosition){
    
    int fromX = pressPosition.x-(int)m_position.x;
    int fromY = pressPosition.y-(int)m_position.y;

    auto fromCoord_o = m_boardPtr->getSquareCoord({fromX,fromY});

    if(fromCoord_o == std::nullopt){
        return;
    }

    int toX = currentPosition.x-(int)m_position.x;
    int toY = currentPosition.y-(int)m_position.y;

    auto toCoord_o = m_boardPtr->getSquareCoord({toX, toY});

    if(toCoord_o == std::nullopt){
        m_boardPtr->removeDragArrow();
        return;
    }

    auto fromCoord = fromCoord_o.value();
    auto toCoord = toCoord_o.value();

    if(fromCoord == toCoord){
        m_boardPtr->removeDragArrow();
        return;
    }

    switch(tool.selection()){
        case ToolSelection::Select:
            if(!m_boardPtr->isEmptySquare(fromCoord)){
                m_boardPtr->updateDragArrow(fromCoord, toCoord);
            }
            return;
        case ToolSelection::DrawArrow:
            m_boardPtr->updateDragArrow(fromCoord, toCoord);
            return;
        default:
            return;
    }
    return;
}

void WorkWindow::keyPressed(const sf::Event::KeyPressed& event){
    m_boardPtr->keyPressed(event);
}

void WorkWindow::textEntered(const std::string& text){
    m_boardPtr->textEntered(text);
}

void WorkWindow::reset(){
    std::string fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"};
    m_boardPtr->clear();
    m_boardPtr->loadFENPiecePlacement(fen);
}

void WorkWindow::clear(){
    m_boardPtr->clear();
}

void WorkWindow::print(){
    m_boardPtr->print();
}

void WorkWindow::saveLogicBoard(){
    m_boardPtr->saveLogic();
}

void WorkWindow::saveBoardImage(const std::string& filename){
    m_boardPtr->saveImage(filename);
}

void WorkWindow::addCoordinates(){
    m_boardPtr->addCoordinates();
}

void WorkWindow::removeCoordinates(){
    m_boardPtr->removeCoordinates();
}

void WorkWindow::moveCoordinatesOutside(){
    m_boardPtr->moveCoordinatesOutside();
}

void WorkWindow::moveCoordinatesInside(){
    m_boardPtr->moveCoordinatesInside();
}

void WorkWindow::setBigCoordinates(){
    m_boardPtr->setBigCoordinates();    
}

void WorkWindow::setSmallCoordinates(){
    m_boardPtr->setSmallCoordinates();
}

void WorkWindow::addBoardBorder(){
    m_boardPtr->addBorder();
}

void WorkWindow::removeBoardBorder(){
    m_boardPtr->removeBorder();
}

void WorkWindow::addPlayerToMoveToken(){
    m_boardPtr->addPlayerToMoveToken();
}

void WorkWindow::removePlayerToMoveToken(){
    m_boardPtr->removePlayerToMoveToken();
}