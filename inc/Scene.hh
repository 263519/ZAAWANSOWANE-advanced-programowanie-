#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include <map>
#include <string>
#include <memory>
#include "AccessControl.hh"


// DO ZMIANY KLASA SCENY ~~~!!!!!!

/*!
 * \brief Ilość stanów każdego z obiektów.
 *
 * Ilość stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER   8

/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 1
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj1[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,23)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,26)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,29)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,32)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,35)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,38)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,41)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,44)\n"  
 };


/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 2
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj2[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-48,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-45,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-42,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-39,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-36,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-33,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-30,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-27,0)\n"
 };

/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 3
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj3[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-48,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-51,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-54,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-57,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-60,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-63,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-66,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-69,0)\n"
 };


/*!
 * \brief Ta klasa trochę udaję klasę MobileObj, która jest w zadaniu.
 *
 */
class GeomObject {
  /*!
   * \brief Identyfikuje aktualny stan obiektu.
   *
   * Identyfikuje aktualny stan obiektu. Indeks ten pozwala
   * na wybór z tablicy \link GeomObject::_Cmd4StatDesc _Cmd4StatDesc\endlink
   * odpowiedniego polecenia dla serwera, które reprezentuje aktualne
   * położenie i orientację obiektu.
   */
   int _StateIdx = 0;
  /*!
   * \brief Zestaw sekwencji poleceń symulujących ruch obiektu.
   *
   * Zestaw sekwencji poleceń symulujących ruch obiektu.
   * Każde polecenie odpowiada kolejnym stanom obiektu.
   */
   const char** _Cmd4StatDesc = nullptr;
  
 public:

  /*!
   * \brief Ustawia zestaw poleceń odpowiadających kolejnym stanom
   *        obiektu.
   */
  void SetCmds(const char *CmdsTab[STATES_NUMBER]) { _Cmd4StatDesc = CmdsTab; }
  /*!
   * \brief Udostępnia kolejny zestaw poleceń umożliwiających
   *        zespołu obiektu.
   *
   * Udostępnia kolejny zestaw poleceń umożliwiających
   * zespołu obiektu. Ta metoda "udaje" metodę, która w oryginalnym
   * rozwiązaniu powinna wygenerować odpowiednie polecenie na podstawie
   * przechowywanej informacji o położeniu i orientacji obiektu.
   */
  const char* GetStateDesc() const
  {
    return _Cmd4StatDesc[_StateIdx];
  }
  /*!
   * \brief Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *
   *  Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *  Ta metoda "udaje" metodę, która w oryginalnym rozwiązaniu
   *  jest odpowiedzialna za zmianę stanu obiektu, tzn. zmianę jego
   *  położenia lub orientacji.
   */
  bool IncStateIndex() {
    if (_StateIdx >= STATES_NUMBER-1) return false;
    ++_StateIdx;
    return true;
  }
};

// class Scene : public AbstractScene {
// public:
//     Scene();  
//     virtual ~Scene();  

//     virtual AbstractMobileObj* FindMobileObj(const char *sName) override;  
//     virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;  

// private:
//     std::map<std::string, std::shared_ptr<AbstractMobileObj>> _Set_MobileObjs;  
// };


/*!
 * \brief Namiastka sceny z prostą kolekcją trzech wizualizowanych obiektów.
 */
class Scene: public AccessControl {
  public:
    Scene(): _Container4Objects(3)
    {
      _Container4Objects[0].SetCmds(Cmds4Obj1);
      _Container4Objects[1].SetCmds(Cmds4Obj2);
      _Container4Objects[2].SetCmds(Cmds4Obj3);
    }
  
  /*!
   * \brief Prosta kolekcja obiektów sceny
   */
   std::vector<GeomObject>   _Container4Objects;
};


#endif // SCENE_HH
