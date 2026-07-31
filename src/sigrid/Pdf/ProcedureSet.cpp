#pragma once

#include "sigrid/Pdf/ProcedureSet.h"

using namespace sigrid_pdf;

std::string ProcedureSet::getString() const{
    return "  [/PDF /Text /ImageB /ImageC ImageI]\n";
}