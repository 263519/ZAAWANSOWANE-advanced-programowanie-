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

         std::shared_ptr<Cuboid> cuboid = std::dynamic_pointer_cast<Cuboid>(pair.second);
            if (cuboid) {
                std::cout << "  Pozycja (m): " << cuboid->GetPositoin_m() << std::endl;
                std::cout << "  Przesunięcie: " << cuboid->GetShift() << std::endl;
                std::cout << "  Skala: " << cuboid->GetScale() << std::endl;
                std::cout << "  Rotacja: " << cuboid->GetRotation() << std::endl;
                std::cout << "  Translacja: " << cuboid->GetTranslation() << std::endl;
                std::cout << "  Kolor RGB: " << cuboid->GetRGB() << std::endl;
            } else {
                std::cout << "  (Obiekt nie jest typu Cuboid)" << std::endl;
            }
        }
    }
}
