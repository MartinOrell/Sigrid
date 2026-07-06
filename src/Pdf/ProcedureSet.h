#pragma once

#include "Pdf/Object.h"

namespace myPdf{

    struct ProcedureSet : Object{
        std::string getString() const override;
    };
}