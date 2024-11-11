
#include "gsv-Map4SceneGeomObjs.hh"
#include "gtsDebug.hh"
#include "gsv-GraphObject.hh"
#include <sstream>

using namespace std;




/*!
 * Wyszukuje węzeł wg jego adresu. Adresem jest ciąg słów rozdzielonych
 * znakami kropki, np.
\verbatim
     Podstawa.Ramie1.Ramie2.Chwytak
\endverbatim
 * \pre Wykorzystując tę metodę zakłada się, że obiekt klasy gsv::Map4SceneGeomObjs
 *       jest składnikiem obiektu klasy gsv::GraphObject.
 * \param[in] rAddr - adres węzła, który ma zostać znaleziony.
 * \return Jeśli węzeł zostanie znaleziony, to zwracany jest jego wskaźnik.
 *         W przypadku przeciwnym zwracany jest adres \p nullptr.
 */
const gsv::GraphObject* gsv::Map4SceneGeomObjs::FindNode(const std::string &rAddr) const
{
  string ObjName;
  istringstream IStrm(rAddr);
  const GraphObject  *pCurrNode = nullptr;
  const Map4DescGeomObjs *pCurrDescMap = this;
  
  while (!getline(IStrm,ObjName,'.').fail()) {
    if (ObjName.empty()) continue;
    if (!(pCurrNode = pCurrDescMap->FindHere(ObjName))) {
      CWarning_1("Nie znaleziono wezla \"" << rAddr << "\"");
      return nullptr;
    }
    pCurrDescMap = &pCurrNode->GetDescMap();
  }
  
  return pCurrNode;
}


/*!
 * Dodaje obiekt graficzny w zadanym węźle z wykorzystaniem jego adresu.
 *
 * \param[in] rAddr - adres węzła, gdzie ma być wstawiony nowy obiekt.
 * \param[in] rPObj - wskaźnik dzielony, który ma być wstawiony do danej kolekcji.
 * \retval true - operacja zakończyła się powodzeniem,
 * \retval false - w przypadku przeciwnym. Powodem jest istnienie obiektu
 *                 mającego tę samą nazwę własną.
 */
bool gsv::Map4SceneGeomObjs::AddObjUsingAddr( const std::string            &rAddr,
				  	      std::shared_ptr<GraphObject>      &rPObj
				            )
{
  GraphObject *pTrgNode = FindNode(rAddr);

  if (pTrgNode == nullptr) {
    CWarning_1("Obiekt o nazwie \"" << rPObj->GetName() << "\" nie zostal dodany.");
    return false;
  }
  return pTrgNode->UseDescMap().InsertNamedGraphObj(rPObj);
}


/*!
 * Wstawia obiekt bez nazwy traktując parametr z kwalifikową nazwą jako 
 * miejsce lokalizacji obiektu. Wykorzystując tę nazwę ekstrahuje z niej
 * nazwę własną obiektu i nadaje ją temu wstawianemu obiektowei.
 * Dołącza go we właściwe miejsce łańcucha kinematycznego.
 *
 * \param[in] rQName - pełna kwalifikowana nazwa obiektu będąca jego adrestem
 *                     w strukturze łańcucha kinematycznego.
 * \param[in] rPObj - wskaźnik dzielony, który ma być wstawiony do danej kolekcji.
 * \retval true - gdy operajca powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool gsv::Map4SceneGeomObjs::InsertNoNameGraphObj_UseQualifiedName(
						   const std::string                 &rQName,
                                                   std::shared_ptr<gsv::GraphObject> &rPObj
					     	 )
{
  string ObjName, Tmp_ObjName;
  istringstream   IStrm(rQName);
  GraphObject      *pCurrNode = nullptr; 
  Map4DescGeomObjs *pCurrDescMap = this;
  
  while (!getline(IStrm,ObjName,'.').fail()) {
    if (ObjName.empty()) continue;
    if (!(pCurrNode = pCurrDescMap->FindHere(ObjName))) {
      if ((IStrm >> Tmp_ObjName).fail()) {
	rPObj->SetName(ObjName);
        pCurrDescMap->InsertNamedGraphObj(rPObj);
	return true;
      }
      CWarning_1("Nie znaleziono wezla \"" << rQName << "\"");
      return false;
    }
    pCurrDescMap = &pCurrNode->UseDescMap();
  }
  CErr_1(endl <<
	 "Operacja dodania obiektu nie powiodla sie." << endl <<
         "Element o nazwie \"" << rQName << "\" juz istnieje." );
  return false;
}
