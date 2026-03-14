#pragma once

#include <string>

namespace sigrid{
    struct PieceIdentifier{
        std::string name;
        std::string style;

        bool operator<(const PieceIdentifier& rhs) const;
    };
}
