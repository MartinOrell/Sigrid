#pragma once

#include "Pdf/Object.h"
#include "Pdf/Image.h"

namespace myPdf{

    struct ContentStream : Object{

        Image image;
        unsigned int imageId = 0;

        std::string getString() const override;

    };
}