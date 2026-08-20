#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct CircleDataContainer{

    bool load(sigrid::InputStream& is);
    sigrid::String getString() const;

    int colorId; //0 = white, 1 = black
    sigrid::String position; //example: a2
};

}  // namespace sigrid