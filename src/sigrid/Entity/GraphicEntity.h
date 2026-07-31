#pragma once

#include <variant>

#include "sigrid/Entity/Piece/GraphicPiece.h"
#include "sigrid/Entity/Shape/Circle/GraphicCircle.h"
#include "sigrid/Entity/Shape/Arrow/GraphicArrow.h"
#include "sigrid/Entity/Icon/Icon.h"

namespace sigrid{

typedef std::variant<
    GraphicPiece,
    GraphicCircle,
    GraphicArrow,
    Icon
> GraphicEntity;

}  // namespace sigrid