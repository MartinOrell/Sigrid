#include "GraphicBoardConfigContainer.h"

#include <fstream>
#include <iostream>

using namespace sigrid;

GraphicBoardConfigContainer::GraphicBoardConfigContainer(const std::string& filename){
    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        std::cout << "Graphic Board Config Container: Failed to open config file: " << filename << std::endl;
        return;
    }

    std::string key;
    while(ifs >> key){

        if(key == "SquareSize:"){
            ifs >> squareSize;
        }
        else if(key == "LabelsInside:"){
            std::string isEnabled;
            ifs >> isEnabled;
            labelsInside = isEnabled == "ON";
        }
        else if(key == "LabelsOutside:"){
            std::string isEnabled;
            ifs >> isEnabled;
            labelsOutside = isEnabled == "ON";
        }
        else if(key == "LabelFont:"){
            ifs >> labelFont;
        }
        else if(key == "InsideLabelSize:"){
            ifs >> insideLabelSize;
            insideLabelSize = insideLabelSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "OutsideLabelSize:"){
            ifs >> outsideLabelSize;
            outsideLabelSize = outsideLabelSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "OutsideLabelSmallSize:"){
            ifs >> outsideLabelSmallSize;
            outsideLabelSmallSize = outsideLabelSmallSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "OutsideLabelBigSize:"){
            ifs >> outsideLabelBigSize;
            outsideLabelBigSize = outsideLabelBigSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "Border:"){
            std::string isEnabled;
            ifs >> isEnabled;
            border = isEnabled == "ON";
        }
        else if(key == "BorderWidth:"){
            ifs >> borderWidth;
        }
        else if(key == "Border:"){
            std::string isEnabled;
            ifs >> isEnabled;
            border = isEnabled == "ON";
        }
        else if(key == "PlayerToMoveToken:"){
            std::string isEnabled;
            ifs >> isEnabled;
            playerToMoveToken = isEnabled == "ON";
        }
        else{
            std::cout << "Graphic Board Config File: Unknown key: " << key << std::endl;
        }
    }
}

