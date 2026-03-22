#include "WorkWindow.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;


WorkWindow::WorkWindow()
: m_backgroundColor{255,255,255,0}{}

void WorkWindow::init(const std::string& boardFilename, const std::string& defaultBoardImageFilename, const BoardDataContainer& boardData, const BoardDesignContainer& graphicData, ColorManager* const squareColorManagerPtr, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr){
    
    m_activeBoardId = 0;
    m_pieceManagerPtr = pieceManagerPtr;

    auto board = std::make_unique<Board>();

    board->init(boardData, graphicData, squareColorManagerPtr, pieceManagerPtr, arrowColorManagerPtr);

    std::cout << "Save location: " << boardFilename << std::endl;

    board->setFilename(boardFilename);

    if(!board->isImageFilenameSet()){
        board->setImageFilename(defaultBoardImageFilename);
    }
    m_boardPtrs.push_back(std::move(board));
}

void WorkWindow::createGraphic(const sf::Vector2u& size)
{
    m_texture = std::make_unique<sf::RenderTexture>(size);

    for(auto& board: m_boardPtrs){
        unsigned int boardWidth = board->getImageWidth();
        unsigned int boardHeight = board->getImageHeight();
        float widthRatio = (float)size.x/(float)boardWidth;
        float heightRatio = (float)size.y/(float)boardHeight;
        float boardScale;
        if(widthRatio < heightRatio){
            boardScale = widthRatio;
        }
        else{
            boardScale = heightRatio;
        }
        board->setScale(boardScale);

        float posX = ((float)(size.x)-float(board->getDisplayWidth()))/2.f;
        float posY = ((float)(size.y)-float(board->getDisplayHeight()))/2.f;
        board->setPosition({posX, posY});
    }
}

void WorkWindow::loadFen(const std::string& fen){
    m_boardPtrs.at(m_activeBoardId)->loadFen(fen);
}

std::string WorkWindow::getFen() const{
    return m_boardPtrs.at(m_activeBoardId)->getFen();
}

void WorkWindow::setPosition(sf::Vector2f position){
    m_position = position;
}

unsigned int WorkWindow::getNumColumns() const{
    if(m_boardPtrs.size() <= m_activeBoardId){
        return 0;
    }
    return m_boardPtrs.at(m_activeBoardId)->getNumColumns();
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
    return m_boardPtrs.at(m_activeBoardId)->isCoordinatesOutside();
}

void WorkWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_texture){
        return;
    }

    sf::RenderTexture texture(m_texture->getSize());
    texture.clear(m_backgroundColor);
    for(auto& board: m_boardPtrs){
        texture.draw(*board);
    }
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}



Action WorkWindow::clicked(const sigrid::Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& releasePosition){
    
    m_boardPtrs.at(m_activeBoardId)->removeDragArrow();

    int fromX = pressPosition.x-(int)m_position.x;
    int fromY = pressPosition.y-(int)m_position.y;

    int toX = releasePosition.x-(int)m_position.x;
    int toY = releasePosition.y-(int)m_position.y;


    if(m_boardPtrs.at(m_activeBoardId)->isWithinPlayerToMoveToken({fromX, fromY}) &&
    m_boardPtrs.at(m_activeBoardId)->isWithinPlayerToMoveToken({toX, toY})){
        m_boardPtrs.at(m_activeBoardId)->togglePlayerToMoveToken();
    }

    auto fromCoord_o = m_boardPtrs.at(m_activeBoardId)->getSquareCoord({fromX,fromY});
    auto toCoord_o = m_boardPtrs.at(m_activeBoardId)->getSquareCoord({toX, toY});

    
    if(fromCoord_o == std::nullopt){
        return ActionType::None();
    }

    if(toCoord_o == std::nullopt){
        switch(tool.selection()){
            case ToolSelection::Select:
                m_boardPtrs.at(m_activeBoardId)->deselect();
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
                m_boardPtrs.at(m_activeBoardId)->select(toCoord);
            }
            else{
                m_boardPtrs.at(m_activeBoardId)->dragAndDrop(fromCoord_o.value(), toCoord_o.value());
            }
            return ActionType::None();
        case ToolSelection::EntityAdder:
            m_boardPtrs.at(m_activeBoardId)->addEntity(toCoord, tool.getEntity());
            return ActionType::None();
        case ToolSelection::EntityPicker:
            {
                auto logicEntity_o = m_boardPtrs.at(m_activeBoardId)->getLogicEntity(toCoord);
                if(logicEntity_o == std::nullopt){
                    return ActionType::None();
                }
                auto graphicEntity_o = m_boardPtrs.at(m_activeBoardId)->getGraphicEntity(toCoord);
                if(graphicEntity_o == std::nullopt){
                    return ActionType::None();
                }
                ActionType::PickEntity action{logicEntity_o.value(), graphicEntity_o.value()};
                return action;
            }
        case ToolSelection::DrawArrow:
            if(fromCoord == toCoord){
                m_boardPtrs.at(m_activeBoardId)->addSquareHighlight(toCoord, tool.arrowColorId());
                return ActionType::None();
            }
            m_boardPtrs.at(m_activeBoardId)->addArrow(fromCoord, toCoord, tool.arrowColorId());
            return ActionType::None();
        default:
            return ActionType::None();
    }
    return ActionType::None();
}

