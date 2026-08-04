#pragma once

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

template <typename T>
bool loadValueContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is);

}  // namespace sigrid_config

#include "sigrid/utilities/lists/listLoaders/LoadValueContainers.tpp"