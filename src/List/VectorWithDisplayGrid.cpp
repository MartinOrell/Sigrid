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
    return m_vector.at(position);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> VectorWithDisplayGrid<T>::at(const unsigned int& position) const{
    return m_vector.at(position);
}

template<typename T>
std::optional<std::reference_wrapper<T>> VectorWithDisplayGrid<T>::atDisplay(const unsigned int& displayPosition){

    auto id_o = m_displayIds.at(displayPosition);

    if(id_o == std::nullopt){
        return std::nullopt;
    }
    const auto& id = id_o.value().get();

    return at(id);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> VectorWithDisplayGrid<T>::atDisplay(const unsigned int& displayPosition) const{

    auto id_o = m_displayIds.at(displayPosition);

    if(id_o == std::nullopt){
        return std::nullopt;
    }
    const auto& id = id_o.value().get();

    return at(id);
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
    return m_vector.size();
}

template<typename T>
unsigned int VectorWithDisplayGrid<T>::currentDisplaySize() const{
    return m_displayIds.size();
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
bool VectorWithDisplayGrid<T>::isDisplayedElementSelected(const unsigned int& displayPosition) const{
    
    if(!m_selectIndex_o){
        return false;
    }
    return m_selectIndex_o.value() != displayPosition;
}

template<typename T>
typename std::vector<T>::iterator VectorWithDisplayGrid<T>::begin(){
    return m_vector.begin();
}

template<typename T>
typename std::vector<T>::const_iterator VectorWithDisplayGrid<T>::begin() const{
    return m_vector.begin();
}

template<typename T>
typename std::vector<T>::iterator VectorWithDisplayGrid<T>::end(){
    return m_vector.end();
}

template<typename T>
typename std::vector<T>::const_iterator VectorWithDisplayGrid<T>::end() const{
    return m_vector.end();
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftLeft(){

    for(unsigned int i = 0; i < m_displayIds.size()-1; i++){

        auto currentId_o = m_displayIds.at(i);
        if(currentId_o == std::nullopt){
            continue;
        }
        auto rightId_o = m_displayIds.at(i+1);
        if(rightId_o == std::nullopt){
            continue;
        }
        auto& currentId = currentId_o.value().get();
        const auto& rightId = rightId_o.value().get();

        currentId = rightId;
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
        auto backId_o = m_displayIds.back();
        if(backId_o == std::nullopt){
            return false;
        }
        auto& backId = backId_o.value().get();

        unsigned int newBackId = (backId+1)%m_vector.size();
        
        while(newBackId != backId){
            if(!isDisplayed(newBackId)){
                backId = newBackId;
                break;
            }

            newBackId = (newBackId+1)%m_vector.size();
        }
    }
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftRight(){

    for(int i = m_displayIds.size()-1; i > 0; i--){

        auto currentId_o = m_displayIds.at(i);
        if(currentId_o == std::nullopt){
            continue;
        }
        auto leftId_o = m_displayIds.at(i-1);
        if(leftId_o == std::nullopt){
            continue;
        }
        auto& currentId = currentId_o.value().get();
        const auto& leftId = leftId_o.value().get();

        currentId = leftId;
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
        auto frontId_o = m_displayIds.front();
        if(frontId_o == std::nullopt){
            return false;
        }
        auto& frontId = frontId_o.value().get();

        int newFrontId = (m_vector.size()+frontId-1)%m_vector.size();
        
        while(newFrontId != frontId){

            if(!isDisplayed(newFrontId)){
                frontId = newFrontId;
                break;
            }

            newFrontId = (m_vector.size()+newFrontId-1)%m_vector.size();
        }
    }
    return true;
}

template<typename T>
bool VectorWithDisplayGrid<T>::shiftUp(){

    if(isOneRowDisplayed()){
        return false;
    }

    for(unsigned int displayIndex = 0; displayIndex < m_displayIds.size(); displayIndex++){

        auto id_o = m_displayIds.at(displayIndex);
        if(id_o == std::nullopt){
            continue;
        }
        auto& id = id_o.value().get();

        unsigned int newId = id + m_displayColumns;

        if(newId >= m_vector.size()){
            m_displayIds.eraseFrom(displayIndex);
            m_selectIndex_o = m_displayIds.size() - 1;
            break;
        }

        id = newId;
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

        auto backId_o = m_displayIds.back();
        if(backId_o == std::nullopt){
            continue;
        }
        const auto& backId = backId_o.value().get();

        int id = backId+1;
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

        auto id_o = m_displayIds.at(0);
        if(id_o == std::nullopt){
            return false;
        }
        auto& id = id_o.value().get();

        if(id == 0){
            if(m_multiRowStartEndWrap){
                id = m_vector.size()-1;
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
                m_selectIndex_o = m_displayIds.size()-1;
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
                if(m_selectIndex_o.value() > m_displayIds.size()-1){
                    m_selectIndex_o = m_displayIds.size()-1;
                }
                return true;
            }
            case NEXTWRAP_ON:
            {
                if(m_multiRowStartEndWrap){
                    displayLastElements();
                    m_selectIndex_o = m_displayIds.size()-1;
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
                if(m_selectIndex_o.value() > m_displayIds.size()-1){
                    m_selectIndex_o = m_displayIds.size()-1;
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
            if(m_selectIndex_o.value() > m_displayIds.size()-1){
                m_selectIndex_o = m_displayIds.size()-1;
            }
            return true;
        }
        case NEXTWRAP_ON:
        {
            for(auto& id : m_displayIds){
                id -= m_displayColumns;
            }
            for(int i = m_displayIds.size(); i < m_displayRows*m_displayColumns; i++){

                auto backId_o = m_displayIds.back();
                if(backId_o == std::nullopt){
                    continue;
                }
                const auto& backId = backId_o.value();

                int id = backId+1;
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

        auto id_o = m_displayIds.at(0);
        if(id_o == std::nullopt){
            return false;
        }
        auto& id = id_o.value().get();

        if(id == m_vector.size()-1){
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

            for(unsigned int displayIndex = 0; displayIndex < m_displayIds.size(); displayIndex++){
                
                auto id_o = m_displayIds.at(displayIndex);
                if(id_o == std::nullopt){
                    continue;
                }
                auto& id = id_o.value().get();

                int newId = id + m_displayColumns;
                if(newId >= m_vector.size()){
                    m_displayIds.eraseFrom(displayIndex);
                    break;
                }

                id = newId;
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
            int lastX = (m_vector.size() - 1) % m_displayColumns;

            m_selectIndex_o = m_displayIds.size() - 1;
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
        if(newId > m_displayIds.size() - 1){
            newId = m_displayIds.size() - 1;
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
        m_displayIds.size() <= m_displayColumns;
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
    
    auto id_o = m_displayIds.at(displayIndex);
    if(id_o == std::nullopt){
        return false;
    }
    const auto& id = id_o.value().get();

    return id < m_displayColumns;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isBottomDisplayRow(const unsigned int& displayIndex) const{
    int displayRow = displayIndex/m_displayColumns;
    int bottomDisplayRow = (m_displayIds.size()-1)/m_displayColumns;
    return displayRow == bottomDisplayRow;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isBottomRow(const unsigned int& displayIndex) const{

    auto id_o = m_displayIds.at(displayIndex);
    if(id_o == std::nullopt){
        return false;
    }
    const auto& id = id_o.value().get();

    int displayRow = id/m_displayColumns;
    int bottomDisplayRow = (m_vector.size()-1)/m_displayColumns;
    return displayRow == bottomDisplayRow;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isFirstElement(const unsigned int& displayIndex) const{

    auto id_o = m_displayIds.at(displayIndex);
    if(id_o == std::nullopt){
        return false;
    }
    const auto& id = id_o.value().get();
    return id == 0;
}

template<typename T>
bool VectorWithDisplayGrid<T>::isLastElement(const unsigned int& displayIndex) const{

    auto id_o = m_displayIds.at(displayIndex);
    if(id_o == std::nullopt){
        return false;
    }
    const auto& id = id_o.value().get();

    return id == m_vector.size()-1;
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