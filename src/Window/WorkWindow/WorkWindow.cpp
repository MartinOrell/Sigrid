#include "WorkWindow.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include "../../Tool/Tool.h"

#include <SFML/Graphics/Sprite.hpp>
#include "../../Coord/Coord.h"
#include "../../Entity/Shape/Arrow/LogicArrow.h"

#include <iostream>

using namespace sigrid;


WorkWindow::WorkWindow()
: m_backgroundColor{255,255,255,0}
, m_activeBoardId{0}{}

void WorkWindow::setBoardFilename(const std::string& filename){
    if(m_boardPtrs.size() == 0){
        auto board = std::make_unique<Board>();
        m_boardPtrs.push_back(std::move(board));
    }
    if(m_boardPtrs.size() < m_activeBoardId){
        std::cerr << "Invalid board id: " << m_activeBoardId << std::endl;
        return;
    }
    m_boardPtrs.at(m_activeBoardId)->setFilename(filename);
}

void WorkWindow::setDefaultBoardImageFilename(const std::string& filename){
    m_defaultBoardImageFilename = filename;
}

void WorkWindow::setTileColorManagerPtr(ColorManager* const managerPtr){
    if(m_boardPtrs.size() == 0){
        auto board = std::make_unique<Board>();
        m_boardPtrs.push_back(std::move(board));
    }
    if(m_boardPtrs.size() < m_activeBoardId){
        std::cerr << "Invalid board id: " << m_activeBoardId << std::endl;
        return;
    }
    m_boardPtrs.at(m_activeBoardId)->setTileColorManagerPtr(managerPtr);
}

void WorkWindow::setPieceManagerPtr(PieceManager* const managerPtr){
    if(m_boardPtrs.size() == 0){
        auto board = std::make_unique<Board>();
        m_boardPtrs.push_back(std::move(board));
    }
    if(m_boardPtrs.size() < m_activeBoardId){
        std::cerr << "Invalid board id: " << m_activeBoardId << std::endl;
        return;
    }
    m_boardPtrs.at(m_activeBoardId)->setPieceManagerPtr(managerPtr);
}

void WorkWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){
    if(m_boardPtrs.size() == 0){
        auto board = std::make_unique<Board>();
        m_boardPtrs.push_back(std::move(board));
    }
    if(m_boardPtrs.size() < m_activeBoardId){
        std::cerr << "Invalid board id: " << m_activeBoardId << std::endl;
        return;
    }
    m_boardPtrs.at(m_activeBoardId)->setArrowColorManagerPtr(managerPtr);
}

void WorkWindow::setFontManagerPtr(FontManager* const managerPtr){
    if(m_boardPtrs.size() == 0){
        auto board = std::make_unique<Board>();
        m_boardPtrs.push_back(std::move(board));
    }
    if(m_boardPtrs.size() < m_activeBoardId){
        std::cerr << "Invalid board id: " << m_activeBoardId << std::endl;
        return;
    }
    m_boardPtrs.at(m_activeBoardId)->setFontManagerPtr(managerPtr);
}

void WorkWindow::init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData){

    if(m_boardPtrs.size() == 0){
        auto board = std::make_unique<Board>();
        m_boardPtrs.push_back(std::move(board));
    }
    m_activeBoardId = 0;

    m_boardPtrs.at(0)->init(boardData, graphicData);

    std::cout << "Save location: " << m_boardPtrs.at(0)->getFilename() << std::endl;

    if(!m_boardPtrs.at(0)->isImageFilenameSet()){
        m_boardPtrs.at(0)->setImageFilename(m_defaultBoardImageFilename);
    }
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

std::string WorkWindow::getName() const{
    return m_boardPtrs.at(m_activeBoardId)->getName();
}

std::string WorkWindow::getFen() const{
    return m_boardPtrs.at(m_activeBoardId)->getFen();
}

void WorkWindow::setPosition(const sf::Vector2f& position){
    m_position = position;
}

unsigned int WorkWindow::getNumColumns() const{
    if(m_boardPtrs.size() <= m_activeBoardId){
        return 0;
    }
    return m_boardPtrs.at(m_activeBoardId)->getNumColumns();
}

bool WorkWindow::contains(const sf::Vector2f& point) const{

    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point);
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
    texture.draw(*m_boardPtrs.at(m_activeBoardId));
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}



