#include "Pdf/Page.h"

using namespace myPdf;

std::string Page::getString() const{
    
    std::string s;
    s.append("  <<\n");
    s.append("    /Type /Page\n");
    s.append("    /Parent ");
    s.append(std::to_string(parentObjectNumber));
    s.append(" 0 R\n");
    s.append("    /MediaBox ");
    s.append(std::to_string(mediaBoxObjectNumber));
    s.append(" 0 R\n");

    if(resources.objectNumber > 0){
        s.append("    /Resources ");
        s.append(std::to_string(resources.objectNumber));
        s.append(" 0 R\n");
    }

    if(contents.objectNumber > 0){
        s.append("    /Contents ");
        s.append(std::to_string(contents.objectNumber));
        s.append(" 0 R\n");
    }

    s.append("  >>\n");

    return s;
}