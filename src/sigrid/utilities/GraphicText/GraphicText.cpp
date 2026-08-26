#include "sigrid/utilities/GraphicText/GraphicText.h"

#include <iostream>

void sigrid::GraphicText::setFont(const sf::Font& font){

    if(m_text_o == std::nullopt){
        m_text_o = sf::Text{font};
        return;
    }
    auto& text = m_text_o.value();

    text.setFont(font);
}

void sigrid::GraphicText::setString(const sigrid::String& string){

    if(m_text_o == std::nullopt){
        std::cerr << "GraphicText: Failed to set string \"" << string << "\"."
            << " Font is not set" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    text.setString(string.getStdString());
}

bool sigrid::GraphicText::setCharacterSize(const int& size){
    
    if(size < 0){
        std::cerr << "GraphicText: Failed to set character size " << size << "."
            << " Character size can not be negative" << std::endl;
        return false;
    }

    if(m_text_o == std::nullopt){
        std::cerr << "GraphicText: Failed to set character size " << size << "."
            << " Font is not set" << std::endl;
        return false;
    }
    auto& text = m_text_o.value();

    text.setCharacterSize(size);
    return true;
}

void sigrid::GraphicText::setOrigin(const sf::Vector2f& origin){

    if(m_text_o == std::nullopt){
        std::cerr << "GraphicText: Failed to set origin."
            << " Font is not set" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    text.setOrigin(origin);
}

void sigrid::GraphicText::setPosition(const sf::Vector2f& position){

    if(m_text_o == std::nullopt){

        std::cerr << "GraphicText: Failed to set position."
            << " Font is not set" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    text.setPosition(position);
}

void sigrid::GraphicText::setFillColor(const sigrid::Color& color){

    if(m_text_o == std::nullopt){

        std::cerr << "GraphicText: Failed to set Fill color."
            << " Font is not set" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    text.setFillColor(color.getSfColor());
}

void sigrid::GraphicText::setOutlineColor(const sigrid::Color& color){

    if(m_text_o == std::nullopt){

        std::cerr << "GraphicText: Failed to set Outline color."
            << " Font is not set" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    text.setOutlineColor(color.getSfColor());
}

void sigrid::GraphicText::setOutlineThickness(const float& thickness){

    if(m_text_o == std::nullopt){

        std::cerr << "GraphicText: Failed to set outline thickness."
            << " Font is not set" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    text.setOutlineThickness(thickness);
}

bool sigrid::GraphicText::isInitialized() const{
    return m_text_o != std::nullopt;
}

float sigrid::GraphicText::getLocalWidth() const{

    if(m_text_o == std::nullopt){
        return 0.f;
    }
    const auto& text = m_text_o.value();

    return text.getLocalBounds().size.x;
}

void sigrid::GraphicText::move(const sf::Vector2f& offset){

    if(m_text_o == std::nullopt){
        return;
    }
    auto& text = m_text_o.value();

    text.move(offset);
}

void sigrid::GraphicText::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(m_text_o == std::nullopt){
        return;
    }
    const auto& text = m_text_o.value();

    target.draw(text);
}