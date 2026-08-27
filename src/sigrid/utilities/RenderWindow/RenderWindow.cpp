#include "sigrid/utilities/RenderWindow/RenderWindow.h"

bool sigrid::RenderWindow::create(const int& width, const int& height){
    
    if(width <= 0){
        return false;
    }

    if(height <= 0){
        return false;
    }
    
    m_renderWindow.create(
        sf::VideoMode({
            (unsigned int)width,
            (unsigned int)height}),
        "sigrid"
    );

    return true;
}

void sigrid::RenderWindow::setTitle(const sigrid::String& title){
    m_renderWindow.setTitle(title.getStdString());
}

bool sigrid::RenderWindow::setFramerateLimit(const int& limit){

    if(limit <= 0){
        return false;
    }
    m_renderWindow.setFramerateLimit(limit);
    return true;
}

void sigrid::RenderWindow::setView(const sf::Rect<float>& visibleArea){
    m_renderWindow.setView(sf::View(visibleArea));
}

void sigrid::RenderWindow::setBackgroundColor(const sigrid::Color& backgroundColor){
    m_backgroundColor = backgroundColor;
}

bool sigrid::RenderWindow::isOpen() const{
    return m_renderWindow.isOpen();
}

std::optional<sf::Event> sigrid::RenderWindow::pollEvent(){
    return m_renderWindow.pollEvent();
}

void sigrid::RenderWindow::close(){
    m_renderWindow.close();
}

void sigrid::RenderWindow::clear(){
    m_renderWindow.clear(m_backgroundColor.getSfColor());
}

void sigrid::RenderWindow::draw(const sf::Drawable &drawable, const sf::RenderStates &states){
    m_renderWindow.draw(drawable, states);
}

void sigrid::RenderWindow::display(){
    m_renderWindow.display();
}