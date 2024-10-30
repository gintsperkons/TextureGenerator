#include "FileHandler.h"
#include <fstream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <libloaderapi.h>
#elif defined(__linux__)
#include <unistd.h>
#include <linux/limits.h>
#endif

std::string TextureGenEngine::ReadFile(std::string filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        printf("Failed to read %s! File doesn't exist.", filePath.c_str());
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

std::string TextureGenEngine::GetAbsolutePath(std::string relativePath)
{
#ifdef _WIN32
        char exePath[MAX_PATH];
        GetModuleFileNameA(NULL, exePath, MAX_PATH);
#elif defined(__linux__)
        char exePath[PATH_MAX];
        readlink("/proc/self/exe", exePath, PATH_MAX);
#endif
        std::string::size_type pos = std::string(exePath).find_last_of("\\/");
        return std::string(exePath).substr(0, pos) + "/" + relativePath;
    
    
}
