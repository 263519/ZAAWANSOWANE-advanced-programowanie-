#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include <map>
#include <string>
#include <memory>
#include "AccessControl.hh"
#include "Cuboid.hh"
#include "geomVector.hh"



class Scene : public AbstractScene {
public:
    Scene();  
    virtual ~Scene();  

    virtual AbstractMobileObj* FindMobileObj(const char *sName) override;  
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override; 
    void PrintSceneObjects() const; 

private:
    std::map<std::string, std::shared_ptr<AbstractMobileObj>> _Set_MobileObjs;  
};





#endif // SCENE_HH
