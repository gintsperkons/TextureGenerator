#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
  TAPI char *LoadFileDialog(const char *title, const char *defaultPath, int numOfFilterPatterns, const char *const *filterPatterns, const char *filterDescription, int allowMultiSelect);
  TAPI char *SaveFileDialog(const char *title, const char *defaultPath, int numOfFilterPatterns, const char *const *filterPatterns, const char *filterDescription);
  TAPI char *SelectFolderDialog(const char *title, const char *defaultPath);
} // namespace TextureGenEngine
