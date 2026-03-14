#pragma once

#include <variant>

#include "Piece/GraphicPiece.h"
#include "Shape/Circle/GraphicCircle.h"

namespace sigrid{
    typedef std::variant<
        GraphicPiece,
        GraphicCircle
    > GraphicEntity;
}