void WorkWindow::dragMouse(const Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& currentPosition){
    
    int fromX = pressPosition.x-(int)m_position.x;
    int fromY = pressPosition.y-(int)m_position.y;

    auto fromCoord_o = m_boardPtrs.at(m_activeBoardId)->getSquareCoord({fromX,fromY});

    if(fromCoord_o == std::nullopt){
        return;
    }

    int toX = currentPosition.x-(int)m_position.x;
    int toY = currentPosition.y-(int)m_position.y;

    auto toCoord_o = m_boardPtrs.at(m_activeBoardId)->getSquareCoord({toX, toY});

    if(toCoord_o == std::nullopt){
        m_boardPtrs.at(m_activeBoardId)->removeDragArrow();
        return;
    }

    auto fromCoord = fromCoord_o.value();
    auto toCoord = toCoord_o.value();

    if(fromCoord == toCoord){
        m_boardPtrs.at(m_activeBoardId)->removeDragArrow();
        return;
    }

    switch(tool.selection()){
        case ToolSelection::Select:
            if(!m_boardPtrs.at(m_activeBoardId)->isEmptySquare(fromCoord)){
                m_boardPtrs.at(m_activeBoardId)->updateDragArrow(fromCoord, toCoord);
            }
            return;
        case ToolSelection::DrawArrow:
            m_boardPtrs.at(m_activeBoardId)->updateDragArrow(fromCoord, toCoord);
            return;
        default:
            return;
    }
    return;
}

void WorkWindow::keyPressed(const sf::Event::KeyPressed& event){

}

void WorkWindow::textEntered(const std::string& text){
    int colorId;
    std::string pieceNotation(text);
    if(std::isupper(pieceNotation.back())){
        colorId = 0;
    }
    else{
        colorId = 1;
        pieceNotation.back() = std::toupper(pieceNotation.back());
    }

    LogicPiece logicPiece{pieceNotation, colorId};

    auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(logicPiece);

    if(graphicPiece_o == std::nullopt){
        return;
    }

    m_boardPtrs.at(m_activeBoardId)->addEntityAtSelection(logicPiece);
}

void WorkWindow::reset(){
    std::string fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"};
    m_boardPtrs.at(m_activeBoardId)->loadFen(fen);
}

void WorkWindow::clear(){
    m_boardPtrs.at(m_activeBoardId)->clear();
}

void WorkWindow::print(){
    m_boardPtrs.at(m_activeBoardId)->print();
}

void WorkWindow::saveBoard(){
    m_boardPtrs.at(m_activeBoardId)->save();
}

void WorkWindow::flipBoard(){
    m_boardPtrs.at(m_activeBoardId)->flipBoard();
}

void WorkWindow::addCoordinates(){
    m_boardPtrs.at(m_activeBoardId)->addCoordinates();
}

void WorkWindow::removeCoordinates(){
    m_boardPtrs.at(m_activeBoardId)->removeCoordinates();
}

void WorkWindow::moveCoordinatesOutside(){
    m_boardPtrs.at(m_activeBoardId)->moveCoordinatesOutside();
}

void WorkWindow::moveCoordinatesInside(){
    m_boardPtrs.at(m_activeBoardId)->moveCoordinatesInside();
}

void WorkWindow::setCoordinateSize(const float& size){
    m_boardPtrs.at(m_activeBoardId)->setCoordinateSize(size);    
}

void WorkWindow::addBoardBorder(){
    m_boardPtrs.at(m_activeBoardId)->addBorder();
}

void WorkWindow::removeBoardBorder(){
    m_boardPtrs.at(m_activeBoardId)->removeBorder();
}

void WorkWindow::addPlayerToMoveToken(){
    m_boardPtrs.at(m_activeBoardId)->addPlayerToMoveToken();
}

void WorkWindow::removePlayerToMoveToken(){
    m_boardPtrs.at(m_activeBoardId)->removePlayerToMoveToken();
}