#include "ExternalObjects.h"

using namespace myPdf;

std::string ExternalObjects::getString() const{

    std::string s;
    s.append("  <<\n");
    for(int i = 0; i < xObjects.size(); i++){
        auto& xObject = xObjects.at(i);
        s.append("    /Image");
        s.append(std::to_string(i));
        s.append(" ");
        s.append(std::to_string(xObject.objectNumber));
        s.append(" 0 R\n");
    }
    s.append("  >>\n");

    return s;
}