#include "Catalog.h"

using namespace myPdf;

std::string Catalog::getString() const{
    std::string s;
    s.append("  <<\n");
    s.append("    /Type /Catalog\n");
    s.append("    /Pages ");
    s.append(std::to_string(pages.objectNumber));
    s.append(" 0 R\n");
    s.append("  >>\n");
    return s;
}