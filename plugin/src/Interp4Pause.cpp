#include <iostream>
#include "Interp4Pause.hh"

#include <thread>
#include <iostream> 
#include <chrono>
using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause(): _Speed_mmS(0)
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mmS  << " 10  2" << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
    std::thread::id threadId = std::this_thread::get_id();
    std::cout << "ID wątku wykonującego polecenie: " << threadId << std::endl;

    AbstractMobileObj *pObj = rScn.FindMobileObj(sMobObjName);
    if (pObj == nullptr) {
        std::cerr << "Błąd: Obiekt '" << sMobObjName << "' nie istnieje w scenie." << std::endl;
        return false;
    }
    pObj->LockAccess();
    if (!pObj->Rotate()) {
          
            return false;
    }
    rComChann.LockAccess();
    if (!rComChann.Send("Pause")){
            return false;
    }
    rComChann.UnlockAccess();
    pObj->UnlockAccess();
    
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  std::cout << "Koniec Pause "<< std::endl;
    return true;
  
}

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "Pause Czas_pauzy_ms" << endl;
}
