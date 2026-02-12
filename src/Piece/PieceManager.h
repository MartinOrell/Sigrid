#pragma once


#include "Piece.h"
#include <map>
#include <vector>
#include "PieceColor.h"
#include "PieceContainer.h"
#include "PieceIdentifier.h"

namespace sigrid{


    class PieceManager{

        public:
            PieceManager(const std::vector<PieceColor>& pieceColors);
            void addPieceColor(const PieceColor& newColor);
            void loadImages(const std::vector<PieceContainer>& pieces);
            std::optional<Piece> getPiece(const LogicPiece& logicPiece = LogicPiece{"P", 0});
        private:
            std::map<PieceIdentifier, std::string> m_pieceImageFilenames;

            std::vector<PieceColor> m_colors;
            std::vector<std::map<PieceIdentifier, Piece>> m_pieces;
            std::vector<std::map<PieceIdentifier, sf::Texture>> m_pieceTextures;

            sf::Vector2u m_pieceSize;
            
    };

}