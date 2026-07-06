#pragma once

#include "Pdf/Object.h"
#include "Pdf/Image.h"

namespace myPdf{

    struct ExternalObject : Object{

        Image image;

        std::string getString() const override;
    };
}