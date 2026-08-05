#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/Entity/Piece/PieceDataContainer.h"

namespace sigrid{

class LogicPiece{

  public:

    LogicPiece() = default;
    LogicPiece(const LogicPiece&) = default;
    LogicPiece(LogicPiece&&) = default;
    LogicPiece& operator=(const LogicPiece&) = default;
    LogicPiece& operator=(LogicPiece&&) = default;

    void setNotation(const sigrid::String& notation);
    void setColorId(const int& colorId);

    int getColorId() const;
    sigrid::String getNotation() const;
    PieceDataContainer getContainer() const;

    bool operator==(const LogicPiece& rhs) const;
    bool operator!=(const LogicPiece& rhs) const;

  private:

    sigrid::String m_notation;
    int m_colorId = -1;
};

}  // namespace sigrid