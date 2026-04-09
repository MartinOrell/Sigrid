#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Entity/Piece/LogicPiece.h"
#include "LogicBoard.h"
#include "../Entity/Piece/PieceManager.h"

#include <vector>
#include <map>
#include <optional>
#include <memory>
#include "../Coord/Coord.h"
#include "../Coord/CoordPair.h"

#include "../Entity/Shape/Arrow/LogicArrow.h"
#include "../Entity/Shape/Arrow/GraphicArrow.h"

#include "../Color/ColorManager.h"

#include "BoardDesignContainer.h"

#include "../Entity/Shape/Circle/LogicCircle.h"
#include "../Entity/Shape/Circle/GraphicCircle.h"

#include "../Entity/GraphicEntities.h"
#include "../Entity/Shape/Arrow/GraphicArrows.h"

#include "../Entity/Tile/GraphicTile.h"
#include "../Entity/Tile/GraphicTiles.h"

#include "../Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "../Entity/TurnToken/TurnToken.h"

#include "../Font/FontManager.h"
#include "BoardLabels.h"

namespace sigrid{
    class GraphicBoard: public sf::Drawable{
        public:
            
            GraphicBoard();
            
            void init(const LogicBoard& logicBoard, const BoardDesignContainer& config, PieceManager* const pieceManagerPtr, ColorManager* const tileColorManagerPtr, ColorManager* const arrowColorManagerPtr, FontManager* const fontManagerPtr);

            GraphicBoard& operator=(const GraphicBoard& rhs);

            sf::Vector2f getTileSize() const;

            void setPosition(const sf::Vector2f& position);

            void setPositionX(float x);

            void setScale(const float scale);

            unsigned int getImageWidth() const;

            unsigned int getImageHeight() const;

            float getDisplayWidth() const;

            float getDisplayHeight() const;

            std::optional<GraphicEntity> getEntityAt(const Coord& coord) const;

            bool contains(const sf::Vector2f& point) const;

            bool isLeftToRight() const;

            bool isCoordinatesOutside() const;

            bool isWithinTurnToken(const sf::Vector2f& point) const;

            std::optional<Coord> getTileCoord(const sf::Vector2f& point);

            void addEntity(const Coord& coord, const LogicEntity& logicEntity);
            void removeEntity(const Coord& coord);
            void moveEntity(const Coord& fromCoord, const Coord& toCoord);

            void addTileHighlight(const Coord& coord, const int& colorId);
            void removeTileHighlight(const Coord& coord);

            void addArrow(const CoordPair& coordPair, const LogicArrow& arrow);
            void removeArrow(const CoordPair& coordPair);

            void updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId);
            void removeDragArrow();

            void highlightTile(const Coord& coord);

            void unhighlight();
            

            void saveImage(const std::string& fileName);

            void clearEntities();
            void clearArrows();

            void addSquareColumnRight(const std::vector<int>& repeatTileColorIds);
            void addSquareColumnLeft(const std::vector<int>& repeatTileColorIds);
            void removeSquareColumnRight();
            void removeSquareColumnLeft();

            void flip();

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setCoordinateSize(const float& size);

            void addBorder();

            void removeBorder();

            void addTurnToken(const int& turnToMove);

            void removeTurnToken();

            void setTurnToMove(const int& turnToMove);

        private:

            void initTurnToken(const int& turnToMove);

            unsigned int getTextureWidth() const;

            unsigned int getTextureHeight() const;

            void resizeTexture();

            void redrawTexture();

            void setLeftAndBottomEdgeWidth(const unsigned int leftWidth, const unsigned int bottomWidth);

            void addOutsideLabels();
            void addInsideLabels();

            void moveTiles(const sf::Vector2f& offset);
            void moveTurnToken(const sf::Vector2f& offset);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<sf::RenderTexture> m_texturePtr;
            sf::Vector2f m_position;
            float m_scale;

            unsigned int m_leftEdgeWidth;
            unsigned int m_rightEdgeWidth;
            unsigned int m_topEdgeWidth;
            unsigned int m_bottomEdgeWidth;

            sf::Color m_backgroundColor;

            std::unique_ptr<RectangleBorder> m_borderPtr;

            std::unique_ptr<BoardLabels> m_labelsPtr;

            std::unique_ptr<TurnToken> m_turnTokenPtr;

            std::unique_ptr<GraphicTiles> m_tileLayerPtr;

            std::unique_ptr<GraphicEntities> m_pieceLayerPtr;

            std::unique_ptr<GraphicArrows> m_arrowLayerPtr;

            std::unique_ptr<GraphicArrow> m_dragArrowPtr;

            std::unique_ptr<GraphicTile> m_selectHighlight;

            ColorManager* m_arrowColorManagerPtr;

            unsigned int m_borderWidth;

            bool m_isLeftToRight;
            bool m_isTopToBottom;
    };
}