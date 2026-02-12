#include "PieceManager.h"

#include <fstream>
#include <iostream>
#include <cctype>

using namespace sigrid;

PieceManager::PieceManager(const std::vector<PieceColor>& pieceColors)
: m_pieceSize{108,108}{

    for(const auto& color: pieceColors){
        addPieceColor(color);
    }
}

void PieceManager::addPieceColor(const PieceColor& newColor){
    m_colors.push_back(newColor);
    std::map<PieceIdentifier, Piece> coloredPieces;
    m_pieces.push_back(coloredPieces);
    std::map<PieceIdentifier, sf::Texture> pieceColorTextures;
    m_pieceTextures.push_back(pieceColorTextures);
}


void PieceManager::loadImages(const std::vector<PieceContainer>& pieces){

    for(const auto& piece : pieces){
        PieceIdentifier id;
        id.name = piece.name;
        id.style = piece.style;
        m_pieceImageFilenames.insert({id, piece.filename});
    }
}

// Get the piece matching the value of the logicPiece
// If the piece does not exist, create it together with its texture
std::optional<Piece> PieceManager::getPiece(const LogicPiece& logicPiece){

    int colorId = logicPiece.colorId();

    if(colorId >= m_pieces.size()){
        return std::nullopt;
    }

    PieceIdentifier id;
    id.name = logicPiece.notation();
    if(m_colors.at(colorId).isLight){
        id.style = "light";
    }
    else{
        id.style = "dark";
    }

    {
        auto it = m_pieces.at(colorId).find(id);

        if(it != m_pieces.at(colorId).end()){
            return m_pieces.at(colorId).at(id);
        }
    }

    {
        auto it = m_pieceImageFilenames.find(id);
        if(it == m_pieceImageFilenames.end()){
            return std::nullopt;
        }

        sf::Image newImage{it->second};

        sf::Color lightModifier = sf::Color(m_colors.at(colorId).lightModifier);
        sf::Color darkModifier = sf::Color(m_colors.at(colorId).darkModifier);

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
        m_pieceTextures.at(colorId).insert(std::pair{id, newTexture});

        m_pieces.at(colorId).insert({id, Piece{m_pieceSize, &(m_pieceTextures.at(colorId).at(id)), colorId, id.name}});
    }

    return m_pieces.at(colorId).at(id);
}