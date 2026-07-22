#include "Config/IO.h"

std::string sigrid_config::readString(std::istream& is){

    std::string s;
    is >> std::ws >> s;
    if(s.front() == '"'){
        s.erase(0,1); //remove front '"'
        while(is.peek() != EOF){    
            std::string s2;
            is >> s2;
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

bool sigrid_config::readToggle(std::istream& is){

    std::string s;
    is >> s;
    return s == "ON";
}