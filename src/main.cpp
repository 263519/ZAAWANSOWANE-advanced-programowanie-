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
    
    Set4LibInterfaces libInterfaces;

    
    auto rotate = std::make_shared<LibInterface>();
    auto move = std::make_shared<LibInterface>();
    auto set = std::make_shared<LibInterface>();
    auto pause = std::make_shared<LibInterface>();



    rotate->Init("Rotate");
    move->Init("Move");
    set->Init("Set");
    pause->Init("Pause");



    libInterfaces.AddLibInterface(rotate->GetCmdName(),rotate);
    libInterfaces.AddLibInterface(move->GetCmdName(),move);
    libInterfaces.AddLibInterface(set->GetCmdName(),set);
    libInterfaces.AddLibInterface(pause->GetCmdName(),pause);
   
    auto m = libInterfaces.GetLibInterface("Move");
    auto s = libInterfaces.GetLibInterface("Set");
    auto r = libInterfaces.GetLibInterface("Rotate");
    auto p = libInterfaces.GetLibInterface("Pause");

    m->CreateCmd()->PrintCmd();
    s->CreateCmd()->PrintCmd();
    r->CreateCmd()->PrintCmd();
    p->CreateCmd()->PrintCmd();
   

    return 0;
}