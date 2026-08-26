#include "sigrid/Entity/Piece/PieceManager.h"

#include <iostream>

#include "sigrid/utilities/Image/Image.h"

#include "sigrid/Entity/Piece/PieceContainer.h"

void sigrid::PieceManager::setPieceColors(const sigrid_list::Vector<PieceColor>& pieceColors){

    for(const auto& color: pieceColors){
        addPieceColor(color);
    }
}

sigrid_list::Vector<sigrid::PieceColor> sigrid::PieceManager::getContainer() const{

    sigrid_list::Vector<PieceColor> containers;
    for(auto& color: m_colors){
        PieceColor container = color;
        container.darkModifier = color.darkModifier;
        container.lightModifier = color.lightModifier;
        containers.push_back(container);
    }
    return containers;
}

void sigrid::PieceManager::addPieceColor(const PieceColor& newColor){
    m_colors.push_back(newColor);
    std::map<PieceIdentifier, GraphicPiece> coloredPieces;
    m_graphicPieces.push_back(coloredPieces);
    std::map<PieceIdentifier, sf::Texture> pieceColorTextures;
    m_pieceTextures.push_back(pieceColorTextures);
}


void sigrid::PieceManager::loadImages(const sigrid_list::Vector<PieceContainer>& pieces){

    for(const auto& piece : pieces){
        PieceIdentifier id;
        id.name = piece.name;
        id.style = piece.style;
        m_pieceImageFilenames.insert(id, piece.filename);
    }
}

sigrid_list::Vector<sigrid::PieceContainer> sigrid::PieceManager::getPieceContainer() const{

    sigrid_list::Vector<PieceContainer> containers;
    for(const auto& piece: m_pieceImageFilenames){
        PieceContainer container;
        container.name = piece.first.name;
        container.style = piece.first.style;
        container.filename = piece.second;
        containers.push_back(container);
    }
    return containers;
}

// Get the piece matching the value of the logicPiece
// If the piece does not exist, create it together with its texture
std::optional<sigrid::GraphicPiece> sigrid::PieceManager::getGraphicPiece(const LogicPiece& logicPiece){

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
        auto pieceImageFilename_o = m_pieceImageFilenames.at(id);
        if(pieceImageFilename_o == std::nullopt){
            return std::nullopt;
        }
        auto& pieceImageFilename = pieceImageFilename_o.value().get();

        sigrid::Image newImage;
        if(!newImage.loadFromFile(pieceImageFilename)){
            std::cerr << "PieceManager: Failed to load from file \""
                << pieceImageFilename << "\"."
                << " Failed to get GraphicPiece" << std::endl;
            return std::nullopt;
        }

        sf::Color lightModifier = color.lightModifier.getSfColor();
        sf::Color darkModifier = color.darkModifier.getSfColor();

        newImage.modifyColor(lightModifier, darkModifier);

        sf::Texture newTexture{newImage.getSfImage()};
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