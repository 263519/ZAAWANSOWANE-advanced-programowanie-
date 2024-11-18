#include "Scene.hh"
#include "Cuboid.hh"

Scene::Scene() {}

Scene::~Scene() {}

AbstractMobileObj* Scene::FindMobileObj(const char *sName) {
    auto it = _Set_MobileObjs.find(sName);
    if (it != _Set_MobileObjs.end()) {
        return it->second.get();
    }
    return nullptr;
}

void Scene::AddMobileObj(std::shared_ptr<AbstractMobileObj> pMobObj) {
    _Set_MobileObjs[pMobObj->GetName()] = pMobObj;
}

void Scene::PrintSceneObjects() const {
    if (_Set_MobileObjs.empty()) {
        std::cout << "Brak obiektów na scenie!" << std::endl;
    } else {
        std::cout << "Obiekty na scenie:" << std::endl;
        for (const auto &pair : _Set_MobileObjs) {
            std::cout << "Nazwa obiektu: " << pair.first << std::endl;
            
        }
    }
}
