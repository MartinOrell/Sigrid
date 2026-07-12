#include "List/Vector.h"
#include "List/Vector_contentTypes.h"
// Any type used must be added in the Vector_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Vector.h
// Both includes above can then be removed from this file

using namespace sigrid::list;

template <typename T> 
void Vector<T>::push_back(const T& value){
    m_vector.push_back(value);
}

template <typename T> 
void Vector<T>::insert(const int& position, const T& value){

    if(position < 0){
        return;
    } 
    m_vector.insert(m_vector.begin() + position, value);
}

template <typename T> 
void Vector<T>::pop_back(){
    m_vector.pop_back();
}

template <typename T> 
void Vector<T>::erase(const int& position){

    if(position < 0){
        return;
    }

    if(position >= m_vector.size()){
        return;
    }

    m_vector.erase(m_vector.begin() + position);
}

template <typename T> 
void Vector<T>::eraseFrom(const int& position){

    if(position < 0){
        return;
    }

    if(position >= m_vector.size()){
        return;
    }

    m_vector.erase(m_vector.begin() + position, m_vector.end());
}

template<typename T>
typename std::vector<T>::iterator Vector<T>::erase(const typename std::vector<T>::iterator& iterator){
    return m_vector.erase(iterator);
}

template <typename T> 
void Vector<T>::clear(){
    m_vector.clear();
}

template<typename T>
std::optional<std::reference_wrapper<T>> Vector<T>::front(){

    if(m_vector.size() == 0){
        return std::nullopt;
    }

    return m_vector.front();
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Vector<T>::front() const{
    
    if(m_vector.size() == 0){
        return std::nullopt;
    }

    return m_vector.front();
}

template<typename T>
std::optional<std::reference_wrapper<T>> Vector<T>::back(){

    if(m_vector.size() == 0){
        return std::nullopt;
    }

    return m_vector.back();
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Vector<T>::back() const{
    
    if(m_vector.size() == 0){
        return std::nullopt;
    }

    return m_vector.back();
}

template<typename T>
std::optional<std::reference_wrapper<T>> Vector<T>::at(const int& position){

    if(position < 0){
        return std::nullopt;
    }

    if(position >= m_vector.size()){
        return std::nullopt;
    }

    return m_vector.at(position);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> Vector<T>::at(const int& position) const{
    
    if(position < 0){
        return std::nullopt;
    }

    if(position >= m_vector.size()){
        return std::nullopt;
    }

    return m_vector.at(position);
}

template <typename T> 
int Vector<T>::size() const{
    return (int)m_vector.size();
}

template<typename T>
typename std::vector<T>::iterator Vector<T>::begin(){
    return m_vector.begin();
}

template<typename T>
typename std::vector<T>::const_iterator Vector<T>::begin() const{
    return m_vector.cbegin();
}

template<typename T>
typename std::vector<T>::iterator Vector<T>::end(){
    return m_vector.end();
}

template<typename T>
typename std::vector<T>::const_iterator Vector<T>::end() const{
    return m_vector.cend();
}