Action WorkWindow::clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition){
    
    m_boardPtrs.at(m_activeBoardId)->removeDragArrow();

    sf::Vector2f from = pressPosition - m_position;
    sf::Vector2f to = releasePosition - m_position;

    if(m_boardPtrs.at(m_activeBoardId)->isWithinTurnToken(from) &&
    m_boardPtrs.at(m_activeBoardId)->isWithinTurnToken(to)){
        m_boardPtrs.at(m_activeBoardId)->toggleTurnToken();
    }

    auto fromCoord_o = m_boardPtrs.at(m_activeBoardId)->getTileCoord(from);
    auto toCoord_o = m_boardPtrs.at(m_activeBoardId)->getTileCoord(to);

    
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
            useAddEntityTool(toCoord,tool.getEntity());
            return ActionType::None();
        case ToolSelection::EntityPicker:
            {
                auto logicEntity_o = m_boardPtrs.at(m_activeBoardId)->getLogicEntity(toCoord);
                if(logicEntity_o == std::nullopt){
                    return ActionType::None();
                }
                ActionType::PickEntity action{logicEntity_o.value()};
                return action;
            }
        case ToolSelection::DrawArrow:
            if(fromCoord == toCoord){
                useAddTileHighlightTool(toCoord, tool.getArrowColorId());
                return ActionType::None();
            }
            useAddArrowTool(fromCoord, toCoord, tool.getArrowColorId());
            return ActionType::None();
        default:
            return ActionType::None();
    }
    return ActionType::None();
}

void WorkWindow::dragMouse(const Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& currentPosition){
    
    sf::Vector2f from = pressPosition - m_position;

    auto fromCoord_o = m_boardPtrs.at(m_activeBoardId)->getTileCoord(from);

    if(fromCoord_o == std::nullopt){
        return;
    }

    sf::Vector2f to = currentPosition - m_position;

    auto toCoord_o = m_boardPtrs.at(m_activeBoardId)->getTileCoord(to);

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
            if(!m_boardPtrs.at(m_activeBoardId)->isEmptyTile(fromCoord)){
                m_boardPtrs.at(m_activeBoardId)->updateDragArrow(fromCoord, toCoord, tool.getArrowColorId());
            }
            return;
        case ToolSelection::DrawArrow:
            m_boardPtrs.at(m_activeBoardId)->updateDragArrow(fromCoord, toCoord, tool.getArrowColorId());
            return;
        default:
            return;
    }
    return;
}

void WorkWindow::reset(){
    std::string fen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
    m_boardPtrs.at(m_activeBoardId)->loadFen(fen);
    m_boardPtrs.at(m_activeBoardId)->clearArrows();
}

void WorkWindow::clear(){
    m_boardPtrs.at(m_activeBoardId)->clearEntities();
    m_boardPtrs.at(m_activeBoardId)->clearArrows();
}

void WorkWindow::print(){
    m_boardPtrs.at(m_activeBoardId)->print();
}

std::string WorkWindow::getUniqueName(const std::string& name){
    std::string newName(name);
    while(true){
        
        bool exists = false;
        for(const auto& board: m_boardPtrs){
            if(board->getFilename() == newName || board->getImageFilename() == newName){
                exists = true;
                break;
            }
        }
        if(!exists){
            if(!std::filesystem::exists(newName)){
                break;
            }
        }

        auto endPos = newName.rfind('.');
        if(endPos == newName.npos){
            std::cerr << "WorkWindow: No . in getUniqueName";
            return newName;
        }
        auto startPos = endPos;
        while(std::isdigit(newName.at(startPos-1))){
            startPos--;
        }
        if(startPos == endPos){
            newName.insert(startPos, "2");
        }
        else{
            std::string digitString = newName.substr(startPos,endPos-startPos);
            int digit = std::stoi(digitString);
            digit++;
            digitString = std::to_string(digit);
            newName.erase(startPos,endPos-startPos);
            newName.insert(startPos, digitString);
        }
    }
    return newName;
}

void WorkWindow::newBoard(){

    auto newBoard = std::make_unique<Board>();
    *newBoard = *m_boardPtrs.at(m_activeBoardId);

    std::string newName = getUniqueName(m_boardPtrs.at(m_activeBoardId)->getFilename());
    std::string newImageName = getUniqueName(m_boardPtrs.at(m_activeBoardId)->getImageFilename());

    std::cout << "New board name " << newName << std::endl;
    std::cout << "New image name " << newImageName << std::endl;    
    
    newBoard->setFilename(newName);
    newBoard->setImageFilename(newImageName);

    m_boardPtrs.push_back(std::move(newBoard));
    m_activeBoardId = m_boardPtrs.size()-1;
    reset();
}

