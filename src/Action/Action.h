#pragma once

#include <variant>

#include "../Entity/LogicEntity.h"
#include "../Entity/GraphicEntity.h"
#include "../Entity/Piece/LogicPiece.h"
#include "../Entity/Piece/GraphicPiece.h"
#include "../Tool/Tool.h"

namespace sigrid{
    namespace ActionType{
        struct None{};
        struct PinMenu{};
        struct ShowMenu{};
        struct ToggleHeader{
            int headerId;
        };
        struct Reset{};
        struct Clear{};
        struct Print{};
        struct PickEntity{
            LogicEntity logicEntity;
            GraphicEntity graphicEntity;
        };
        struct PickPieceColor{
            LogicPiece logicPiece;
            GraphicPiece graphicPiece;
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
        struct PasteFen{};
        struct CopyFen{};

        struct FlipBoard{};
        struct AddCoordinates{};
        struct RemoveCoordinates{};
        struct MoveCoordinatesOutside{};
        struct MoveCoordinatesInside{};
        struct SetCoordinateSize{
            float size;
        };
        struct AddBoardBorder{};
        struct RemoveBoardBorder{};
        struct AddTurnToken{};
        struct RemoveTurnToken{};
    }

    typedef std::variant<
        ActionType::None,
        ActionType::PinMenu,
        ActionType::ShowMenu,
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
        ActionType::PasteFen,
        ActionType::CopyFen,
        ActionType::FlipBoard,
        ActionType::AddCoordinates,
        ActionType::RemoveCoordinates,
        ActionType::MoveCoordinatesOutside,
        ActionType::MoveCoordinatesInside,
        ActionType::SetCoordinateSize,
        ActionType::AddBoardBorder,
        ActionType::RemoveBoardBorder,
        ActionType::AddTurnToken,
        ActionType::RemoveTurnToken
    > Action;

    Action getAction(const std::string& s);
}