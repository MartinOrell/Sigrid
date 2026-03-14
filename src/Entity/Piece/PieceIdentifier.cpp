#include "PieceIdentifier.h"

using namespace sigrid;

bool PieceIdentifier::operator<(const PieceIdentifier& rhs) const{
    if(name < rhs.name){
        return true;
    }
    if(name > rhs.name){
        return false;
    }
    return style < rhs.style;
}