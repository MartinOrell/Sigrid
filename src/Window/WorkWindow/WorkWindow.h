#pragma once

#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Board/Board.h"
#include "../../Tool/Tool.h"

#include "../../Action/Action.h"

namespace sigrid{
    class WorkWindow: public sf::Drawable{
        public:
            WorkWindow();

            void init(const std::string& boardFilename, const std::string& defaultBoardImageFilename, const BoardDataContainer& boardData, const BoardDesignContainer& graphicData, ColorManager* const tileColorManagerPtr, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr);

            void createGraphic(const sf::Vector2u& size);

            void loadFen(const std::string& fen);

            std::string getFen() const;
            
            void setPosition(const sf::Vector2f& position);

            unsigned int getNumColumns() const;

            bool contains(const sf::Vector2i& point) const;

            bool isCoordinatesOutside() const;

            Action clicked(const sigrid::Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& releasePosition);
            void dragMouse(const Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& currentPosition);
            
            void keyPressed(const sf::Event::KeyPressed& event);
            void textEntered(const std::string& text);

            void reset();

            void clear();

            void print();

            void newBoard();

            void saveBoard();

            void flipBoard();

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setCoordinateSize(const float& size);

            void addBoardBorder();

            void removeBoardBorder();

            void addPlayerToMoveToken();

            void removePlayerToMoveToken();

        private:

            std::string getUniqueName(const std::string& name);

            void useAddEntityTool(const Coord& coord, const LogicEntity& newEntity);
            void useAddTileHighlightTool(const Coord& coord, const int& colorId);
            void useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;
            std::vector<std::unique_ptr<sigrid::Board>> m_boardPtrs;
            int m_activeBoardId;

            sf::Color m_backgroundColor;

            PieceManager* m_pieceManagerPtr;
    };
}