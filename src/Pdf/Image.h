#pragma once

#include <string>

namespace sigrid_pdf{

    struct Image{
        unsigned int dataWidth = 0;
        unsigned int dataHeight = 0;
        unsigned int displayWidth = 0;
        unsigned int displayHeight = 0;
        unsigned int xPos = 0;
        unsigned int yPos = 0;
        std::string asciiHexStream = "";
    };
}