#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include <memory>



using namespace std;



#define LINE_SIZE 500
bool ExecPreprocesor( const char *FileName, istringstream &IStrm4Cmds )
{
    string Cmd4Preproc = "cpp -P";
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

int main(int argc, char **argv)
{
    // Create an instance of the Set4LibInterfaces class
    Set4LibInterfaces libInterfaces;

    // Create shared pointers to LibInterface objects for different commands
    auto rotate = std::make_shared<LibInterface>();
    auto move = std::make_shared<LibInterface>();
    auto set = std::make_shared<LibInterface>();
    auto pause = std::make_shared<LibInterface>();



    rotate->Init("Rotate");
    

    return 0;
}