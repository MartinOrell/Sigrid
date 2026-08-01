#pragma once

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Input/InputStream.h"

namespace sigrid_config{

template <typename T>
bool loadNamedContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is);

}  // namespace sigrid_config

#include "sigrid/Config/LoadNamedContainers.tpp"