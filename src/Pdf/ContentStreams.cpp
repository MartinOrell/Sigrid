#include "ContentStreams.h"

using namespace myPdf;

std::string ContentStreams::getString() const{

    std::string s;
    s.append("  [\n");
    for(auto& stream: streams){
        s.append("    ");
        s.append(std::to_string(stream.objectNumber));
        s.append(" 0 R\n");
    }
    s.append("  ]\n");

    return s;
}