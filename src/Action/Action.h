#pragma once

#include <variant>
#include <SFML/Window/Mouse.hpp>

#include "../Entity/LogicEntity.h"
#include "../Entity/GraphicEntity.h"
#include "../Entity/Piece/LogicPiece.h"
#include "../Entity/Piece/GraphicPiece.h"
#include "../Tool/ToolSelection.h"

namespace sigrid{
    namespace ActionType{
        struct None{};
        struct PinMenu{};
        struct UnPinMenu{};
        struct ShowMenu{};
        struct HideMenu{};
        struct ToggleHeader{
            int headerId;
        };
        struct Reset{};
        struct Clear{};
        struct Print{};
        struct PickEntity{
            LogicEntity logicEntity;
        };
        struct PickPieceColor{
            LogicPiece logicPiece;
        };
        struct PickArrow{
            int colorId;
        };
        struct PickArrowColor{
            int colorId;
        };
        struct PickCircle{
            int colorId;
        };
        struct PickCircleColor{
            int colorId;
        };
        struct SetTool{
            sf::Mouse::Button button;
            ToolSelection selection;
        };
        struct ShowColorTools{};
        struct HideColorTools{};
        struct ShowTools{};
        struct HideTools{};
        struct NewBoard{};
        struct OpenLeftBoard{};
        struct OpenRightBoard{};
        struct SaveBoard{};
        struct SavePdf{};
        struct PasteFen{};
        struct CopyFen{};

        struct FlipBoard{};
        struct AddLeftInsideLabels{};
        struct AddBottomInsideLabels{};
        struct AddLeftOutsideLabels{};
        struct AddRightOutsideLabels{};
        struct AddTopOutsideLabels{};
        struct AddBottomOutsideLabels{};
        struct RemoveLeftInsideLabels{};
        struct RemoveBottomInsideLabels{};
        struct RemoveLeftOutsideLabels{};
        struct RemoveRightOutsideLabels{};
        struct RemoveTopOutsideLabels{};
        struct RemoveBottomOutsideLabels{};
        struct SetCoordinateSize{
            float size;
        };
        struct AddTileColumnRight{};
        struct AddTileColumnLeft{};
        struct RemoveTileColumnRight{};
        struct RemoveTileColumnLeft{};
        struct AddTileRowUp{};
        struct AddTileRowDown{};
        struct RemoveTileRowUp{};
        struct RemoveTileRowDown{};
        struct AddBoardBorder{};
        struct RemoveBoardBorder{};
        struct AddTurnToken{};
        struct RemoveTurnToken{};
    }

    typedef std::variant<
        ActionType::None,
        ActionType::PinMenu,
        ActionType::UnPinMenu,
        ActionType::ShowMenu,
        ActionType::HideMenu,
        ActionType::ToggleHeader,
        ActionType::Reset,
        ActionType::Clear,
        ActionType::Print,
        ActionType::PickEntity,
        ActionType::PickPieceColor,
        ActionType::PickArrow,
        ActionType::PickArrowColor,
        ActionType::PickCircle,
        ActionType::PickCircleColor,
        ActionType::SetTool,
        ActionType::ShowColorTools,
        ActionType::HideColorTools,
        ActionType::ShowTools,
        ActionType::HideTools,
        ActionType::NewBoard,
        ActionType::OpenLeftBoard,
        ActionType::OpenRightBoard,
        ActionType::SaveBoard,
        ActionType::SavePdf,
        ActionType::PasteFen,
        ActionType::CopyFen,
        ActionType::FlipBoard,
        ActionType::AddLeftInsideLabels,
        ActionType::AddBottomInsideLabels,
        ActionType::AddLeftOutsideLabels,
        ActionType::AddRightOutsideLabels,
        ActionType::AddTopOutsideLabels,
        ActionType::AddBottomOutsideLabels,
        ActionType::RemoveLeftInsideLabels,
        ActionType::RemoveBottomInsideLabels,
        ActionType::RemoveLeftOutsideLabels,
        ActionType::RemoveRightOutsideLabels,
        ActionType::RemoveTopOutsideLabels,
        ActionType::RemoveBottomOutsideLabels,
        ActionType::SetCoordinateSize,
        ActionType::AddTileColumnRight,
        ActionType::AddTileColumnLeft,
        ActionType::RemoveTileColumnRight,
        ActionType::RemoveTileColumnLeft,
        ActionType::AddTileRowUp,
        ActionType::AddTileRowDown,
        ActionType::RemoveTileRowUp,
        ActionType::RemoveTileRowDown,
        ActionType::AddBoardBorder,
        ActionType::RemoveBoardBorder,
        ActionType::AddTurnToken,
        ActionType::RemoveTurnToken
    > Action;

    Action getAction(const std::string& s);
}