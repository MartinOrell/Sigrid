#pragma once

#include <string>
#include <istream>

namespace sigrid_config{

std::string readString(std::istream& is);
bool readToggle(std::istream& is);

}  // namespace sigrid_config