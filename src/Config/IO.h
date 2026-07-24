#pragma once

#include <string>
#include <istream>
#include <optional>

namespace sigrid_config{

std::optional<std::string> readString(std::istream& is);
std::optional<bool> readToggle(std::istream& is);

}  // namespace sigrid_config