#ifndef GSV_BUFFEREDSCENE_HH
#define GSV_BUFFEREDSCENE_HH

/*!
 * \file
 * \brief Zawiera definicję klasy BufferedScene
 */

#include "gsv-Scene.hh"
#include <mutex>
#include <memory>


namespace gsv {

 /*!
  * \brief Modeleluje buforowaną scenę.
  *
  * Modeleluje buforowaną scenę. Pozwala to wykonywać
  * niezależnie peracje wyświetlania i przebudowywania sceny.
  */
 class BufferedScene {
  /*!
   * \brief Scena zawierającej bryły reprezentowane przez
   *        obiekty graficzne.
   */
   Scene               _Scene;
  /* !
   * \brief Wskaźnik na wyświetlaną bieżącą scenę.
   */
  //   Scene              *_pCurrScn = nullptr;
  /*!
   * \brief Zabezpiecza selektywny dostęp do aktualnej sceny.
   */
   std::mutex          _Mutex_CurrScn;

  /*!
   * \brief Zabezpiecza selektywny dostęp do przygotowywanej sceny.
   */
   std::mutex          _Mutex_PrepScn;
  /*!
   * \brief Ślad zmiany
   */
   bool                _Trace0Change = false;

  public:
   /*!
    * \brief Inicjalizuje pola dla aktualnej sceny i przygotowywanej.
    */
    BufferedScene() {}
   /*!
    * \brief Udostępnia informacje o zmianie.
    */
    bool IsChanged() const { return _Trace0Change; }
   /*!
    * \brief Zaznacza zmianę
    */
    void MarkTrace0Change() { _Trace0Change = true; }
   /*!
    * \brief Kasuje ślad zmiany
    */
    void CancelTrace0Change() { _Trace0Change = false; }

  /*!
   * \brief Zablokowanie dostępu do bieżącej sceny
   */
   void LockAccessToCurrScn() { _Mutex_CurrScn.lock(); }



  /*!
   * \brief Otwarcie dostępu do bieżącej sceny
   */
   void UnlockAccessToCurrScn() { _Mutex_CurrScn.unlock(); }
  /*!
   * \brief Dostęp do bieżącej sceny.
   */
   const Scene& GetCurrScn() const { return _Scene; }
  /*!
   * \brief Dostęp do bieżącej sceny z możliwością modyfikacji.
   */
   Scene& UseCurrScn() { return _Scene; }
 };
}

#endif
