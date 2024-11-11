#ifndef ACCESSCONTROLL_HH
#define ACCESSCONTROLL_HH

#include <mutex>

/*!
 * \file
 * \brief Zawiera definicję klasy AccessControl
 */


/*!
 * \brief Przechowuje informacje o zmianie
 *
 *  Przechowuje informacje o zmianie z zabezpieczeniem
 *  wielowątkowej modyfikacji.
 */
class AccessControl {
   /*!
    * \brief Zapewnia wyłączny dostęp do obiektu w trakcie modyfikacji.
    */
    std::mutex   _InternalGuard;
   /*!
    * \brief Przechowuje informacje o zmianie.
    *
    * Przechowuje informacje o tym czy zmiana nastąpiła (\p true) czy też
    * nie (\p false).
    */ 
    bool         _Changed = false;
   /*!
    * \brief Wykorzystywany do blokowania całej sceny.
    */
    std::mutex  _ExternalGuard;
 public:
  /*!
   * \brief Dostęp do informacji o zmianie.
   *
   * Dostęp do informacji o zmianie.
   * \retval true - gdy zmiana nastąpiła.
   * \retval false - w przypadku przeciwnym.
   */
   bool IsChanged() const { return _Changed; }
  /*!
   * \brief Zaznaczenie, że zmiana nastąpiła.
   */
   void MarkChange() { _InternalGuard.lock();  _Changed = true;  _InternalGuard.unlock(); }
  /*!
   * \brief Skasowanie informacji, że zmiana nastąpiła.
   */
   void CancelChange() { _InternalGuard.lock();  _Changed = false;  _InternalGuard.unlock(); }
  /*!
   * \brief Zamyka dostęp całej sceny.
   */
   void LockAccess() { _ExternalGuard.lock(); }
  /*!
   * \brief Otwiera dostęp do całej sceny.
   */
   void UnlockAccess() { _ExternalGuard.unlock(); } 
};




#endif 
