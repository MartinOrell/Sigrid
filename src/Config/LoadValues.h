#pragma once

#include <istream>

#include <List/Vector.h>

namespace sigrid_config{

template <typename T>
bool loadValues(sigrid_list::Vector<T>& containers, std::istream& is);

}  // namespace sigrid_config

#include "Config/LoadValues.tpp"