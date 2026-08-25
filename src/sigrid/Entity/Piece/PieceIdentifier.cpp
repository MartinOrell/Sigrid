#include "sigrid/Entity/Piece/PieceIdentifier.h"

bool sigrid::PieceIdentifier::operator<(const PieceIdentifier& rhs) const{
    if(name < rhs.name){
        return true;
    }
    if(name > rhs.name){
        return false;
    }
    return style < rhs.style;
}