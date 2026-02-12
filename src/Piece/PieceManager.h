#pragma once


#include "Piece.h"
#include <map>
#include <vector>
#include "PieceColor.h"
#include "PieceContainer.h"

namespace sigrid{


    class PieceManager{

        public:
            PieceManager(const std::vector<PieceColor>& pieceColors);
            void addPieceColor(const PieceColor& newColor);
            void loadImages(const std::vector<PieceContainer>& pieces);
            std::optional<Piece> getPiece(const LogicPiece& logicPiece = LogicPiece{"P", 0});
        private:
            std::map<std::string, std::string> m_pieceImageFilenames;

            std::vector<PieceColor> m_colors;
            std::vector<std::map<std::string, Piece>> m_pieces;
            std::vector<std::map<std::string, sf::Texture>> m_pieceTextures;

            sf::Vector2u m_pieceSize;
            
    };

}