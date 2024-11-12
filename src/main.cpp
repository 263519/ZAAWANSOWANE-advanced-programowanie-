
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






using namespace std;
using namespace xercesc;
//#define DEBUG 1



#define LINE_SIZE 500
bool ExecPreprocesor( const char *FileName, istringstream &IStrm4Cmds )
{
    string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    ostringstream OTmpStrm;
    Cmd4Preproc += FileName;
    FILE *pProc = popen(Cmd4Preproc.c_str(),"r");

    if (!pProc) return false;
    while (fgets(Line,LINE_SIZE,pProc)) {
        OTmpStrm << Line;
    }

    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}



int main (int argc, char* args[]) 
{
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

ProgramInterpreter program_interp;
program_interp.Read_XML_Config("config/config.xml");

}
