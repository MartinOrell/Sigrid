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

    if(m_activeIndex < 0){
        m_activeIndex = 0;
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
void Sigrid2DList<T>::selectLast(){
    m_activeIndex = m_displayIds.size()-1;
}

template<typename T>
void Sigrid2DList<T>::select(const unsigned int& displayPosition){
    m_activeIndex = displayPosition;
}

template<typename T>
T& Sigrid2DList<T>::at(const unsigned int& position){
    return m_vector.at(position);
}

template<typename T>
const T& Sigrid2DList<T>::at(const unsigned int& position) const{
    return m_vector.at(position);
}

template<typename T>
T& Sigrid2DList<T>::atDisplay(const unsigned int& displayPosition){
    return m_vector.at(m_displayIds.at(displayPosition));
}

template<typename T>
const T& Sigrid2DList<T>::atDisplay(const unsigned int& displayPosition) const{
    return m_vector.at(m_displayIds.at(displayPosition));
}

template<typename T>
T& Sigrid2DList<T>::atActive(){
    return m_vector.at(m_displayIds.at(m_activeIndex));
}

template<typename T>
const T& Sigrid2DList<T>::atActive() const{
    return m_vector.at(m_displayIds.at(m_activeIndex));
}

template<typename T>
unsigned int& Sigrid2DList<T>::activeDisplayIndex(){
    return m_displayIds.at(m_activeIndex);
}

template<typename T>
const unsigned int& Sigrid2DList<T>::activeDisplayIndex() const{
    return m_displayIds.at(m_activeIndex);
}

template<typename T>
unsigned int Sigrid2DList<T>::size() const{
    return m_vector.size();
}

template<typename T>
unsigned int Sigrid2DList<T>::currentDisplaySize() const{
    return m_displayIds.size();
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
const std::vector<T>& Sigrid2DList<T>::getVector() const{
    return m_vector;
}

template<typename T>
bool Sigrid2DList<T>::isDisplayActive(const unsigned int& displayPosition) const{
    return m_activeIndex != displayPosition;
}

template<typename T>
bool Sigrid2DList<T>::shiftLeft(){

    if(m_vector.size() < 2){
        return false;
    }

    if(m_activeIndex == 0 &&
    m_displayIds.front() == 0){
        return false;
    }

    if(m_displayIds.size() == m_vector.size()
    || m_activeIndex % m_displayColumns != 0){
        m_activeIndex = (m_displayIds.size() + m_activeIndex - 1)%m_displayIds.size();
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

    if(m_vector.size() < 2){
        return false;
    }

    if(m_activeIndex == m_displayIds.size()-1 &&
    m_displayIds.back() == m_vector.size()-1){
        return false;
    }

    if(m_displayIds.size() == m_vector.size()
    || m_activeIndex % m_displayColumns != m_displayColumns - 1){
        m_activeIndex = (m_activeIndex + 1)%m_displayIds.size();
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
        int backId = m_displayIds.back();
        backId = (backId+1)%m_vector.size();
        while(backId != m_displayIds.back()){
            if(!isDisplayed(backId)){
                m_displayIds.back() = backId;
                break;
            }

            backId = (backId+1)%m_vector.size();
        }
    }
    return true;
}

template<typename T>
bool Sigrid2DList<T>::selectLeft(){

    if(m_displayRows == 1){
        return shiftLeft();
    }

    if(m_displayIds.size() < 2){
        unsigned int& id = m_displayIds.at(0);
        id = (m_vector.size() + id - 1)%m_vector.size();
        return true;
    }
    
    if(m_activeIndex > 0){
        m_activeIndex--;
        return true;
    }

    if(m_displayIds.at(0) == 0){
        displayLastElements();
        m_activeIndex = m_displayIds.size()-1;
        return true;
    }

    for(auto& id : m_displayIds){
        id -= m_displayColumns;
    }
    for(int i = m_displayIds.size(); i < m_displayRows*m_displayColumns; i++){
        int id = m_displayIds.back()+1;
        m_displayIds.push_back(id);
    }
    m_activeIndex = m_displayColumns-1;
    
    return true;
}

template<typename T>
bool Sigrid2DList<T>::selectRight(){

    if(m_displayRows == 1){
        return shiftRight();
    }

    if(m_displayIds.size() < 2){
        unsigned int& id = m_displayIds.at(0);
        id = (id + 1)%m_vector.size();
        return true;
    }

    if(m_activeIndex < m_displayIds.size()-1){
        m_activeIndex++;
        return true;
    }
    
    if(m_displayIds.back() == m_vector.size()-1){
        displayFirstElements();
        m_activeIndex = 0;
        return true;
    }
    
    for(auto it = m_displayIds.begin(); it != m_displayIds.end();it++){
        int newId = *it + m_displayColumns;
        if(newId >= m_vector.size()){
            m_displayIds.erase(it, m_displayIds.end());
            break;
        }
        *it = newId;
    }
    m_activeIndex += 1 - m_displayColumns;
    
    return true;
}

template<typename T>
bool Sigrid2DList<T>::selectUp(){

    if(m_displayRows < 2){
        return false;
    }

    if(m_displayIds.size() <= m_displayColumns){
        return false;
    }

    if(m_activeIndex > m_displayColumns-1){
        m_activeIndex -= m_displayColumns;
        return true;
    }


    if(m_displayIds.at(m_activeIndex) < m_displayColumns){
        displayLastElements();
        
        int oldX = m_activeIndex % m_displayColumns;
        int lastX = (m_vector.size() - 1) % m_displayColumns;

        m_activeIndex = m_displayIds.size() - 1;
        if(oldX < lastX){
            m_activeIndex += oldX - lastX;
        }
        return true;
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

    if(m_displayRows < 2){
        return false;
    }

    if(m_displayIds.size() <= m_displayColumns){
        return false;
    }

    if(m_activeIndex/m_displayColumns < (m_displayIds.size()-1)/m_displayColumns){
        int newId = m_activeIndex + m_displayColumns;
        if(newId > m_displayIds.size() - 1){
            newId = m_displayIds.size() - 1;
        }
        m_activeIndex = newId;
        return true;
    }

    if(m_displayIds.at(m_activeIndex)/m_displayColumns >= (m_vector.size()-1)/m_displayColumns){
        displayFirstElements();
        m_activeIndex = m_activeIndex % m_displayColumns;
        return true;
    }

    for(auto it = m_displayIds.begin(); it != m_displayIds.end(); it++){
        int newId = *it + m_displayColumns;
        if(newId >= m_vector.size()){
            m_displayIds.erase(it, m_displayIds.end());
            m_activeIndex = m_displayIds.size() - 1;
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