#include <iostream>
#include "Interp4Rotate.hh"
#include <thread>
#include <iostream> 
#include <chrono>

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _Speed_mmS(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mmS  << " 10  2" << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
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
    if (!rComChann.Send("Rotate")){
            return false;
    }
    rComChann.UnlockAccess();
    pObj->UnlockAccess();
    
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  std::cout << "Koniec Rotate "<< std::endl;
    return true;
  
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "Rotate nazwa_obiektu nazwa_osi szybko±¢_k¡towa k¡t_obrotu" << endl;
}
