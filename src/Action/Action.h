#pragma once

#include <variant>

#include "../Piece/Piece.h"
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
        struct PickPiece{
            Piece piece;
        };
        struct PickPieceColor{
            Piece piece;
        };
        struct PickArrow{
            int colorId;
        };
        struct PickArrowColor{
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
        struct AddPlayerToMoveToken{};
        struct RemovePlayerToMoveToken{};
    }

    typedef std::variant<
        ActionType::None,
        ActionType::PinMenu,
        ActionType::ShowMenu,
        ActionType::ToggleHeader,
        ActionType::Reset,
        ActionType::Clear,
        ActionType::Print,
        ActionType::PickPiece,
        ActionType::PickPieceColor,
        ActionType::PickArrow,
        ActionType::PickArrowColor,
        ActionType::SetTool,
        ActionType::ShowColorTools,
        ActionType::HideColorTools,
        ActionType::ShowTools,
        ActionType::HideTools,
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
        ActionType::AddPlayerToMoveToken,
        ActionType::RemovePlayerToMoveToken
    > Action;

    Action getAction(const std::string& s);
}