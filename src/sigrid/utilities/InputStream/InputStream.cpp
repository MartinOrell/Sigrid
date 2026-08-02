#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

void InputStream::set(std::ifstream&& is){
    m_is = std::move(is);
}

bool InputStream::isEndOfFile(){
    return m_is.peek() == EOF;
}

std::optional<sigrid::String> InputStream::readString(){

    std::string s;
    try{
        m_is >> std::ws >> s;
    }
    catch(...){
        return std::nullopt;
    }
    
    if(s.front() == '"'){
        s.erase(0,1); //remove front '"'
        while(m_is.peek() != EOF){    
            std::string s2;
            try{
                m_is >> s2;
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

    m_is >> std::ws;

    sigrid::String retVal;
    retVal.set(std::move(s));
    return retVal;
}

std::optional<int> InputStream::readInt(){

    int value;
    try{
        m_is >> value;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<float> InputStream::readFloat(){

    float value;
    try{
        m_is >> value;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<float> InputStream::readPercentage(){

    auto float_o = readFloat();
    if(float_o == std::nullopt){
        return std::nullopt;
    }
    float f = float_o.value();

    m_is.ignore(1);// ignore % sign
    return f/100.f;
}

std::optional<uint32_t> InputStream::readHex(){

    uint32_t value;
    try{
        m_is >> std::hex >> value >> std::ws;
    }
    catch(...){
        return std::nullopt;
    }
    return value;
}

std::optional<bool> InputStream::readToggle(){

    auto string_o = readString();
    if(string_o == std::nullopt){
        return std::nullopt;
    }
    sigrid::String s = string_o.value();
    return s == "ON";
}

std::optional<bool> InputStream::readVisibility(){

    auto string_o = readString();
    if(string_o == std::nullopt){
        return std::nullopt;
    }
    sigrid::String s = string_o.value();
    return s == "Visible";
}

}  // namespace sigrid