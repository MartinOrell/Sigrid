#pragma once

#include <variant>

#include "Piece/LogicPiece.h"
#include "Shape/Circle/LogicCircle.h"

namespace sigrid{
    typedef std::variant<
        LogicPiece,
        LogicCircle
    > LogicEntity;
}