#ifndef GSV_SERVERCOMMAND_HH
#define GSV_SERVERCOMMAND_HH


/*!
 * \file
 * \brief Zawiera definicję klasy gsv::ServerCommand.
 */

#include <string>
#include <iostream>
#include "gsv-GeomParams.hh"
#include "gsv-Scene.hh"


namespace gsv {
  /*!
   * \brief Identyfikator polecenia, które ma być wykonane przez serwer.
   */
  enum Enum_CommandIndentifier  {
	 CI_Nothing /*! Nic do wykonania */,
	 CI_AddObj /*! Dodanie obiektu */,
	 CI_UpdateObj /*! Uaktualnienie ustawień parametrów obiektu */,
	 CI_Display /*! Wymuszenie wyświetlenia sceny */,
	 CI_Close /*! Zakończenie pracy serwera */,
	 CI_Clear /*! Usuwa wszystkie elementy sceny */
  };
  
  /*!
   * \brief Modeluje interpreter polecenia odbieranego przez serwer.
   */
  class ServerCommand {
    /*!
     * \brief Kwalifikowana nazwa obiektu, dka którego ma być 
     *        wykonane dane polecenie.
     */
    std::string  _ObjQName;
    /*!
     * \brief Identyfikator polecenia
     */
    Enum_CommandIndentifier   _CmdID = CI_Nothing;

    /*!
     * \brief Geometryczne parametry obiektu.
     */
    gsv::GeomParams  _ObjParams;

   private:
    /*!
     * \brief Wstawia do sceny nowy obiekt.
     */
     bool InsertNewObj(Scene &rScn);
    /*!
     * \brief Aktualizuje ustawienia obiektu geometrycznego.
     */
     bool UpdateObj(Scene &rScn);
    
   public:
    /*!
     * \brief Udostępnia identyfikator polecenia.
     */
    Enum_CommandIndentifier GetCmdID() const { return _CmdID; }
    /*!
     * \brief Zmienia identyfikator polecenia.
     */
    void SetCmdID(Enum_CommandIndentifier CmdID) { _CmdID = CmdID; }
    /*!
     * \brief Udostępnia kwalifikowaną nazwę obiektu geometrycznego.
     */
    const std::string & GetQName() const { return _ObjQName; }
    /*!
     * \brief Zmienia kwalifikowaną nazwę obiektu geometrycznego.
     */
    void SetQName(const std::string &sName) { _ObjQName = sName; }
    
    /*!
     * \brief Udostępnia do odczytu parametry geometryczne, które mają
     *        być użyte dla zadanego obiektu graficznego.
     */
    const gsv::GeomParams & GetParams() const { return _ObjParams; }
    /*!
     * \brief Udostępnia do modyfikacji parametry geometryczne, które mają
     *        być użyte dla zadanego obiektu graficznego.
     */
    gsv::GeomParams & UseParams() { return _ObjParams; }
    /*!
     * \brief Wykonuje polecenie przesłane przez klienta.
     */
    bool ExecCmd(Scene &rScn);
    /*!
     * \brief Czyta i wykonuje polecenie.
     */
    bool ReadCmd_Exec(const std::string &rCmdText, Scene &rScn);
  };
}


/*!
 * \brief Wczytuje identyfikator polecenia ze strumienia
 */
std::istream &operator >> (std::istream &rIStrm, gsv::Enum_CommandIndentifier &rCmdID);
/*!
 * \brief Zapisuje identyfikator polecenia do strumienia
 */
std::ostream &operator << (std::ostream &rOStrm, gsv::Enum_CommandIndentifier CmdID);


/*!
 * \brief Wczytuje polecenie ze strumienia
 */
std::istream &operator >> (std::istream &rIStrm, gsv::ServerCommand &rCmd);
/*!
 * \brief Zapisuje polecenie do strumienia
 */
std::ostream &operator << (std::ostream &rOStrm, const gsv::ServerCommand &rCmd);

#endif
