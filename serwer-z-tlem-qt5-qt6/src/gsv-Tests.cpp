#include <iostream>
#include <sstream>
#include "gsv-GeomParams.hh"
#include "gsv-ServerCommand.hh"

using namespace std;

namespace gsv {


 void Test_Params()
 {
  gsv::GeomParams  Params;

  cout << endl << endl << " Params: " << Params << endl;
  istringstream IStrm("Shift=(2, 1, 3) Scale=(0.1, 0.3, 0.4) RotXYZ_deg=(10, 20, 30.5) Trans_m=(20, 30, 40) RGB=(160, 190, 220)");
  IStrm >> Params;
  if (IStrm.fail()) {
    cout << "Blad" << endl << endl;
    return;
  }
  cout << endl << "   Nowe: " << Params << endl << endl;
 }

 void Test_CmdInterp()
 {
  gsv::ServerCommand   CmdInter;
  istringstream  IStrm("UpdateObj Name=Podstawa.Ramie1 RGB=(20,144,255) RotXYZ_deg=(0,20,10)");

  cout << endl
       << " To read: " << IStrm.str() << endl
       << endl;
  
  if ((IStrm >> CmdInter).fail()) {
    cout << endl
	 << " Blad wczytania polececenia." << endl
	 << endl;
    return;
  }
  
  cout << endl
       << " Cmd Interp.: " << CmdInter << endl
       << endl;
 }




 void Test_SceneCmd()
 {
  Scene  Scn;
  gsv::ServerCommand   CmdInter;

#define EXEC_CMD( TextCmd ) \
  if (!CmdInter.ReadCmd_Exec(TextCmd,Scn)) {			\
    cout << ":( Blad plecenia: \"" << TextCmd << "\"" << endl;  \
    return;                                                     \
  }
  
  EXEC_CMD("AddObj Name=Podstawa RGB=(20,144,255) RotXYZ_deg=(0,20,10)");
  EXEC_CMD("AddObj Name=Podstawa.Ramie1 RGB=(240,0,0) RotXYZ_deg=(0,20,10)");
  EXEC_CMD("AddObj Name=Podstawa2 RGB=(20,0,0) RotXYZ_deg=(90,20,10)");
  cout << "-- Obiekty ---------------------------" << endl;
  Scn.PrintNodeTree();
  EXEC_CMD("UpdateObj Name=Podstawa.Ramie1 RGB=(0,0,1) Trans_m=(40,20,5) RotXYZ_deg=(190,1,1)");
  cout << "-- Aktualizacja ----------------------" << endl;
  Scn.PrintNodeTree();
  cout << endl;
 }

} // namespace gsv
