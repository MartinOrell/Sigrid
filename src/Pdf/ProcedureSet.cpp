#pragma once

#include "Pdf/ProcedureSet.h"

using namespace sigrid_pdf;

std::string ProcedureSet::getString() const{
    return "  [/PDF /Text /ImageB /ImageC ImageI]\n";
}