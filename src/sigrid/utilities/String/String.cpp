#include "sigrid/utilities/String/String.h"

#include <iostream>
#include <sstream>
#include <cctype> //isdigit

namespace sigrid{

String::String(const char* cString){
    *this = cString;
}

String& String::operator=(const char* cString){
    m_string = cString;
    return *this;
}

void String::set(std::string&& string){
    m_string = std::move(string);
}

bool String::operator==(const String& rhs) const{
    return m_string == rhs.m_string;
}

bool String::operator==(const char* cString) const{
    return m_string == cString;
}

bool String::operator!=(const String& rhs) const{
    return m_string != rhs.m_string;
}

bool String::operator!=(const char* cString) const{
    return m_string != cString;
}

bool String::operator<(const String& rhs) const{
    return m_string < rhs.m_string;
}

bool String::operator<(const char* cString) const{
    return m_string < cString;
}

bool String::operator>(const String& rhs) const{
    return m_string > rhs.m_string;
}

bool String::operator>(const char* cString) const{
    return m_string > cString;
}

sigrid::String operator+(const sigrid::String& lhs, const sigrid::String& rhs){

    std::string stdResult = lhs.m_string + rhs.m_string;
    sigrid::String result;
    result.set(std::move(stdResult));
    return result;
}

sigrid::String operator+(const sigrid::String& lhs, const std::string& rhs){

    std::string stdResult = lhs.m_string + rhs;
    sigrid::String result;
    result.set(std::move(stdResult));
    return result;
}

sigrid::String operator+(const sigrid::String& lhs, const char* rhs){

    std::string stdResult = lhs.m_string + rhs;
    sigrid::String result;
    result.set(std::move(stdResult));
    return result;
}

std::ostream& operator<<(std::ostream& os, const sigrid::String& s){
    return os << s.m_string;
}

int String::length() const{
    return (int)m_string.length();
}

const std::optional<std::reference_wrapper<const char>> String::at(const int& position) const{

    if(position < 0){
        return std::nullopt;
    }

    if(position >= m_string.size()){
        return std::nullopt;
    }

    return m_string.at(position);
}

std::string String::getStdString() const{
    return m_string;
}

void String::append(const sigrid::String& s){
    m_string.append(s.getStdString());
}

 bool String::insert(const int& index, const int& count, const char& c){

    if(index < 0){
        return false;
    }

    if(count < 0){
        return false;
    }

    try{
        m_string.insert(index, count, c);
    }
    catch(...){
        return false;
    }
    return true;
 }

bool String::insert(const int& index, const sigrid::String& s){

    if(index < 0){
        return false;
    }

    m_string.insert(index, s.getStdString());
    return true;
}

bool String::erase(const int& index, const int& count){

    std::string::size_type stdIndex;
    try{
        stdIndex = index;
    }
    catch(...){
        return false;
    }

    std::string::size_type stdCount;
    if(count < 0){
        stdCount = std::string::npos;
    }
    else{
        try{
            stdCount = count;
        }
        catch(...){
            return false;
        }
    }

    try{
        m_string.erase(stdIndex, stdCount);
    }
    catch(...){
        return false;
    }
    return true;
}

void String::push_back(const char& c){
    m_string.push_back(c);
}

bool String::pop_back(){

    if(m_string.size() == 0){
        return false;
    }
    m_string.pop_back();
    return true;
}

bool String::isUpper(){

    for(auto& c: m_string){
        if(!std::isupper(c)){
            return false;
        }
    }
    return true;
}

void String::toUpper(){

    for(auto& c: m_string){
        std::toupper(c);
    }
}

sigrid::String String::getUpper() const{

    sigrid::String upper{*this};
    upper.toUpper();
    return upper;
}

void String::toLower(){

    for(auto& c: m_string){
        std::tolower(c);
    }
}

bool String::isDigits() const{

    if(m_string.length() == 0){
        return false;
    }

    for(const auto& c: m_string){
        if(!std::isdigit(c)){
            return false;
        }
    }
    return true;
}

std::optional<int> String::toInt() const{

    int value;
    try{
        value = std::stoi(m_string);
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<int> String::toValue() const{
    return toInt();
}

std::optional<uint32_t> String::toHex() const{

    uint32_t value;
    std::stringstream ss;
    try{
        ss << std::hex << m_string;
        ss >> value;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<int> String::find(const char& c, const int& pos) const{

    auto stdResult = m_string.find(c, pos);
    if(stdResult == std::string::npos){
        return std::nullopt;
    }
    return (int)stdResult;
}

std::optional<int> String::rfind(const char& c) const{

    auto stdResult = m_string.rfind(c);
    if(stdResult == std::string::npos){
        return std::nullopt;
    }
    return (int)stdResult;
}

std::optional<String> String::substr(const int& pos, const int& count) const{

    std::string::size_type stdPos;
    try{
        stdPos = pos;
    }
    catch(...){

        std::cerr << "String: Failed to convert position " << pos
            << " into size type."
            << " Failed to get substring from \"" << m_string << "\"" << std::endl;
        return std::nullopt;
    }

    std::string::size_type stdCount;
    if(count < 0){
        stdCount = std::string::npos;
    }
    else{
        try{
            stdCount = count;
        }
        catch(...){

            std::cerr << "String: Failed to convert count " << count
                << " into size type."
                << " Failed to get substring from \"" << m_string << "\"" << std::endl;
            return std::nullopt;
        }
    }

    std::string stdSubstr;
    try{
        stdSubstr = m_string.substr(stdPos, stdCount);
    }
    catch(...){
        std::cerr << "String: Failed standard library call to substr."
            << " Failed to get substring from \"" << m_string << "\""
            << " with position " << pos << " and count " << count << std::endl;
        return std::nullopt;
    }

    if(stdSubstr == ""){
        std::cerr << "String: standard library string is empty after call to substr."
            << " Failed to get substring from \"" << m_string << "\""
            << " with position " << pos << " and count " << count << std::endl;
        return std::nullopt;
    }

    sigrid::String substr;
    substr.set(std::move(stdSubstr));
    return substr;
}

}  // namespace sigrid