#pragma once

#include <map>
#include <optional>
#include <functional> //Reference wrapper

namespace sigrid{

    template <typename TKey, typename TValue> class SigridMap{

        public:
            SigridMap();

            std::optional<std::reference_wrapper<TValue>> insert(const TKey& key, const TValue& value);

            std::optional<std::reference_wrapper<TValue>> at(const TKey& key);
            const std::optional<std::reference_wrapper<const TValue>> at(const TKey& key) const;

        private:
            
            std::map<TKey, TValue> m_map;
    };
}