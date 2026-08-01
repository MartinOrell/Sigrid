#pragma once

#include "sigrid/List/Vector.h"
#include "sigrid/Input/InputStream.h"

namespace sigrid_config{

template <typename T>
bool loadContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is);

}  // namespace sigrid_config

#include "sigrid/Config/LoadContainers.tpp"