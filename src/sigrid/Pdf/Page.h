#pragma once

#include "sigrid/Pdf/Object.h"
#include "sigrid/Pdf/PageResources.h"
#include "sigrid/Pdf/ContentStreams.h"

namespace sigrid_pdf{

struct Page : Object{

    unsigned int parentObjectNumber = 0;
    unsigned int mediaBoxObjectNumber = 0;

    Resources resources;
    ContentStreams contents;

    std::string getString() const override;

};

}  // namespace sigrid_pdf