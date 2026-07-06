#pragma once

#include <vector>

#include "Pdf/Object.h"
#include "Pdf/ExternalObject.h"

namespace myPdf{

    struct ExternalObjects : Object{

        std::vector<ExternalObject> xObjects;

        std::string getString() const override;

    };
}