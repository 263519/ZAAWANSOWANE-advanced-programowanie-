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

        void AddLibInterface(const std::string& cmdName, LibInterface* libInterface) {

        _LibMap[cmdName] = std::shared_ptr<LibInterface>(libInterface);
    }


    std::shared_ptr<LibInterface> GetLibInterface(const std::string& cmdName) const {
        auto it = _LibMap.find(cmdName);  
        if (it != _LibMap.end()) {
            std::cout << "Znaleziono wtyczkę: " << cmdName << std::endl;
            return it->second; 
        } else {
            std::cout << "Brak wtyczki o nazwie: " << cmdName << std::endl;
            return nullptr;  
        }
    }


    void PrintPlugins() const {
        if (_LibMap.empty()) {
            std::cout << "Brak dostępnych wtyczek." << std::endl;
            return;
        }

        std::cout << "Dostępne wtyczki:" << std::endl;
        for (const auto& [cmdName, libInterface] : _LibMap) {
            std::cout << " - " << cmdName << std::endl;
        }
    }
};

#endif