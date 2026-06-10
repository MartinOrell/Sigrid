#include "Pages.h"

using namespace myPdf;

std::string Pages::getString() const{
    
    std::string s;
    s.append("  <<\n");
    s.append("    /Type /Pages\n");
    s.append("    /Count ");
    s.append(std::to_string(kids.size()));
    s.append("\n");
    s.append("    /Kids [");
    for(auto it = kids.begin(); it != kids.end(); it++){
        auto& page = *it;
        if(it != kids.begin()){
            s.append(" ");
        }
        s.append(std::to_string(page.objectNumber));
        s.append(" 0 R");
    }
    s.append("]\n");
    s.append("  >>\n");

    return s;
}