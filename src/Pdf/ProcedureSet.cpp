#pragma once

#include "Pdf/ProcedureSet.h"

using namespace myPdf;

std::string ProcedureSet::getString() const{
    return "  [/PDF /Text /ImageB /ImageC ImageI]\n";
}