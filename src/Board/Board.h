#pragma once

#include "../Piece/Piece.h"
#include "GraphicBoard.h"
#include "LogicBoard.h"
#include "../Piece/LogicPiece.h"
#include "../Piece/GraphicPiece.h"
#include "Coord.h"
#include "../Piece/PieceManager.h"
#include "../Tool/Tool.h"

#include <SFML/Window/Event.hpp>

#include "../Arrow/LogicArrow.h"

#include "../Arrow/GraphicArrow.h"

namespace sigrid{
    class Board: public sf::Drawable{
        public:            

            Board(std::string boardFilename, const GraphicBoardConfigContainer& graphicData, const std::vector<uint32_t>& squareColors, PieceManager* pieceManagerPtr, ColorManager* colorManagerPtr);


            void setPosition(sf::Vector2f);

            void setPositionX(const float x);

            void setScale(const float scale);

            unsigned int getNumColumns() const;

            unsigned int getImageWidth() const;

            unsigned int getImageHeight() const;

            float getDisplayWidth() const;

            float getDisplayHeight() const;

            bool contains(sf::Vector2i point) const;

            bool isEmptySquare(const Coord& coord) const;

            bool isCoordinatesOutside() const;

            bool isWithinPlayerToMoveToken(sf::Vector2i point) const;

            std::optional<Coord> getSquareCoord(sf::Vector2i point);

            std::optional<Piece> getPiece(const Coord& coord);

            void select(const Coord& coord);

            void keyPressed(sf::Event::KeyPressed);
            void textEntered(std::string text);

            void deselect();

            void addPiece(const Piece& piece, const Coord& coord);
            void movePiece(const Coord& fromCoord, const Coord& toCoord);

            void addArrow(const int colorId, const Coord& fromCoord, const Coord& toCoord);

            void addSquareHighlight(const int colorId, const Coord& coord);

            void updateDragArrow(const Coord& fromCoord, const Coord& toCoord);
            void removeDragArrow();

            void loadFENPiecePlacement(std::string);

            void saveLogic();
            void saveImage(const std::string& filename);

            void clear();
            void print();

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

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<LogicBoard> m_logicBoard;

            std::unique_ptr<GraphicBoard> m_graphicBoard;

            std::unique_ptr<Coord> m_selection;
            PieceManager* m_pieceManagerPtr;
    };
}