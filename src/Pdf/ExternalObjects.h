#pragma once

#include <vector>

#include "Pdf/Object.h"
#include "Pdf/ExternalObject.h"

namespace sigrid_pdf{

    struct ExternalObjects : Object{

        std::vector<ExternalObject> xObjects;

        std::string getString() const override;

    };
}