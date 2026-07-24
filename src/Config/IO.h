#pragma once

#include <cstdint>

#include <string>
#include <istream>
#include <optional>

namespace sigrid_config{

std::optional<std::string> readString(std::istream& is);
std::optional<bool> readToggle(std::istream& is);
std::optional<uint32_t> readHex(std::istream& is);

std::optional<uint32_t> stringToHex(const std::string& s);

}  // namespace sigrid_config