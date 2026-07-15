#pragma once

#include <variant>

#include "Entity/Piece/LogicPiece.h"
#include "Entity/Shape/Circle/LogicCircle.h"
#include "Entity/Shape/Arrow/LogicArrow.h"
#include "Entity/Icon/LogicIcon.h"

namespace sigrid{

    typedef std::variant<
        LogicPiece,
        LogicCircle,
        LogicArrow,
        LogicIcon
    > LogicEntity;

}  // namespace sigrid