#ifndef  SET4LIBINTERFACES_HH 
#define  SET4LIBINTERFACES_HH 




#include <map>
#include <memory>
#include <string>
#include "LibInterface.hh"

class Set4LibInterfaces {
private:
    std::map<std::string, std::shared_ptr<LibInterface>> _LibMap;

public:

    void AddLibInterface(const std::string& cmdName, std::shared_ptr<LibInterface> libInterface) {
        _LibMap[cmdName] = libInterface;
    }


    std::shared_ptr<LibInterface> GetLibInterface(const std::string& cmdName) const {
        auto it = _LibMap.find(cmdName);
        if(it != _LibMap.end())
            std::cout<<"Znaleziono wtyczke!\n";
        else
            std::cout<<"Brak wtyczki!\n";

        return (it != _LibMap.end()) ? it->second : nullptr;
    }
};

#endif