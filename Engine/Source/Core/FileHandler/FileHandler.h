#pragma once
#include "Defines.h"
#include <string>
#include <vector>




namespace TextureGenEngine
{
    TAPI std::string ReadFile(std::string filePath);
    TAPI std::string GetAbsolutePath(std::string relativePath);
    TAPI std::string WriteFile(std::string filePath, std::string data);

    TAPI std::vector<std::string> SplitString(std::string str, char delim);
} // namespace TextureGenEngine
