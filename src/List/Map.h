#pragma once

#include <map>
#include <optional>
#include <functional> //Reference wrapper

namespace sigrid{namespace list{

    template <typename TKey, typename TValue> class Map{

        public:
            Map();

            std::optional<std::reference_wrapper<TValue>> insert(const TKey& key, const TValue& value);
            void erase(const TKey& key);
            typename std::map<TKey, TValue>::iterator erase(const typename std::map<TKey, TValue>::iterator& iterator);
            void clear();

            std::optional<std::reference_wrapper<TValue>> at(const TKey& key);
            const std::optional<std::reference_wrapper<const TValue>> at(const TKey& key) const;

            unsigned int size() const;

            typename std::map<TKey, TValue>::iterator begin();
            typename std::map<TKey, TValue>::const_iterator begin() const;
            typename std::map<TKey, TValue>::iterator end();
            typename std::map<TKey, TValue>::const_iterator end() const;

        private:
            
            std::map<TKey, TValue> m_map;
    };
}}