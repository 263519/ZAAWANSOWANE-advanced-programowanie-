#ifndef ABSTRACTINTERP4COMMAND_HH
#define ABSTRACTINTERP4COMMAND_HH

/*!
 * \file 
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractInterp4Command
 *
 *  Zawiera definicję klasy abstrakcyjnej AbstractInterp4Command.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */


#include "AbstractScene.hh"
#include "AbstractComChannel.hh"


 /*!
  * \brief Definiuje interfejs interpretera polecenia.
  *
  * Definiuje interfejs interpretera polecenia udostępnianego
  * przez daną wtyczkę.
  */
  class AbstractInterp4Command {
   public:

    virtual ~AbstractInterp4Command() {}
    
    /*!
     * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
     */
     virtual void PrintCmd() const = 0;
    /*!
     * \brief Wyświetla składnię polecenia
     */
     virtual void PrintSyntax() const = 0;
     /*!
      * \brief Wyświetla wartości wczytanych parametrów
      */
     virtual void PrintParams() const = 0;

     /*!
      * \brief Udostępnia nazwę polecenia
      */
     virtual const char* GetCmdName() const = 0;
     /*!
      * \brief Wykonuje polecenie oraz wizualizuje jego realizację
      *
      * Wykonuje polecenie oraz wizualizuje jego realizację.
      * \param[in,out]  rScn - scena zawierającą obiekty mobilne,
      * \param[in]      sMobObjName - wskaźnik na nazwę lokalizującą i identyfikującą obiekt,
      * \param[in,out]  rComChann - kanał komunikacyjny z serwerem graficznym.
      * \retval true - operacja powiodła się,
      * \retval false - w przypadku przeciwnym.
      */
     virtual bool ExecCmd(AbstractScene      &rScn, 
                          const char         *sMobObjName,
                          AbstractComChannel &rComChann) = 0;
     /*!
      * \brief Czyta wartości parametrów danego polecenia.
      *
      * Czyta ze strumienia wartości parametrów polecenia.
      * \param[in] rStrm_CmdsList - strumień, z którego są czytane parametry polecenia.
      * \retval true - operacja powiodła się,
      * \retval false - w przypadku przeciwnym.
      */
     virtual bool ReadParams(std::istream &rStrm_CmdsList) = 0;
  };


#endif
