#ifndef GSV_COMMANDBUFFER_HH
#define GSV_COMMANDBUFFER_HH

#include <queue>
#include <string>
#include <mutex>

/*!
 * \file
 * \brief Bufor poleceń modelowany przez klasę ComdsBuff
 * 
 */


namespace gsv {
/*!
 * \brief Modeluje bufor poleceń
 *
 * Modeluje bufor poleceń, który przystosowany jest do pracy
 * wielowątkowej. Bufor modelowany jest przez kolejke typu FIFO.
 */
 class CommandBuffer: private std::queue<std::string> {
  /*!
   * \brief Zapobiega próbom jednoczesnej modyfikacji
   *
   * Zaobiega jednoczesnej modyfikacji listy przez
   * kilka wątków.
   */
   std::mutex  _AccGuard;
  public:
  /*!
   * \brief
   */
   void Push(const char* sLine);
  /*!
   * \brief Pobiera 
   */
   bool Pop(std::string &rCmdLine);
  /*!
   * \brief Sprawdza czy bufor jest pusty.
   *
   * Sprawdza czy bufor jest pusty.
   * \retval true - gdy jest pusty,
   * \retval false - w przypadku przeciwnym.
   */
  bool IsEmpty() const { return empty(); }
 };
}

#endif
