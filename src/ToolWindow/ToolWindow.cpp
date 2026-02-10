#include "ToolWindow.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;

ToolWindow::ToolWindow(ToolManager* toolManagerPtr)
: m_toolManagerPtr(toolManagerPtr)
, m_show{true}
, m_backgroundColor{255,255,255,0}{

    bool loadFont = m_font.openFromFile("res/fonts/calibri.ttf");
    assert(loadFont);

    auto leftClickItem = std::make_unique<ToolItem>(ActionType::None());

    auto texturePtr_o = m_toolManagerPtr->getTexturePtr(ToolSelection::Select);
    if(texturePtr_o != std::nullopt){
        leftClickItem->setTexture(texturePtr_o.value());
    }

    m_items.push_back(std::move(leftClickItem));
}

void ToolWindow::createGraphic(const sf::Vector2u& size){
    m_texture = std::make_unique<sf::RenderTexture>(size);
    m_texture->clear(m_backgroundColor);
    m_itemOffsetX = 5.f;

    float itemWidth = (float)size.y;
    float itemHeight = (float)size.y;

    for(int i = 0; i < m_items.size(); i++){
        m_items.at(i)->setSize({itemWidth, itemHeight});

        float posX;
        if(i == 0){
            posX = m_itemOffsetX;
        }
        else{
            posX = m_items.at(i-1)->getPositionRight() + m_itemOffsetX;
        }
        m_items.at(i)->setPosition({posX, 0.f});

        m_texture->draw(*m_items.at(i));
    }
}

void ToolWindow::setPosition(sf::Vector2f position){
    m_position = position;
}

void ToolWindow::setItemTexture(const unsigned int id, const sf::Texture* texturePtr, bool resetRect){
    m_items.at(id)->setTexture(texturePtr,resetRect);
}

bool ToolWindow::isHidden() const{
    return !m_show;
}

bool ToolWindow::contains(sf::Vector2i point) const{
    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}



Action ToolWindow::clicked(const sigrid::Tool& tool, const sf::Vector2i& position){

    std::optional<int> o_itemId = getToolItemId(position);
    if(o_itemId == std::nullopt){
        return ActionType::None();
    }

    return m_items.at(o_itemId.value())->getAction();
}


void ToolWindow::setSetPieceTool(const Piece& piece){
    m_items.at(0)->setTexture(piece.graphic().getTexturePtr());
    redrawTexture();
}

void ToolWindow::setSelectTool(const sf::Mouse::Button button, const ToolSelection selection){

    auto texturePtr_o = m_toolManagerPtr->getTexturePtr(selection);
    if(texturePtr_o != std::nullopt){
        m_items.at(0)->setTexture(texturePtr_o.value());
        redrawTexture();
        return;
    }

    if(selection == ToolSelection::Select){
        std::cout << "Toolwindow: Failed to load toolSelection texture" << std::endl;
    }
    else if(selection == ToolSelection::DrawArrow){
        std::cout << "ToolWindow: Failed to load arrow texture" << std::endl;
    }
    else{
        std::cout << "ToolWindow: Failed to load texture for tool" << std::endl;
    }
}

void ToolWindow::setAddArrowTool(const int colorId){
    auto texturePtr_o = m_toolManagerPtr->getArrowTexturePtr(colorId);

    if(texturePtr_o == std::nullopt){
        std::cout << "ToolWindow: Failed to load arrow texture" << std::endl;
        return;
    }

    m_items.at(0)->setTexture(texturePtr_o.value());
    redrawTexture();
}

void ToolWindow::show(){
    m_show = true;
}

void ToolWindow::hide(){
    m_show = false;
}

void ToolWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    if(!m_texture || !m_show){
        return;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    target.draw(sprite);
}

void ToolWindow::redrawTexture(){
    if(!m_texture){
        return;
    }

    m_texture->clear(m_backgroundColor);
    for(auto& itemPtr : m_items){
        m_texture->draw(*itemPtr);
    }
}

std::optional<int> ToolWindow::getToolItemId(sf::Vector2i point){
    int i{0};
    for(const auto& item: m_items){
        if(item->isWithin(point)){
            return i;
        }
        i++;
    }
    return std::nullopt;
}