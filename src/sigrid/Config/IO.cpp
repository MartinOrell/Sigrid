#include "sigrid/Config/IO.h"

#include <sstream>

std::optional<int> sigrid_config::stringToInt(const std::string& s){

    int value;
    try{
        value = std::stoi(s);
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<int> sigrid_config::stringToValue(const std::string& s){
    return stringToInt(s);
}

std::optional<uint32_t> sigrid_config::stringToHex(const std::string& s){

    uint32_t value;
    std::stringstream ss;
    try{
        ss << std::hex << s;
        ss >> value;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}