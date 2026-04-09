#include "Action.h"
#include <iostream>

using namespace sigrid;

Action sigrid::getAction(const std::string& s){
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
        return ActionType::SaveBoard{};
    }
    else if(name == "openLeft"){
        return ActionType::OpenLeftBoard{};
    }
    else if(name == "openRight"){
        return ActionType::OpenRightBoard{};
    }
    else if(name == "new"){
        return ActionType::NewBoard{};
    }
    else if(name == "reset"){
        return ActionType::Reset{};
    }
    else if(name == "clear"){
        return ActionType::Clear{};
    }
    else if(name == "addCoordinates"){
        return ActionType::AddCoordinates{};
    }
    else if(name == "removeCoordinates"){
        return ActionType::RemoveCoordinates{};
    }
    else if(name == "moveCoordinatesOutside"){
        return ActionType::MoveCoordinatesOutside{};
    }
    else if(name == "moveCoordinatesInside"){
        return ActionType::MoveCoordinatesInside{};
    }
    else if(name == "setCoordinateSize"){
        std::string number = content;
        number.pop_back(); //remove '%'
        float size = std::stof(number)/100.f;
        return ActionType::SetCoordinateSize{size};
    }
    else if(name == "addSquareColumnRight"){
        return ActionType::AddSquareColumnRight{};
    }
    else if(name == "addSquareColumnLeft"){
        return ActionType::AddSquareColumnLeft{};
    }
    else if(name == "removeSquareColumnRight"){
        return ActionType::RemoveSquareColumnRight{};
    }
    else if(name == "removeSquareColumnLeft"){
        return ActionType::RemoveSquareColumnLeft{};
    }
    else if(name == "addBoardBorder"){
        return ActionType::AddBoardBorder{};
    }
    else if(name == "removeBoardBorder"){
        return ActionType::RemoveBoardBorder{};
    }
    else if(name == "addTurnToken"){
        return ActionType::AddTurnToken{};
    }
    else if(name == "removeTurnToken"){
        return ActionType::RemoveTurnToken{};
    }
    else if(name == "pasteFen"){
        return ActionType::PasteFen{};
    }
    else if(name == "copyFen"){
        return ActionType::CopyFen{};
    }
    else if(name == "flipBoard"){
        return ActionType::FlipBoard{};
    }
    else if(name == "pinMenu"){
        return ActionType::PinMenu{};
    }
    else if(name == "unpinMenu"){
        return ActionType::PinMenu{};
    }
    else if(name == "showToolWindow"){
        return ActionType::ShowTools{};
    }
    else if(name == "hideToolWindow"){
        return ActionType::HideTools{};
    }
    else if(name == "showColorTools"){
        return ActionType::ShowColorTools{};
    }
    else if(name == "hideColorTools"){
        return ActionType::HideColorTools{};
    }
    else if(name == "print"){
        return ActionType::Print{};
    }

    std::cout << "Action.cpp: Unidentified Action: " << s << std::endl;
    return ActionType::None{};
}