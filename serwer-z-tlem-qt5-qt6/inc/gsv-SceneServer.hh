#ifndef  GSV_SCENESERVER_HH
#define  GSV_SCENESERVER_HH

/*!
 * \file
 * \brief Zawiera definicję klasy SceneServer.
 *
 */

#include "gsv-Scene.hh"
#include "gsv-CommandInterpreter.hh"
#include "gsv-BufferedScene.hh"


namespace gsv {
/*!
 * \brief Modeluje serwer sceny
 *
 *  Modeluje serwer sceny, który przyjmuje polecenia zmianiające
 *  jej stan.
 */
 class SceneServer {
  /*!
   *  \brief Buforowana scena na potrzeby wyświetlania i interpretacji
   *         poleceń klienta.
   */
   BufferedScene      _BuffScn;
  /*!
   * \brief Interpreter poleceń przychodzących do serwera.
   */
   gsv::CommandInterpreter  _CmdInterp;
  /*!
   * \brief Kontynuuacja operacji w pętlach poszczególnych wątków.
   */
   bool  _ContinueLooping = true;
  public:

   SceneServer() {}
  /*!
   * \brief Ustawia nakaz zakończenia pętli poszczególnych wątków.
   */
   void FinishLooping() { _ContinueLooping = false; }
  /*!
   * \brief Czy pętle wątków powinny być kontynuowane?
   */
   bool ShouldContinueLooping() const { return _ContinueLooping; }
  /*!
   * \brief
   */
  bool ShouldContinueListening() const { return _CmdInterp.ShouldContinueListening(); }
  /*!
   * \brief Wykonuje plecenia pobierając je z bufora poleceń
   */
   void ExecCmds();
  
  /*!
   * \brief Nasłuchuje poleceń dla interpretera
   */
   void Listing4InterpCmds(int Socket);
  /*!
   * \brief Udostępnia buforowaną scenę w trybie tylko do odczytu.
   */
   const BufferedScene& GetBuffScn() const { return _BuffScn; }
  /*!
   * \brief Udostępnia buforowaną scenę w trybie modyfikacji.
   */
   BufferedScene& UseBuffScn() { return _BuffScn; }
 };
}
#endif
