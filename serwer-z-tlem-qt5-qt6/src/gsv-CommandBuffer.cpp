#include "gsv-CommandBuffer.hh"


/*!
 * Umieszcza w buforze tekst polecenia.
 * \param[in] sLine - tekst zawierający polecenie.
 */
void gsv::CommandBuffer::Push(const char* sLine)
{
  std::lock_guard<std::mutex>  oGuard(_AccGuard);
  push(sLine);
}



/*!
 * Pobiera z bufora polecenie.
 * \retval true - gdy operacja się powiodła,
 * \retval false - gdy bufor jest pusty.
 */
bool gsv::CommandBuffer::Pop(std::string &rCmdLine)
{
 if (IsEmpty()) return false;
 std::lock_guard<std::mutex>  oGuard(_AccGuard);
 rCmdLine = front();
 pop();
 return true;
}
