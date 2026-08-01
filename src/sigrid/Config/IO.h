#pragma once

#include <cstdint>

#include <string>
#include <istream>
#include <optional>

namespace sigrid_config{

std::optional<int> stringToInt(const std::string& s);
std::optional<int> stringToValue(const std::string& s);

std::optional<uint32_t> stringToHex(const std::string& s);

}  // namespace sigrid_config