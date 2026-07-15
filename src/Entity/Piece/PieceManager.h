#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "List/Map.h"
#include "List/Vector.h"
#include "Entity/Piece/LogicPiece.h"
#include "Entity/Piece/GraphicPiece.h"
#include "Entity/Piece/PieceColor.h"
#include "Entity/Piece/PieceIdentifier.h"

namespace sigrid{

    struct PieceContainer;

    class PieceManager{

        public:
            PieceManager(const std::vector<PieceColor>& pieceColors);
            void addPieceColor(const PieceColor& newColor);
            void loadImages(const std::vector<PieceContainer>& pieces);
            std::optional<GraphicPiece> getGraphicPiece(const LogicPiece& logicPiece);
        private:
            sigrid_list::Map<PieceIdentifier, std::string> m_pieceImageFilenames;

            sigrid_list::Vector<PieceColor> m_colors;
            sigrid_list::Vector<std::map<PieceIdentifier, GraphicPiece>> m_graphicPieces;
            sigrid_list::Vector<std::map<PieceIdentifier, sf::Texture>> m_pieceTextures;

            sf::Vector2f m_pieceSize;
            
    };

}