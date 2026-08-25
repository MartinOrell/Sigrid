#pragma once

#include "sigrid/Pdf/ProcedureSet.h"

std::string sigrid_pdf::ProcedureSet::getString() const{
    return "  [/PDF /Text /ImageB /ImageC ImageI]\n";
}