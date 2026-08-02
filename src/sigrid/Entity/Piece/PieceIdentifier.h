#pragma once

#include "sigrid/utilities/String/String.h"

namespace sigrid{

struct PieceIdentifier{
    sigrid::String name;
    sigrid::String style;

    bool operator<(const PieceIdentifier& rhs) const;
};

}  // namespace sigrid