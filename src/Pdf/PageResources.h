#pragma once

#include "Pdf/Object.h"
#include "Pdf/ExternalObjects.h"

namespace sigrid_pdf{

struct Resources : Object{

    unsigned int procedureSetObjectNumber = 0;

    ExternalObjects externalObjects;

    std::string getString() const override;

};

}  // namespace sigrid_pdf