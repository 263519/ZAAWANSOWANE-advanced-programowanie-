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

void ExecSetCmd(std::shared_ptr<AbstractInterp4Command> pCmd_set, Scene& scene, const std::string& objectName, ComChannel& comChann) {
    pCmd_set->ExecCmd(scene, objectName.c_str(), comChann);
}

void ExecPauseCmd(std::shared_ptr<AbstractInterp4Command> pCmd_pause, Scene& scene, const std::string& objectName, ComChannel& comChann) {
    pCmd_pause->ExecCmd(scene, objectName.c_str(), comChann);
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

    void *pLibHnd_Set = dlopen("libInterp4Set.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Set)(void);
    void *pFun_set;

    if (!pLibHnd_Set) {
        std::cerr << "!!! Brak biblioteki: libInterp4Set.so" << std::endl;
        return 1;
    }

    pFun_set = dlsym(pLibHnd_Set, "CreateCmd");
    if (!pFun_set) {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Set.so" << std::endl;
        return 1;
    }
    pCreateCmd_Set = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_set);
    std::shared_ptr<AbstractInterp4Command> pCmd_set = std::shared_ptr<AbstractInterp4Command>(pCreateCmd_Set());

   
    void *pLibHnd_Pause = dlopen("libInterp4Pause.so", RTLD_LAZY);
    AbstractInterp4Command *(*pCreateCmd_Pause)(void);
    void *pFun_pause;

    if (!pLibHnd_Pause) {
        std::cerr << "!!! Brak biblioteki: libInterp4Pause.so" << std::endl;
        return 1;
    }

    pFun_pause = dlsym(pLibHnd_Pause, "CreateCmd");
    if (!pFun_pause) {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd w libInterp4Pause.so" << std::endl;
        return 1;
    }
    pCreateCmd_Pause = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_pause);
    std::shared_ptr<AbstractInterp4Command> pCmd_pause = std::shared_ptr<AbstractInterp4Command>(pCreateCmd_Pause());
    //    ProgramInterpreter program_interpreter;
//    program_interpreter.Read_XML_Config("config/config.xml");
//  //   istringstream IStrm4Cmds;

// //     ExecPreprocesor("config/data.cmd",  IStrm4Cmds);
// //     cout  << IStrm4Cmds.str() << endl;
   

// //      cout << "Port: " << PORT << endl;
// //   Scene               Scn;
// //   int                 Socket4Sending;   

// //   if (!OpenConnection(Socket4Sending)) return 1;
  
// //   Sender   ClientSender(Socket4Sending,&Scn);
// //   //  thread   Thread4Sending(Fun_Sender, Socket4Sending, &ClientSender);

// //   thread   Thread4Sending(Fun_CommunicationThread, &ClientSender);
// //   const char *sConfigCmds =
// // "Clear\n"
// // "AddObj Name=Podstawa1 RGB=(200,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
// // "AddObj Name=Podstawa1.Ramie1 RGB=(200,200,300) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
// // "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,300) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";     



// //   cout << "Konfiguracja:" << endl;
// //   cout << sConfigCmds << endl;
  
// //   Send(Socket4Sending,sConfigCmds);
  

// //   // cout << "Akcja:" << endl;    
// //   // for (GeomObject &rObj : Scn._Container4Objects) {
// //   //   usleep(20000);
// //   //   ChangeState(Scn);
// //   //   Scn.MarkChange();
// //   //   usleep(100000);
// //   // }
// //   // usleep(100000);

// //   //-------------------------------------
// //   // Należy pamiętać o zamknięciu połączenia.
// //   // Bez tego serwer nie będzie reagował na
// //   // nowe połączenia.
// //   //

// #ifdef DEBUG
// Scene scene;

//     Cuboid* cuboid1 = new Cuboid();
//     cuboid1->SetName("Cuboid_A");
//     cuboid1->SetPosition_m(Vector3D(1.0, 2.0, 3.0));
//     cuboid1->SetAng_Roll_deg(10.0);
//     cuboid1->SetAng_Pitch_deg(20.0);
//     cuboid1->SetAng_Yaw_deg(30.0);

//     Cuboid* cuboid2 = new Cuboid();
//     cuboid2->SetName("Cuboid_B");
//     cuboid2->SetPosition_m(Vector3D(4.0, 5.0, 6.0));
//     cuboid2->SetAng_Roll_deg(15.0);
//     cuboid2->SetAng_Pitch_deg(25.0);
//     cuboid2->SetAng_Yaw_deg(35.0);

//     Cuboid* cuboid3 = new Cuboid();
//     cuboid3->SetName("Cuboid_C");
//     cuboid3->SetPosition_m(Vector3D(7.0, 8.0, 9.0));
//     cuboid3->SetAng_Roll_deg(20.0);
//     cuboid3->SetAng_Pitch_deg(30.0);
//     cuboid3->SetAng_Yaw_deg(40.0);

    
//     scene.AddMobileObj(cuboid1);
//     scene.AddMobileObj(cuboid2);
//     scene.AddMobileObj(cuboid3);

    
//      const char* names[] = {"Cuboid_A", "Cuboid_B", "Cuboid_C", "Cuboid_D"};
//     for (const char* name : names) {
//         AbstractMobileObj* obj = scene.FindMobileObj(name);
//         if (obj) {
//             std::cout << "Znaleziono obiekt: " << obj->GetName() << std::endl;
//             static_cast<Cuboid*>(obj)->DisplayParameters();
//         } else {
//             std::cout << "Nie znaleziono obiektu o nazwie: " << name << std::endl;
//         }
//     }

// #endif




//   // cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
//   // Send(Socket4Sending,"Close\n");
//   // ClientSender.CancelCountinueLooping();
//   // Thread4Sending.join();
//   // close(Socket4Sending);



    Scene scene;
    ComChannel comChann;

    ProgramInterpreter program_interp;
    program_interp.Read_XML_Config("config/config.xml", libSet, scene);

    
    std::thread moveThread(ExecMoveCmd, pCmd_move, std::ref(scene), "Podstawa", std::ref(comChann));
    std::thread rotateThread(ExecRotateCmd, pCmd_rotate, std::ref(scene), "Podstawa.Ramie1", std::ref(comChann));
    std::thread setThread(ExecMoveCmd, pCmd_move, std::ref(scene), "Podstawa", std::ref(comChann));
    std::thread pauseThread(ExecRotateCmd, pCmd_rotate, std::ref(scene), "Podstawa.Ramie1", std::ref(comChann));

    moveThread.join();
    rotateThread.join();
    setThread.join();
    pauseThread.join();
    
    cout << "Main koniec" << endl;

    return 0;
}
