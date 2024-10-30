#ifndef  PLUGINSSTRUCTURE_HH
#define  PLUGINSSTRUCTURE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"
#include <map>

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluj47e ...
 */
class LibInterface{

 void *_pLibHnd = nullptr;
 AbstractInterp4Command *(*pCreateCmd_Move)(void) = nullptr;
 const char* (*_pGetname)() = nullptr;

 public:
    ~LibInterface() { if (_pLibHnd) dclose(_pLibHnd); }

    bool Init(const char *FileLibName){
        _pLibHnd = dlopen(FileLibName, RTLD_LAZY);

        if(_pLibHnd == nullptr){
            // TO DO
            return false;
        }
            
        void *pFun = dlsym(_pLibHnd, "CreateCmd");

        if(pFun = nullptr){
            // TO DO
            return false;
        }

        pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
        return true;
    }


    AbstractInterp4Command *CreateCmd() { return (*_pCreateCmd)(); }
    const char *GetCmdName() const {return (*_pGetCmdName)(); }
 };

#endif