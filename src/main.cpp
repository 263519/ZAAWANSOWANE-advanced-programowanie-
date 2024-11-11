
#include "ProgramInterpreter.hh"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;




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
   ProgramInterpreter program_interpreter;
   program_interpreter.Read_XML_Config("config/config.xml");
//    istringstream IStrm4Cmds;

//    ExecPreprocesor("config/data.cmd",  IStrm4Cmds);
//    cout  << IStrm4Cmds.str() << endl;
   
}
