#pragma once


#include "Piece.h"
#include <map>
#include <vector>
#include "PieceColor.h"

namespace sigrid{


    class PieceManager{

        public:
            PieceManager(const std::string& pieceColorFilename);
            void addPieceColor(const std::string& name, const bool isLight, const sf::Color& lightModifier, const sf::Color& darkModifier);
            void loadImageFilenames(const std::string& filename);
            std::optional<Piece> getPiece(const LogicPiece& logicPiece = LogicPiece{"P", 0});
        private:
            std::map<std::string, std::string> m_pieceImageFilenames;

            std::map<std::string, unsigned int> m_colorIds;
            std::vector<PieceColor> m_colors;
            std::vector<std::map<std::string, Piece>> m_pieces;
            std::vector<std::map<std::string, sf::Texture>> m_pieceTextures;

            sf::Vector2u m_pieceSize;
            
    };

}