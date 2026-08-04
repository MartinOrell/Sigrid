#pragma once

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

template <typename T>
bool loadContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is);

}  // namespace sigrid

#include "sigrid/utilities/lists/listLoaders/LoadContainers.tpp"