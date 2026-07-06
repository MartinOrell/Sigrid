#include "Pdf/ExternalObject.h"

using namespace myPdf;

std::string ExternalObject::getString() const{

    std::string s;
    s.append("  <<\n");
    s.append("    /Type /XObject\n");
    s.append("    /Subtype /Image\n");
    s.append("    /Width ");
    s.append(std::to_string(image.dataWidth));
    s.append("\n");
    s.append("    /Height ");
    s.append(std::to_string(image.dataHeight));
    s.append("\n");
    s.append("    /ColorSpace /DeviceRGB\n");
    s.append("    /BitsPerComponent 8\n");
    s.append("    /Length ");
    s.append(std::to_string(image.asciiHexStream.length()));
    s.append("\n");
    s.append("    /Filter /ASCIIHexDecode\n");
    s.append("  >>\n");

    s.append("  stream\n");
    s.append(image.asciiHexStream);
    s.append("\n");
    s.append("  endstream\n");

    return s;
}