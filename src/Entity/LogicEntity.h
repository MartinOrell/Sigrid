#pragma once

#include <variant>

#include "Piece/LogicPiece.h"
#include "Shape/Circle/LogicCircle.h"
#include "Shape/Arrow/LogicArrow.h"
#include "Icon/LogicIcon.h"

namespace sigrid{
    typedef std::variant<
        LogicPiece,
        LogicCircle,
        LogicArrow,
        LogicIcon
    > LogicEntity;
}