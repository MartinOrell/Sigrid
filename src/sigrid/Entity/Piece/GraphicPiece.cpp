#include "sigrid/Entity/Piece/GraphicPiece.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

void sigrid::GraphicPiece::setSize(const sf::Vector2f& size){

    m_size = size;
    if(m_sprite_o == std::nullopt){
        return;
    }
    auto& sprite = m_sprite_o.value();

    sprite.setPosition({size.x/2.f, size.y/2.f});
}

void sigrid::GraphicPiece::setTexturePtr(const sigrid::Texture* const texturePtr){
    
    m_texturePtr = texturePtr;

    if(m_sprite_o == std::nullopt){
        m_sprite_o = sf::Sprite(texturePtr->getSfTexture());
        float scale = 0.8;
        auto& sprite = m_sprite_o.value();
        sprite.scale({scale,scale});
    }
    else{
        m_sprite_o = sf::Sprite(texturePtr->getSfTexture());
    }

    auto& sprite = m_sprite_o.value();

    sf::FloatRect rect(sprite.getLocalBounds());
    sprite.setOrigin({rect.size.x/2.f, rect.size.y/2.f});

    if(m_size.x <= 0.f){
        return;
    }
    if(m_size.y <= 0.f){
        return;
    }

    sprite.setPosition({m_size.x/2.f, m_size.y/2.f});
}

void sigrid::GraphicPiece::setPosition(const sigrid::Position_f& position){
    
    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    sprite.setPosition(position.getSfVector());
}

bool sigrid::GraphicPiece::contains(const sf::Vector2i& point) const{

    if(!m_sprite_o){
        return false;
    }
    auto& sprite = m_sprite_o.value();
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

void sigrid::GraphicPiece::resize(const sigrid::Size_f& size){

    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    auto rect = sprite.getTextureRect();
    float scaleX = size.x/rect.size.x;
    float scaleY = size.y/rect.size.y;

    sprite.setScale({scaleX, scaleY});
}

const sigrid::Texture sigrid::GraphicPiece::getTexture() const{
    return *m_texturePtr;
}

const sigrid::Texture* sigrid::GraphicPiece::getTexturePtr() const{
    return m_texturePtr;
}

void sigrid::GraphicPiece::move(const sigrid::Offset_f& offset){

    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    sprite.move(offset.getSfVector());
}

void sigrid::GraphicPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    target.draw(sprite);
}