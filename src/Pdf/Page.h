#pragma once

#include "Object.h"
#include "PageResources.h"
#include "ContentStreams.h"

namespace myPdf{

    struct Page : Object{

        unsigned int parentObjectNumber = 0;
        unsigned int mediaBoxObjectNumber = 0;

        Resources resources;
        ContentStreams contents;

        std::string getString() const override;

    };
}