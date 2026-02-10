#include "PieceManager.h"

#include <fstream>
#include <iostream>
#include <cctype>

using namespace sigrid;

PieceManager::PieceManager(const std::string& pieceColorFilename)
: m_pieceSize{108,108}{

    std::ifstream ifs(pieceColorFilename);

    assert(ifs.is_open());

    std::string colorName;
    std::string type; //light or dark
    uint32_t lightColorModifierHex;
    uint32_t darkColorModifierHex;

    while(ifs.peek() != EOF){
        ifs >> colorName >> type >> std::hex >> lightColorModifierHex >> darkColorModifierHex >> std::ws;
        lightColorModifierHex = lightColorModifierHex * 0x100 + 0xff;
        darkColorModifierHex = darkColorModifierHex * 0x100 + 0xff;
        bool isLight = type == "light";
        addPieceColor(colorName, isLight, sf::Color(lightColorModifierHex), sf::Color(darkColorModifierHex));
    }
}

void PieceManager::addPieceColor(const std::string& name, const bool isLight, const sf::Color& lightModifier, const sf::Color& darkModifier){
    PieceColor newColor;
    newColor.isLight = isLight;
    newColor.lightModifier = lightModifier;
    newColor.darkModifier = darkModifier;
    unsigned int id = m_colors.size();
    m_colors.push_back(newColor);
    m_colorIds.insert({name, id});
    std::map<std::string, Piece> coloredPieces;
    m_pieces.push_back(coloredPieces);
    std::map<std::string, sf::Texture> pieceColorTextures;
    m_pieceTextures.push_back(pieceColorTextures);
}


void PieceManager::loadImageFilenames(const std::string& filename){
    std::ifstream ifs(filename);

    assert(ifs.is_open());

    while(ifs.peek() != EOF){
        std::string notation;
        std::string filename;
        ifs >> notation >> filename >> std::ws;

        m_pieceImageFilenames.insert({notation, filename});
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

        sf::Color lightModifier = m_colors.at(colorId).lightModifier;
        sf::Color darkModifier = m_colors.at(colorId).darkModifier;

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