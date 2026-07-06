#include "Pdf/PageResources.h"

using namespace myPdf;

std::string Resources::getString() const{

    std::string s;
    s.append("  <<\n");
    s.append("    /ProcSet ");
    s.append(std::to_string(procedureSetObjectNumber));
    s.append(" 0 R\n");

    if(externalObjects.objectNumber > 0){
        s.append("    /XObject ");
        s.append(std::to_string(externalObjects.objectNumber));
        s.append(" 0 R\n");
    }

    s.append("  >>\n");

    return s;
}