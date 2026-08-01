#pragma once

#include <string>

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Input/InputStream.h"

namespace sigrid_config{

bool loadStrings(sigrid_list::Vector<std::string>& strings, sigrid::InputStream& is);

}  // namespace sigrid_config