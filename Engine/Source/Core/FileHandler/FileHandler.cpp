#include "FileHandler.h"
#include <fstream>
#include <iostream>

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
    ssize_t length = readlink("/proc/self/exe", exePath, PATH_MAX - 1);
    if (length == -1)
    {
        std::cerr << "Error getting executable path on Linux." << std::endl;
        return "";
    }
    exePath[length] = '\0';
#endif
    std::string path = std::string(exePath);
    std::size_t pos = path.find_last_of("\\/");
    return std::string(path).substr(0, pos) + "/" + relativePath;
}
