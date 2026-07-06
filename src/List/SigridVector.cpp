#include "List/SigridVector.h"
#include "List/SigridVector_contentTypes.h"
// Any type used must be added in the SigridVector_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Sigrid2DList.h
// Both includes above can then be removed from this file

using namespace sigrid::list;

template <typename T> 
SigridVector<T>::SigridVector(){}

template <typename T> 
void SigridVector<T>::push_back(const T& value){
    m_vector.push_back(value);
}

template <typename T> 
void SigridVector<T>::insert(const unsigned int& position, const T& value){
    m_vector.insert(m_vector.begin() + position, value);
}

template <typename T> 
void SigridVector<T>::pop_back(){
    m_vector.pop_back();
}

template <typename T> 
void SigridVector<T>::erase(const unsigned int& position){

    if(position >= m_vector.size()){
        return;
    }

    m_vector.erase(m_vector.begin() + position);
}

template<typename T>
typename std::vector<T>::iterator SigridVector<T>::erase(const typename std::vector<T>::iterator& iterator){
    return m_vector.erase(iterator);
}

template <typename T> 
void SigridVector<T>::clear(){
    m_vector.clear();
}

template<typename T>
std::optional<std::reference_wrapper<T>> SigridVector<T>::back(){

    if(m_vector.size() == 0){
        return std::nullopt;
    }

    return m_vector.back();
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> SigridVector<T>::back() const{
    
    if(m_vector.size() == 0){
        return std::nullopt;
    }

    return m_vector.back();
}

template<typename T>
std::optional<std::reference_wrapper<T>> SigridVector<T>::at(const unsigned int& position){

    if(position >= m_vector.size()){
        return std::nullopt;
    }

    return m_vector.at(position);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> SigridVector<T>::at(const unsigned int& position) const{
    
    if(position >= m_vector.size()){
        return std::nullopt;
    }
    
    return m_vector.at(position);
}

template<typename T>
std::optional<std::reference_wrapper<T>> SigridVector<T>::at(const int& position){

    if(position < 0){
        return std::nullopt;
    }
    return at((unsigned int)position);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> SigridVector<T>::at(const int& position) const{
    
    if(position < 0){
        return std::nullopt;
    }
    return at((unsigned int)position);
}

template <typename T> 
unsigned int SigridVector<T>::size() const{
    return m_vector.size();
}

template<typename T>
typename std::vector<T>::iterator SigridVector<T>::begin(){
    return m_vector.begin();
}

template<typename T>
typename std::vector<T>::const_iterator SigridVector<T>::begin() const{
    return m_vector.cbegin();
}

template<typename T>
typename std::vector<T>::iterator SigridVector<T>::end(){
    return m_vector.end();
}

template<typename T>
typename std::vector<T>::const_iterator SigridVector<T>::end() const{
    return m_vector.cend();
}