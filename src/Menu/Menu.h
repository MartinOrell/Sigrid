#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include "MenuItem.h"

#include <SFML/Graphics/Font.hpp>
#include "../Tool/Tool.h"

#include "../Board/GraphicBoardConfigContainer.h"
#include "../MainWindow/MainWindowConfigContainer.h"


namespace sigrid{
    class Menu: public sf::Drawable{
        public:
            Menu(const GraphicBoardConfigContainer& gConfig, const MainWindowConfigContainer& wConfig);

            void createGraphic(const sf::Vector2u& size);

            void setPosition(sf::Vector2f position);
            bool contains(sf::Vector2i point) const;

            bool isPinned() const;

            bool isCollapsed() const;

            Action clicked(const Tool& tool, const sf::Vector2i& position);

            void pinMenu();

            void showMenu();

            void toggleHeader(const int headerId);

            void addSuperHeader(const std::string&);

            void addHeader(const std::string&);

            void addItem(const std::string&, const int index, const Action);

            void addToggleItem(const std::string& key, const int index, const std::string& text0, const Action action0, const std::string& text1, const Action action1);

            void toggleItem(const std::string& key);

            void hideItem(const std::string& key);

            void showItem(const std::string& key);

        private:

            struct PosIndex{
                int x;
                int y;
            };

            struct LayoutItem{
                unsigned int headerIndex;
                unsigned int priority;
            };

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void addSuperHeaderGraphic();
            void addHeaderGraphic(const unsigned int id);
            void addItemGraphic(const unsigned int headerIndex, const unsigned int itemIndex);

            void reDrawTexture();

            float getTopPos();
            float getBottomPos();
            std::optional<PosIndex> getMenuItemPosIndex(sf::Vector2i point);

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;

            std::unique_ptr<MenuItem> m_superHeaderPtr;

            std::map<std::string, std::unique_ptr<MenuItem>> m_items;

            std::vector<std::vector<std::string>> m_itemKeys;

            //std::vector<std::vector<LayoutItem>> m_layoutItems;

            std::map<std::string, LayoutItem> m_layoutItems;

            float m_lineHeight;
            float m_itemOffsetX;

            sf::Color m_backgroundColor;
            sf::Font m_font;

            bool m_isPinned;
            bool m_showItems;
            int m_showHeaderIndex;
    };
}