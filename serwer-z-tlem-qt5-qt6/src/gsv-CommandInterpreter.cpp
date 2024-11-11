#include <iostream>
#include "gtsDebug.hh"
#include "gsv-CommandInterpreter.hh"
#include "gsv-RGB.hh"
#include "gsv-ServerCommand.hh"


using namespace std;





/*!
 * Pobiera z kolejki polecenie graficzne i usuwa je z niej.
 * \param[out] rCmd - zawiera pobrane polecenie, o ile istnieje.
 * \retval true - operacja powiodła się,
 * \retval false - w przeciwnym przypadku.
 */
bool gsv::SrvCommandQueue::Pop_SrvCmd(gsv::ServerCommand &rCmd)
{
  if (_SrvCmdQueue.empty()) return false;
  rCmd = _SrvCmdQueue.front();
  _SrvCmdQueue.pop();
  return true;
}



/*!
 * Dodaje nowe polecenie do kolejki, które ma wykonać serwer.
 * \param[in] sCmdLine - tekst polecenia, które ma wykonać serwer.
 */
void  gsv::CommandInterpreter::AddCmd(const char* sCmdLine)
{
  //  DOut1( "Polecenie: " << sCmdLine );
  _CmdBuff.Push(sCmdLine);
}




/*
 * Wykonuje polecenie, które jest jako pierwsze w kolejce.
 * Polecenie pobierane jest w wewnętrznej kolejki poleceń,
 * które reprezentowane jest przez pole 
 * \link CommandInterpreter::_CmdBuff _CmdBuff\endlink.
 */
bool gsv::CommandInterpreter::ExecCmd(BufferedScene &rBScn)
{
  std::string  CmdLine;

  if (_CmdBuff.IsEmpty()) return false;
  _CmdBuff.Pop(CmdLine);
  InterpCmd(CmdLine,rBScn);
  return true;
}



/*!
 * Wykonuje wszystkie polecenia graficzne dla danej sceny
 * znajdujące się w kolejki poleceń.
 * \param[in,out]  rBScn - scena, dla której mają zostać wykonane polecenia.
 * \retval true - wszyskie polecenia zostały poprawnie wykonane,
 * \retval false - co najmniej jedno z poleceń nie zostało poprawnie wykonane.
 */
bool gsv::CommandInterpreter::ExecCmds4Scene(BufferedScene &rBScn)
{
  gsv::ServerCommand   SrvCmd;
  bool   Result = true;

  if (IsEmpty_GraphCmds()) return true;
  rBScn.LockAccessToCurrScn();
  while (Pop_GraphCmd(SrvCmd)) {
    if (!SrvCmd.ExecCmd(rBScn.UseCurrScn())) Result = false;
  }
  rBScn.MarkTrace0Change();
  rBScn.UnlockAccessToCurrScn();
  return Result;
}



/*!
 * Rozpoznaje polecenie i je wykonuje.
 * \param[in] rCmdLine - treść rozpoznawanego polecenia.
 * \param[in,out] rBScn - zawiera odesłanie do bieżącej sceny, dla której dane polecenie
 *                        ma zostać wykonane.
 * \retval true - jeżeli z kolejki zostało pobrane jakieś polecenie,
 * \retval false - w przeciwnym przypadku.
 */
bool gsv::CommandInterpreter::InterpCmd(const std::string &rCmdLine, BufferedScene  &rBScn)
{
  istringstream        IStrm(rCmdLine);
  gsv::ServerCommand   SrvCmd;


  if ((IStrm >> SrvCmd).fail()) return false;

  switch (SrvCmd.GetCmdID()) {
    case gsv::CI_Nothing: return true;

    case gsv::CI_AddObj:      
    case gsv::CI_UpdateObj:
      Push_GraphCmd(SrvCmd);
      ExecCmds4Scene(rBScn);
      break;
      
    case gsv::CI_Display:
      ExecCmds4Scene(rBScn);
      break;

    case gsv::CI_Clear:
      Push_GraphCmd(SrvCmd);
      ExecCmds4Scene(rBScn);
      break;
      
    case gsv::CI_Close:
      CancelContinueListening();
      return true;
  }

  return true;
}
