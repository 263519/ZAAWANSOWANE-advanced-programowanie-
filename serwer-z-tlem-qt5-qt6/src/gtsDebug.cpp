#include <cstring>
#include "gtsDebug.hh"


namespace gts {
 bool         Debug_Display = true;
 std::string  Debug_FunName;

 const char *MoveToLastSlash(const char* sFileName)
 {
  const char* pStr = sFileName;
  const char* pLast = strrchr(pStr,'/');

  return pLast == nullptr ? sFileName : pLast+1;
 }

}
