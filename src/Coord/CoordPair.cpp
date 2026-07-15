#include "Coord/CoordPair.h"

#include <cctype>

using namespace sigrid_coord;

bool CoordPair::operator<(const CoordPair& rhs) const{
    if(from < rhs.from){
        return true;
    }
    if(rhs.from < from){
        return false;
    }
    return to < rhs.to;
}

bool CoordPair::operator==(const CoordPair& rhs) const{
    return from == rhs.from && to == rhs.to;
}

bool CoordPair::operator!=(const CoordPair& rhs) const{
    return !(*this == rhs);
}

std::string CoordPair::getNotation() const{

    std::string notation = from.getNotation();
    notation.push_back('-');
    notation.append(to.getNotation());
    return notation;
}

std::ostream& sigrid_coord::operator<<(std::ostream &out, const CoordPair &coordPair)
{
    out << coordPair.getNotation();
    return out;
}