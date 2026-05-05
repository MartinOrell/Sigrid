#pragma once

#include <variant>

#include "Piece/GraphicPiece.h"
#include "Shape/Circle/GraphicCircle.h"
#include "Shape/Arrow/GraphicArrow.h"
#include "Icon/Icon.h"

namespace sigrid{
    typedef std::variant<
        GraphicPiece,
        GraphicCircle,
        GraphicArrow,
        Icon
    > GraphicEntity;
}