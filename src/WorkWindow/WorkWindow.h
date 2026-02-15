#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Board/Board.h"
#include "../Tool/Tool.h"

#include "../Action/Action.h"

namespace sigrid{
    class WorkWindow: public sf::Drawable{
        public:
            WorkWindow();

            void createGraphic(const sf::Vector2u& size);

            void addBoard(std::unique_ptr<sigrid::Board> board);
            
            virtual void setPosition(sf::Vector2f);

            unsigned int getNumColumns() const;

            bool contains(sf::Vector2i point) const;

            bool isCoordinatesOutside() const;

            Action clicked(const sigrid::Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& releasePosition);
            void dragMouse(const Tool& tool, const sf::Vector2i& pressPosition, const sf::Vector2i& currentPosition);
            
            void keyPressed(const sf::Event::KeyPressed& event);
            void textEntered(const std::string& text);

            void reset();

            void clear();

            void print();

            void saveLogicBoard();

            void saveBoardImage(const std::string& imageFileName);

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setBigCoordinates();

            void setSmallCoordinates();

            void addBoardBorder();

            void removeBoardBorder();

            void addPlayerToMoveToken();

            void removePlayerToMoveToken();

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;
            std::unique_ptr<sigrid::Board> m_boardPtr;

            sf::Color m_backgroundColor;
    };
}