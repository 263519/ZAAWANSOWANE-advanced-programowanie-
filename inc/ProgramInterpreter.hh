#ifndef  PROGRAMINTERPRETER_HH 
#define  PROGRAMINTERPRETER_HH 


#include "Set4LibInterfaces.hh"
//#include "Scene.hh"
#include "ComChannel.hh"

class ProgramInterpreter {
private:
   // Scene _Scn;
    Set4LibInterfaces _LibManager;
    ComChannel _Chann2Serv;

public:
    
    bool Read_XML_Config(const char *FileName);
    bool ExecProgram(const char *FileName_Prog);
};

#endif