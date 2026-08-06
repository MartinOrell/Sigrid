#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct IconDataContainer{

    bool load(sigrid::InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const IconDataContainer& piece);

    sigrid::String imageFilename;
    sigrid::String position;
};

}  // namespace sigrid