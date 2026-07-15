#pragma once

#include "Pdf/Object.h"
#include "Pdf/Pages.h"

namespace sigrid_pdf{

    struct Catalog : Object{

        Pages pages;

        std::string getString() const override;

    };
}