#pragma once

#include "Pdf/Object.h"
#include "Pdf/ExternalObjects.h"

namespace myPdf{

    struct Resources : Object{

        unsigned int procedureSetObjectNumber = 0;

        ExternalObjects externalObjects;

        std::string getString() const override;

    };
}