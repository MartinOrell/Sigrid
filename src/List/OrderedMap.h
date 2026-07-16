#pragma once

#include "List/Map.h"
#include "List/Vector.h"

namespace sigrid_list{

template <typename TKey, typename TValue> class OrderedMap{

  public:

    OrderedMap() = default;
    OrderedMap(const OrderedMap&) = default;
    OrderedMap(OrderedMap&&) = default;
    OrderedMap& operator=(const OrderedMap&) = default;
    OrderedMap& operator=(OrderedMap&&) = default;

    void push_back(const TKey& key, const TValue& value);
    void insert(const int& position, const TKey& key, const TValue& value);
    void erase(const int& position);
    void erase(const TKey& key);
    void clear();

    const std::optional<std::reference_wrapper<const TKey>> keyAt(const int& position) const;
    std::optional<std::reference_wrapper<TValue>> atPosition(int& position);
    const std::optional<std::reference_wrapper<const TValue>> atPosition(const int& position) const;
    std::optional<std::reference_wrapper<TValue>> atKey(const TKey& key);
    const std::optional<std::reference_wrapper<const TValue>> atKey(const TKey& key) const;

    int size() const;

    void print() const;

  private:

    Map<TKey, TValue> m_map;
    Vector<TKey> m_order;

};

}  // namespace sigrid_list