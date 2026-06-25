#include "Sigrid2DMap.h"
#include "Sigrid2DMap_contentTypes.h"
// Any type used must be added in the Sigrid2DMap_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Sigrid2DList.h
// Both includes above can then be removed from this file

using namespace sigrid;

template<typename T>
Sigrid2DMap<T>::Sigrid2DMap(){}

template<typename T>
void Sigrid2DMap<T>::setInsertPattern(const std::vector<T>& insertPattern){

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
void Sigrid2DMap<T>::setNumColumns(const unsigned int& columns){
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
void Sigrid2DMap<T>::setNumRows(const unsigned int& rows){
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
void Sigrid2DMap<T>::setSize(const unsigned int& columns, const unsigned int& rows){

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
bool Sigrid2DMap<T>::addColumnLeft(){

    shiftInsertPatternRight();

    m_columns++;

    if(m_columns > 1){
        int x = m_columns-1;
        for(int y = 0; (unsigned int)y < m_rows; y++){
            auto leftIt = m_map.find({x-1, y});
            if(leftIt != m_map.end()){
                m_map.insert({{x,y}, leftIt->second});
            }
        }
    }

    for(int x = m_columns-1; x > 0; x--){
        for(int y = 0; (unsigned int)y < m_rows; y++){
            auto currentIt = m_map.find({x,y});
            auto leftIt = m_map.find({x-1, y});
            if(leftIt != m_map.end()){
                if(currentIt == m_map.end()){
                    m_map.insert({{x,y}, leftIt->second});
                }
                else{
                    currentIt->second = leftIt->second;
                }
            }
            else{
                if(currentIt != m_map.end()){
                    m_map.erase(currentIt);
                }
            }
        }
    }

    {
        int x = 0;
        for(int y = 0; (unsigned int)y < m_rows; y++){
            auto currentIt = m_map.find({x,y});
            if(currentIt == m_map.end()){
                m_map.insert({{x,y}, getInsertElement({x,y})});
            }
            else{
                currentIt->second = getInsertElement({x,y});
            }
        }
    }
    return true;
}

template<typename T>
bool Sigrid2DMap<T>::addColumnRight(){

    m_columns++;

    int x = m_columns-1;
    for(int y = 0; y < m_rows; y++){
        m_map.insert({{x,y}, getInsertElement({x,y})});
    }

    return true;
}

template<typename T>
bool Sigrid2DMap<T>::addRowUp(){

    shiftInsertPatternRight();

    m_rows++;

    if(m_rows > 1){
        int y = (int)m_rows-1;
        for(int x = 0; (unsigned int)x < m_columns; x++){
            auto upIt = m_map.find({x, y-1});
            if(upIt != m_map.end()){
                m_map.insert({{x,y}, upIt->second});
            }
        }
    }

    for(int y = (int)m_rows-1; y > 0; y--){
        for(int x = 0; (unsigned int)x < m_columns; x++){
            auto currentIt = m_map.find({x,y});
            auto upIt = m_map.find({x, y-1});
            if(upIt != m_map.end()){
                if(currentIt == m_map.end()){
                    m_map.insert({{x,y}, upIt->second});
                }
                else{
                    currentIt->second = upIt->second;
                }
            }
            else{
                if(currentIt != m_map.end()){
                    m_map.erase(currentIt);
                }
            }
        }
    }

    {
        int y = 0;
        for(int x = 0; (unsigned int)x < m_columns; x++){
            auto currentIt = m_map.find({x,y});
            if(currentIt == m_map.end()){
                m_map.insert({{x,y}, getInsertElement({x,y})});
            }
            else{
                currentIt->second = getInsertElement({x,y});
            }
        }
    }

    return true;
}

template<typename T>
bool Sigrid2DMap<T>::addRowDown(){

    m_rows++;

    int y = (int)m_rows -1;
    for(int x = 0; (unsigned int)x < m_columns; x++){
        m_map.insert({{x,y}, getInsertElement({x,y})});
    }

    return true;
}

template<typename T>
bool Sigrid2DMap<T>::removeColumnLeft(){

    if(m_columns < 2){
        return false;
    }

    shiftInsertPatternRight();

    m_columns--;

    for(int x = 0; (unsigned int)x < m_columns; x++){
        for(int y = 0; (unsigned int)y < m_rows; y++){
            auto currentIt = m_map.find({x,y});
            auto rightIt = m_map.find({x+1, y});
            if(rightIt != m_map.end()){
                if(currentIt == m_map.end()){
                    m_map.insert({{x,y}, rightIt->second});
                }
                else{
                    currentIt->second = rightIt->second;
                }
            }
            else{
                if(currentIt != m_map.end()){
                    m_map.erase(currentIt);
                }
            }
            
        }
    }

    {
        int x = (int)m_columns;
        for(int y = 0; (unsigned int)y < m_rows; y++){
            auto currentIt = m_map.find({x,y});
            if(currentIt != m_map.end()){
                m_map.erase(currentIt);
            }
        }
    }

    return true;
}

template<typename T>
bool Sigrid2DMap<T>::removeColumnRight(){

    if(m_columns < 2){
        return false;
    }

    m_columns--;

    int x = (int)m_columns;
    for(int y = 0; (unsigned int)y < m_rows; y++){
        auto currentIt = m_map.find({x,y});
        if(currentIt != m_map.end()){
            m_map.erase(currentIt);
        }
    }

    return true;
}

template<typename T>
bool Sigrid2DMap<T>::removeRowUp(){

    if(m_rows < 2){
        return false;
    }

    shiftInsertPatternRight();

    m_rows--;

    for(int y = 0; (unsigned int)y < m_rows; y++){
        for(int x = 0; (unsigned int)x < m_columns; x++){
            auto currentIt = m_map.find({x,y});
            auto upIt = m_map.find({x, y+1});
            if(upIt != m_map.end()){
                if(currentIt == m_map.end()){
                    m_map.insert({{x,y}, upIt->second});
                }
                else{
                    currentIt->second = upIt->second;
                }
            }
            else{
                if(currentIt != m_map.end()){
                    m_map.erase(currentIt);
                }
            }
        }
    }

    {
        int y = (int)m_rows;
        for(int x = 0; (unsigned int)x < m_columns; x++){
            auto currentIt = m_map.find({x,y});
            if(currentIt != m_map.end()){
                m_map.erase(currentIt);
            }
        }
    }

    return true;
}

template<typename T>
bool Sigrid2DMap<T>::removeRowDown(){

    if(m_rows < 2){
        return false;
    }

    m_rows--;

    int y = (int)m_rows;
    for(int x = 0; (unsigned int)x < m_columns; x++){
        auto currentIt = m_map.find({x,y});
        if(currentIt != m_map.end()){
            m_map.erase(currentIt);
        }
    }

    return true;
}

template<typename T>
void Sigrid2DMap<T>::clear(){
    m_columns = 0;
    m_rows = 0;
    m_map.clear();
}

template<typename T>
std::optional<std::reference_wrapper<T>> Sigrid2DMap<T>::at(const Coord& coord){

    if(coord.x >= m_columns){
        return std::nullopt;
    }

    if(coord.y >= m_rows){
        return std::nullopt;
    }

    auto it = m_map.find(coord);

    if(it == m_map.end()){
        return std::nullopt;
    }

    return it->second;
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Sigrid2DMap<T>::at(const Coord& coord) const{

    if(coord.x >= m_columns){
        return std::nullopt;
    }

    if(coord.y >= m_rows){
        return std::nullopt;
    }

    auto it = m_map.find(coord);

    if(it == m_map.end()){
        return std::nullopt;
    }

    return it->second;
}

template<typename T>
bool Sigrid2DMap<T>::removeAt(const Coord& coord){

    auto it = m_map.find(coord);
    if(it == m_map.end()){
        return false;
    }
    m_map.erase(it);
    return true;
}

template<typename T>
const unsigned int& Sigrid2DMap<T>::numColumns() const{
    return m_columns;
}

template<typename T>
const unsigned int& Sigrid2DMap<T>::numRows() const{
    return m_rows;
}

template<typename T>
const std::vector<T>& Sigrid2DMap<T>::getInsertPattern() const{
    return m_insertPattern;
}

template<typename T>
T Sigrid2DMap<T>::getInsertElement(const Coord& coord) const{
    if(m_insertPattern.size() == 0){
        return T{};
    }
    return m_insertPattern.at((coord.x+coord.y)%m_insertPattern.size());
}

template<typename T>
void Sigrid2DMap<T>::refill(){

    m_map.clear();

    for(int y = 0; (unsigned int)y < m_rows; y++){
        for(int x = 0; (unsigned int)x < m_columns; x++){
            m_map.insert({{x,y}, getInsertElement({x,y})});
        }
    }
}

template<typename T>
void Sigrid2DMap<T>::shiftInsertPatternRight(){
    
    if(m_insertPattern.size() < 2){
        return;
    }

    T lastElement = m_insertPattern.back();
    m_insertPattern.insert(m_insertPattern.begin(), lastElement);
    m_insertPattern.pop_back();
}