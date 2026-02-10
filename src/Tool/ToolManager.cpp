#include "ToolManager.h"

#include "../Arrow/GraphicArrow.h"

#include <iostream>

using namespace sigrid;

ToolManager::ToolManager(ColorManager* colorManagerPtr)
: m_colorManagerPtr{colorManagerPtr}{
    sf::Texture selectTexture{"res/icons/select_object.png"};
    m_toolTextures.insert({ToolSelection::Select, selectTexture});
}

std::optional<sf::Texture*> ToolManager::getTexturePtr(const ToolSelection& selection){
    auto it = m_toolTextures.find(selection);
    
    if(it == m_toolTextures.end()){
        return std::nullopt;
    }

    return &(m_toolTextures.at(selection));
}

std::optional<sf::Texture*> ToolManager::getArrowTexturePtr(const int colorId){

    auto it = m_arrowTextures.find(colorId);

    if(it != m_arrowTextures.end()){
        return &(m_arrowTextures.at(colorId));
    }

    unsigned int squareWidth(70);
    unsigned int squareHeight(70);

    sf::Color arrowColor = m_colorManagerPtr->getSolidColor(colorId);

    if(m_graphicArrowPtr == nullptr){

        sf::Vector2f arrowFrom;
        arrowFrom.x = (float)squareWidth/2.f;
        arrowFrom.y = (float)squareHeight*0.9f;
        sf::Vector2f arrowTo;
        arrowTo.x = (float)squareWidth/2.f;
        arrowTo.y = (float)squareHeight*0.1f;

        

        m_graphicArrowPtr = std::make_unique<GraphicArrow>(arrowFrom, arrowTo, arrowColor);
    }
    else{
        m_graphicArrowPtr->setColor(arrowColor);
    }

    sf::RenderTexture arrowRenderTexture{{squareWidth,squareHeight}};
    arrowRenderTexture.clear(sf::Color::Transparent);
    arrowRenderTexture.draw(*m_graphicArrowPtr);
    arrowRenderTexture.display();

    sf::Texture arrowTexture = arrowRenderTexture.getTexture();

    m_arrowTextures.insert({colorId, arrowTexture});
    return &(m_arrowTextures.at(colorId));
}