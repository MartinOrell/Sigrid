#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct ArrowDataContainer{

    bool load(sigrid::InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const ArrowDataContainer& arrow);

    int colorId;
    sigrid::String position;
};

}  // namespace sigrid