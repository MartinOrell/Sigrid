#include "sigrid/SigridRenderTexture/SigridRenderTexture.h"

void sigrid::SigridRenderTexture::setBackgroundColor(const sf::Color& color){
    m_backgroundColor = color;
}

bool sigrid::SigridRenderTexture::setSize(const sf::Vector2f& size){

    sf::Vector2u sizeU{(unsigned int)size.x, (unsigned int)size.y};
    return m_texture.resize(sizeU);
}

void sigrid::SigridRenderTexture::setPosition(const sf::Vector2f& position){
    m_position = position;
}

void sigrid::SigridRenderTexture::setScale(const float& scale){
    m_scale = scale;
}

void sigrid::SigridRenderTexture::show(){
    m_show = true;
}

void sigrid::SigridRenderTexture::hide(){
    m_show = false;
}

const sf::Color& sigrid::SigridRenderTexture::getBackgroundColor() const{
    return m_backgroundColor;
}

const sf::Vector2f& sigrid::SigridRenderTexture::getPosition() const{
    return m_position;
}

const float& sigrid::SigridRenderTexture::getTopPosition() const{
    return m_position.y;
}

float sigrid::SigridRenderTexture::getBottomPosition() const{

    float y = m_position.y;
    y += m_scale*(float)m_texture.getSize().y;
    return y;
}

const float& sigrid::SigridRenderTexture::getScale() const{
    return m_scale;
}

sf::Vector2f sigrid::SigridRenderTexture::getTextureSize() const{

    if(!m_show){
        return {0.f, 0.f};
    }

    const auto size = m_texture.getSize();
    return sf::Vector2f{(float)size.x, (float)size.y};
}

sf::Vector2f sigrid::SigridRenderTexture::getDisplaySize() const{
    
    return m_scale*getTextureSize();
}

sigrid::Image sigrid::SigridRenderTexture::getImage() const{

    auto sfImage = m_texture.getTexture().copyToImage();
    sfImage.flipVertically();

    sigrid::Image image;
    image.set(std::move(sfImage));
    return image;
}

sigrid::Image sigrid::SigridRenderTexture::getImage(const int maxWidth, const int maxHeight) const{

    const auto& size = m_texture.getSize();
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

    sf::Sprite sprite(m_texture.getTexture());
    sprite.setPosition({0.f,0.f});
    sprite.setScale({ratio,ratio});

    sf::RenderTexture newRenderTexture{sf::Vector2u{newWidth, newHeight}};
    newRenderTexture.clear(sf::Color::White);
    newRenderTexture.draw(sprite);

    auto sfImage = newRenderTexture.getTexture().copyToImage();
    sigrid::Image image;
    image.set(std::move(sfImage));
    return image;
}

bool sigrid::SigridRenderTexture::isInitialized() const{
    return m_texture.getSize().x > 0 && m_texture.getSize().y > 0;
}

bool sigrid::SigridRenderTexture::isVisible() const{
    return m_show;
}

bool sigrid::SigridRenderTexture::isHidden() const{
    return !m_show;
}

bool sigrid::SigridRenderTexture::contains(const sf::Vector2f& point) const{

    if(!m_show){
        return false;
    }

    sf::Sprite sprite(m_texture.getTexture());
    sprite.setPosition(m_position/m_scale);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point/m_scale);
}

void sigrid::SigridRenderTexture::clear(){
    m_texture.clear(m_backgroundColor);
}

void sigrid::SigridRenderTexture::draw(const sf::Drawable& drawable){
    m_texture.draw(drawable);
}

void sigrid::SigridRenderTexture::display(){

    m_sprite_o = sf::Sprite{m_texture.getTexture()};
    auto& sprite = m_sprite_o.value();
    sprite.setPosition(m_position);
    sprite.move({0.f, m_scale*(float)m_texture.getTexture().getSize().y});
    sprite.setScale({m_scale, -m_scale});
}

void sigrid::SigridRenderTexture::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_show){
        return;
    }

    if(m_sprite_o == std::nullopt){
        return;
    }
    auto& sprite = m_sprite_o.value();

    target.draw(sprite);
}