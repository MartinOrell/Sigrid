#include "List/Map.h"
#include "List/Map_contentTypes.h"
// Any type used must be added in the Map_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Map.h
// Both includes above can then be removed from this file

using namespace sigrid::list;

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<TValue>> Map<TKey, TValue>::insert(const TKey& key, const TValue& value){
    
    auto result = m_map.insert(std::pair{key, value});
    if(!result.second){
        return std::nullopt;
    }
    return result.first->second;
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::erase(const TKey& key){
    m_map.erase(key);
}

template<typename TKey, typename TValue>
typename std::map<TKey, TValue>::iterator Map<TKey, TValue>::erase(const typename std::map<TKey, TValue>::iterator& iterator){
    return m_map.erase(iterator);
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::clear(){
    m_map.clear();
}

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<TValue>> Map<TKey, TValue>::at(const TKey& key){

    auto it = m_map.find(key);

    if(it == m_map.end()){
        return std::nullopt;
    }

    return it->second;
}

template<typename TKey, typename TValue>
const std::optional<std::reference_wrapper<const TValue>> Map<TKey, TValue>::at(const TKey& key) const{

    auto it = m_map.find(key);

    if(it == m_map.end()){
        return std::nullopt;
    }

    return it->second;
}

template<typename TKey, typename TValue>
int Map<TKey, TValue>::size() const{
    return m_map.size();
}

template<typename TKey, typename TValue>
typename std::map<TKey, TValue>::iterator Map<TKey, TValue>::begin(){
    return m_map.begin();
}

template<typename TKey, typename TValue>
typename std::map<TKey, TValue>::const_iterator Map<TKey, TValue>::begin() const{
    return m_map.cbegin();
}

template<typename TKey, typename TValue>
typename std::map<TKey, TValue>::iterator Map<TKey, TValue>::end(){
    return m_map.end();
}

template<typename TKey, typename TValue>
typename std::map<TKey, TValue>::const_iterator Map<TKey, TValue>::end() const{
    return m_map.cend();
}