#include "sigrid/Action/Action.h"

#include <iostream>

using namespace sigrid_action;

std::optional<Action> sigrid_action::getAction(const sigrid::String& s){

    sigrid::String name;
    sigrid::String content;

    auto nameEndPos_o = s.find('(');
    if(nameEndPos_o == std::nullopt){
        name = s;
    }
    else{
        
        int nameEndPos = nameEndPos_o.value();

        auto name_o = s.substr(0, nameEndPos);
        if(name_o == std::nullopt){
            return std::nullopt;
        }
        name = name_o.value();

        auto content_o = s.substr(nameEndPos+1);
        if(content_o == std::nullopt){
            return std::nullopt;
        }
        content = content_o.value();
        content.pop_back(); //remove ')'
    }

    if(name == "save"){
        return sigrid_action::SaveBoard{};
    }
    else if(name == "saveSettings"){
        return sigrid_action::SaveSettings{};
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

        sigrid::String numberString = content;
        numberString.pop_back(); //remove '%'
        auto number_o = numberString.toInt();
        if(number_o == std::nullopt){
            return std::nullopt;
        }
        int number = number_o.value();

        float size = (float)number/100.f;
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

sigrid::String sigrid_action::getString(const Action& action){

    if(std::holds_alternative<sigrid_action::PinMenu>(action)){
        return "pinMenu";
    }
    else if(std::holds_alternative<sigrid_action::UnPinMenu>(action)){
        return "unpinMenu";
    }
    else if(std::holds_alternative<sigrid_action::ShowMenu>(action)){
        return "showMenu";
    }
    else if(std::holds_alternative<sigrid_action::HideMenu>(action)){
        return "hideMenu";
    }
    else if(std::holds_alternative<sigrid_action::ToggleHeader>(action)){
        return "toggleHeader";
    }
    else if(std::holds_alternative<sigrid_action::Reset>(action)){
        return "reset";
    }
    else if(std::holds_alternative<sigrid_action::Clear>(action)){
        return "clear";
    }
    else if(std::holds_alternative<sigrid_action::Print>(action)){
        return "print";
    }
    else if(std::holds_alternative<sigrid_action::PickEntity>(action)){
        return "pickEntity";
    }
    else if(std::holds_alternative<sigrid_action::PickPieceColor>(action)){
        return "pickPieceColor";
    }
    else if(std::holds_alternative<sigrid_action::PickArrow>(action)){
        return "pickArrow";
    }
    else if(std::holds_alternative<sigrid_action::PickArrowColor>(action)){
        return "pickArrowColor";
    }
    else if(std::holds_alternative<sigrid_action::PickCircle>(action)){
        return "pickCircle";
    }
    else if(std::holds_alternative<sigrid_action::PickCircleColor>(action)){
        return "pickCircleColor";
    }
    else if(std::holds_alternative<sigrid_action::SetTool>(action)){
        return "setTool";
    }
    else if(std::holds_alternative<sigrid_action::ShowColorTools>(action)){
        return "showColorTools";
    }
    else if(std::holds_alternative<sigrid_action::HideColorTools>(action)){
        return "hideColorTools";
    }
    else if(std::holds_alternative<sigrid_action::ShowTools>(action)){
        return "showTools";
    }
    else if(std::holds_alternative<sigrid_action::HideTools>(action)){
        return "hideTools";
    }
    else if(std::holds_alternative<sigrid_action::NewBoard>(action)){
        return "new";
    }
    else if(std::holds_alternative<sigrid_action::AddBoardColumn>(action)){
        return "addBoardColumn";
    }
    else if(std::holds_alternative<sigrid_action::RemoveBoardColumn>(action)){
        return "removeBoardColumn";
    }
    else if(std::holds_alternative<sigrid_action::AddBoardRow>(action)){
        return "addBoardRow";
    }
    else if(std::holds_alternative<sigrid_action::RemoveBoardRow>(action)){
        return "removeBoardRow";
    }
    else if(std::holds_alternative<sigrid_action::ShiftBoardsLeft>(action)){
        return "shiftBoardsLeft";
    }
    else if(std::holds_alternative<sigrid_action::ShiftBoardsRight>(action)){
        return "shiftBoardsRight";
    }
    else if(std::holds_alternative<sigrid_action::GotoLeftBoard>(action)){
        return "gotoLeftBoard";
    }
    else if(std::holds_alternative<sigrid_action::GotoRightBoard>(action)){
        return "gotoRightBoard";
    }
    else if(std::holds_alternative<sigrid_action::GotoUpBoard>(action)){
        return "gotoUpBoard";
    }
    else if(std::holds_alternative<sigrid_action::GotoDownBoard>(action)){
        return "gotoDownBoard";
    }
    else if(std::holds_alternative<sigrid_action::SaveBoard>(action)){
        return "save";
    }
    else if(std::holds_alternative<sigrid_action::SaveSettings>(action)){
        return "saveSettings";
    }
    else if(std::holds_alternative<sigrid_action::SavePdf>(action)){
        return "savePdf";
    }
    else if(std::holds_alternative<sigrid_action::PasteFen>(action)){
        return "pasteFen";
    }
    else if(std::holds_alternative<sigrid_action::CopyFen>(action)){
        return "copyFen";
    }
    else if(std::holds_alternative<sigrid_action::FlipBoard>(action)){
        return "flipBoard";
    }
    else if(std::holds_alternative<sigrid_action::AddLeftInsideLabels>(action)){
        return "addLeftInsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::AddBottomInsideLabels>(action)){
        return "addBottomInsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::AddLeftOutsideLabels>(action)){
        return "addLeftOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::AddRightOutsideLabels>(action)){
        return "addRightOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::AddTopOutsideLabels>(action)){
        return "addTopOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::AddBottomOutsideLabels>(action)){
        return "addBottomOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::RemoveLeftInsideLabels>(action)){
        return "removeLeftInsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::RemoveBottomInsideLabels>(action)){
        return "removeBottomInsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::RemoveLeftOutsideLabels>(action)){
        return "removeLeftOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::RemoveRightOutsideLabels>(action)){
        return "removeRightOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::RemoveTopOutsideLabels>(action)){
        return "removeTopOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::RemoveBottomOutsideLabels>(action)){
        return "removeBottomOutsideLabels";
    }
    else if(std::holds_alternative<sigrid_action::SetCoordinateSize>(action)){

        float size = std::get<sigrid_action::SetCoordinateSize>(action).size;
        int percentSize = size*100;
        std::string stdString = "setCoordinateSize(" + std::to_string(percentSize) + "%)";
        sigrid::String s;
        s.set(std::move(stdString));
        return s;
    }
    else if(std::holds_alternative<sigrid_action::AddTileColumnRight>(action)){
        return "addTileColumnRight";
    }
    else if(std::holds_alternative<sigrid_action::AddTileColumnLeft>(action)){
        return "addTileColumnLeft";
    }
    else if(std::holds_alternative<sigrid_action::RemoveRightTileColumn>(action)){
        return "removeRightTileColumn";
    }
    else if(std::holds_alternative<sigrid_action::RemoveLeftTileColumn>(action)){
        return "removeLeftTilColumn";
    }
    else if(std::holds_alternative<sigrid_action::AddTileRowUp>(action)){
        return "addTileRowUp";
    }
    else if(std::holds_alternative<sigrid_action::AddTileRowDown>(action)){
        return "addTileRowDown";
    }
    else if(std::holds_alternative<sigrid_action::RemoveTopTileRow>(action)){
        return "removeTopTileRow";
    }
    else if(std::holds_alternative<sigrid_action::RemoveBottomTileRow>(action)){
        return "removeBottomTileRow";
    }
    else if(std::holds_alternative<sigrid_action::AddBoardBorder>(action)){
        return "addBoardBorder";
    }
    else if(std::holds_alternative<sigrid_action::RemoveBoardBorder>(action)){
        return "removeBoardBorder";
    }
    else if(std::holds_alternative<sigrid_action::AddTurnToken>(action)){
        return "addTurnToken";
    }
    else if(std::holds_alternative<sigrid_action::RemoveTurnToken>(action)){
        return "removeTurnToken";
    }

    std::cerr << "Action: Unknown action. Failed to get String" << std::endl;
    return "none";
}