#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid_coord{

struct Coord{
    Coord();
    Coord(const int x, const int y);
    Coord(const sigrid::String& notation);

    Coord& operator=(const Coord& rhs);

    bool operator<(const Coord& rhs) const;
    bool operator==(const Coord& rhs) const;
    bool operator!=(const Coord& rhs) const;

    bool set(const sigrid::String& notation);

    sigrid::String getNotation() const;

    bool load(sigrid::InputStream& is);

    int x;
    int y;
};

sigrid::String getColumnNotation(const int& x);
sigrid::String getRowNotation(const int& y);

}  // namespace sigrid_coord