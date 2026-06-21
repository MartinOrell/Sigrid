#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <map>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include "../Action/Action.h"

#include "../SigridRenderTexture/SigridRenderTexture.h"

namespace sigrid{

    class MenuContainer;
    class FontManager;
    class MenuItem;

    class Menu: public sf::Drawable{
        public:
            Menu();

            void setFontManagerPtr(FontManager* const managerPtr);

            void init(const MenuContainer& menuData);

            void createGraphic(const sf::Vector2f& size);

            void setPosition(const sf::Vector2f& position);
            bool contains(const sf::Vector2f& point) const;

            bool isPinned() const;

            bool isCollapsed() const;

            Action clicked(const sf::Vector2f& position);

            void pinMenu();

            void unPinMenu();

            void showMenu();

            void hideMenu();

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
                int x = -1;
                int y = -1;
            };

            struct LayoutItem{
                unsigned int headerIndex = -1;
                unsigned int priority = -1;
            };

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void addSuperHeaderGraphic();
            void addHeaderGraphic(const unsigned int id);
            void addItemGraphic(const unsigned int headerIndex, const unsigned int itemIndex);

            void redrawTexture();

            float getTopPos();
            float getBottomPos();
            std::optional<PosIndex> getMenuItemPosIndex(const sf::Vector2f& point);

            FontManager* m_fontManagerPtr = nullptr;

            SigridRenderTexture m_texture;

            std::unique_ptr<MenuItem> m_superHeaderPtr;

            std::map<std::string, std::unique_ptr<MenuItem>> m_items;

            std::vector<std::vector<std::string>> m_itemKeys;

            std::map<std::string, LayoutItem> m_layoutItems;

            float m_lineHeight = 0.f;
            float m_itemOffsetX = 0.f;

            std::string m_fontFilename = "";

            bool m_isPinned = false;
            bool m_showItems = true;
            int m_showHeaderIndex = -1;
    };
}