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
    std::map<std::string, Piece> coloredPieces;
    m_pieces.push_back(coloredPieces);
    std::map<std::string, sf::Texture> pieceColorTextures;
    m_pieceTextures.push_back(pieceColorTextures);
}


void PieceManager::loadImages(const std::vector<PieceContainer>& pieces){

    for(const auto& piece : pieces){
        std::string notation = piece.name;
        if(piece.style == "light"){
            notation = toupper(notation.at(0));
        }
        else{
            notation = tolower(notation.at(0));
        }
        m_pieceImageFilenames.insert({notation, piece.filename});
    }
}

// Get the piece matching the value of the logicPiece
// If the piece does not exist, create it together with its texture
std::optional<Piece> PieceManager::getPiece(const LogicPiece& logicPiece){

    int colorId = logicPiece.colorId();

    if(colorId >= m_pieces.size()){
        return std::nullopt;
    }

    std::string notation = logicPiece.notation();

    if(m_colors.at(colorId).isLight){
        for(int i = 0; i < notation.size(); i++){
            notation.at(i) = toupper(notation.at(i));
        }
    }
    else{
        for(int i = 0; i < notation.size(); i++){
            notation.at(i) = tolower(notation.at(i));
        }
    }

    {
        auto it = m_pieces.at(colorId).find(notation);

        if(it != m_pieces.at(colorId).end()){
            return m_pieces.at(colorId).at(notation);
        }
    }

    {
        auto it = m_pieceImageFilenames.find(notation);
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
        m_pieceTextures.at(colorId).insert(std::pair{notation, newTexture});

        m_pieces.at(colorId).insert({notation, Piece{m_pieceSize, &(m_pieceTextures.at(colorId).at(notation)), colorId, notation}});
    }

    return m_pieces.at(colorId).at(notation);
}