#pragma once

#include <vector>
#include <optional>
#include <functional> //Reference wrapper

#include "sigrid/utilities/Coord/Coord.h"

namespace sigrid_list{

template <typename T> class Vector2D{

  public:

    Vector2D() = default;
    Vector2D(const Vector2D&) = default;
    Vector2D(Vector2D&&) = default;
    Vector2D& operator=(const Vector2D&) = default;
    Vector2D& operator=(Vector2D&&) = default;

    void addColumn();
    bool push_back(const int& x, const T& value);

    bool insert(const sigrid_coord::Coord& position, const T& value);
    bool erase(const sigrid_coord::Coord& position);
    void clear();

    std::optional<std::reference_wrapper<T>> at(const sigrid_coord::Coord& position);
    const std::optional<std::reference_wrapper<const T>> at(const sigrid_coord::Coord& position) const;

    int numColumns() const;
    int numRows(const int& x) const;
  private:

    std::vector<std::vector<T>> m_vector;
};

}  // namespace sigrid_list