void WorkWindow::openLeftBoard(){

    if(m_activeBoardId == 0){
        m_activeBoardId = m_boardPtrs.size()-1;
    }
    else{
        m_activeBoardId--;
    }
}

void WorkWindow::openRightBoard(){
    m_activeBoardId = (m_activeBoardId+1)%m_boardPtrs.size();
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

void WorkWindow::addSquareColumnRight(){
    m_boardPtrs.at(m_activeBoardId)->addSquareColumnRight();
}

void WorkWindow::addSquareColumnLeft(){
    m_boardPtrs.at(m_activeBoardId)->addSquareColumnLeft();
}

void WorkWindow::removeSquareColumnRight(){
    m_boardPtrs.at(m_activeBoardId)->removeSquareColumnRight();
}

void WorkWindow::removeSquareColumnLeft(){
    m_boardPtrs.at(m_activeBoardId)->removeSquareColumnLeft();
}

void WorkWindow::addSquareRowUp(){
    m_boardPtrs.at(m_activeBoardId)->addSquareRowUp();
}

void WorkWindow::addSquareRowDown(){
    m_boardPtrs.at(m_activeBoardId)->addSquareRowDown();
}

void WorkWindow::removeSquareRowUp(){
    m_boardPtrs.at(m_activeBoardId)->removeSquareRowUp();
}

void WorkWindow::removeSquareRowDown(){
    m_boardPtrs.at(m_activeBoardId)->removeSquareRowDown();
}

void WorkWindow::addBoardBorder(){
    m_boardPtrs.at(m_activeBoardId)->addBorder();
}

void WorkWindow::removeBoardBorder(){
    m_boardPtrs.at(m_activeBoardId)->removeBorder();
}

void WorkWindow::addTurnToken(){
    m_boardPtrs.at(m_activeBoardId)->addTurnToken();
}

void WorkWindow::removeTurnToken(){
    m_boardPtrs.at(m_activeBoardId)->removeTurnToken();
}

void WorkWindow::useAddEntityTool(const Coord& coord, const LogicEntity& newEntity){

    auto occupying_entity_o = m_boardPtrs.at(m_activeBoardId)->getLogicEntity(coord);

    if(occupying_entity_o == std::nullopt){
        m_boardPtrs.at(m_activeBoardId)->addEntity(coord, newEntity);
        return;
    }

    if(occupying_entity_o.value() == newEntity){
        m_boardPtrs.at(m_activeBoardId)->removeEntity(coord);
        return;
    }

    m_boardPtrs.at(m_activeBoardId)->removeEntity(coord);
    m_boardPtrs.at(m_activeBoardId)->addEntity(coord, newEntity);
}

void WorkWindow::useAddEntityAtSelectionTool(const LogicEntity& newEntity){
    m_boardPtrs.at(m_activeBoardId)->addEntityAtSelection(newEntity);
}

void WorkWindow::useAddTileHighlightTool(const Coord& coord, const int& colorId){

    auto tile_o = m_boardPtrs.at(m_activeBoardId)->getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "WorkWindow: unable to find logic tile "
            << coord.getNotation() << " on board with id "
            << m_activeBoardId
            << " when adding highlight" << std::endl;
        return;
    }

    auto occupyingColor_o = tile_o.value().getHighlightColorId();

    if(occupyingColor_o == std::nullopt){
        m_boardPtrs.at(m_activeBoardId)->addTileHighlight(coord, colorId);
        return;
    }

    if(occupyingColor_o.value() == colorId){
        m_boardPtrs.at(m_activeBoardId)->removeTileHighlight(coord);
        return;
    }

    m_boardPtrs.at(m_activeBoardId)->removeTileHighlight(coord);
    m_boardPtrs.at(m_activeBoardId)->addTileHighlight(coord, colorId);
}

void WorkWindow::useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId){

    auto occupyingArrow_o = m_boardPtrs.at(m_activeBoardId)->getLogicArrow({fromCoord, toCoord});

    if(occupyingArrow_o == std::nullopt){
        m_boardPtrs.at(m_activeBoardId)->addArrow(fromCoord, toCoord, LogicArrow{colorId});
        return;
    }

    if(occupyingArrow_o.value().getColorId() == colorId){
        m_boardPtrs.at(m_activeBoardId)->removeArrow(fromCoord, toCoord);
        return;
    }

    m_boardPtrs.at(m_activeBoardId)->removeArrow(fromCoord, toCoord);
    m_boardPtrs.at(m_activeBoardId)->addArrow(fromCoord, toCoord, LogicArrow{colorId});
}