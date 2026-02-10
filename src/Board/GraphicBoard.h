#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Piece/Piece.h"
#include "LogicBoard.h"
#include "../Piece/PieceManager.h"

#include <vector>
#include <map>
#include <optional>
#include <memory>
#include "Coord.h"

#include "../Arrow/Arrow.h"
#include "../Arrow/LogicArrow.h"
#include "../Arrow/GraphicArrow.h"

#include "../Color/ColorManager.h"

#include "GraphicBoardConfigContainer.h"

namespace sigrid{
    class GraphicBoard: public sf::Drawable{
        public:
            
            GraphicBoard(const LogicBoard& logicBoard, const GraphicBoardConfigContainer& config, PieceManager* pieceManagerPtr, const std::vector<sf::Color> squareColors, ColorManager* colorManagerPtr);
            

            sf::Vector2f getSquareSize() const;

            void setPosition(sf::Vector2f);

            void setPositionX(float x);

            void setScale(const float scale);

            unsigned int getImageWidth() const;

            unsigned int getImageHeight() const;

            float getDisplayWidth() const;

            float getDisplayHeight() const;

            bool contains(sf::Vector2i point) const;

            bool isCoordinatesOutside() const;

            bool isWithinPlayerToMoveToken(sf::Vector2i point) const;

            std::optional<Coord> getSquareCoord(sf::Vector2i point);

            void addPiece(const GraphicPiece& piece, const Coord& coord);
            void removePiece(const Coord& coord);

            void movePiece(const Coord& fromCoord, const Coord& toCoord);

            void addSquareHighlight(const int colorId, const Coord& coord);

            void addArrow(const LogicArrow& arrow);
            void removeArrow(const LogicArrow& arrow);

            void updateDragArrow(const Coord& fromCoord, const Coord& toCoord);
            void removeDragArrow();

            void highlightSquare(const Coord& coord);

            void unhighlight();

            

            void saveImage(const std::string& fileName);

            void clear();

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setBigCoordinates();

            void setSmallCoordinates();

            void addBorder();

            void removeBorder();

            void addPlayerToMoveToken();

            void removePlayerToMoveToken();

            void togglePlayerToMoveToken();

        private:

            void initPlayerToMoveToken();

            void initLeftBorder();

            void initRightBorder();

            void initTopBorder();

            void initBottomBorder();

            unsigned int getTextureWidth() const;

            unsigned int getTextureHeight() const;

            void resizeTexture();

            void redrawTexture();

            void setLeftAndBottomEdgeWidth(const unsigned int leftWidth, const unsigned int bottomWidth);
            

            void addOutsideLabels();
            void addInsideLabels();

            void moveSquares(const sf::Vector2f& offset);
            void moveBorder(const sf::Vector2f& offset);
            void moveLeftInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomInsideCoordinateLabels(const sf::Vector2f& offset);
            void moveLeftOutsideCoordinateLabels(const sf::Vector2f& offset);
            void moveBottomOutsideCoordinateLabels(const sf::Vector2f& offset);
            void movePlayerToMoveToken(const sf::Vector2f& offset);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<sf::RenderTexture> m_texturePtr;
            sf::Vector2f m_position;
            float m_scale;

            unsigned int m_leftEdgeWidth;
            unsigned int m_rightEdgeWidth;
            unsigned int m_topEdgeWidth;
            unsigned int m_bottomEdgeWidth;

            std::vector<std::vector<sf::RectangleShape>> m_squares;

            sf::Color m_backgroundColor;

            std::vector<sf::Color> m_squareColors;

            std::map<Coord, sf::RectangleShape> m_squareHighlights;

            std::map<Coord, GraphicPiece> m_pieces;

            std::map<LogicArrow, GraphicArrow> m_arrows;

            std::unique_ptr<Arrow> m_dragArrowPtr;

            std::unique_ptr<sf::RectangleShape> m_selectHighlight;

            ColorManager* m_colorManagerPtr;

            bool m_showLabels;
            bool m_isCoordinateLabelsInside;
            sf::Font m_font;
            std::vector<sf::Text> m_leftOutsideCoordinateLabels;
            std::vector<sf::Text> m_bottomOutsideCoordinateLabels;
            std::vector<sf::Text> m_bottomInsideCoordinateLabels;
            std::vector<sf::Text> m_leftInsideCoordinateLabels;

            bool m_showBorder;
            unsigned int m_borderWidth;
            std::unique_ptr<sf::RectangleShape> m_leftBorder;
            std::unique_ptr<sf::RectangleShape> m_rightBorder;
            std::unique_ptr<sf::RectangleShape> m_topBorder;
            std::unique_ptr<sf::RectangleShape> m_bottomBorder;

            float m_insideLabelSizeFactor;
            float m_outsideLabelSizeFactor;
            float m_outsideLabelBigSizeFactor;
            float m_outsideLabelSmallSizeFactor;

            bool m_showPlayerToMoveToken;
            std::unique_ptr<sf::CircleShape> m_playerToMoveToken;
    };
}