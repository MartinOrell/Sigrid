#pragma once

#include "Pdf/Object.h"

namespace sigrid_pdf{

struct MediaBox : Object{

    unsigned int xPos = 0;
    unsigned int yPos = 0;
    unsigned int width = 595; //A4 width
    unsigned int height = 842; //A4 height

    std::string getString() const override;
};

}  // namespace sigrid_pdf