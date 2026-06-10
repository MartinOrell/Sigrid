#pragma once

#include "Object.h"

namespace myPdf{

    struct ProcedureSet : Object{
        std::string getString() const override;
    };
}