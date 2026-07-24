#include "Config/IO.h"

#include <sstream>

std::optional<std::string> sigrid_config::readString(std::istream& is){

    std::string s;
    try{
        is >> std::ws >> s;
    }
    catch(...){
        return std::nullopt;
    }
    
    if(s.front() == '"'){
        s.erase(0,1); //remove front '"'
        while(is.peek() != EOF){    
            std::string s2;
            try{
                is >> s2;
            }
            catch(...){
                return std::nullopt;
            }
            
            s.append(" " + s2);
            if(s2.back() == '"'){
                s.pop_back(); //remove back '"'
                break;
            }
        }
    }

    is >> std::ws;
    return s;
}

std::optional<int> sigrid_config::readInt(std::istream& is){

    int value;
    try{
        is >> value;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<float> sigrid_config::readFloat(std::istream& is){

    float value;
    try{
        is >> value;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<bool> sigrid_config::readToggle(std::istream& is){

    auto string_o = readString(is);
    if(string_o == std::nullopt){
        return std::nullopt;
    }
    std::string s = string_o.value();
    return s == "ON";
}

std::optional<uint32_t> sigrid_config::readHex(std::istream& is){

    uint32_t value;
    try{
        is >> std::hex >> value >> std::ws;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
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