#pragma once

#include <variant>
#include <optional>

#include <SFML/Window/Mouse.hpp>

#include "Entity/LogicEntity.h"
#include "Entity/GraphicEntity.h"
#include "Entity/Piece/LogicPiece.h"
#include "Entity/Piece/GraphicPiece.h"
#include "Tool/ToolSelection.h"

namespace sigrid_action{

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
    sigrid::LogicEntity logicEntity;
};
struct PickPieceColor{
    sigrid::LogicPiece logicPiece;
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
    sigrid::ToolSelection selection;
};
struct ShowColorTools{};
struct HideColorTools{};
struct ShowTools{};
struct HideTools{};
struct NewBoard{};
struct AddBoardColumn{};
struct RemoveBoardColumn{};
struct AddBoardRow{};
struct RemoveBoardRow{};
struct ShiftBoardsLeft{};
struct ShiftBoardsRight{};
struct GotoLeftBoard{};
struct GotoRightBoard{};
struct GotoUpBoard{};
struct GotoDownBoard{};
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
struct RemoveRightTileColumn{};
struct RemoveLeftTileColumn{};
struct AddTileRowUp{};
struct AddTileRowDown{};
struct RemoveTopTileRow{};
struct RemoveBottomTileRow{};
struct AddBoardBorder{};
struct RemoveBoardBorder{};
struct AddTurnToken{};
struct RemoveTurnToken{};

typedef std::variant<
    sigrid_action::PinMenu,
    sigrid_action::UnPinMenu,
    sigrid_action::ShowMenu,
    sigrid_action::HideMenu,
    sigrid_action::ToggleHeader,
    sigrid_action::Reset,
    sigrid_action::Clear,
    sigrid_action::Print,
    sigrid_action::PickEntity,
    sigrid_action::PickPieceColor,
    sigrid_action::PickArrow,
    sigrid_action::PickArrowColor,
    sigrid_action::PickCircle,
    sigrid_action::PickCircleColor,
    sigrid_action::SetTool,
    sigrid_action::ShowColorTools,
    sigrid_action::HideColorTools,
    sigrid_action::ShowTools,
    sigrid_action::HideTools,
    sigrid_action::NewBoard,
    sigrid_action::AddBoardColumn,
    sigrid_action::RemoveBoardColumn,
    sigrid_action::AddBoardRow,
    sigrid_action::RemoveBoardRow,
    sigrid_action::ShiftBoardsLeft,
    sigrid_action::ShiftBoardsRight,
    sigrid_action::GotoLeftBoard,
    sigrid_action::GotoRightBoard,
    sigrid_action::GotoUpBoard,
    sigrid_action::GotoDownBoard,
    sigrid_action::SaveBoard,
    sigrid_action::SavePdf,
    sigrid_action::PasteFen,
    sigrid_action::CopyFen,
    sigrid_action::FlipBoard,
    sigrid_action::AddLeftInsideLabels,
    sigrid_action::AddBottomInsideLabels,
    sigrid_action::AddLeftOutsideLabels,
    sigrid_action::AddRightOutsideLabels,
    sigrid_action::AddTopOutsideLabels,
    sigrid_action::AddBottomOutsideLabels,
    sigrid_action::RemoveLeftInsideLabels,
    sigrid_action::RemoveBottomInsideLabels,
    sigrid_action::RemoveLeftOutsideLabels,
    sigrid_action::RemoveRightOutsideLabels,
    sigrid_action::RemoveTopOutsideLabels,
    sigrid_action::RemoveBottomOutsideLabels,
    sigrid_action::SetCoordinateSize,
    sigrid_action::AddTileColumnRight,
    sigrid_action::AddTileColumnLeft,
    sigrid_action::RemoveRightTileColumn,
    sigrid_action::RemoveLeftTileColumn,
    sigrid_action::AddTileRowUp,
    sigrid_action::AddTileRowDown,
    sigrid_action::RemoveTopTileRow,
    sigrid_action::RemoveBottomTileRow,
    sigrid_action::AddBoardBorder,
    sigrid_action::RemoveBoardBorder,
    sigrid_action::AddTurnToken,
    sigrid_action::RemoveTurnToken
> Action;

std::optional<Action> getAction(const std::string& s);

}  // namespace sigrid_action