#pragma once

#include <vector>

#include "Pdf/Object.h"
#include "Pdf/ContentStream.h"

namespace sigrid_pdf{

struct ContentStreams : Object{

    std::vector<ContentStream> streams;

    std::string getString() const override;

};

}  // namespace sigrid_pdf