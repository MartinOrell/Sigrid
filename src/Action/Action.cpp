#include "Action/Action.h"

#include <iostream>

using namespace sigrid_action;

std::optional<Action> sigrid_action::getAction(const std::string& s){
    std::string name;
    std::string content;

    auto nameEndPos = s.find('(');
    if(nameEndPos == std::string::npos){
        name = s;
    }
    else{
        name = s.substr(0,nameEndPos);
        content = s.substr(nameEndPos+1);
        content.pop_back(); //remove ')'
    }

    if(name == "save"){
        return sigrid_action::SaveBoard{};
    }
    else if(name == "savePdf"){
        return sigrid_action::SavePdf{};
    }
    else if(name == "new"){
        return sigrid_action::NewBoard{};
    }
    else if(name == "addBoardColumn"){
        return sigrid_action::AddBoardColumn{};
    }
    else if(name == "removeBoardColumn"){
        return sigrid_action::RemoveBoardColumn{};
    }
    else if(name == "addBoardRow"){
        return sigrid_action::AddBoardRow{};
    }
    else if(name == "removeBoardRow"){
        return sigrid_action::RemoveBoardRow{};
    }
    else if(name == "reset"){
        return sigrid_action::Reset{};
    }
    else if(name == "clear"){
        return sigrid_action::Clear{};
    }
    else if(name == "addLeftInsideLabels"){
        return sigrid_action::AddLeftInsideLabels{};
    }
    else if(name == "addRightOutsideLabels"){
        return sigrid_action::AddRightOutsideLabels{};
    }
    else if(name == "addBottomInsideLabels"){
        return sigrid_action::AddBottomInsideLabels{};
    }
    else if(name == "addLeftOutsideLabels"){
        return sigrid_action::AddLeftOutsideLabels{};
    }
    else if(name == "addTopOutsideLabels"){
        return sigrid_action::AddTopOutsideLabels{};
    }
    else if(name == "addBottomOutsideLabels"){
        return sigrid_action::AddBottomOutsideLabels{};
    }
    else if(name == "removeLeftInsideLabels"){
        return sigrid_action::RemoveLeftInsideLabels{};
    }
    else if(name == "removeBottomInsideLabels"){
        return sigrid_action::RemoveBottomInsideLabels{};
    }
    else if(name == "removeLeftOutsideLabels"){
        return sigrid_action::RemoveLeftOutsideLabels{};
    }
    else if(name == "removeRightOutsideLabels"){
        return sigrid_action::RemoveRightOutsideLabels{};
    }
    else if(name == "removeTopOutsideLabels"){
        return sigrid_action::RemoveTopOutsideLabels{};
    }
    else if(name == "removeBottomOutsideLabels"){
        return sigrid_action::RemoveBottomOutsideLabels{};
    }
    else if(name == "setCoordinateSize"){
        std::string number = content;
        number.pop_back(); //remove '%'
        float size = std::stof(number)/100.f;
        return sigrid_action::SetCoordinateSize{size};
    }
    else if(name == "addTileColumnRight"){
        return sigrid_action::AddTileColumnRight{};
    }
    else if(name == "addTileColumnLeft"){
        return sigrid_action::AddTileColumnLeft{};
    }
    else if(name == "removeRightTileColumn"){
        return sigrid_action::RemoveRightTileColumn{};
    }
    else if(name == "removeLeftTileColumn"){
        return sigrid_action::RemoveLeftTileColumn{};
    }
    else if(name == "addTileRowUp"){
        return sigrid_action::AddTileRowUp{};
    }
    else if(name == "addTileRowDown"){
        return sigrid_action::AddTileRowDown{};
    }
    else if(name == "removeTopTileRow"){
        return sigrid_action::RemoveTopTileRow{};
    }
    else if(name == "removeBottomTileRow"){
        return sigrid_action::RemoveBottomTileRow{};
    }
    else if(name == "addBoardBorder"){
        return sigrid_action::AddBoardBorder{};
    }
    else if(name == "removeBoardBorder"){
        return sigrid_action::RemoveBoardBorder{};
    }
    else if(name == "addTurnToken"){
        return sigrid_action::AddTurnToken{};
    }
    else if(name == "removeTurnToken"){
        return sigrid_action::RemoveTurnToken{};
    }
    else if(name == "pasteFen"){
        return sigrid_action::PasteFen{};
    }
    else if(name == "copyFen"){
        return sigrid_action::CopyFen{};
    }
    else if(name == "flipBoard"){
        return sigrid_action::FlipBoard{};
    }
    else if(name == "pinMenu"){
        return sigrid_action::PinMenu{};
    }
    else if(name == "unpinMenu"){
        return sigrid_action::UnPinMenu{};
    }
    else if(name == "showToolWindow"){
        return sigrid_action::ShowTools{};
    }
    else if(name == "hideToolWindow"){
        return sigrid_action::HideTools{};
    }
    else if(name == "showColorTools"){
        return sigrid_action::ShowColorTools{};
    }
    else if(name == "hideColorTools"){
        return sigrid_action::HideColorTools{};
    }
    else if(name == "print"){
        return sigrid_action::Print{};
    }

    std::cerr << "Action: Unidentified Action: " << s << std::endl;
    return std::nullopt;
}