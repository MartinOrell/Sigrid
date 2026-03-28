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

namespace sigrid{
    class GraphicBoard: public sf::Drawable{
        public:
            
            GraphicBoard();
            
            void init(const LogicBoard& logicBoard, const BoardDesignContainer& config, PieceManager* const pieceManagerPtr, ColorManager* const tileColorManagerPtr, ColorManager* const arrowColorManagerPtr);

            GraphicBoard& operator=(const GraphicBoard& rhs);

            sf::Vector2f getTileSize() const;

            void setPosition(sf::Vector2f);

            void setPositionX(float x);

            void setScale(const float scale);

            unsigned int getImageWidth() const;

            unsigned int getImageHeight() const;

            float getDisplayWidth() const;

            float getDisplayHeight() const;

            std::optional<GraphicEntity> getEntityAt(const Coord& coord) const;

            bool contains(sf::Vector2i point) const;

            bool isCoordinatesOutside() const;

            bool isWithinPlayerToMoveToken(sf::Vector2i point) const;

            std::optional<Coord> getTileCoord(sf::Vector2i point);

            void addEntity(const Coord& coord, const LogicEntity& logicEntity);
            void removeEntity(const Coord& coord);
            void moveEntity(const Coord& fromCoord, const Coord& toCoord);

            void addTileHighlight(const Coord& coord, const int& highlightColorId);
            void removeTileHighlight(const Coord& coord);

            void addArrow(const CoordPair& coordPair, const LogicArrow& arrow);
            void removeArrow(const CoordPair& coordPair);

            void updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId);
            void removeDragArrow();

            void highlightTile(const Coord& coord);

            void unhighlight();
            

            void saveImage(const std::string& fileName);

            void clear();

            void flip();

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setCoordinateSize(const float& size);

            void addBorder();

            void removeBorder();

            void addPlayerToMoveToken();

            void removePlayerToMoveToken();

            void togglePlayerToMoveToken();

        private:

            std::optional<sf::Vector2f> getTilePosition(const Coord& coord);
            std::optional<sf::Vector2f> getTileCenterPosition(const Coord& coord);

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

            void moveTiles(const sf::Vector2f& offset);
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

            std::vector<std::vector<GraphicTile>> m_tiles;

            sf::Color m_backgroundColor;

            std::unique_ptr<GraphicEntities> m_pieceLayerPtr;

            std::unique_ptr<GraphicArrows> m_arrowLayerPtr;

            std::unique_ptr<GraphicArrow> m_dragArrowPtr;

            std::unique_ptr<GraphicTile> m_selectHighlight;

            ColorManager* m_tileColorManagerPtr;
            ColorManager* m_arrowColorManagerPtr;

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

            bool m_showPlayerToMoveToken;
            std::unique_ptr<sf::CircleShape> m_playerToMoveToken;

            bool m_isLeftToRight;
            bool m_isTopToBottom;
    };
}