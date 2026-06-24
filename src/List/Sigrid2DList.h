#pragma once

#include <vector>
#include <optional>
#include <functional> //Reference wrapper

namespace sigrid{

    template <typename T> class Sigrid2DList{

        public:
            Sigrid2DList();

            void push_back(const T& value);
            void addColumn();
            void addRow();
            bool removeColumn();
            bool removeRow();

            bool selectLast();
            bool select(const unsigned int& displayPosition);

            std::optional<std::reference_wrapper<T>> at(const unsigned int& position);
            const std::optional<std::reference_wrapper<const T>> at(const unsigned int& position) const;
            std::optional<std::reference_wrapper<T>> atDisplay(const unsigned int& displayPosition);
            const std::optional<std::reference_wrapper<const T>> atDisplay(const unsigned int& displayPosition) const;
            std::optional<std::reference_wrapper<T>> atSelection();
            const std::optional<std::reference_wrapper<const T>> atSelection() const;
            std::optional<std::reference_wrapper<unsigned int>> activeDisplayIndex();
            const std::optional<std::reference_wrapper<const unsigned int>> activeDisplayIndex() const;

            unsigned int size() const;
            unsigned int currentDisplaySize() const;
            unsigned int currentDisplayColumns() const;
            unsigned int currentDisplayRows() const;
            unsigned int maxDisplayColumns() const;
            unsigned int maxDisplayRows() const;
            std::vector<T>& getVector();
            const std::vector<T>& getVector() const;

            bool isDisplayedElementSelected(const unsigned int& displayPosition) const;

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
            bool isRightDisplayColumn(const unsigned int& displayIndex) const;
            bool isTopDisplayRow(const unsigned int& displayIndex) const;
            bool isTopRow(const unsigned int& displayIndex) const;
            bool isBottomDisplayRow(const unsigned int& displayIndex) const;
            bool isBottomRow(const unsigned int& displayIndex) const;

            bool isLastElement(const unsigned int& displayIndex) const;

            void displayFirstElements();
            void displayLastElements();

            std::vector<T> m_vector;
            unsigned int m_displayColumns = 1;
            unsigned int m_displayRows = 1;
            std::vector<unsigned int> m_displayIds;
            std::optional<unsigned int> m_selectIndex_o = std::nullopt;

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
}