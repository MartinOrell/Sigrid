#include "GraphicBoard.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include "LogicBoard.h"
#include "../Piece/PieceManager.h"


using namespace sigrid;

GraphicBoard::GraphicBoard(const LogicBoard& logicBoard, const GraphicBoardConfigContainer& config, PieceManager* pieceManagerPtr, const std::vector<sf::Color> squareColors, ColorManager* colorManagerPtr)
: m_scale{1.f}
, m_colorManagerPtr{colorManagerPtr}
, m_backgroundColor{sf::Color{255,255,255,255}}
, m_leftEdgeWidth{0}
, m_rightEdgeWidth{0}
, m_topEdgeWidth{0}
, m_bottomEdgeWidth{0}
, m_showLabels{config.labelsInside || config.labelsOutside}
, m_isCoordinateLabelsInside{config.labelsInside}
, m_insideLabelSizeFactor{config.insideLabelSize}
, m_outsideLabelSizeFactor{config.outsideLabelSize}
, m_outsideLabelSmallSizeFactor{config.outsideLabelSmallSize}
, m_outsideLabelBigSizeFactor{config.outsideLabelBigSize}
, m_showBorder{config.border}
, m_borderWidth{config.borderWidth}
, m_showPlayerToMoveToken{config.playerToMoveToken}{

    if(!m_font.openFromFile(config.labelFont)){
        std::cout << "GraphicBoard: Failed to open font: " << config.labelFont << std::endl;
    }

    for(int i = 0; i < squareColors.size(); i++){
        m_squareColors.push_back(squareColors.at(i));
    }

    for(int y = 0; y < logicBoard.height(); y++){
        std::vector<sf::RectangleShape> row;
        for(int x = 0; x < logicBoard.height(); x++){
            sf::RectangleShape square{sf::Vector2f((float)config.squareSize, (float)config.squareSize)};
            sf::Color squareColor = m_squareColors.at((x+y)%m_squareColors.size());
            square.setFillColor(squareColor);
            sf::Vector2f position;
            position.x = (float)(x*config.squareSize);
            position.x += m_leftEdgeWidth;
            position.y = (float)(y*config.squareSize);
            position.y += m_topEdgeWidth;
            square.setPosition(position);
            row.push_back(square);

            auto piece_o = logicBoard.getPieceAt({x,y});
            if(piece_o != std::nullopt){

                auto newPiece_o = pieceManagerPtr->getPiece(*piece_o.value());
                if(newPiece_o != std::nullopt){
                    GraphicPiece newPiece = newPiece_o.value().graphic();
                    newPiece.resize({(float)config.squareSize,(float)config.squareSize});
                    newPiece.setPosition(square.getPosition());
                    m_pieces.insert({{x,y}, newPiece});
                }
            }
        }
        m_squares.push_back(row);
    }

    if(m_showLabels){
        if(m_isCoordinateLabelsInside){
            addInsideLabels();
        }
        else{
            unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().x;
            unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().y;

            setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);
            addOutsideLabels();
        }
    }

    if(m_showPlayerToMoveToken){
        m_rightEdgeWidth = (unsigned int)(0.5*m_squares.at(0).at(0).getSize().y);
        initPlayerToMoveToken();
    }

    if(m_showBorder){
        moveSquares({(float)m_borderWidth, (float)m_borderWidth});
        initLeftBorder();
        initRightBorder();
        initTopBorder();
        initBottomBorder();
    }
    
    m_texturePtr = std::make_unique<sf::RenderTexture>();
    resizeTexture();
    redrawTexture();
}

sf::Vector2f GraphicBoard::getSquareSize() const{
    return m_squares.at(0).at(0).getSize();
}

void GraphicBoard::setPosition(sf::Vector2f position){
    m_position = position;
}

void GraphicBoard::setPositionX(float x){
    m_position.x = x;
}

void GraphicBoard::setScale(const float scale){
    m_scale = scale;
}

unsigned int GraphicBoard::getImageWidth() const{
    return m_texturePtr->getSize().x;
}

unsigned int GraphicBoard::getImageHeight() const{
    return m_texturePtr->getSize().y;
}

