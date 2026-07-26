#pragma once

#include <istream>

#include <List/Vector.h>

namespace sigrid_config{

template <typename T>
bool loadContainers(sigrid_list::Vector<T>& containers, std::istream& is);

}  // namespace sigrid_config

#include "Config/LoadContainers.tpp"