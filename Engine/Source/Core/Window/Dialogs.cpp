#include "Dialogs.h"
#include "Core/Logger/Logger.h"
#include <tinyfiledialogs.h>

char *TextureGenEngine::LoadFileDialog(const char *title, const char *defaultPath, int numOfFilterPatterns, const char *const *filterPatterns, const char *filterDescription, int allowMultiSelect)
{
  return tinyfd_openFileDialog(title, defaultPath, numOfFilterPatterns, filterPatterns, filterDescription, allowMultiSelect);
  // char const *lFilterPatterns[2] = {"*.tgsn"};
  // char const * returned = tinyfd_openFileDialog("Load Save File","",1,lFilterPatterns,"TexGen Save Files",0);

  // LOG_DEBUG("test out %s\n", returned);
}

char *TextureGenEngine::SaveFileDialog(const char *title, const char *defaultPath, int numOfFilterPatterns, const char *const *filterPatterns, const char *filterDescription)

{
  LOG_DEBUG("test%s\n",tinyfd_saveFileDialog(title, defaultPath, numOfFilterPatterns, filterPatterns, filterDescription));
  return tinyfd_saveFileDialog(title, defaultPath, numOfFilterPatterns, filterPatterns, filterDescription);
}

char *TextureGenEngine::SelectFolderDialog(const char *title, const char *defaultPath)
{
  //LOG_DEBUG("test%s\n",tinyfd_selectFolderDialog(title, defaultPath));
  return tinyfd_selectFolderDialog(title, defaultPath);
}