float GraphicBoard::getDisplayWidth() const{
    return (float)m_texturePtr->getSize().x*m_scale;
}

float GraphicBoard::getDisplayHeight() const{
    return (float)m_texturePtr->getSize().y*m_scale;
}

bool GraphicBoard::contains(sf::Vector2i point) const{
    sf::Sprite sprite(m_texturePtr->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

bool GraphicBoard::isCoordinatesOutside() const{
    return !m_isCoordinateLabelsInside;
}

bool GraphicBoard::isWithinPlayerToMoveToken(sf::Vector2i point) const{
    if(!m_showPlayerToMoveToken){
        return false;
    }
    if(!m_playerToMoveToken){
        return false;
    }

    float x = (float)point.x - m_position.x;
    float y = (float)point.y - m_position.y;

    float radius = m_playerToMoveToken->getRadius()*m_scale;
    float centerX = m_playerToMoveToken->getPosition().x*m_scale+radius;
    float centerY = m_playerToMoveToken->getPosition().y*m_scale+radius;

    return (x-centerX)*(x-centerX)+(y-centerY)*(y-centerY) < radius*radius;
}

std::optional<Coord> GraphicBoard::getSquareCoord(sf::Vector2i point){

    sf::Vector2u rect = m_texturePtr->getSize();
    rect.x = rect.x - m_leftEdgeWidth - m_rightEdgeWidth;
    rect.x *= m_scale;

    rect.y = rect.y - m_topEdgeWidth - m_bottomEdgeWidth;
    rect.y *= m_scale;

    float x = (float)point.x - m_position.x;
    x = x - (float)m_leftEdgeWidth*m_scale;
    x = x *(float)m_squares.at(0).size()/(float)rect.x;

    float y = (float)point.y - m_position.y;
    y = y - (float)(m_topEdgeWidth*m_scale);
    y = y * (float)m_squares.size() / (float)rect.y;

    if(x < 0.f){
        return std::nullopt;
    }
    if(x >= (float)m_squares.at(0).size()){
        return std::nullopt;
    }
    if(y < 0.f){
        return std::nullopt;
    }
    if(y >= (float)m_squares.size()){
        return std::nullopt;
    }
    return std::make_optional<Coord>((int)x,(int)y);
}

void GraphicBoard::addPiece(const GraphicPiece& piece, const Coord& coord){
    
    assert(m_pieces.find(coord) == m_pieces.end());

    GraphicPiece newPiece{piece};
    newPiece.resize({(float)m_squares[coord.y][coord.x].getSize().x,(float)m_squares[coord.y][coord.x].getSize().y});
    newPiece.setPosition(m_squares[coord.y][coord.x].getPosition());
    m_pieces.insert({coord, newPiece});
    redrawTexture();
}

void GraphicBoard::removePiece(const Coord& coord){
    auto pieceIt = m_pieces.find(coord);
    assert(pieceIt != m_pieces.end());
    m_pieces.erase(pieceIt);
    redrawTexture();
}

void GraphicBoard::movePiece(const Coord& fromCoord, const Coord& toCoord){
    assert(fromCoord != toCoord);

    auto capturedPieceIt = m_pieces.find(toCoord);

    if(capturedPieceIt != m_pieces.end()){
        m_pieces.erase(capturedPieceIt);
    }

    GraphicPiece newPiece{m_pieces.at(fromCoord)};
    newPiece.setPosition(m_squares[toCoord.y][toCoord.x].getPosition());

    m_pieces.insert({toCoord, newPiece});

    m_pieces.erase(fromCoord);

    redrawTexture();
}

void GraphicBoard::addSquareHighlight(const int colorId, const Coord& coord){

    auto it = m_squareHighlights.find(coord);

    if(it != m_squareHighlights.end()){
        m_squareHighlights.erase(it);
        redrawTexture();
        return;
    }

    sf::RectangleShape newHighlight(getSquareSize());

    sf::Color color;
    if(m_colorManagerPtr == nullptr){
        color = sf::Color(0xff000088);
    }
    else{
        color = m_colorManagerPtr->getTransparentColor(colorId);
    }

    newHighlight.setFillColor(color);
    newHighlight.setPosition(m_squares.at(coord.y).at(coord.x).getPosition());

    auto result = m_squareHighlights.insert({coord, newHighlight});

    assert (result.second);

    redrawTexture();
}

void GraphicBoard::addArrow(const LogicArrow& logicArrow){

    for(auto it = m_arrows.begin(); it != m_arrows.end(); it++){
        if(it->first.fromCoord() == logicArrow.fromCoord() && it->first.toCoord() == logicArrow.toCoord()){
            if(it->first.colorId() == logicArrow.colorId()){
                m_arrows.erase(it);
                redrawTexture();
                return;
            }
            m_arrows.erase(it);
            break;
        }
    }

    int fromX = logicArrow.fromCoord().x;
    int fromY = logicArrow.fromCoord().y;
    int toX = logicArrow.toCoord().x;
    int toY = logicArrow.toCoord().y;
    auto fromPosition = m_squares.at(fromY).at(fromX).getPosition() + m_squares.at(fromY).at(fromX).getSize()/2.f;
    auto toPosition = m_squares.at(toY).at(toX).getPosition() + m_squares.at(toY).at(toX).getSize()/2.f;
    
    sf::Color color;
    if(m_colorManagerPtr == nullptr){
        color = sf::Color::Red;
    }
    else{
        color = m_colorManagerPtr->getSolidColor(logicArrow.colorId());
    }

    GraphicArrow graphicArrow(fromPosition, toPosition, color);
    m_texturePtr->draw(graphicArrow);
    auto result = m_arrows.insert({logicArrow, graphicArrow});

    assert(result.second);
}

void GraphicBoard::removeArrow(const LogicArrow& arrow){

}

void GraphicBoard::updateDragArrow(const Coord& fromCoord, const Coord& toCoord){
    
    if(!m_dragArrowPtr){
        int fromX = fromCoord.x;
        int fromY = fromCoord.y;
        int toX = toCoord.x;
        int toY = toCoord.y;
        auto fromPosition = m_squares.at(fromY).at(fromX).getPosition() + m_squares.at(fromY).at(fromX).getSize()/2.f;
        auto toPosition = m_squares.at(toY).at(toX).getPosition() + m_squares.at(toY).at(toX).getSize()/2.f;

        sf::Color color = sf::Color::Red;

        m_dragArrowPtr = std::make_unique<Arrow>(fromCoord, toCoord, 0, fromPosition, toPosition, color);
        m_texturePtr->draw(*m_dragArrowPtr);
        return;
    }

    if(m_dragArrowPtr->fromCoord() == fromCoord && m_dragArrowPtr->toCoord() == toCoord){
        return;
    }

    int fromX = fromCoord.x;
    int fromY = fromCoord.y;
    int toX = toCoord.x;
    int toY = toCoord.y;
    auto fromPosition = m_squares.at(fromY).at(fromX).getPosition() + m_squares.at(fromY).at(fromX).getSize()/2.f;
    auto toPosition = m_squares.at(toY).at(toX).getPosition() + m_squares.at(toY).at(toX).getSize()/2.f;

    m_dragArrowPtr->set(fromCoord, toCoord, fromPosition, toPosition);
    redrawTexture();
}

void GraphicBoard::removeDragArrow(){
    if(m_dragArrowPtr){
        m_dragArrowPtr = nullptr;
        redrawTexture();
    }
}

void GraphicBoard::highlightSquare(const Coord& coord){
    if(!m_selectHighlight){
        m_selectHighlight = std::make_unique<sf::RectangleShape>(m_squares[coord.y][coord.x].getSize());
        m_selectHighlight->setFillColor(sf::Color(255,255,0,100));
    }

    m_selectHighlight->setPosition(m_squares[coord.y][coord.x].getPosition());

    redrawTexture();
}

void GraphicBoard::unhighlight(){
    if(m_selectHighlight){
        m_selectHighlight = nullptr;
        redrawTexture();
    }
}



void GraphicBoard::saveImage(const std::string& fileName){
    auto image = m_texturePtr->getTexture().copyToImage();
    image.flipVertically();
    std::cout << "Saving board image: " << fileName << std::endl;
    auto success = image.saveToFile(fileName);
    if(success){
        std::cout << "board image: " << fileName << " saved" << std::endl;
    }
    else{
        std::cout << "Failed to save board image: " << fileName << std::endl;
    }
}

void GraphicBoard::clear(){
    m_pieces.clear();
    redrawTexture();
}

void GraphicBoard::addCoordinates(){

    if(m_isCoordinateLabelsInside){
        addInsideLabels();
        redrawTexture();
        return;
    }

    unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().x;
    unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().y;

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    addOutsideLabels();
    redrawTexture();
}

void GraphicBoard::removeCoordinates(){
    
    if(m_isCoordinateLabelsInside){
        m_leftInsideCoordinateLabels.clear();
        m_bottomInsideCoordinateLabels.clear();
        redrawTexture();
        return;
    }

    setLeftAndBottomEdgeWidth(0,0);

    m_leftOutsideCoordinateLabels.clear();
    m_bottomOutsideCoordinateLabels.clear();
    redrawTexture();
}

void GraphicBoard::moveCoordinatesOutside(){
    if(!m_isCoordinateLabelsInside){
        return;
    }
    m_isCoordinateLabelsInside = false;
    m_showLabels = true;

    unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().x;
    unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().y;

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    m_leftInsideCoordinateLabels.clear();
    m_bottomInsideCoordinateLabels.clear();
    addOutsideLabels();
    redrawTexture();
}

void GraphicBoard::moveCoordinatesInside(){
    if(m_isCoordinateLabelsInside){
        return;
    }
    m_isCoordinateLabelsInside = true;
    m_showLabels = true;

    setLeftAndBottomEdgeWidth(0,0);

    m_leftOutsideCoordinateLabels.clear();
    m_bottomOutsideCoordinateLabels.clear();
    addInsideLabels();
    redrawTexture();
}

void GraphicBoard::setBigCoordinates(){
    
    m_outsideLabelSizeFactor = m_outsideLabelBigSizeFactor;

    unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().x;
    unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().y;

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    addOutsideLabels();
    redrawTexture();

}

void GraphicBoard::setSmallCoordinates(){

    m_outsideLabelSizeFactor = m_outsideLabelSmallSizeFactor;

    unsigned int leftEdgeWidth = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().x;
    unsigned int leftEdgeHeight = m_outsideLabelSizeFactor* m_squares.at(0).at(0).getSize().y;

    setLeftAndBottomEdgeWidth(leftEdgeWidth,leftEdgeHeight);

    addOutsideLabels();
    redrawTexture();
}

void GraphicBoard::addBorder(){

    if(m_showBorder){
        return;
    }

    m_showBorder = true;

    moveSquares({(float)m_borderWidth, (float)m_borderWidth});
    moveLeftInsideCoordinateLabels({(float)m_borderWidth, (float)m_borderWidth});
    moveBottomInsideCoordinateLabels({(float)m_borderWidth, (float)m_borderWidth});
    moveLeftOutsideCoordinateLabels({0.f, (float)m_borderWidth});
    moveBottomOutsideCoordinateLabels({(float)m_borderWidth, 2.f*(float)m_borderWidth});
    movePlayerToMoveToken({2.f*(float)m_borderWidth, (float)m_borderWidth});

    if(!m_leftBorder){
        initLeftBorder();
    }

    if(!m_rightBorder){
        initRightBorder();
    }

    if(!m_topBorder){
        initTopBorder();
    }

    if(!m_bottomBorder){
        initBottomBorder();
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removeBorder(){

    if(!m_showBorder){
        return;
    }

    m_showBorder = false;

    moveSquares({-(float)m_borderWidth, -(float)m_borderWidth});
    movePlayerToMoveToken({-2.f*(float)m_borderWidth, -(float)m_borderWidth});
    moveLeftInsideCoordinateLabels({-(float)m_borderWidth, -(float)m_borderWidth});
    moveBottomInsideCoordinateLabels({-(float)m_borderWidth, -(float)m_borderWidth});
    moveLeftOutsideCoordinateLabels({0.f, -(float)m_borderWidth});
    moveBottomOutsideCoordinateLabels({-(float)m_borderWidth, -2.f*(float)m_borderWidth});

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::addPlayerToMoveToken(){

    if(m_showPlayerToMoveToken){
        return;
    }

    m_showPlayerToMoveToken = true;

    m_rightEdgeWidth = (unsigned int)(0.5*m_squares.at(0).at(0).getSize().y);

    if(!m_playerToMoveToken){
        initPlayerToMoveToken();
    }

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::removePlayerToMoveToken(){

    if(!m_showPlayerToMoveToken){
        return;
    }

    m_showPlayerToMoveToken = false;

    m_rightEdgeWidth = 0;

    resizeTexture();
    redrawTexture();
}

void GraphicBoard::togglePlayerToMoveToken(){
    if(!m_playerToMoveToken){
        std::cout << "GraphicBoard: Unable to toggle player-to-move token. It does not exist" << std::endl;
        return;
    }

    if(m_playerToMoveToken->getFillColor().toInteger() == sf::Color{255,255,255,255}.toInteger()){
        m_playerToMoveToken->setFillColor(sf::Color{0,0,0,255});
    }
    else{
        m_playerToMoveToken->setFillColor(sf::Color{255,255,255,255});
    }

    m_texturePtr->draw(*m_playerToMoveToken);
}

void GraphicBoard::initPlayerToMoveToken(){
    float radius = 0.2*m_squares.at(0).at(0).getSize().y;
    std::size_t pointCount = 30;
    m_playerToMoveToken = std::make_unique<sf::CircleShape>(radius, pointCount);
    float x = m_leftEdgeWidth;
    if(m_showBorder){
        x+= 2*m_borderWidth;
    }
    x += m_squares.at(0).at(0).getSize().x*m_squares.size();
    x += m_rightEdgeWidth/2.f;
    x -= radius;
    float y = m_topEdgeWidth;
    y += m_squares.at(0).at(0).getSize().y/2.f;
    y -= radius;
    m_playerToMoveToken->setPosition({x,y});

    m_playerToMoveToken->setFillColor(sf::Color{255,255,255,255});
    m_playerToMoveToken->setOutlineColor(sf::Color{0,0,0,255});
    m_playerToMoveToken->setOutlineThickness(-6.f);
}

void GraphicBoard::initLeftBorder(){
    float width = (float)m_borderWidth;
    float height = m_squares.at(0).at(0).getSize().x*m_squares.at(0).size() + 2*m_borderWidth;
    m_leftBorder = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = (float)m_leftEdgeWidth;
    float y = 0.f;
    m_leftBorder->setPosition({x,y});
    m_leftBorder->setFillColor(sf::Color{0,0,0,255});
}

void GraphicBoard::initRightBorder(){
    float width = (float)m_borderWidth;
    float height = m_squares.at(0).at(0).getSize().y*m_squares.at(0).size() + 2*m_borderWidth;
    m_rightBorder = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = (float)m_leftEdgeWidth + (float)m_squares.at(0).at(0).getSize().x*(float)m_squares.at(0).size() + m_borderWidth;
    float y = 0.f;
    m_rightBorder->setPosition({x,y});
    m_rightBorder->setFillColor(sf::Color{0,0,0,255});
}

void GraphicBoard::initTopBorder(){
    float width = m_squares.at(0).at(0).getSize().x*m_squares.at(0).size() + 2*m_borderWidth;
    float height = (float)m_borderWidth;
    m_topBorder = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = (float)m_leftEdgeWidth;
    float y = 0.f;
    m_topBorder->setPosition({x,y});
    m_topBorder->setFillColor(sf::Color{0,0,0,255});
}

void GraphicBoard::initBottomBorder(){
    float width = m_squares.at(0).at(0).getSize().x*m_squares.at(0).size() + 2*m_borderWidth;
    float height = (float)m_borderWidth;
    m_bottomBorder = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = (float)m_leftEdgeWidth;
    float y = (float)m_topEdgeWidth + (float)m_squares.at(0).at(0).getSize().y*(float)m_squares.at(0).size() + m_borderWidth;
    m_bottomBorder->setPosition({x,y});
    m_bottomBorder->setFillColor(sf::Color{0,0,0,255});
}

unsigned int GraphicBoard::getTextureWidth() const{

    unsigned int boardWidth = (unsigned int)(m_squares.at(0).at(0).getSize().x*m_squares.at(0).size());
    boardWidth += m_leftEdgeWidth+m_rightEdgeWidth;
    if(m_showBorder){
        boardWidth += 2*m_borderWidth;
    }

    return boardWidth;

}

unsigned int GraphicBoard::getTextureHeight() const{
    unsigned int boardHeight = (unsigned int)(m_squares.at(0).at(0).getSize().y*(unsigned int)m_squares.size());
    boardHeight += m_topEdgeWidth+m_bottomEdgeWidth;
    if(m_showBorder){
        boardHeight += 2*m_borderWidth;
    }

    return boardHeight;
}

void GraphicBoard::resizeTexture(){

    bool success;
    success = m_texturePtr->resize({getTextureWidth(), getTextureHeight()});
    if(!success){
        std::cout << "GraphicWindow: Failed to resize texture" << std::endl;
        return;
    }
}

void GraphicBoard::redrawTexture(){
    m_texturePtr->clear(m_backgroundColor);

    for(int y = 0; y < m_squares.size(); y++){
        for(int x = 0; x < m_squares.at(y).size(); x++){
            m_texturePtr->draw(m_squares[y][x]);
        }
    }

    

    for(const auto& highlightSquare: m_squareHighlights){
        m_texturePtr->draw(highlightSquare.second);
    }

    if(m_selectHighlight){
        m_texturePtr->draw(*m_selectHighlight);
    }

    for(auto& piece : m_pieces){
        m_texturePtr->draw(piece.second);
    }

    for(auto& arrow : m_arrows){
        m_texturePtr->draw(arrow.second);
    }

    if(m_dragArrowPtr){
        m_texturePtr->draw(*m_dragArrowPtr);
    }

    for(const auto& label : m_leftOutsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    for(const auto& label : m_bottomOutsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    for(const auto& label : m_leftInsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    for(const auto& label : m_bottomInsideCoordinateLabels){
        m_texturePtr->draw(label);
    }

    if(m_leftBorder && m_showBorder){
        m_texturePtr->draw(*m_leftBorder);
    }

    if(m_rightBorder && m_showBorder){
        m_texturePtr->draw(*m_rightBorder);
    }

    if(m_topBorder && m_showBorder){
        m_texturePtr->draw(*m_topBorder);
    }

    if(m_bottomBorder && m_showBorder){
        m_texturePtr->draw(*m_bottomBorder);
    }

    if(m_playerToMoveToken && m_showPlayerToMoveToken){
        m_texturePtr->draw(*m_playerToMoveToken);
    }
}

void GraphicBoard::setLeftAndBottomEdgeWidth(const unsigned int leftWidth, const unsigned int bottomWidth){
    
    float moveX = (float)leftWidth - (float)m_leftEdgeWidth;
    m_leftEdgeWidth = leftWidth;
    m_bottomEdgeWidth = bottomWidth;

    moveSquares({moveX, 0.f});
    moveBorder({moveX, 0.f});
    movePlayerToMoveToken({moveX, 0.f});

    if(m_texturePtr){
        resizeTexture();
    }
    
}

void GraphicBoard::addOutsideLabels(){

    m_bottomOutsideCoordinateLabels.clear();
    m_leftOutsideCoordinateLabels.clear();

    for(int i = 0; i < m_squares.at(0).size(); i++){
        std::string s = std::to_string(i);
        s[0] = s[0] + 'a' - '0';
        unsigned int labelSize = m_outsideLabelSizeFactor*m_squares.at(0).at(i).getSize().x;
        sf::Text label{m_font, s, labelSize};

        sf::Vector2f position;
        position.x =
            m_squares.at(0).at(i).getPosition().x +
            m_squares.at(0).at(i).getSize().x/2 -
            label.getLocalBounds().size.x/2;

        position.y =
            getTextureHeight() -
            m_bottomEdgeWidth -
            labelSize/4;
        
        label.setPosition(position);
        label.setFillColor(sf::Color::Black);

        m_bottomOutsideCoordinateLabels.push_back(label);
    }

    for(int i = 0; i < m_squares.size(); i++){
        std::string s = std::to_string(m_squares.size() -i);
        unsigned int labelSize = m_outsideLabelSizeFactor*m_squares.at(i).at(0).getSize().y;
        sf::Text label{m_font, s, labelSize};

        label.setOrigin({0.f,0.f});

        sf::Vector2f position;

        //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
        position.x = ((float)m_leftEdgeWidth-(float)labelSize/2.f)/2.f;

        position.y = m_squares.at(i).at(0).getPosition().y +
            m_squares.at(i).at(0).getSize().y/2.f -
            (float)labelSize*9.f/14.f;
        
        label.setPosition(position);
        label.setFillColor(sf::Color::Black);

        m_leftOutsideCoordinateLabels.push_back(label);
    }
}

void GraphicBoard::addInsideLabels(){

    m_bottomInsideCoordinateLabels.clear();
    m_leftInsideCoordinateLabels.clear();

    for(int i = 0; i < m_squares.at(0).size(); i++){
        std::string s = std::to_string(i);
        s[0] = s[0] + 'a' - '0';
        unsigned int labelSize = m_insideLabelSizeFactor*m_squares.at(0).at(i).getSize().x;
        sf::Text label{m_font, s, labelSize};

        sf::Vector2f position;
        position.x =
            m_squares.at(0).at(i).getPosition().x +
            m_squares.at(0).at(i).getSize().x -
            label.getLocalBounds().size.x*5/4;
        
        position.y = getTextureHeight() - labelSize*5/4;
        
        position.y -= (float)m_bottomEdgeWidth;

        label.setPosition(position);

        label.setFillColor(sf::Color(100,100,100,255));
        label.setOutlineColor(m_squareColors.at((i+1)%2));
        label.setOutlineThickness(2);

        m_bottomInsideCoordinateLabels.push_back(label);
    }

    for(int i = 0; i < m_squares.size(); i++){
        std::string s = std::to_string(m_squares.size() -i);
        unsigned int labelSize = m_insideLabelSizeFactor*m_squares.at(i).at(0).getSize().y;
        sf::Text label{m_font, s, labelSize};

        label.setOrigin({0.f,0.f});

        sf::Vector2f position;

        //using labelSize instead of label.getLocalBounds().size.x because localBounds has a weird gap
        position.x = (float)labelSize/16.f;
        position.x += (float)m_leftEdgeWidth;

        position.y = m_squares.at(i).at(0).getPosition().y - (float)labelSize/4.f;
        
        label.setPosition(position);

        label.setFillColor(sf::Color(100,100,100,255));
        label.setOutlineColor(m_squareColors.at(i%2));
        label.setOutlineThickness(2);

        m_leftInsideCoordinateLabels.push_back(label);
    }
}

void GraphicBoard::moveSquares(const sf::Vector2f& offset){
    for(int y = 0; y < m_squares.size(); y++){
        for(int x = 0; x < m_squares.at(y).size(); x++){
            m_squares.at(y).at(x).move(offset);

            auto piecePtr = m_pieces.find({x,y});
            if(piecePtr != m_pieces.end()){
                piecePtr->second.setPosition(m_squares.at(y).at(x).getPosition());
            }
        }
    }
}

void GraphicBoard::moveBorder(const sf::Vector2f& offset){
    if(m_leftBorder){
        m_leftBorder->move(offset);
    }

    if(m_rightBorder){
        m_rightBorder->move(offset);
    }

    if(m_topBorder){
        m_topBorder->move(offset);
    }

    if(m_bottomBorder){
        m_bottomBorder->move(offset);
    }
}

void GraphicBoard::moveLeftInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftInsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::moveBottomInsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomInsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_leftOutsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset){
    for(auto& label : m_bottomOutsideCoordinateLabels){
        label.move(offset);
    }
}

void GraphicBoard::movePlayerToMoveToken(const sf::Vector2f& offset){
    if(m_playerToMoveToken){
        m_playerToMoveToken->move(offset);
    }
}


void GraphicBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite sprite(m_texturePtr->getTexture());
    sprite.setPosition(m_position);
    sprite.setScale({m_scale,m_scale});
    target.draw(sprite);
}