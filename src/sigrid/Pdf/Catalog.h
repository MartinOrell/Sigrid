#pragma once

#include "sigrid/Pdf/Object.h"
#include "sigrid/Pdf/Pages.h"

namespace sigrid_pdf{

struct Catalog : Object{

    Pages pages;

    std::string getString() const override;

};

}  // namespace sigrid_pdf