#include "Entity/Piece/PieceManager.h"

#include <SFML/Graphics/Image.hpp>

#include "Entity/Piece/PieceContainer.h"

using namespace sigrid;

void PieceManager::setPieceColors(const std::vector<PieceColor>& pieceColors){

    for(const auto& color: pieceColors){
        addPieceColor(color);
    }
}

void PieceManager::addPieceColor(const PieceColor& newColor){
    m_colors.push_back(newColor);
    std::map<PieceIdentifier, GraphicPiece> coloredPieces;
    m_graphicPieces.push_back(coloredPieces);
    std::map<PieceIdentifier, sf::Texture> pieceColorTextures;
    m_pieceTextures.push_back(pieceColorTextures);
}


void PieceManager::loadImages(const std::vector<PieceContainer>& pieces){

    for(const auto& piece : pieces){
        PieceIdentifier id;
        id.name = piece.name;
        id.style = piece.style;
        m_pieceImageFilenames.insert(id, piece.filename);
    }
}

// Get the piece matching the value of the logicPiece
// If the piece does not exist, create it together with its texture
std::optional<GraphicPiece> PieceManager::getGraphicPiece(const LogicPiece& logicPiece){

    int colorId = logicPiece.getColorId();

    auto color_o = m_colors.at(colorId);
    if(color_o == std::nullopt){
        return std::nullopt;
    }

    auto graphicPieces_o = m_graphicPieces.at(colorId);
    if(graphicPieces_o == std::nullopt){
        return std::nullopt;
    }

    PieceIdentifier id;
    id.name = logicPiece.getNotation();

    const auto& color = color_o.value().get();
    if(color.isLight){
        id.style = "light";
    }
    else{
        id.style = "dark";
    }

    auto& graphicPieces = graphicPieces_o.value().get();    
    {
        auto it = graphicPieces.find(id);

        if(it != graphicPieces.end()){
            return graphicPieces.at(id);
        }
    }

    {
        auto pieceImageFileName_o = m_pieceImageFilenames.at(id);
        if(pieceImageFileName_o == std::nullopt){
            return std::nullopt;
        }
        auto& pieceImageFileName = pieceImageFileName_o.value().get();

        sf::Image newImage{pieceImageFileName};

        sf::Color lightModifier = sf::Color(color.lightModifier);
        sf::Color darkModifier = sf::Color(color.darkModifier);

        for(unsigned int x = 0; x < newImage.getSize().x; x++){
            for(unsigned int y = 0; y < newImage.getSize().y; y++){
                sf::Color color = newImage.getPixel({x,y});
                color.r = (color.r * lightModifier.r) / 255;
                color.g = (color.g * lightModifier.g) / 255;
                color.b = (color.b * lightModifier.b) / 255;

                color.r = color.r + (darkModifier.r * (255-color.r)) / 255;
                color.g = color.g + (darkModifier.g * (255-color.g)) / 255;
                color.b = color.b + (darkModifier.b * (255-color.b)) / 255;

                newImage.setPixel({x,y},color);
            }
        }

        sf::Texture newTexture{newImage};
        auto pieceTexture_o = m_pieceTextures.at(colorId);
        if(pieceTexture_o == std::nullopt){
            return std::nullopt;
        }
        auto& pieceTextures = pieceTexture_o.value().get();

        pieceTextures.insert(std::pair{id, newTexture});
        GraphicPiece newPiece;
        newPiece.setSize(m_pieceSize);
        newPiece.setTexturePtr(&(pieceTextures.at(id)));
        graphicPieces.insert({id, std::move(newPiece)});
    }

    return graphicPieces.at(id);
}