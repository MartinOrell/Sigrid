#pragma once

#include "Object.h"
#include "Image.h"

namespace myPdf{

    struct ExternalObject : Object{

        Image image;

        std::string getString() const override;
    };
}