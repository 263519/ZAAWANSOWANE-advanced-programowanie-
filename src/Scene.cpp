#include "Scene.hh"
#include <iostream>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {
    if (pMobObj == nullptr) {
        std::cerr << "Dodanie pustego wskaznika AbstractMobileObj!" << std::endl;
        return;
    }
    std::string objName = pMobObj->GetName();
    _Set_MobileObjs[objName] = std::shared_ptr<AbstractMobileObj>(pMobObj);
}

AbstractMobileObj* Scene::FindMobileObj(const char *sName) {
    auto it = _Set_MobileObjs.find(sName);
    if (it != _Set_MobileObjs.end()) {
        return it->second.get();
    }
    std::cerr << "Nie znaleziono obiektu o nazwie: " << sName << std::endl;
    return nullptr;
}
