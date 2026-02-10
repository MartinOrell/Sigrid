#pragma once

#include "GraphicPiece.h"
#include "LogicPiece.h"

namespace sigrid{
    class Piece: public sf::Drawable{
        public:
            Piece(sf::Vector2u size, const sf::Texture* texturePtr, const int colorId, std::string notation);
            void setPosition(sf::Vector2f);
            bool contains(sf::Vector2i point) const;

            const LogicPiece& logic() const;
            const GraphicPiece& graphic() const;
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            LogicPiece m_logicPiece;
            GraphicPiece m_graphicPiece;
    };
}