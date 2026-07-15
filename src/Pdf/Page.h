#pragma once

#include "Pdf/Object.h"
#include "Pdf/PageResources.h"
#include "Pdf/ContentStreams.h"

namespace sigrid_pdf{

    struct Page : Object{

        unsigned int parentObjectNumber = 0;
        unsigned int mediaBoxObjectNumber = 0;

        Resources resources;
        ContentStreams contents;

        std::string getString() const override;

    };
}