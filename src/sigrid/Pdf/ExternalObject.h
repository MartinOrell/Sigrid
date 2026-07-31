#pragma once

#include "sigrid/Pdf/Object.h"
#include "sigrid/Pdf/Image.h"

namespace sigrid_pdf{

struct ExternalObject : Object{

    Image image;

    std::string getString() const override;
};

}  // namespace sigrid_pdf