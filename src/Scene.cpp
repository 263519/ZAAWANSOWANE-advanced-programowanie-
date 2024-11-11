#include "Scene.hh"
#include <iostream>


Scene::Scene() {
   
}


Scene::~Scene() {
   
}


AbstractMobileObj* Scene::FindMobileObj(const char *sName) {
    auto it = _Set_MobileObjs.find(sName);
    if (it != _Set_MobileObjs.end()) {
        return it->second.get();  
    }
    return nullptr;  
}


void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {
    if (pMobObj != nullptr) {
        _Set_MobileObjs[pMobObj->GetName()] = std::shared_ptr<AbstractMobileObj>(pMobObj);
    } else {
        std::cerr << "Nie można dodać pustego obiektu!" << std::endl;
    }
}
