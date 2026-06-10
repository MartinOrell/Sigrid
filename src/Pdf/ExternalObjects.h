#pragma once

#include <vector>

#include "Object.h"
#include "ExternalObject.h"

namespace myPdf{

    struct ExternalObjects : Object{

        std::vector<ExternalObject> xObjects;

        std::string getString() const override;

    };
}