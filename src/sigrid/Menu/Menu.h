#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <optional>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include "sigrid/Action/Action.h"

#include "sigrid/utilities/Coord/Coord.h"
#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector2D.h"
#include "sigrid/utilities/lists/Map.h"
#include "sigrid/SigridRenderTexture/SigridRenderTexture.h"
#include "sigrid/Menu/MenuItem.h"
#include "sigrid/Menu/MenuContainer.h"

namespace sigrid{

class FontManager;

class Menu: public sf::Drawable{

  public:

    Menu() = default;
    Menu(const Menu&) = default;
    Menu(Menu&&) = default;
    Menu& operator=(const Menu&) = default;
    Menu& operator=(Menu&&) = default;

    void setFontManagerPtr(FontManager* const managerPtr);

    bool load(const MenuContainer& menuData);
    std::optional<MenuContainer> getContainer() const;

    void createGraphic(const sf::Vector2f& size);

    void setPosition(const sf::Vector2f& position);
    bool contains(const sf::Vector2f& point) const;

    bool isPinned() const;

    bool isCollapsed() const;

    std::optional<sigrid_action::Action> clicked(const sf::Vector2f& position);

    void pinMenu();

    void unPinMenu();

    void showMenu();

    void hideMenu();

    void toggleHeader(const int headerId);

    void addSuperHeader(const sigrid::String&);

    void addHeader(const sigrid::String&);

    void addItem(const sigrid::String&, const int index, const sigrid_action::Action);

    void addToggleItem(const sigrid::String& key, const int index, const sigrid::String& text0, const sigrid_action::Action action0, const sigrid::String& text1, const sigrid_action::Action action1);

    void toggleItem(const sigrid::String& key);

    void hideItem(const sigrid::String& key);

    void showItem(const sigrid::String& key);

    struct LayoutItem{
        int headerIndex = -1;
        int priority = -1;
    };

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void addSuperHeaderGraphic();
    void addHeaderGraphic(const int id);
    void addItemGraphic(const int headerIndex, const int itemIndex);

    void redrawTexture();

    float getTopPos();
    float getBottomPos();
    std::optional<sigrid_coord::Coord> getMenuItemPosIndex(const sf::Vector2f& point);

    void printItemKeys() const;

    FontManager* m_fontManagerPtr = nullptr;

    SigridRenderTexture m_texture;

    MenuItem m_superHeader;

    sigrid_list::Map<sigrid::String, MenuItem> m_items;

    sigrid_list::Vector2D<sigrid::String> m_itemKeys;

    sigrid_list::Map<sigrid::String, LayoutItem> m_layoutItems;

    float m_lineHeight = 0.f;
    float m_itemOffsetX = 0.f;

    sigrid::String m_fontFilename;

    bool m_isPinned = false;
    bool m_showItems = true;
    int m_showHeaderIndex = -1;
};

}  // namespace sigrid