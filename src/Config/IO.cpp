#include "Config/IO.h"

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

std::optional<bool> sigrid_config::readToggle(std::istream& is){

    auto string_o = readString(is);
    if(string_o == std::nullopt){
        return std::nullopt;
    }
    std::string s = string_o.value();
    return s == "ON";
}