#pragma once

#include "ContentStream.h"

using namespace myPdf;

std::string ContentStream::getString() const{
    
    std::string stream;

    stream.append("    q\n");
    stream.append("      ");
    stream.append(std::to_string(image.displayWidth));
    stream.append(" 0 0 ");
    stream.append(std::to_string(image.displayHeight));
    stream.append(" ");
    stream.append(std::to_string(image.xPos));
    stream.append(" ");
    stream.append(std::to_string(image.yPos));
    stream.append(" cm\n");
    stream.append("      /Image");
    stream.append(std::to_string(imageId));
    stream.append(" Do\n");
    stream.append("    Q\n");
    
    std::string s;

    s.append("  <<\n");
    s.append("    /Length ");
    s.append(std::to_string(stream.length()));
    s.append("\n");
    s.append("  >>\n");
    s.append("  stream\n");
    s.append(stream);
    s.append("  endstream\n");
    
    return s;
}