#include "Sigrid2DList.h"
#include "Sigrid2DList_contenTypes.h"
// Any type used must be added in the Sigrid2DList_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Sigrid2DList.h
// Both includes above can then be removed from this file

using namespace sigrid;

template<typename T>
Sigrid2DList<T>::Sigrid2DList(){}

template<typename T>
void Sigrid2DList<T>::push_back(const T& value){
    
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
void Sigrid2DList<T>::addColumn(){
    m_displayColumns++;
    displayLastElements();
}

template<typename T>
void Sigrid2DList<T>::addRow(){
    m_displayRows++;
    displayLastElements();
}

template<typename T>
bool Sigrid2DList<T>::removeColumn(){

    if(m_displayColumns < 2){
        return false;
    }

    m_displayColumns--;

    displayLastElements();
    return true;
}

template<typename T>
bool Sigrid2DList<T>::removeRow(){

    if(m_displayRows < 2){
        return false;
    }

    m_displayRows--;

    displayLastElements();
    return true;
}

template<typename T>
bool Sigrid2DList<T>::selectLast(){

    const unsigned int displaySize = m_displayIds.size();
    if(displaySize == 0){
        m_selectIndex_o = std::nullopt;
        return false;
    }
    m_selectIndex_o = displaySize-1;
    return true;
}

template<typename T>
bool Sigrid2DList<T>::select(const unsigned int& displayPosition){

    const unsigned int displaySize = m_displayIds.size();
    if(displayPosition >= displaySize){
        m_selectIndex_o = std::nullopt;
        return false;
    }
    m_selectIndex_o = displayPosition;
    return true;
}

template<typename T>
std::optional<std::reference_wrapper<T>> Sigrid2DList<T>::at(const unsigned int& position){

    if(position >= m_vector.size()){
        return std::nullopt;
    }

    return m_vector.at(position);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Sigrid2DList<T>::at(const unsigned int& position) const{
    
    if(position >= m_vector.size()){
        return std::nullopt;
    }
    
    return m_vector.at(position);
}

template<typename T>
std::optional<std::reference_wrapper<T>> Sigrid2DList<T>::atDisplay(const unsigned int& displayPosition){

    if(displayPosition >= m_displayIds.size()){
        return std::nullopt;
    }

    return at(m_displayIds.at(displayPosition));
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Sigrid2DList<T>::atDisplay(const unsigned int& displayPosition) const{

    if(displayPosition >= m_displayIds.size()){
        return std::nullopt;
    }

    return at(m_displayIds.at(displayPosition));
}

template<typename T>
std::optional<std::reference_wrapper<T>> Sigrid2DList<T>::atSelection(){

    if(!m_selectIndex_o){
        return std::nullopt;
    }

    return atDisplay(m_selectIndex_o.value());
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Sigrid2DList<T>::atSelection() const{

    if(!m_selectIndex_o){
        return std::nullopt;
    }

    return atDisplay(m_selectIndex_o.value());
}

template<typename T>
std::optional<std::reference_wrapper<unsigned int>> Sigrid2DList<T>::activeDisplayIndex(){

    if(!m_selectIndex_o){
        return std::nullopt;
    }
    return m_displayIds.at(m_selectIndex_o.value());
}

template<typename T>
const std::optional<std::reference_wrapper<const unsigned int>> Sigrid2DList<T>::activeDisplayIndex() const{
    
    if(!m_selectIndex_o){
        return std::nullopt;
    }
    return m_displayIds.at(m_selectIndex_o.value());
}

template<typename T>
unsigned int Sigrid2DList<T>::size() const{
    return (unsigned int)m_vector.size();
}

template<typename T>
unsigned int Sigrid2DList<T>::currentDisplaySize() const{
    return (unsigned int)m_displayIds.size();
}

template<typename T>
unsigned int Sigrid2DList<T>::currentDisplayColumns() const{
    return (m_displayIds.size() > m_displayColumns) ? m_displayColumns : m_displayIds.size();
}

template<typename T>
unsigned int Sigrid2DList<T>::currentDisplayRows() const{
    return (m_displayIds.size() + m_displayColumns - 1)/m_displayColumns;
}

template<typename T>
unsigned int Sigrid2DList<T>::maxDisplayColumns() const{
    return m_displayColumns;
}

template<typename T>
unsigned int Sigrid2DList<T>::maxDisplayRows() const{
    return m_displayRows;
}

template<typename T>
std::vector<T>& Sigrid2DList<T>::getVector(){
    return m_vector;
}

template<typename T>
const std::vector<T>& Sigrid2DList<T>::getVector() const{
    return m_vector;
}

template<typename T>
bool Sigrid2DList<T>::isDisplayedElementSelected(const unsigned int& displayPosition) const{
    
    if(!m_selectIndex_o){
        return false;
    }
    return m_selectIndex_o.value() != displayPosition;
}

template<typename T>
bool Sigrid2DList<T>::shiftLeft(){

    if(!m_selectIndex_o){
        return false;
    }
    auto& selectIndex = m_selectIndex_o.value();

    if(m_vector.size() < 2){
        return false;
    }

    if(selectIndex == 0 &&
    m_displayIds.front() == 0){

        if(m_singleRowStartEndWrap){
            displayLastElements();
            m_selectIndex_o = (unsigned int)m_displayIds.size()-1;
            return true;
        }
        return false;
    }

    if(m_displayIds.size() == m_vector.size()
    || selectIndex % m_displayColumns != 0){
        m_selectIndex_o = ((unsigned int)m_displayIds.size() + selectIndex - 1)%(unsigned int)m_displayIds.size();
        return true;
    }

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
bool Sigrid2DList<T>::shiftRight(){

    if(!m_selectIndex_o){
        return false;
    }
    auto& selectIndex = m_selectIndex_o.value();

    if(m_vector.size() < 2){
        return false;
    }

    if(selectIndex == (unsigned int)m_displayIds.size()-1 &&
    m_displayIds.back() == m_vector.size()-1){

        if(m_singleRowStartEndWrap){
            displayFirstElements();
            m_selectIndex_o = 0;
            return true;
        }

        return false;
    }

    if(m_displayIds.size() == m_vector.size()
    || selectIndex % m_displayColumns != m_displayColumns - 1){
        m_selectIndex_o = (selectIndex + 1)%(unsigned int)m_displayIds.size();
        return true;
    }

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
bool Sigrid2DList<T>::selectLeft(){

    if(!m_selectIndex_o){
        return false;
    }
    auto& selectIndex = m_selectIndex_o.value();

    if(m_displayRows == 1){
        return shiftLeft();
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
    
    if(selectIndex > 0){
        if(selectIndex%m_displayColumns == 0){
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
        m_selectIndex_o = m_selectIndex_o.value() -1;
        return true;
    }

    if(m_displayIds.at(0) == 0){
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
bool Sigrid2DList<T>::selectRight(){

    if(!m_selectIndex_o){
        return false;
    }
    auto& selectIndex = m_selectIndex_o.value();

    if(m_displayRows == 1){
        return shiftRight();
    }

    if(m_displayIds.size() < 2){
        unsigned int& id = m_displayIds.at(0);

        if(id == (unsigned int)m_vector.size()-1){
            if(m_multiRowStartEndWrap){
                id = 0;
                return true;
            }
            return false;
        }
        id++;

        return true;
    }

    if(selectIndex < (unsigned int)m_displayIds.size()-1){

        if(selectIndex % m_displayColumns == m_displayColumns-1){
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

        m_selectIndex_o = m_selectIndex_o.value() + 1;
        return true;
    }
    
    if(m_displayIds.back() == (unsigned int)m_vector.size()-1){
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
bool Sigrid2DList<T>::selectUp(){

    if(!m_selectIndex_o){
        return false;
    }
    auto& selectIndex = m_selectIndex_o.value();

    if(m_displayRows < 2){
        return false;
    }

    if((unsigned int)m_displayIds.size() <= m_displayColumns){
        return false;
    }

    if(selectIndex > m_displayColumns-1){
        m_selectIndex_o = m_selectIndex_o.value() - m_displayColumns;
        return true;
    }


    if(m_displayIds.at(selectIndex) < m_displayColumns){
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
bool Sigrid2DList<T>::selectDown(){

    if(!m_selectIndex_o){
        return false;
    }
    auto& selectIndex = m_selectIndex_o.value();

    if(m_displayRows < 2){
        return false;
    }

    if((unsigned int)m_displayIds.size() <= m_displayColumns){
        return false;
    }

    if(selectIndex/m_displayColumns < ((unsigned int)m_displayIds.size()-1)/m_displayColumns){
        unsigned int newId = selectIndex + m_displayColumns;
        if(newId > (unsigned int)m_displayIds.size() - 1){
            newId = (unsigned int)m_displayIds.size() - 1;
        }
        m_selectIndex_o = newId;
        return true;
    }

    if(m_displayIds.at(selectIndex)/m_displayColumns >= ((unsigned int)m_vector.size()-1)/m_displayColumns){
        if(m_verticalWrap){
            displayFirstElements();
            m_selectIndex_o = selectIndex % m_displayColumns;
            return true;
        }
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
void Sigrid2DList<T>::displayFirstElements(){

    m_displayIds.clear();
    for(int id = 0; id < m_displayColumns * m_displayRows; id++){
        if(id >= m_vector.size()){
            break;
        }
        m_displayIds.push_back(id);
    }
}

template<typename T>
void Sigrid2DList<T>::displayLastElements(){

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