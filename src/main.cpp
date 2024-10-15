#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

using namespace std;


int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);


  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);

   // Obsługa Interp4Rotate
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so", RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: libInterp4Rotate.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Rotate, "CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Rotate.so" << endl;
    dlclose(pLibHnd_Rotate);
    return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  AbstractInterp4Command *pCmd_Rotate = pCreateCmd_Rotate();

  cout << endl;
  cout << pCmd_Rotate->GetCmdName() << endl;
  cout << endl;
  pCmd_Rotate->PrintSyntax();
  cout << endl;
  pCmd_Rotate->PrintCmd();
  cout << endl;

  delete pCmd_Rotate;
  dlclose(pLibHnd_Rotate);
}