#pragma once

#include "Pdf/Object.h"

namespace sigrid_pdf{

    struct ProcedureSet : Object{
        std::string getString() const override;
    };
}