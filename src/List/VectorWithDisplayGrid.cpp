#include "List/VectorWithDisplayGrid.h"
#include "List/VectorWithDisplayGrid_contentTypes.h"
// Any type used must be added in the VectorWithDisplayGrid_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of VectorWithDisplayGrid.h
// Both includes above can then be removed from this file

using namespace sigrid::list;

template<typename T>
VectorWithDisplayGrid<T>::VectorWithDisplayGrid(){}

template<typename T>
void VectorWithDisplayGrid<T>::push_back(const T& value){
    
    m_vector.push_back(value);

    if(m_displayIds.size() < m_displayColumns * m_displayRows){
        m_displayIds.push_back(m_vector.size()-1);
    }
    else{
        displayLastElements();
    }

    if(m_displayIds.size() == 1){
        m_selectIndex_o = 0;
    }
}

template<typename T>
void VectorWithDisplayGrid<T>::addColumn(){
    m_displayColumns++;
    displayLastElements();
}

template<typename T>
void VectorWithDisplayGrid<T>::addRow(){
    m_displayRows++;
    displayLastElements();
}

template<typename T>
bool VectorWithDisplayGrid<T>::removeColumn(){

    if(m_displayColumns < 2){
        return false;
    }

    m_displayColumns--;

    displayLastElements();
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::removeRow(){

    if(m_displayRows < 2){
        return false;
    }

    m_displayRows--;

    displayLastElements();
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::selectLast(){

    const unsigned int displaySize = m_displayIds.size();
    if(displaySize == 0){
        m_selectIndex_o = std::nullopt;
        return false;
    }
    m_selectIndex_o = displaySize-1;
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::select(const unsigned int& displayPosition){

    const unsigned int displaySize = m_displayIds.size();
    if(displayPosition >= displaySize){
        m_selectIndex_o = std::nullopt;
        return false;
    }
    m_selectIndex_o = displayPosition;
    return true;
}

template<typename T>
std::optional<std::reference_wrapper<T>> VectorWithDisplayGrid<T>::at(const unsigned int& position){

    if(position >= m_vector.size()){
        return std::nullopt;
    }

    return m_vector.at(position);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> VectorWithDisplayGrid<T>::at(const unsigned int& position) const{
    
    if(position >= m_vector.size()){
        return std::nullopt;
    }
    
    return m_vector.at(position);
}

template<typename T>
std::optional<std::reference_wrapper<T>> VectorWithDisplayGrid<T>::atDisplay(const unsigned int& displayPosition){

    if(displayPosition >= m_displayIds.size()){
        return std::nullopt;
    }

    return at(m_displayIds.at(displayPosition));
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> VectorWithDisplayGrid<T>::atDisplay(const unsigned int& displayPosition) const{

    if(displayPosition >= m_displayIds.size()){
        return std::nullopt;
    }

    return at(m_displayIds.at(displayPosition));
}

template<typename T>
std::optional<std::reference_wrapper<T>> VectorWithDisplayGrid<T>::atSelection(){

    if(!m_selectIndex_o){
        return std::nullopt;
    }

    return atDisplay(m_selectIndex_o.value());
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> VectorWithDisplayGrid<T>::atSelection() const{

    if(!m_selectIndex_o){
        return std::nullopt;
    }

    return atDisplay(m_selectIndex_o.value());
}

template<typename T>
std::optional<std::reference_wrapper<unsigned int>> VectorWithDisplayGrid<T>::activeDisplayIndex(){

    if(!m_selectIndex_o){
        return std::nullopt;
    }
    return m_displayIds.at(m_selectIndex_o.value());
}

template<typename T>
const std::optional<std::reference_wrapper<const unsigned int>> VectorWithDisplayGrid<T>::activeDisplayIndex() const{
    
    if(!m_selectIndex_o){
        return std::nullopt;
    }
    return m_displayIds.at(m_selectIndex_o.value());
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::size() const{
    return (unsigned int)m_vector.size();
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::currentDisplaySize() const{
    return (unsigned int)m_displayIds.size();
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::currentDisplayColumns() const{
    return (m_displayIds.size() > m_displayColumns) ? m_displayColumns : m_displayIds.size();
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::currentDisplayRows() const{
    return (m_displayIds.size() + m_displayColumns - 1)/m_displayColumns;
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::maxDisplayColumns() const{
    return m_displayColumns;
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::maxDisplayRows() const{
    return m_displayRows;
}

template<typename T>
std::vector<T>& VectorWithDisplayGrid<T>::getVector(){
    return m_vector;
}

template<typename T>
const std::vector<T>& VectorWithDisplayGrid<T>::getVector() const{
    return m_vector;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isDisplayedElementSelected(const unsigned int& displayPosition) const{
    
    if(!m_selectIndex_o){
        return false;
    }
    return m_selectIndex_o.value() != displayPosition;
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftLeft(){

    for(int i = 0; i < m_displayIds.size()-1; i++){
        m_displayIds.at(i) = m_displayIds.at(i+1);
    }

    auto isDisplayed = [this](const int& id){
        for(int i = 0; i < m_displayIds.size()-1; i++){
            if(m_displayIds.at(i) == id){
                return true;
            }
        }
        return false;
    };

    {
        unsigned int backId = m_displayIds.back();
        backId = (backId+1)%(unsigned int)m_vector.size();
        while(backId != m_displayIds.back()){
            if(!isDisplayed(backId)){
                m_displayIds.back() = backId;
                break;
            }

            backId = (backId+1)%(unsigned int)m_vector.size();
        }
    }
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftRight(){

    for(int i = m_displayIds.size()-1; i > 0; i--){
        m_displayIds.at(i) = m_displayIds.at(i-1);
    }

    auto isDisplayed = [this](const int& id){
        for(int i = 1; i < m_displayIds.size(); i++){
            if(m_displayIds.at(i) == id){
                return true;
            }
        }
        return false;
    };

    {
        int frontId = m_displayIds.front();
        frontId = (m_vector.size()+frontId-1)%m_vector.size();
        
        while(frontId != m_displayIds.front()){
            if(!isDisplayed(frontId)){
                m_displayIds.front() = frontId;
                break;
            }

            frontId = (m_vector.size()+frontId-1)%m_vector.size();
        }
    }
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftUp(){

    if(isOneRowDisplayed()){
        return false;
    }

    for(auto it = m_displayIds.begin(); it != m_displayIds.end(); it++){
        unsigned int newId = *it + m_displayColumns;
        if(newId >= (unsigned int)m_vector.size()){
            m_displayIds.erase(it, m_displayIds.end());
            m_selectIndex_o = (unsigned int)m_displayIds.size() - 1;
            break;
        }
        *it = newId;
    }
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftDown(){

    if(isOneRowDisplayed()){
        return false;
    }

    for(auto& id : m_displayIds){
        id -= m_displayColumns;
    }

    for(int i = m_displayIds.size(); i < m_displayRows*m_displayColumns; i++){
        int id = m_displayIds.back()+1;
        m_displayIds.push_back(id);
    }
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::selectLeft(){

    if(!m_selectIndex_o){
        return false;
    }

    if(m_vector.size() < 2){
        return false;
    }

    if(m_displayIds.size() < 2){
        unsigned int& id = m_displayIds.at(0);

        if(id == 0){
            if(m_multiRowStartEndWrap){
                id = (unsigned int)m_vector.size()-1;
                return true;
            }
            return false;
        }
        id--;
        return true;
    }

    auto& selectIndex = m_selectIndex_o.value();

    if(isFirstElement(selectIndex)){
    // First Element
        if(isOneRowDisplayed()){
             if(m_singleRowStartEndWrap){
                displayLastElements();
                m_selectIndex_o = (unsigned int)m_displayIds.size()-1;
                return true;
            }
            return false;
        }

        switch(m_multiRowHorisontalWrap){
            case WRAP_OFF:
                return false;
            case WRAP_ON:
            {
                m_selectIndex_o = m_selectIndex_o.value() + m_displayColumns - 1;
                if(m_selectIndex_o.value() > (unsigned int)m_displayIds.size()-1){
                    m_selectIndex_o = (unsigned int)m_displayIds.size()-1;
                }
                return true;
            }
            case NEXTWRAP_ON:
            {
                if(m_multiRowStartEndWrap){
                    displayLastElements();
                    m_selectIndex_o = (unsigned int)m_displayIds.size()-1;
                    return true;
                }
                return false;
            }
        }
    }

    if(!isLeftDisplayColumn(selectIndex)){
    // Normal case: Not far left, Not first element
        m_selectIndex_o = m_selectIndex_o.value() - 1;
        return true;
    }

    if(!isTopDisplayRow(selectIndex)){
    // Far left, but NOT top display row
        switch(m_multiRowHorisontalWrap){
            case WRAP_OFF:
                return false;
            case WRAP_ON:
            {
                m_selectIndex_o = m_selectIndex_o.value() + m_displayColumns - 1;
                if(m_selectIndex_o.value() > (unsigned int)m_displayIds.size()-1){
                    m_selectIndex_o = (unsigned int)m_displayIds.size()-1;
                }
                return true;
            }
            case NEXTWRAP_ON:
            {
                m_selectIndex_o = m_selectIndex_o.value() -1;
                return true;
            }
        }
    }

    // Far left AND top display, but NOT first element
    if(m_displayRows == 1){
        return shiftRight();
    }

    switch(m_multiRowHorisontalWrap){
        case WRAP_OFF:
            return false;
        case WRAP_ON:
        {
            m_selectIndex_o = m_selectIndex_o.value() + m_displayColumns - 1;
            if(m_selectIndex_o.value() > (unsigned int)m_displayIds.size()-1){
                m_selectIndex_o = (unsigned int)m_displayIds.size()-1;
            }
            return true;
        }
        case NEXTWRAP_ON:
        {
            for(auto& id : m_displayIds){
                id -= m_displayColumns;
            }
            for(int i = m_displayIds.size(); i < m_displayRows*m_displayColumns; i++){
                int id = m_displayIds.back()+1;
                m_displayIds.push_back(id);
            }
            m_selectIndex_o = m_displayColumns-1;
            return true;
        }
    }
    
    return false; //Should never be reached
}

template<typename T>
bool VectorWithDisplayGrid<T>::selectRight(){

    if(!m_selectIndex_o){
        return false;
    }

    if(m_vector.size() < 2){
        return false;
    }

    if(m_displayIds.size() < 2){
        unsigned int& id = m_displayIds.at(0);

        if(id == (unsigned int)m_vector.size()-1){
            if(m_singleRowStartEndWrap){
                id = 0;
                return true;
            }
            return false;
        }
        id++;

        return true;
    }

    auto& selectIndex = m_selectIndex_o.value();

    if(isLastElement(selectIndex)){
    // Last Element
        if(isOneRowDisplayed()){
            if(m_singleRowStartEndWrap){
                displayFirstElements();
                m_selectIndex_o = 0;
                return true;
            }
            return false;
        }

        switch(m_multiRowHorisontalWrap){
            case WRAP_OFF:
                return false;
            case WRAP_ON:
            {
                m_selectIndex_o = selectIndex - selectIndex % m_displayColumns;
                return true;
            }
            case NEXTWRAP_ON:
            {
                if(m_multiRowStartEndWrap){
                    displayFirstElements();
                    m_selectIndex_o = 0;
                    return true;
                }
                return false;
            }
        }
    }

    if(!isRightDisplayColumn(selectIndex)){
    // Normal case: Not far right, Not last element
        m_selectIndex_o = m_selectIndex_o.value() + 1;
        return true;
    }

    if(!isBottomDisplayRow(selectIndex)){
    // Far right, but NOT bottom display row
        switch(m_multiRowHorisontalWrap){
            case WRAP_OFF:
                return false;
            case WRAP_ON:
            {
                m_selectIndex_o = selectIndex - selectIndex % m_displayColumns;
                return true;
            }
            case NEXTWRAP_ON:
            {
                m_selectIndex_o = m_selectIndex_o.value() + 1;
                return true;
            }
        }
    }

    // Far right AND bottom display row, but NOT last element
    if(m_displayRows == 1){
        return shiftLeft();
    }

    switch(m_multiRowHorisontalWrap){
        case WRAP_OFF:
            return false;
        case WRAP_ON:
        {
            m_selectIndex_o = selectIndex - selectIndex % m_displayColumns;
            return true;
        }
        case NEXTWRAP_ON:
        {
            for(auto it = m_displayIds.begin(); it != m_displayIds.end();it++){
                int newId = *it + m_displayColumns;
                if(newId >= (unsigned int)m_vector.size()){
                    m_displayIds.erase(it, m_displayIds.end());
                    break;
                }
                *it = newId;
            }
            m_selectIndex_o = m_selectIndex_o.value() + 1 - m_displayColumns;       
            return true;
        }
    }
    
    return false; //Should never be reached
}

template<typename T>
bool VectorWithDisplayGrid<T>::selectUp(){

    if(!m_selectIndex_o){
        return false;
    }

    if(isOneRowDisplayed()){
        return false;
    }

    auto& selectIndex = m_selectIndex_o.value();

    if(!isTopDisplayRow(selectIndex)){
        m_selectIndex_o = m_selectIndex_o.value() - m_displayColumns;
        return true;
    }

    if(isTopRow(selectIndex)){
        if(m_verticalWrap){
            displayLastElements();
        
            int oldX = selectIndex % m_displayColumns;
            int lastX = ((unsigned int)m_vector.size() - 1) % m_displayColumns;

            m_selectIndex_o = (unsigned int)m_displayIds.size() - 1;
            if(oldX < lastX){
                m_selectIndex_o = m_selectIndex_o.value() + oldX - lastX;
            }
            return true;
        }
        return false;
    }
    
    return shiftDown();
}

template<typename T>
bool VectorWithDisplayGrid<T>::selectDown(){

    if(!m_selectIndex_o){
        return false;
    }
    
    if(isOneRowDisplayed()){
        return false;
    }

    auto& selectIndex = m_selectIndex_o.value();

    if(!isBottomDisplayRow(selectIndex)){
        unsigned int newId = selectIndex + m_displayColumns;
        if(newId > (unsigned int)m_displayIds.size() - 1){
            newId = (unsigned int)m_displayIds.size() - 1;
        }
        m_selectIndex_o = newId;
        return true;
    }

    if(isBottomRow(selectIndex)){
        if(m_verticalWrap){
            displayFirstElements();
            m_selectIndex_o = selectIndex % m_displayColumns;
            return true;
        }
        return false;
    }

    return shiftUp();
}

template<typename T>
bool VectorWithDisplayGrid<T>::isOneRowDisplayed() const{
    return m_displayRows == 1 ||
        (unsigned int)m_displayIds.size() <= m_displayColumns;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isLeftDisplayColumn(const unsigned int& displayIndex) const{
    return displayIndex % m_displayColumns == 0;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isRightDisplayColumn(const unsigned int& displayIndex) const{
    return displayIndex % m_displayColumns == m_displayColumns-1;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isTopDisplayRow(const unsigned int& displayIndex) const{
    return displayIndex < m_displayColumns;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isTopRow(const unsigned int& displayIndex) const{
    return m_displayIds.at(displayIndex) < m_displayColumns;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isBottomDisplayRow(const unsigned int& displayIndex) const{
    int displayRow = displayIndex/m_displayColumns;
    int bottomDisplayRow = ((unsigned int)m_displayIds.size()-1)/m_displayColumns;
    return displayRow == bottomDisplayRow;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isBottomRow(const unsigned int& displayIndex) const{
    int displayRow = m_displayIds.at(displayIndex)/m_displayColumns;
    int bottomDisplayRow = ((unsigned int)m_vector.size()-1)/m_displayColumns;
    return displayRow == bottomDisplayRow;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isFirstElement(const unsigned int& displayIndex) const{
    return m_displayIds.at(displayIndex) == 0;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isLastElement(const unsigned int& displayIndex) const{
    return m_displayIds.at(displayIndex) == (unsigned int)m_vector.size()-1;
}

template<typename T>
void VectorWithDisplayGrid<T>::displayFirstElements(){

    m_displayIds.clear();
    for(int id = 0; id < m_displayColumns * m_displayRows; id++){
        if(id >= m_vector.size()){
            break;
        }
        m_displayIds.push_back(id);
    }
}

template<typename T>
void VectorWithDisplayGrid<T>::displayLastElements(){

    m_displayIds.clear();

    if(m_displayRows == 1){
        int lastId = m_vector.size()-1;
        int firstDisplayId = lastId - m_displayColumns + 1;
        if(firstDisplayId < 0){
            firstDisplayId = 0;
        }
        for(int id = firstDisplayId; id < m_vector.size(); id++){
            m_displayIds.push_back(id);
        }
        return;
    }
    
    int numColumns = m_displayColumns;
    if(numColumns > m_vector.size()){
        numColumns = m_vector.size();
    }
    int lastId = m_vector.size()-1;
    int lastX = (m_vector.size()-1)%numColumns;
    int maxDisplayBoards = numColumns*m_displayRows;
    if(maxDisplayBoards > m_vector.size()){
        maxDisplayBoards = m_vector.size();
    }
    int offsetX = numColumns - 1 - lastX;
    if(maxDisplayBoards == m_vector.size()){
        offsetX = 0;
    }
    int numDisplayBoards = maxDisplayBoards - offsetX;

    int topLeftId = lastId - numDisplayBoards + 1;

    if(topLeftId < 0){
        topLeftId = 0;
    }
    for(int id = topLeftId; id < m_vector.size(); id++){
        m_displayIds.push_back(id);
    }
}