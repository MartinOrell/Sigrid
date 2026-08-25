#include "sigrid/Pdf/ContentStreams.h"

std::string sigrid_pdf::ContentStreams::getString() const{

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