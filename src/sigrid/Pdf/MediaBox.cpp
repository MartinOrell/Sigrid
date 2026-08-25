#include "sigrid/Pdf/MediaBox.h"

std::string sigrid_pdf::MediaBox::getString() const{
    
    std::string s;
    s.append("  [");
    s.append(std::to_string(xPos));
    s.append(" ");
    s.append(std::to_string(yPos));
    s.append(" ");
    s.append(std::to_string(width));
    s.append(" ");
    s.append(std::to_string(height));
    s.append("]\n");

    return s;
}