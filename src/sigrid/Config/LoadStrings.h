#pragma once

#include <string>
#include <istream>

#include <sigrid/List/Vector.h>

namespace sigrid_config{

bool loadStrings(sigrid_list::Vector<std::string>& strings, std::istream& is);

}  // namespace sigrid_config