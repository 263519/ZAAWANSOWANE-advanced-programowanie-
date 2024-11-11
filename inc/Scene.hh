#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include <map>
#include <string>
#include <memory>


class Scene : public AbstractScene {
public:

    Scene() = default;

    virtual ~Scene() {}

    virtual AbstractMobileObj* FindMobileObj(const char *sName) override;

    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;

private:
    std::map<std::string, std::shared_ptr<AbstractMobileObj>> _Set_MobileObjs; 
};

#endif // SCENE_HH
