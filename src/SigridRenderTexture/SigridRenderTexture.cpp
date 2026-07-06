#include "SigridRenderTexture/SigridRenderTexture.h"

#include <SFML/Graphics/RenderTexture.hpp>

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

void SigridRenderTexture::setScale(const float& scale){
    m_scale = scale;
}

void SigridRenderTexture::show(){
    m_show = true;
}

void SigridRenderTexture::hide(){
    m_show = false;
}

const sf::Color& SigridRenderTexture::getBackgroundColor() const{
    return m_backgroundColor;
}

const sf::Vector2f& SigridRenderTexture::getPosition() const{
    return m_position;
}

const float& SigridRenderTexture::getTopPosition() const{
    return m_position.y;
}

float SigridRenderTexture::getBottomPosition() const{
    float y = m_position.y;
    if(m_texture){
        y += m_scale*(float)m_texture->getSize().y;
    }
    return y;
}

const float& SigridRenderTexture::getScale() const{
    return m_scale;
}

sf::Vector2f SigridRenderTexture::getTextureSize() const{
    
    if(!m_texture){
        return {0.f, 0.f};
    }

    if(!m_show){
        return {0.f, 0.f};
    }

    const auto size = m_texture->getSize();
    return sf::Vector2f{(float)size.x, (float)size.y};
}

sf::Vector2f SigridRenderTexture::getDisplaySize() const{
    
    return m_scale*getTextureSize();
}

sf::Image SigridRenderTexture::getImage() const{

    auto image = m_texture->getTexture().copyToImage();
    image.flipVertically();
    return image;
}

sf::Image SigridRenderTexture::getImage(const unsigned int maxWidth, const unsigned int maxHeight) const{

    const auto& size = m_texture->getSize();
    float oldWidth = size.x;
    float oldHeight = size.y;

    float widthRatio = 1.f;
    if(oldWidth > maxWidth){
        widthRatio = (float)maxWidth/(float)oldWidth;
    }
    float heightRatio = 1.f;
    if(oldHeight > maxHeight){
        heightRatio = (float)maxHeight/(float)oldHeight;
    }

    float ratio;
    if(widthRatio < heightRatio){
        ratio = widthRatio;
    }
    else{
        ratio = heightRatio;
    }

    unsigned int newWidth = oldWidth * ratio;
    unsigned int newHeight = oldHeight * ratio;

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition({0.f,0.f});
    sprite.setScale({ratio,ratio});

    sf::RenderTexture newRenderTexture{sf::Vector2u{newWidth, newHeight}};
    newRenderTexture.clear(sf::Color::White);
    newRenderTexture.draw(sprite);
    return newRenderTexture.getTexture().copyToImage();
}

bool SigridRenderTexture::isInitialized() const{
    return !(!m_texture);
}

bool SigridRenderTexture::isVisible() const{
    return m_show;
}

bool SigridRenderTexture::isHidden() const{
    return !m_show;
}

bool SigridRenderTexture::contains(const sf::Vector2f& point) const{

    if(!m_texture){
        return false;
    }

    if(!m_show){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position/m_scale);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point/m_scale);
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
    m_sprite->move({0.f, m_scale*(float)m_texture->getTexture().getSize().y});
    m_sprite->setScale({m_scale, -m_scale});
}

void SigridRenderTexture::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_sprite){
        return;
    }

    if(!m_texture){
        return;
    }

    if(!m_show){
        return;
    }

    target.draw(*m_sprite);
}