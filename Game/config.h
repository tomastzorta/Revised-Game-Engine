//
// Created by Tomas Tzorta on 07/12/2023.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

std::string GetAssetDirectory()
{
#ifdef NDEBUG //Release build
    return "@ASSET_FOLDER_NAME@/";
#else //Debug build
    return "@ASSET_FOLDER_PATH@/";
#endif
}

#endif //CONFIG_H
