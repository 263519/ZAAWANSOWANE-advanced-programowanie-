#ifndef GSV_COMMANDINTERPRETER_HH
#define GSV_COMMANDINTERPRETER_HH

#include "gsv-BufferedScene.hh"
#include "gsv-CommandBuffer.hh"
#include "gsv-ServerCommand.hh"
#include <queue>
#include <mutex>


/*!
 * \brief Interpreter poleceń dla serwera
 *
 * Plik zawiera definicję klasy modelującej interpreter
 * poleceń dla serwera.
 */



namespace gsv {

  /*!
   * \brief Modeluje kolejkę poleceń dla serwera.
   */
  class SrvCommandQueue {
    /*!
     * \brief Nadzoruje dostęp do kolejki polecń graficznych.
     */
     std::mutex      _Mutex_GraphCmdQueue;
    /*!
     * \brief Kolejka poleceń serwera
     */
     std::queue<gsv::ServerCommand>   _SrvCmdQueue;
    
    public:
    /*!
     * \brief Czy kolejka poleceń wykonywanych dla scey jest pusta?
     */
      bool IsEmpty() const { return _SrvCmdQueue.empty(); }
     /*!
      * \brief Pobiera z kolejki polecenie graficzne.
      */
      bool Pop_SrvCmd(gsv::ServerCommand &rCmd);
    
     /*!
      * \brief Umieszcza w kolejce polecenie graficzne.
      */
      void Push_SrvCmd(const gsv::ServerCommand &rCmd)
       {
	 std::lock_guard<std::mutex> oGuard_PrepScn(_Mutex_GraphCmdQueue);
	 _SrvCmdQueue.push(rCmd);
       }
  };




 /*!
  * \brief Interpreter poleceń dla serwera
  *
  * Modeluje interpreter poleceń wysyłanych do serwera.
  */
 class CommandInterpreter {

   /*!
    * \brief Decyduje o kontynuowaniu nasłuchu lub jego przerwaniu.
    */
    bool           _ContinueListening = true;
   /*!
    * \brief Bufor poleceń, które ma wykonać serwer
    */
    CommandBuffer  _CmdBuff;
   /*!
    * \brief Kolejka poleceń graficznych
    */
    gsv::SrvCommandQueue _GraphCmdQueue;
  
  private:
   /*!
    * \brief Rozpoznaje polecenie i je wykonuje.
    */
    bool InterpCmd(const std::string &rCmdLine, BufferedScene &rBScn);
   /*!
    * \brief Umieszcza w kolejce polecenie graficzne.
    */
    void Push_GraphCmd(const gsv::ServerCommand &rCmd)
                        { _GraphCmdQueue.Push_SrvCmd(rCmd); }
   /*!
    * \brief Pobiera z kolejki polecenie graficzne.
    */
    bool Pop_GraphCmd(gsv::ServerCommand &rCmd)
                        { return _GraphCmdQueue.Pop_SrvCmd(rCmd); }
    /*!
     * \brief Czy kolejka poleceń wykonywanych dla scey jest pusta?
     */
    bool IsEmpty_GraphCmds() const
                        { return _GraphCmdQueue.IsEmpty(); }

   /*!
    * \brief Wykonuje polecenia graficzne dla danej sceny z kolejki poleceń.
    */
    bool ExecCmds4Scene(BufferedScene &rScn);
  public:
   /*!
    * \brief Wykonuje polecenie, które jest jako pierwsze w kolejce.
    */
   bool ExecCmd(BufferedScene &rBScn);

   /*!
    * \brief Dostęp do informacji decydującej o tym, czy serwer ma nasłuchiwać,
    *        czy przerwać nasłuch na swoim porcie.
    */
    bool ShouldContinueListening() const { return _ContinueListening; }
   /*!
    * \brief Serwer ma nasłuchiwać.
    */
    void MarkContinueListening() { _ContinueListening = true; }
   /*!
    * \brief Serwer ma przerwać nasłuchiwanie.
    */
    void CancelContinueListening() { _ContinueListening = false; }
   /*!
    * \brief Dodaje nowe polecenie do kolejki, które ma wykonać serwer.
    */
    void AddCmd(const char* sCmdLine);
 };
}
#endif
