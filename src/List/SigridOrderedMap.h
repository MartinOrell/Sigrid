#pragma once

#include "List/SigridMap.h"
#include "List/SigridVector.h"

namespace sigrid{namespace list{
    template <typename TKey, typename TValue> class SigridOrderedMap{

        public:
            SigridOrderedMap();

            void push_back(const TKey& key, const TValue& value);
            void insert(const unsigned int& position, const TKey& key, const TValue& value);
            void erase(const unsigned int& position);
            void erase(const TKey& key);
            void clear();

            const std::optional<std::reference_wrapper<const TKey>> keyAt(const unsigned int& position) const;
            std::optional<std::reference_wrapper<TValue>> at(unsigned int& position);
            const std::optional<std::reference_wrapper<const TValue>> at(const unsigned int& position) const;
            std::optional<std::reference_wrapper<TValue>> at(const TKey& key);
            const std::optional<std::reference_wrapper<const TValue>> at(const TKey& key) const;

            unsigned int size() const;

            void print() const;

        private:

            SigridMap<TKey, TValue> m_map;
            SigridVector<TKey> m_order;

    };
}}