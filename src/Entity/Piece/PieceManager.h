#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "../../List/SigridMap.h"
#include "../../List/SigridVector.h"
#include "LogicPiece.h"
#include "GraphicPiece.h"
#include "PieceColor.h"
#include "PieceIdentifier.h"

namespace sigrid{

    struct PieceContainer;

    class PieceManager{

        public:
            PieceManager(const std::vector<PieceColor>& pieceColors);
            void addPieceColor(const PieceColor& newColor);
            void loadImages(const std::vector<PieceContainer>& pieces);
            std::optional<GraphicPiece> getGraphicPiece(const LogicPiece& logicPiece);
        private:
            SigridMap<PieceIdentifier, std::string> m_pieceImageFilenames;

            SigridVector<PieceColor> m_colors;
            SigridVector<std::map<PieceIdentifier, GraphicPiece>> m_graphicPieces;
            SigridVector<std::map<PieceIdentifier, sf::Texture>> m_pieceTextures;

            sf::Vector2u m_pieceSize;
            
    };

}