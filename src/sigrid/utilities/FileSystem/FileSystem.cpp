#include "sigrid/utilities/FileSystem/FileSystem.h"

#include <filesystem>
#include <iostream>

#include <nfd.h> // nativefiledialog-extended

bool sigrid_filesystem::exists(const sigrid::String& filename){

    return std::filesystem::exists(filename.getStdString());
}

bool sigrid_filesystem::createFolderForFile(const sigrid::String filename){

    auto endPos_o = filename.find('/',1);

    while(endPos_o != std::nullopt){

        int endPos = endPos_o.value();

        auto folder_o = filename.substr(0,endPos);
        if(folder_o == std::nullopt){
            return false;
        }
        sigrid::String folder = folder_o.value();

        if(!sigrid_filesystem::exists(folder)){
            bool createFolderIsSuccessful;
            createFolderIsSuccessful = std::filesystem::create_directory(folder.getStdString());
            if(createFolderIsSuccessful){
                std::cout << "Created folder: " << folder << std::endl;
            }
            else{
                std::cerr << "FileSystem: Failed to create folder: " << folder << std::endl;
                return false;
            }
        }

        endPos_o = filename.find('/',endPos+1);
    }
    return true;
}

std::optional<sigrid::String> sigrid_filesystem::getFilenameFromDialog(){

    NFD_Init();

    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = { { "Board", "txt" } };
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {
        std::string filePath = outPath;
        sigrid::String out;
        out.set(std::move(filePath));

        NFD_FreePathU8(outPath);
        NFD_Quit();
        return out;
    }
    else if (result == NFD_CANCEL)
    {
        NFD_Quit();
        return std::nullopt;
    }
    else 
    {
        std::cerr << "FileSystem: " << NFD_GetError()
            << "\n Failed to get filePath from native dialog" << std::endl;
        NFD_Quit();
        return std::nullopt;
    }
}