#include "SigridRenderTexture.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;

SigridRenderTexture::SigridRenderTexture(){}

void SigridRenderTexture::setBackgroundColor(const sf::Color& color){
    m_backgroundColor = color;
}

bool SigridRenderTexture::setSize(const sf::Vector2f& size){

    sf::Vector2u sizeU{(unsigned int)size.x, (unsigned int)size.y};

    if(!m_texture){
        m_texture = std::make_unique<sf::RenderTexture>(sizeU);
        return true;
    }

    return m_texture->resize(sizeU);
}

void SigridRenderTexture::setPosition(const sf::Vector2f& position){
    m_position = position;
}

sf::Vector2f SigridRenderTexture::getPosition() const{
    return m_position;
}

sf::Vector2f SigridRenderTexture::getSize() const{
    
    if(!m_texture){
        return {0.f, 0.f};
    }

    const auto size = m_texture->getSize();
    return sf::Vector2f{(float)size.x, (float)size.y};
}

bool SigridRenderTexture::isInitialized() const{
    return !(!m_texture);
}

bool SigridRenderTexture::contains(const sf::Vector2f& point) const{

    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point);
}

void SigridRenderTexture::clear(){
    
    if(!m_texture){
        return;
    }

    m_texture->clear(m_backgroundColor);
}

void SigridRenderTexture::draw(const sf::Drawable& drawable){

    if(!m_texture){
        return;
    }

    m_texture->draw(drawable);
}

void SigridRenderTexture::display(){

    if(!m_texture){
        return;
    }

    m_sprite = std::make_unique<sf::Sprite>(m_texture->getTexture());
    m_sprite->setPosition(m_position);
    m_sprite->move({0.f, (float)m_texture->getTexture().getSize().y});
    m_sprite->setScale({1.f, -1.f});
}

void SigridRenderTexture::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_sprite){
        return;
    }

    if(!m_texture){
        return;
    }

    target.draw(*m_sprite);
}