#pragma once

#include <fstream>
#include <optional>

#include "sigrid/utilities/String/String.h"

namespace sigrid{

class InputStream{

  public:

    InputStream() = default;
    InputStream(const InputStream&) = default;
    InputStream(InputStream&&) = default;
    InputStream& operator=(const InputStream&) = default;
    InputStream& operator=(InputStream&&) = default;

    void set(std::ifstream&& is);
    
    bool isEndOfFile();

    std::optional<sigrid::String> readString();
    std::optional<int> readInt();
    std::optional<float> readFloat();
    std::optional<float> readPercentage();
    std::optional<uint32_t> readHex();
    std::optional<bool> readToggle();
    std::optional<bool> readVisibility();
    
  private:
    
    std::ifstream m_is;
};

}  // namespace sigrid

