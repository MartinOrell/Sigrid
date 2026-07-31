#pragma once

#include "sigrid/Pdf/Object.h"
#include "sigrid/Pdf/Image.h"

namespace sigrid_pdf{

struct ContentStream : Object{

    Image image;
    unsigned int imageId = 0;

    std::string getString() const override;

};

}  // namespace sigrid_pdf