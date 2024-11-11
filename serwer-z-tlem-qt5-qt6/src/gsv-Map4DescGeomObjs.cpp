#include "gsv-Map4DescGeomObjs.hh"
#include "gtsDebug.hh"
#include "gsv-GraphObject.hh"
#include <sstream>
#include <GL/gl.h>

using namespace std;



/*!
 *  Wstawia pojedynczy nazwany obiekt graficzny do kolekcji.
 *  Jako klucz indeksujący przyjmuje się nazwę własną obiektu.
 *  \param[in]  rPObj - dodawany obiekt.
 *  \retval true - operacja zakończyła się powodzeniem,
 *  \retval false - w przypadku przeciwnym. Powodem jest istnienie obiektu
 *                  mającego tę samą nazwę własną.
 */
bool gsv::Map4DescGeomObjs::InsertNamedGraphObj(std::shared_ptr<GraphObject> &rPObj)
{
  std::pair<iterator,bool> Pair_IterBool =
    insert(std::pair<std::string,std::shared_ptr<GraphObject>>(rPObj->GetName(),rPObj));
  if (!Pair_IterBool.second) {
    CWarning_1("Obiekt o nazwie \"" << rPObj->GetName() << "\" nie zostal dodany."
	       " On juz istnieje w tym wezle." );
  }
  return Pair_IterBool.second;
}




/*!
 *  Odszukuje obiekt o danej nazwie.
 *  \param[in] rObjName - nazwa własna obiektu (nie zawiera kropek).
 *  \return Jeśli znajdzie to zwraca wskaźnik na obiekt. W przypadku
 *          przeciwnym ...
 */
const gsv::GraphObject* gsv::Map4DescGeomObjs::FindHere(const std::string &rObjName) const
{
  map<std::string,std::shared_ptr<GraphObject>>::const_iterator Iter
                                                              = find(rObjName);
  return Iter == end() ? nullptr : &*Iter->second;
}




/*!
 * Wyświetla pełne drzewo wszystkich potomków.
 * Metda ta wywoływana jest rekurencyjnie.
 * \param[in] rPrevNodeName - nazwa wcześniejszego węzła.
 */
void gsv::Map4DescGeomObjs::PrintDescTree(const std::string& rPrevNodeName) const
{
  std::string  CurrName;

  CurrName.reserve(100);
  for (const pair<std::string,std::shared_ptr<GraphObject>> &rElem : *this) {
    CurrName = rPrevNodeName;
    CurrName += '.';
    CurrName += rElem.first;
    cout << "QName: " << CurrName << endl;
    cout << "     ";
    rElem.second->PrintObj();
    rElem.second->GetDescMap().PrintDescTree(CurrName);
  }
}



/*!
 * Generuje instrukcje dla OpenGL rysującą wszystkie elementy graficzne.
 * Ta metoda może być wywoływana tylko i wyłącznie w kontekście OpenGL.
 */
void  gsv::Map4DescGeomObjs::DrawGeomObjsGL() const
{
  for (const pair<std::string,std::shared_ptr<GraphObject>> &rElem : *this) {
      glPushMatrix();
      rElem.second->DrawGL();
      rElem.second->GetDescMap().DrawGeomObjsGL();
      glPopMatrix();
  }
}
