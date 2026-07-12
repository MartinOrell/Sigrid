#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <optional>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include "Action/Action.h"

#include "List/Map.h"
#include "SigridRenderTexture/SigridRenderTexture.h"
#include "Menu/MenuItem.h"

namespace sigrid{

    class MenuContainer;
    class FontManager;

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

            std::optional<Action> clicked(const sf::Vector2f& position);

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

            struct LayoutItem{
                int headerIndex = -1;
                int priority = -1;
            };

        private:

            struct PosIndex{
                int x = -1;
                int y = -1;
            };

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void addSuperHeaderGraphic();
            void addHeaderGraphic(const int id);
            void addItemGraphic(const int headerIndex, const int itemIndex);

            void redrawTexture();

            float getTopPos();
            float getBottomPos();
            std::optional<PosIndex> getMenuItemPosIndex(const sf::Vector2f& point);

            FontManager* m_fontManagerPtr = nullptr;

            SigridRenderTexture m_texture;

            MenuItem m_superHeader;

            list::Map<std::string, MenuItem> m_items;

            std::vector<std::vector<std::string>> m_itemKeys;

            list::Map<std::string, LayoutItem> m_layoutItems;

            float m_lineHeight = 0.f;
            float m_itemOffsetX = 0.f;

            std::string m_fontFilename = "";

            bool m_isPinned = false;
            bool m_showItems = true;
            int m_showHeaderIndex = -1;
    };
}