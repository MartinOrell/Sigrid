#include "sigrid/utilities/FileSystem/FileSystem.h"

#include <filesystem>
#include <iostream>

#include <nfd.h> // nativefiledialog-extended

bool sigrid_filesystem::exists(const sigrid::String& filename){

    return std::filesystem::exists(filename.getStdString());
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