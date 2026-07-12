#include "Entity/Piece/GraphicPiece.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sigrid;

void GraphicPiece::setSize(const sf::Vector2f& size){

    m_size = size;
    if(m_sprite_o == std::nullopt){
        return;
    }
    auto& sprite = m_sprite_o.value();

    sprite.setPosition({size.x/2.f, size.y/2.f});
}

void GraphicPiece::setTexturePtr(const sf::Texture* const texturePtr){
    
    m_texturePtr = texturePtr;

    if(m_sprite_o == std::nullopt){
        m_sprite_o = sf::Sprite(*texturePtr);
        float scale = 0.8;
        auto& sprite = m_sprite_o.value();
        sprite.scale({scale,scale});
    }
    else{
        m_sprite_o = sf::Sprite(*texturePtr);
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

void GraphicPiece::setPosition(sf::Vector2f position){
    
    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    sprite.setPosition(position);
}

bool GraphicPiece::contains(sf::Vector2i point) const{

    if(!m_sprite_o){
        return false;
    }
    auto& sprite = m_sprite_o.value();
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

void GraphicPiece::resize(sf::Vector2f size){

    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    auto rect = sprite.getTextureRect();
    float scaleX = size.x/rect.size.x;
    float scaleY = size.y/rect.size.y;

    sprite.setScale({scaleX, scaleY});
}

const sf::Texture GraphicPiece::getTexture() const{
    return *m_texturePtr;
}

const sf::Texture* GraphicPiece::getTexturePtr() const{
    return m_texturePtr;
}

void GraphicPiece::move(const sf::Vector2f& offset){

    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    sprite.move(offset);
}

void GraphicPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_sprite_o){
        return;
    }
    auto& sprite = m_sprite_o.value();
    target.draw(sprite);
}