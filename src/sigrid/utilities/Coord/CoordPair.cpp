#include "sigrid/utilities/Coord/CoordPair.h"

#include <iostream>
#include <cctype>

using namespace sigrid_coord;

CoordPair::CoordPair(const Coord& from, const Coord& to){
    
    this->from = from;
    this->to = to;
}

CoordPair::CoordPair(const sigrid::String& notation){
    set(notation);
}

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

bool CoordPair::set(const sigrid::String& notation){

    auto dashPosition_o = notation.find('-');
    if(dashPosition_o == std::nullopt){
        std::cerr << "CoordPair: Failed to find dash (-) position."
            << " Failed to set CoordPair from notation \""
            << notation << "\"." << std::endl;
        return false;
    }
    int dashPosition = dashPosition_o.value();

    auto fromNotation_o = notation.substr(0, dashPosition);
    if(fromNotation_o == std::nullopt){
        std::cerr << "CoordPair: Failed to get substring for fromPosition."
            << " Failed to set CoordPair from notation \""
            << notation << "\"." << std::endl;
        return false;
    }
    sigrid::String fromNotation = fromNotation_o.value();

    auto toNotation_o = notation.substr(dashPosition+1);
    if(toNotation_o == std::nullopt){
        std::cerr << "CoordPair: Failed to get substring for toPosition."
            << " Failed to set CoordPair from notation \""
            << notation << "\"." << std::endl;
        return false;
    }
    sigrid::String toNotation = toNotation_o.value();
    
    if(!from.set(fromNotation)){
        std::cerr << "CoordPair: Failed to set from to \"" << fromNotation << "\"."
            << " Failed to set CoordPair from notation \""
            << notation << "\"." << std::endl;
        return false;
    }

    if(!to.set(toNotation)){
        std::cerr << "CoordPair: Failed to set \"to\" to \"" << fromNotation << "\"."
            << " Failed to set CoordPair from notation \""
            << notation << "\"." << std::endl;
        return false;
    }

    return true;
}

sigrid::String CoordPair::getNotation() const{

    sigrid::String notation = from.getNotation();
    notation.push_back('-');
    notation.append(to.getNotation());
    return notation;
}

std::ostream& sigrid_coord::operator<<(std::ostream &out, const CoordPair &coordPair)
{
    out << coordPair.getNotation();
    return out;
}