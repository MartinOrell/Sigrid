#pragma once

#include <map>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include "LogicPiece.h"
#include "GraphicPiece.h"
#include "PieceColor.h"
#include "PieceContainer.h"
#include "PieceIdentifier.h"

namespace sigrid{


    class PieceManager{

        public:
            PieceManager(const std::vector<PieceColor>& pieceColors);
            void addPieceColor(const PieceColor& newColor);
            void loadImages(const std::vector<PieceContainer>& pieces);
            std::optional<GraphicPiece> getGraphicPiece(const LogicPiece& logicPiece = LogicPiece{"P", 0});
        private:
            std::map<PieceIdentifier, std::string> m_pieceImageFilenames;

            std::vector<PieceColor> m_colors;
            std::vector<std::map<PieceIdentifier, GraphicPiece>> m_graphicPieces;
            std::vector<std::map<PieceIdentifier, sf::Texture>> m_pieceTextures;

            sf::Vector2u m_pieceSize;
            
    };

}