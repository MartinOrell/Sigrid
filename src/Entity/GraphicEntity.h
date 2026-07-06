#pragma once

#include <variant>

#include "Entity/Piece/GraphicPiece.h"
#include "Entity/Shape/Circle/GraphicCircle.h"
#include "Entity/Shape/Arrow/GraphicArrow.h"
#include "Entity/Icon/Icon.h"

namespace sigrid{
    typedef std::variant<
        GraphicPiece,
        GraphicCircle,
        GraphicArrow,
        Icon
    > GraphicEntity;
}