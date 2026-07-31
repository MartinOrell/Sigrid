#pragma once

#include <variant>

#include "sigrid/Entity/Piece/LogicPiece.h"
#include "sigrid/Entity/Shape/Circle/LogicCircle.h"
#include "sigrid/Entity/Shape/Arrow/LogicArrow.h"
#include "sigrid/Entity/Icon/LogicIcon.h"

namespace sigrid{

    typedef std::variant<
        LogicPiece,
        LogicCircle,
        LogicArrow,
        LogicIcon
    > LogicEntity;

}  // namespace sigrid