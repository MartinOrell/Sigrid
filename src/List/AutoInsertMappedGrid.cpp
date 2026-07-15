#include "List/AutoInsertMappedGrid.h"
#include "List/AutoInsertMappedGrid_contentTypes.h"
// Any type used must be added in the AutoInsertMappedGrid_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of AutoInsertMappedGrid.h
// Both includes above can then be removed from this file

using namespace sigrid_list;

template<typename T>
void AutoInsertMappedGrid<T>::setInsertPattern(const sigrid_list::Vector<T>& insertPattern){

    m_insertPattern = insertPattern;

    if(m_columns == 0){
        return;
    }
    if(m_rows == 0){
        return;
    }
    if(m_insertPattern.size() == 0){
        return;
    }

    refill();
}

template<typename T>
void AutoInsertMappedGrid<T>::setNumColumns(const int& columns){

    m_columns = columns;

    if(m_columns == 0){
        return;
    }
    if(m_rows == 0){
        return;
    }
    if(m_insertPattern.size() == 0){
        return;
    }

    refill();
}

template<typename T>
void AutoInsertMappedGrid<T>::setNumRows(const int& rows){

    m_rows = rows;

    if(m_columns == 0){
        return;
    }
    if(m_rows == 0){
        return;
    }
    if(m_insertPattern.size() == 0){
        return;
    }

    refill();
}

template<typename T>
void AutoInsertMappedGrid<T>::setSize(const int& columns, const int& rows){

    m_columns = columns;
    m_rows = rows;

    if(m_columns == 0){
        return;
    }
    if(m_rows == 0){
        return;
    }
    if(m_insertPattern.size() == 0){
        return;
    }

    refill();
}

