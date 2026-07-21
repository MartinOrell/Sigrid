#pragma once

#include <optional>
#include <functional> //Reference wrapper

#include "List/Vector.h"

namespace sigrid_list{

template <typename T> class VectorWithDisplayGrid{

  public:

    VectorWithDisplayGrid() = default;
    VectorWithDisplayGrid(const VectorWithDisplayGrid&) = default;
    VectorWithDisplayGrid(VectorWithDisplayGrid&&) = default;
    VectorWithDisplayGrid& operator=(const VectorWithDisplayGrid&) = default;
    VectorWithDisplayGrid& operator=(VectorWithDisplayGrid&&) = default;

    void push_back(const T& value);
    void addColumn();
    void addRow();
    bool removeColumn();
    bool removeRow();

    bool selectLast();
    bool select(const int& displayPosition);

    std::optional<std::reference_wrapper<T>> at(const int& position);
    const std::optional<std::reference_wrapper<const T>> at(const int& position) const;
    std::optional<std::reference_wrapper<T>> atDisplay(const int& displayPosition);
    const std::optional<std::reference_wrapper<const T>> atDisplay(const int& displayPosition) const;
    std::optional<std::reference_wrapper<T>> atSelection();
    const std::optional<std::reference_wrapper<const T>> atSelection() const;
    std::optional<std::reference_wrapper<int>> activeDisplayIndex();
    const std::optional<std::reference_wrapper<const int>> activeDisplayIndex() const;

    int size() const;
    int currentDisplaySize() const;
    int currentDisplayColumns() const;
    int currentDisplayRows() const;
    int maxDisplayColumns() const;
    int maxDisplayRows() const;

    bool isDisplayedElementSelected(const int& displayPosition) const;

    typename std::vector<T>::iterator begin();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator end() const;

    bool shiftLeft();
    bool shiftRight();
    bool shiftUp();
    bool shiftDown();

    bool selectLeft();
    bool selectRight();
    bool selectUp();
    bool selectDown();

  private:

    bool isOneRowDisplayed() const;
    bool isLeftDisplayColumn(const int& displayIndex) const;
    bool isRightDisplayColumn(const int& displayIndex) const;
    bool isTopDisplayRow(const int& displayIndex) const;
    bool isTopRow(const int& displayIndex) const;
    bool isBottomDisplayRow(const int& displayIndex) const;
    bool isBottomRow(const int& displayIndex) const;

    bool isFirstElement(const int& displayIndex) const;
    bool isLastElement(const int& displayIndex) const;

    void displayFirstElements();
    void displayLastElements();

    sigrid_list::Vector<T> m_vector;
    int m_displayColumns = 1;
    int m_displayRows = 1;
    sigrid_list::Vector<int> m_displayIds;
    std::optional<int> m_selectIndex_o = std::nullopt;

    enum Wrap{
        WRAP_ON,
        WRAP_OFF,
        NEXTWRAP_ON
    };

    Wrap m_multiRowHorisontalWrap = NEXTWRAP_ON;
    bool m_verticalWrap = false;
    bool m_singleRowStartEndWrap = false;
    bool m_multiRowStartEndWrap = false;
};

}  // namespace sigrid_list