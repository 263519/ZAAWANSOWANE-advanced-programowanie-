#include "ProgramInterpreter.hh"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"
#include "Sender.hh"
#include "xmlinterp.hh"
#include "LibInterface.hh"
#include <thread>
#include <mutex>

using namespace std;
using namespace xercesc;
//#define DEBUG 1

#define LINE_SIZE 500

bool ExecPreprocesor(const char *FileName, istringstream &IStrm4Cmds)
{
    string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    ostringstream OTmpStrm;
    Cmd4Preproc += FileName;
    FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

    if (!pProc) return false;
    while (fgets(Line, LINE_SIZE, pProc)) {
        OTmpStrm << Line;
    }

    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

void ExecMoveCmd(std::shared_ptr<AbstractInterp4Command> pCmd_move, Scene& scene, const string& objectName, ComChannel& comChann) {
    pCmd_move->ExecCmd(scene, objectName.c_str(), comChann);
}

void ExecRotateCmd(std::shared_ptr<AbstractInterp4Command> pCmd_rotate, Scene& scene, const string& objectName, ComChannel& comChann) {
    pCmd_rotate->ExecCmd(scene, objectName.c_str(), comChann);
}

int main (int argc, char* args[]) 
{
    Set4LibInterfaces libSet;

    void *pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Move)(void);
    void *pFun_move;

    if (!pLibHnd_Move) {
        cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
        return 1;
    }

    pFun_move = dlsym(pLibHnd_Move, "CreateCmd");
    if (!pFun_move) {
        cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
        return 1;
    }
    pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_move);

    std::shared_ptr<AbstractInterp4Command> pCmd_move = std::shared_ptr<AbstractInterp4Command>(pCreateCmd_Move());

    void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
    void *pFun_rotate;

    if (!pLibHnd_Rotate) {
        cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
        return 1;
    }

    pFun_rotate = dlsym(pLibHnd_Rotate, "CreateCmd");
    if (!pFun_rotate) {
        cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
        return 1;
    }
    pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_rotate);

    std::shared_ptr<AbstractInterp4Command> pCmd_rotate = std::shared_ptr<AbstractInterp4Command>(pCreateCmd_Rotate());

    Scene scene;
    ComChannel comChann;

    ProgramInterpreter program_interp;
    program_interp.Read_XML_Config("config/config.xml", libSet, scene);

    
    std::thread moveThread(ExecMoveCmd, pCmd_move, std::ref(scene), "Podstawa2", std::ref(comChann));
    std::thread rotateThread(ExecRotateCmd, pCmd_rotate, std::ref(scene), "Podstawa.Ramie1", std::ref(comChann));

    moveThread.join();
    rotateThread.join();

    cout << "Main koniec" << endl;

    return 0;
}
