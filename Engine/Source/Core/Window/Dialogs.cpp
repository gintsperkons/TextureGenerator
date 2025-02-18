#include "Dialogs.h"
#include "Core/Logger/Logger.h"
#include <tinyfiledialogs.h>

char *TextureGenEngine::LoadFileDialog(const char *title, const char *defaultPath, int numOfFilterPatterns, const char *const *filterPatterns, const char *filterDescription, int allowMultiSelect)
{
  return tinyfd_openFileDialog(title, defaultPath, numOfFilterPatterns, filterPatterns, filterDescription, allowMultiSelect);
}

char *TextureGenEngine::SaveFileDialog(const char *title, const char *defaultPath, int numOfFilterPatterns, const char *const *filterPatterns, const char *filterDescription)

{
  return tinyfd_saveFileDialog(title, defaultPath, numOfFilterPatterns, filterPatterns, filterDescription);
}

char *TextureGenEngine::SelectFolderDialog(const char *title, const char *defaultPath)
{
  return tinyfd_selectFolderDialog(title, defaultPath);
}
