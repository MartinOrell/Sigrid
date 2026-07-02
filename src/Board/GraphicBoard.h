#pragma once

#include <memory>
#include <optional>

#include "../Coord/Coord.h"

#include "../Entity/Shape/RectangleBorder/RectangleBorder.h"

#include "../Entity/LogicEntity.h"
#include "../Entity/GraphicEntity.h"

#include "../Entity/Shape/Arrow/LogicArrow.h"
#include "../Entity/Shape/Arrow/GraphicArrow.h"

#include "../Font/FontManager.h"

#include "../SigridRenderTexture/SigridRenderTexture.h"

namespace sigrid{

    class LogicBoard;
    class BoardDesignContainer;
    class PieceManager;
    class ColorManager;
    class IconManager;
    
    class CoordPair;

    class GraphicTile;
    class GraphicTiles;
    class GraphicEntities;
    class GraphicArrows;
    
    class BoardLabels;
    class TurnToken;    

    class GraphicBoard: public sf::Drawable{
        public:
            
            GraphicBoard();
            
            void setPieceManagerPtr(PieceManager* const managerPtr);
            void setTileColorManagerPtr(ColorManager* const managerPtr);
            void setArrowColorManagerPtr(ColorManager* const managerPtr);
            void setFontManagerPtr(FontManager* const managerPtr);
            void setIconManagerPtr(IconManager* const managerPtr);
            void setLeftToRight();
            void setRightToLeft();
            void setTopToBottom();
            void setBottomToTop();

            void load(const LogicBoard& logicBoard);

            void init(const LogicBoard& logicBoard, const BoardDesignContainer& config);

            GraphicBoard& operator=(const GraphicBoard& rhs);

            sf::Vector2f getTileSize() const;

            void setPosition(const sf::Vector2f& position);

            void setPositionX(float x);

            void setScale(const float scale);

            float getImageWidth() const;

            float getImageHeight() const;

            sf::Image getImage(const unsigned int maxWidth, const unsigned int maxHeight) const;

            const sf::Vector2f& getTopLeftPosition() const;

            sf::Vector2f getDisplaySize() const;
            float getDisplayWidth() const;
            float getDisplayHeight() const;

            bool contains(const sf::Vector2f& point) const;

            bool isLeftToRight() const;

            bool isTopToBottom() const;

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

            void addTileColumnRight(const std::vector<int>& repeatTileColorIds);
            void addTileColumnLeft(const std::vector<int>& repeatTileColorIds);
            void removeRightTileColumn();
            void removeLeftTileColumn();

            void addTileRowUp(const std::vector<int>& repeatTileColorIds);
            void addTileRowDown(const std::vector<int>& repeatTileColorIds);
            void removeTopTileRow();
            void removeBottomTileRow();

            void flip();

            void addLeftInsideLabels();
            void addBottomInsideLabels();
            void addLeftOutsideLabels();
            void addRightOutsideLabels();
            void addTopOutsideLabels();
            void addBottomOutsideLabels();

            void removeLeftInsideLabels();
            void removeBottomInsideLabels();
            void removeLeftOutsideLabels();
            void removeRightOutsideLabels();
            void removeTopOutsideLabels();
            void removeBottomOutsideLabels();

            void setCoordinateSize(const float& size);

            void addBorder();

            void removeBorder();

            void addTurnToken(const int& turnToMove);

            void removeTurnToken();

            void setTurnToMove(const int& turnToMove);

        private:

            void initTurnToken(const int& turnToMove);

            const sf::Color& getBackgroundColor() const;
            sf::Vector2f getTextureSize() const;
            const float& getScale() const;

            float calcTextureWidth() const;
            float calcTextureHeight() const;
            sf::Vector2f calcTextureSize() const;

            void resizeTexture();

            void redrawTexture();

            void updateLeftEdgeWidth();
            void updateRightEdgeWidth();
            void updateTopEdgeWidth();
            void updateBottomEdgeWidth();

            void addLeftInsideLabel_h(const int& row);
            void addLeftInsideLabels_h();
            void addBottomInsideLabel_h(const int& column);
            void addBottomInsideLabels_h();
            void addLeftOutsideLabel_h(const int& row);
            void addLeftOutsideLabels_h();
            void addRightOutsideLabel_h(const int& row);
            void addRightOutsideLabels_h();
            void addTopOutsideLabel_h(const int& column);
            void addTopOutsideLabels_h();
            void addBottomOutsideLabel_h(const int& column);
            void addBottomOutsideLabels_h();

            void moveTiles(const sf::Vector2f& offset);
            void moveTurnToken(const sf::Vector2f& offset);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            SigridRenderTexture m_texture;

            float m_leftEdgeWidth;
            float m_rightEdgeWidth;
            float m_topEdgeWidth;
            float m_bottomEdgeWidth;

            std::optional<RectangleBorder> m_border_o;

            std::unique_ptr<BoardLabels> m_labelsPtr;

            std::unique_ptr<TurnToken> m_turnTokenPtr;

            std::unique_ptr<GraphicTiles> m_tileLayerPtr;

            std::unique_ptr<GraphicEntities> m_pieceLayerPtr;

            std::unique_ptr<GraphicArrows> m_arrowLayerPtr;

            std::unique_ptr<GraphicArrow> m_dragArrowPtr;

            std::unique_ptr<GraphicTile> m_selectHighlight;

            ColorManager* m_arrowColorManagerPtr = nullptr;

            unsigned int m_borderThickness;

            bool m_isLeftToRight;
            bool m_isTopToBottom;
    };
}