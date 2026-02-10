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
        struct SaveBoardImage{
            std::string imageFileName;
        };

        struct AddCoordinates{};
        struct RemoveCoordinates{};
        struct MoveCoordinatesOutside{};
        struct MoveCoordinatesInside{};
        struct SetBigCoordinates{};
        struct SetSmallCoordinates{};
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
        ActionType::SaveBoardImage,
        ActionType::AddCoordinates,
        ActionType::RemoveCoordinates,
        ActionType::MoveCoordinatesOutside,
        ActionType::MoveCoordinatesInside,
        ActionType::SetBigCoordinates,
        ActionType::SetSmallCoordinates,
        ActionType::AddBoardBorder,
        ActionType::RemoveBoardBorder,
        ActionType::AddPlayerToMoveToken,
        ActionType::RemovePlayerToMoveToken
    > Action;
}