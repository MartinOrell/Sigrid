#include "Object.h"

using namespace myPdf;

std::string Object::getObjectString() const{

    std::string s;
    s.append(std::to_string(objectNumber));
    s.append(" 0 obj\n");
    if(description.length() > 0){
        s.append("  % ");
        s.append(description);
        s.append("\n");
    }
    s.append(getString());
    s.append("endobj\n\n");
    return s;
}