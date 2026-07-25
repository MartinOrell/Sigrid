#pragma once

#include <cstdint>

#include <string>
#include <istream>
#include <optional>

namespace sigrid_config{

std::optional<std::string> readString(std::istream& is);
std::optional<int> readInt(std::istream& is);
std::optional<float> readFloat(std::istream& is);
std::optional<float> readPercentage(std::istream& is);
std::optional<bool> readToggle(std::istream& is);
std::optional<bool> readVisibility(std::istream& is);
std::optional<uint32_t> readHex(std::istream& is);

std::optional<int> stringToInt(const std::string& s);
std::optional<uint32_t> stringToHex(const std::string& s);

}  // namespace sigrid_config