#pragma once

#include "List/Map.h"
#include "List/Vector.h"

namespace sigrid{namespace list{
    template <typename TKey, typename TValue> class OrderedMap{

        public:
            OrderedMap();

            void push_back(const TKey& key, const TValue& value);
            void insert(const unsigned int& position, const TKey& key, const TValue& value);
            void erase(const unsigned int& position);
            void erase(const TKey& key);
            void clear();

            const std::optional<std::reference_wrapper<const TKey>> keyAt(const unsigned int& position) const;
            std::optional<std::reference_wrapper<TValue>> atPosition(unsigned int& position);
            const std::optional<std::reference_wrapper<const TValue>> atPosition(const unsigned int& position) const;
            std::optional<std::reference_wrapper<TValue>> atKey(const TKey& key);
            const std::optional<std::reference_wrapper<const TValue>> atKey(const TKey& key) const;

            unsigned int size() const;

            void print() const;

        private:

            Map<TKey, TValue> m_map;
            Vector<TKey> m_order;

    };
}}