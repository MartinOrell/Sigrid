#include "SigridMap.h"
#include "SigridMap_contentTypes.h"
// Any type used must be added in the SigridMap_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Sigrid2DList.h
// Both includes above can then be removed from this file

using namespace sigrid;

template<typename TKey, typename TValue>
SigridMap<TKey, TValue>::SigridMap(){}

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<TValue>> SigridMap<TKey, TValue>::insert(const TKey& key, const TValue& value){
    
    auto result = m_map.insert({key, value});
    if(!result.second){
        return std::nullopt;
    }
    return result.first->second;
}

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<TValue>> SigridMap<TKey, TValue>::at(const TKey& key){

    auto it = m_map.find(key);

    if(it == m_map.end()){
        return std::nullopt;
    }

    return it->second;
}

template<typename TKey, typename TValue>
const std::optional<std::reference_wrapper<const TValue>> SigridMap<TKey, TValue>::at(const TKey& key) const{

    auto it = m_map.find(key);

    if(it == m_map.end()){
        return std::nullopt;
    }

    return it->second;
}