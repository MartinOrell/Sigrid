#pragma once

#include <vector>

#include "sigrid/Pdf/Object.h"
#include "sigrid/Pdf/ExternalObject.h"

namespace sigrid_pdf{

struct ExternalObjects : Object{

    std::vector<ExternalObject> xObjects;

    std::string getString() const override;

};

}  // namespace sigrid_pdf