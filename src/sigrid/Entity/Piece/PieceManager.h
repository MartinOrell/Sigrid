#pragma once

#include "sigrid/utilities/Size/Size_f.h"
#include "sigrid/utilities/Texture/Texture.h"
#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Map.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Entity/Piece/LogicPiece.h"
#include "sigrid/Entity/Piece/GraphicPiece.h"
#include "sigrid/Entity/Piece/PieceColor.h"
#include "sigrid/Entity/Piece/PieceIdentifier.h"

namespace sigrid{

struct PieceContainer;

class PieceManager{

  public:

    PieceManager() = default;
    PieceManager(const PieceManager&) = default;
    PieceManager(PieceManager&&) = default;
    PieceManager& operator=(const PieceManager&) = default;
    PieceManager& operator=(PieceManager&&) = default;

    void setPieceColors(const sigrid_list::Vector<PieceColor>& pieceColors);
    sigrid_list::Vector<PieceColor> getContainer() const;

    void addPieceColor(const PieceColor& newColor);
    void loadImages(const sigrid_list::Vector<PieceContainer>& pieces);
    sigrid_list::Vector<PieceContainer> getPieceContainer() const;

    std::optional<GraphicPiece> getGraphicPiece(const LogicPiece& logicPiece);

  private:

    sigrid_list::Map<PieceIdentifier, sigrid::String> m_pieceImageFilenames;

    sigrid_list::Vector<PieceColor> m_colors;
    sigrid_list::Vector<std::map<PieceIdentifier, GraphicPiece>> m_graphicPieces;
    sigrid_list::Vector<std::map<PieceIdentifier, sigrid::Texture>> m_pieceTextures;

    sigrid::Size_f m_pieceSize{108.f,108.f};
};

}  // namespace sigrid