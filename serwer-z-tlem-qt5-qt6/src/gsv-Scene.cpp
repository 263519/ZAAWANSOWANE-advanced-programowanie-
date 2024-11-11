#include "gsv-Scene.hh"
#include "gsv-Cuboid.hh"


/*!
 * Wstawia obiekt bez nazwy traktując parametr z kwalifikową nazwą jako 
 * miejsce lokalizacji obiektu. Wykorzystując tę nazwę ekstrahuje z niej
 * nazwę własną obiektu i nadaje ją temu wstawianemu obiektowei.
 * Dołącza go we właściwe miejsce łańcucha kinematycznego.
 *
 * \param[in] rQName - pełna kwalifikowana nazwa obiektu będąca jego adrestem
 *                     w strukturze łańcucha kinematycznego.
 * \param[in] rPObj  - wskaźnik dzielony na obiekt, który to wskaźnik 
 *I                    ma zostać dodany do drzewiastej kolekcji
 *                     obiektów sceny.
 * \retval true - gdy operajca powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool gsv::Scene::InsertNoNameGraphObj_UseQualifiedName(
				 const std::string                  &rQName,
				 std::shared_ptr<gsv::GraphObject>  &rPObj
			       )
{
  return _Map4GeomObjs.InsertNoNameGraphObj_UseQualifiedName(rQName,rPObj);
}


