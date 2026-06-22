#pragma once

#include <vector>

namespace sigrid{

    template <typename T> class Sigrid2DList{

        public:
            Sigrid2DList();

            void push_back(const T& value);
            void addColumn();
            void addRow();
            bool removeColumn();
            bool removeRow();

            void selectLast();
            void select(const unsigned int& displayPosition);

            T& at(const unsigned int& position);
            const T& at(const unsigned int& position) const;
            T& atDisplay(const unsigned int& displayPosition);
            const T& atDisplay(const unsigned int& displayPosition) const;
            T& atActive();
            const T& atActive() const;
            unsigned int& activeDisplayIndex();
            const unsigned int& activeDisplayIndex() const;

            unsigned int size() const;
            unsigned int currentDisplaySize() const;
            unsigned int currentDisplayColumns() const;
            unsigned int currentDisplayRows() const;
            unsigned int maxDisplayColumns() const;
            unsigned int maxDisplayRows() const;
            const std::vector<T>& getVector() const;

            bool isDisplayActive(const unsigned int& displayPosition) const;

            bool shiftLeft();
            bool shiftRight();
            bool selectLeft();
            bool selectRight();
            bool selectUp();
            bool selectDown();

        private:

            void displayFirstElements();
            void displayLastElements();

            std::vector<T> m_vector;
            unsigned int m_displayColumns = 1;
            unsigned int m_displayRows = 1;
            std::vector<unsigned int> m_displayIds;
            int m_activeIndex = -1;
    };
}

#include "Sigrid2DList.tpp"