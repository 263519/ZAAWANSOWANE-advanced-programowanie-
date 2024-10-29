#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

using namespace std;

int main() {
    void *pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Move)(void);
    void *pFun;

    if (!pLibHnd_Move) {
        cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
        return 1;
    }

    pFun = dlsym(pLibHnd_Move, "CreateCmd");
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

    void *pLibHnd_Set = dlopen("libInterp4Set.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Set)(void);

    if (!pLibHnd_Set) {
        cerr << "!!! Brak biblioteki: libInterp4Set.so" << endl;
        return 1;
    }

    pFun = dlsym(pLibHnd_Set, "CreateCmd");
    if (!pFun) {
        cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Set.so" << endl;
        dlclose(pLibHnd_Set);
        return 1;
    }
    pCreateCmd_Set = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

    AbstractInterp4Command *pCmd_Set = pCreateCmd_Set();
    cout << endl;
    cout << pCmd_Set->GetCmdName() << endl;
    cout << endl;
    pCmd_Set->PrintSyntax();
    cout << endl;
    pCmd_Set->PrintCmd();
    cout << endl;

    delete pCmd_Set;
    dlclose(pLibHnd_Set);

    void *pLibHnd_Pause = dlopen("libInterp4Pause.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Pause)(void);

    if (!pLibHnd_Pause) {
        cerr << "!!! Brak biblioteki: libInterp4Pause.so" << endl;
        return 1;
    }

    pFun = dlsym(pLibHnd_Pause, "CreateCmd");
    if (!pFun) {
        cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Pause.so" << endl;
        dlclose(pLibHnd_Pause);
        return 1;
    }
    pCreateCmd_Pause = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

    AbstractInterp4Command *pCmd_Pause = pCreateCmd_Pause();
    cout << endl;
    cout << pCmd_Pause->GetCmdName() << endl;
    cout << endl;
    pCmd_Pause->PrintSyntax();
    cout << endl;
    pCmd_Pause->PrintCmd();
    cout << endl;

    delete pCmd_Pause;
    dlclose(pLibHnd_Pause);

    return 0;
}
