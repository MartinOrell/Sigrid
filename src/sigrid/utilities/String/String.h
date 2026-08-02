#pragma once

#include <cstdint>

#include <string>
#include <optional>
#include <ostream>

namespace sigrid{

class String{

  public:

    String() = default;
    String(const String&) = default;
    String(String&&) = default;
    String& operator=(const String&) = default;
    String& operator=(String&&) = default;

    String(const char* cString);
    String& operator=(const char* cString);

    void set(std::string&& string);

    bool operator==(const String&) const;
    bool operator==(const char* cString) const;

    bool operator!=(const String&) const;
    bool operator!=(const char* cString) const;

    bool operator<(const String&) const;
    bool operator<(const char* cString) const;

    bool operator>(const String&) const;
    bool operator>(const char* cString) const;

    friend sigrid::String operator+(const sigrid::String& lhs, const sigrid::String& rhs);
    friend sigrid::String operator+(const sigrid::String& lhs, const std::string& rhs);
    friend sigrid::String operator+(const sigrid::String& lhs, const char* rhs);

    friend std::ostream& operator<<(std::ostream& os, const String& s);

    int length() const;

    const std::optional<std::reference_wrapper<const char>> at(const int& position) const;

    std::string getStdString() const;

    void append(const sigrid::String& s);
    bool insert(const int& index, const int& count, const char& c);
    bool insert(const int& index, const sigrid::String& s);
    bool erase(const int& index = 0, const int& count = -1);
    void push_back(const char& c);
    bool pop_back();

    bool isUpper();
    void toUpper();
    sigrid::String getUpper() const;

    void toLower();

    bool isDigits() const;
    std::optional<int> toInt() const;
    std::optional<int> toValue() const;

    std::optional<uint32_t> toHex() const;

    std::optional<int> find(const char& c, const int& pos = 0) const;
    std::optional<int> rfind(const char& c) const;

    std::optional<String> substr(const int& pos = 0, const int& count = -1) const;

  private:
    
    std::string m_string = "";
};

}  // namespace sigrid