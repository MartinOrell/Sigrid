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

    sf::Color color = m_colorManagerPtr->getSolidColor(colorId);

    if(m_graphicArrowPtr == nullptr){

        sf::Vector2f from;
        from.x = (float)squareWidth/2.f;
        from.y = (float)squareHeight*0.9f;
        sf::Vector2f to;
        to.x = (float)squareWidth/2.f;
        to.y = (float)squareHeight*0.1f;

        m_graphicArrowPtr = std::make_unique<GraphicArrow>(from, to, color, 5.f, 15.f);
    }
    else{
        m_graphicArrowPtr->setColor(color);
    }

    sf::RenderTexture renderTexture{{squareWidth,squareHeight}};
    renderTexture.clear(sf::Color::Transparent);
    renderTexture.draw(*m_graphicArrowPtr);
    renderTexture.display();

    sf::Texture texture = renderTexture.getTexture();

    m_arrowTextures.insert({colorId, texture});
    return &(m_arrowTextures.at(colorId));
}

std::optional<sf::Texture*> ToolManager::getCircleTexturePtr(const int colorId){

    auto it = m_circleTextures.find(colorId);

    if(it != m_circleTextures.end()){
        return &(m_circleTextures.at(colorId));
    }

    unsigned int squareWidth(70);
    unsigned int squareHeight(70);

    sf::Color color = m_colorManagerPtr->getSolidColor(colorId);

    if(m_graphicCirclePtr == nullptr){

        sf::Vector2f position;
        position.x = (float)squareWidth/2.f;
        position.y = (float)squareHeight/2.f;
        float diameter = squareWidth*0.4f;

        m_graphicCirclePtr = std::make_unique<GraphicCircle>(color, diameter);
        m_graphicCirclePtr->setPosition(position);
    }
    else{
        m_graphicCirclePtr->setColor(color);
    }

    sf::RenderTexture renderTexture{{squareWidth,squareHeight}};
    renderTexture.clear(sf::Color::Transparent);
    renderTexture.draw(*m_graphicCirclePtr);
    renderTexture.display();

    sf::Texture texture = renderTexture.getTexture();

    m_circleTextures.insert({colorId, texture});
    return &(m_circleTextures.at(colorId));
}