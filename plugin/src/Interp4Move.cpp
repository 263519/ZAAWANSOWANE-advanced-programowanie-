#include <iostream>
#include "Interp4Move.hh"
#include "ComChannel.hh"
#include "Cuboid.hh"
#include <mutex>
#include <thread>
#include <iostream> 
#include <chrono>

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mmS  << " 10  2" << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
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
    if (!pObj->Move()) {
          
            return false;
    }
    rComChann.LockAccess();
    if (!rComChann.Send("Ruch zakończony pomyślnie."))
            return false;
    }
    rComChann.UnlockAccess();
    pObj->UnlockAccess();
    
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::cout << "Koniec Move "<< std::endl;
    return true;
  
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
