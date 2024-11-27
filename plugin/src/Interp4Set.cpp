#include <iostream>
#include "Interp4Set.hh"

#include <thread>
#include <iostream> 
#include <chrono>
using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _Speed_mmS(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mmS  << " 10  2" << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
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
    if (!rComChann.Send("Set")){
            return false;
    }
    rComChann.UnlockAccess();
    pObj->UnlockAccess();
    
  std::this_thread::sleep_for(std::chrono::microseconds(1000));
  std::cout << "Koniec Set "<< std::endl;
  return true;
  
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << " Set nazwa_obiektu wsp_x wsp_y wsp_z kat_OX kat_OY kat_OZ" << endl;
}