template<typename T>
bool AutoInsertMappedGrid<T>::addColumnLeft(){

    shiftInsertPatternRight();

    m_columns++;

    if(m_columns > 1){
        int x = m_columns-1;
        for(int y = 0; y < m_rows; y++){
            
            auto leftElement_o = m_map.at({x-1, y});
            if(leftElement_o == std::nullopt){
                continue;
            }
            auto leftElement = leftElement_o.value().get();
            m_map.insert({x,y}, std::move(leftElement));
        }
    }

    for(int x = m_columns-1; x > 0; x--){
        for(int y = 0; y < m_rows; y++){

            auto leftElement_o = m_map.at({x-1, y});
            auto currentElement_o = m_map.at({x,y});

            if(leftElement_o == std::nullopt){
                if(currentElement_o != std::nullopt){
                    m_map.erase({x,y});
                }
                continue;
            }

            auto leftElement = leftElement_o.value().get();
            if(currentElement_o == std::nullopt){
                m_map.insert({x,y}, std::move(leftElement));
                continue;
            }

            auto& currentElement = currentElement_o.value().get();
            currentElement = std::move(leftElement);
        }
    }

    {
        int x = 0;
        for(int y = 0; y < m_rows; y++){

            auto currentElement_o = m_map.at({x,y});
            if(currentElement_o == std::nullopt){
                m_map.insert({x,y}, getInsertElement({x,y}));
                continue;
            }
            auto& currentElement = currentElement_o.value().get();
            currentElement = getInsertElement({x,y});
        }
    }
    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::addColumnRight(){

    m_columns++;

    int x = m_columns-1;
    for(int y = 0; y < m_rows; y++){
        m_map.insert({x,y}, getInsertElement({x,y}));
    }

    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::addRowUp(){

    shiftInsertPatternRight();

    m_rows++;

    if(m_rows > 1){
        int y = m_rows-1;
        for(int x = 0; x < m_columns; x++){

            auto upElement_o = m_map.at({x, y-1});
            if(upElement_o == std::nullopt){
                continue;
            }
            auto upElement = upElement_o.value().get();
            m_map.insert({x,y}, std::move(upElement));
        }
    }

    for(int y = m_rows-1; y > 0; y--){
        for(int x = 0; x < m_columns; x++){

            auto currentElement_o = m_map.at({x,y});
            auto upElement_o = m_map.at({x, y-1});

            if(upElement_o == std::nullopt){
                if(currentElement_o == std::nullopt){
                    m_map.erase({x,y});
                }
                continue;
            }
            auto upElement = upElement_o.value().get();

            if(currentElement_o == std::nullopt){
                m_map.insert({x,y}, std::move(upElement));
                continue;
            }

            auto& currentElement = currentElement_o.value().get();
            currentElement = std::move(upElement);
        }
    }

    {
        int y = 0;
        for(int x = 0; x < m_columns; x++){

            auto currentElement_o = m_map.at({x,y});

            if(currentElement_o == std::nullopt){
                m_map.insert({x,y}, getInsertElement({x,y}));
                continue;
            }
            auto& currentElement = currentElement_o.value().get();
            currentElement = getInsertElement({x,y});
        }
    }

    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::addRowDown(){

    m_rows++;

    int y = m_rows -1;
    for(int x = 0; x < m_columns; x++){
        m_map.insert({x,y}, getInsertElement({x,y}));
    }

    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::removeLeftColumn(){

    if(m_columns < 2){
        return false;
    }

    shiftInsertPatternRight();

    m_columns--;

    for(int x = 0; x < m_columns; x++){
        for(int y = 0; y < m_rows; y++){

            auto currentElement_o = m_map.at({x,y});
            auto rightElement_o = m_map.at({x+1, y});

            if(rightElement_o == std::nullopt){
                if(currentElement_o != std::nullopt){
                    m_map.erase({x,y});
                }
                continue;
            }
            auto rightElement = rightElement_o.value().get();

            if(currentElement_o == std::nullopt){
                m_map.insert({x,y}, std::move(rightElement));
                continue;
            }

            auto& currentElement = currentElement_o.value().get();
            currentElement = std::move(rightElement);
        }
    }

    {
        int x = m_columns;
        for(int y = 0; y < m_rows; y++){

            auto currentElement_o = m_map.at({x,y});
            if(currentElement_o == std::nullopt){
                continue;
            }
            m_map.erase({x,y});
        }
    }

    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::removeRightColumn(){

    if(m_columns < 2){
        return false;
    }

    m_columns--;

    int x = m_columns;
    for(int y = 0; y < m_rows; y++){

        auto currentElement_o = m_map.at({x,y});
        if(currentElement_o == std::nullopt){
            continue;
        }
        m_map.erase({x,y});
    }

    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::removeTopRow(){

    if(m_rows < 2){
        return false;
    }

    shiftInsertPatternRight();

    m_rows--;

    for(int y = 0; y < m_rows; y++){
        for(int x = 0; x < m_columns; x++){

            auto currentElement_o = m_map.at({x,y});
            auto upElement_o = m_map.at({x, y+1});

            if(upElement_o == std::nullopt){
                if(currentElement_o != std::nullopt){
                    m_map.erase({x,y});
                }
                continue;
            }
            auto upElement = upElement_o.value().get();

            if(currentElement_o == std::nullopt){
                m_map.insert({x,y}, std::move(upElement));
                continue;
            }
            
            auto& currentElement = currentElement_o.value().get();
            currentElement = std::move(upElement);
        }
    }

    {
        int y = m_rows;
        for(int x = 0; x < m_columns; x++){

            auto currentElement_o = m_map.at({x,y});
            if(currentElement_o == std::nullopt){
                continue;
            }
            m_map.erase({x,y});
        }
    }

    return true;
}

template<typename T>
bool AutoInsertMappedGrid<T>::removeBottomRow(){

    if(m_rows < 2){
        return false;
    }

    m_rows--;

    int y = m_rows;
    for(int x = 0; x < m_columns; x++){

        auto currentElement_o = m_map.at({x,y});
        if(currentElement_o == std::nullopt){
            continue;
        }
        m_map.erase({x,y});
    }

    return true;
}

template<typename T>
void AutoInsertMappedGrid<T>::clear(){
    m_columns = 0;
    m_rows = 0;
    m_map.clear();
}

template<typename T>
std::optional<std::reference_wrapper<T>> AutoInsertMappedGrid<T>::at(const sigrid::Coord& coord){
    return m_map.at(coord);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> AutoInsertMappedGrid<T>::at(const sigrid::Coord& coord) const{
    return m_map.at(coord);
}

template<typename T>
bool AutoInsertMappedGrid<T>::removeAt(const sigrid::Coord& coord){

    auto element_o = m_map.at(coord);
    if(element_o == std::nullopt){
        return false;
    }
    m_map.erase({coord});
    return true;
}

template<typename T>
const int& AutoInsertMappedGrid<T>::numColumns() const{
    return m_columns;
}

template<typename T>
const int& AutoInsertMappedGrid<T>::numRows() const{
    return m_rows;
}

template<typename T>
const sigrid_list::Vector<T>& AutoInsertMappedGrid<T>::getInsertPattern() const{
    return m_insertPattern;
}

template<typename T>
T AutoInsertMappedGrid<T>::getInsertElement(const sigrid::Coord& coord) const{

    auto element_o = m_insertPattern.at((coord.x+coord.y)%m_insertPattern.size());

    if(element_o == std::nullopt){
        return T{};
    }
    return element_o.value().get();
}

template<typename T>
void AutoInsertMappedGrid<T>::refill(){

    m_map.clear();

    for(int y = 0; y < m_rows; y++){
        for(int x = 0; x < m_columns; x++){
            m_map.insert({x,y}, getInsertElement({x,y}));
        }
    }
}

template<typename T>
void AutoInsertMappedGrid<T>::shiftInsertPatternRight(){
    
    if(m_insertPattern.size() < 2){
        return;
    }

    auto lastElement_o = m_insertPattern.back();
    if(lastElement_o == std::nullopt){
        return;
    }
    auto lastElement = lastElement_o.value().get();

    m_insertPattern.insert(0, lastElement);
    m_insertPattern.pop_back();
}