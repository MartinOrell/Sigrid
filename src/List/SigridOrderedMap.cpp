#include "SigridOrderedMap.h"
#include "SigridOrderedMap_contentTypes.h"
// Any type used must be added in the SigridOrderedMap_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Sigrid2DList.h
// Both includes above can then be removed from this file

#include <iostream>

using namespace sigrid;

template<typename TKey, typename TValue>
SigridOrderedMap<TKey, TValue>::SigridOrderedMap(){}

template<typename TKey, typename TValue>
void SigridOrderedMap<TKey, TValue>::push_back(const TKey& key, const TValue& value){

    m_map.insert(key, value);
    m_order.push_back(key);
}

template<typename TKey, typename TValue>
void SigridOrderedMap<TKey, TValue>::insert(const unsigned int& position, const TKey& key, const TValue& value){

    m_map.insert(key, value);
    m_order.insert(position, key);
}

template<typename TKey, typename TValue>
void SigridOrderedMap<TKey, TValue>::erase(const unsigned int& position){

    auto key_o = m_order.at(position);

    if(key_o == std::nullopt){
        return;
    }
    auto& key = key_o.value().get();

    m_map.erase(key);
    m_order.erase(position);
}

template<typename TKey, typename TValue>
void SigridOrderedMap<TKey, TValue>::erase(const TKey& key){
    
    m_map.erase(key);

    for(auto it = m_order.begin(); it != m_order.end(); it++){
        if(*it == key){
            m_order.erase(it);
            break;
        }
    }
}

template<typename TKey, typename TValue>
void SigridOrderedMap<TKey, TValue>::clear(){

    m_map.clear();
    m_order.clear();
}

template<typename TKey, typename TValue>
const std::optional<std::reference_wrapper<const TKey>> SigridOrderedMap<TKey, TValue>::keyAt(const unsigned int& position) const{
    return m_order.at(position);
}

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<TValue>> SigridOrderedMap<TKey, TValue>::at(unsigned int& position){
    
    auto key_o = m_order.at(position);
    if(key_o == std::nullopt){
        return std::nullopt;
    }
    auto& key = key_o.value().get();

    return m_map.at(key);
}

template<typename TKey, typename TValue>
const std::optional<std::reference_wrapper<const TValue>> SigridOrderedMap<TKey, TValue>::at(const unsigned int& position) const{

    auto key_o = m_order.at(position);
    if(key_o == std::nullopt){
        return std::nullopt;
    }
    auto& key = key_o.value().get();

    return m_map.at(key);
}

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<TValue>> SigridOrderedMap<TKey, TValue>::at(const TKey& key){
    return m_map.at(key);
}

template<typename TKey, typename TValue>
const std::optional<std::reference_wrapper<const TValue>> SigridOrderedMap<TKey, TValue>::at(const TKey& key) const{
    return m_map.at(key);
}

template<typename TKey, typename TValue>
unsigned int SigridOrderedMap<TKey, TValue>::size() const{
    return m_map.size();
}

template<typename TKey, typename TValue>
void SigridOrderedMap<TKey, TValue>::print() const{

    std::cout << "Printing ordered map" << std::endl;
    if(m_order.size() != m_map.size()){
        std::cout << "Size of order and map does not match" << std::endl;
    }

    std::cout << "[ ";
    for(auto& key: m_order){

        std::cout << key << " ";

        auto value_o = m_map.at(key);
        if(value_o == std::nullopt){
            std::cout << "<value not found>" << std::endl;
        }
    }
    std::cout << "]" << std::endl;
}