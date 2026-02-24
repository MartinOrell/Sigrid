#include "Action.h"
#include <iostream>

using namespace sigrid;

Action sigrid::getAction(const std::string& s){
    if(s == "save"){
        return ActionType::SaveBoard{};
    }
    else if(s == "reset"){
        return ActionType::Reset{};
    }
    else if(s == "clear"){
        return ActionType::Clear{};
    }
    else if(s == "addCoordinates"){
        return ActionType::AddCoordinates{};
    }
    else if(s == "removeCoordinates"){
        return ActionType::RemoveCoordinates{};
    }
    else if(s == "moveCoordinatesOutside"){
        return ActionType::MoveCoordinatesOutside{};
    }
    else if(s == "moveCoordinatesInside"){
        return ActionType::MoveCoordinatesInside{};
    }
    else if(s == "setBigCoordinates"){
        return ActionType::SetBigCoordinates{};
    }
    else if(s == "setSmallCoordinates"){
        return ActionType::SetSmallCoordinates{};
    }
    else if(s == "addBoardBorder"){
        return ActionType::AddBoardBorder{};
    }
    else if(s == "removeBoardBorder"){
        return ActionType::RemoveBoardBorder{};
    }
    else if(s == "addTurnToken"){
        return ActionType::AddPlayerToMoveToken{};
    }
    else if(s == "removeTurnToken"){
        return ActionType::RemovePlayerToMoveToken{};
    }
    else if(s == "pasteFen"){
        return ActionType::PasteFen{};
    }
    else if(s == "copyFen"){
        return ActionType::CopyFen{};
    }
    else if(s == "pinMenu"){
        return ActionType::PinMenu{};
    }
    else if(s == "unpinMenu"){
        return ActionType::PinMenu{};
    }
    else if(s == "showToolWindow"){
        return ActionType::ShowTools{};
    }
    else if(s == "hideToolWindow"){
        return ActionType::HideTools{};
    }
    else if(s == "showColorTools"){
        return ActionType::ShowColorTools{};
    }
    else if(s == "hideColorTools"){
        return ActionType::HideColorTools{};
    }
    else if(s == "print"){
        return ActionType::Print{};
    }

    std::cout << "Action.cpp: Unidentified Action: " << s << std::endl;
    return ActionType::None{};
}