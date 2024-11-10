#ifndef  LIBINTERFACE_HH 
#define  LIBINTERFACE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"
#include "string"
#include <dlfcn.h>

/*!
 * \file
 * \brief Definicja klasy I//ZMIENIC
 *
 * Plik zawiera definicję klasy //ZMIENIC ...
 */

/*!
 * \brief ZMIENIC
 *
 *  Klasa modeluj47e ...
 */
class LibInterface{

 void *_LibHnd = nullptr;
 AbstractInterp4Command *(*_pCreateCmd)(void) = nullptr;
 std::string _CmdName;



 public:
    ~LibInterface() { if (_LibHnd) dlclose(_LibHnd); }

    bool Init(const char *FileLibName){
        _LibHnd = dlopen(FileLibName, RTLD_LAZY);

        if(_LibHnd == nullptr){
            return false;
        }
            
        void *pFun = dlsym(_LibHnd, "CreateCmd");

        if(pFun == nullptr){
            return false;
        }

        _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
        return true;
    }


    AbstractInterp4Command *CreateCmd() { return (*_pCreateCmd)(); }
    std::string GetCmdName() const { return _CmdName; }
 };

#endif