#pragma once

#include <vector>

#include "Pdf/Object.h"
#include "Pdf/Page.h"

namespace sigrid_pdf{

struct Pages : Object{

    std::vector<Page> kids;

    std::string getString() const override;

};

}  // namespace sigrid_pdf