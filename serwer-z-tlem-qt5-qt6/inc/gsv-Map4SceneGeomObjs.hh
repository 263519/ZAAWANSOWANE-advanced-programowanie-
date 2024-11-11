#ifndef GSV_MAP4SCENEGEOMOBJS_HH
#define GSV_MAP4SCENEGEOMOBJS_HH

/*!
 * \file
 * \brief Zawiera definicję klasy gsv::Map4SceneGeomObjs.
 */

#include <map>
#include <string>
#include <memory>
#include "gsv-Map4DescGeomObjs.hh"

namespace gsv {
  class GraphObject;
}


/*!
 * \brief Przestrzeń nazw modułu serwera graficznego.
 *
 * Przestrzeń nazw modułu serwera graficznego. Zawiera definicje struktur,
 * metoda oraz funkcji wykorzystywanych przez aplikację serwera graficznego.
 */
namespace gsv {

 /*!
  * \brief Zbiór geometrycznych obiektów sceny indeksowany nazwami.
  *
  * Klasa modeluje zbiór geometrycznych obiektów sceny indeksowany nazwami.
  */
  class Map4SceneGeomObjs: private Map4DescGeomObjs {     
    public:
     /*!
      * \brief Dodaje obiekt graficzny w zadanym węźle z wykorzystaniem jego adresu.
      */
      bool AddObjUsingAddr(const std::string &rAddr, std::shared_ptr<GraphObject> &rPObj);

    /*!
     * \brief Wyszukuje węzeł wg jego nazwy kwalifikowanej.
     */
     const GraphObject* FindNode(const std::string &rQName) const;
    /*!
     * \brief Wyszukuje węzeł wg jego nazwy kwalifikowanej (adresu).
     *
     * Wyszukuje węzeł wg jego adresu, tj. nazwy kawlifikowanej. Adresem jest ciąg słów rozdzielonych
     * znakami kropki, np.
\verbatim
     Podstawa.Ramie1.Ramie2.Chwytak
\endverbatim
     * \param[in] rQName - pełna kwalifikowana nazwa obiektu.
     *                     Jest ona adresem węzła, który ma zostać znaleziony.
     * \return Jeśli węzeł zostanie znaleziony, to zwracany jest jego wskaźnik.
     *         W przypadku przeciwnym zwracany jest adres \p nullptr.
     */
     GraphObject* FindNode(const std::string &rQName)
      {
	return const_cast<GraphObject*>
	            (const_cast<const Map4SceneGeomObjs*>(this)->FindNode(rQName));
      }
    /*!
     * \brief Tworzy obiekt na podstawie pełnej kwalifkowanej jego nazwy.
     */
    bool InsertNoNameGraphObj_UseQualifiedName( const std::string             &rQName,
						std::shared_ptr<GraphObject>  &rPObj
					      );
    /*!
     * \brief Wyświetla drzewo wszystkich węzłów.
     */
     void PrintNodeTree() const {  PrintDescTree(""); }
    /*!
     * \brief Generuje instrukcje dla OpenGL resyującą całą scenę.
     */
     void DrawSceneGL() const { Map4DescGeomObjs::DrawGeomObjsGL(); }
    /*!
     * \brief Usuwa wszystkie obiekty kolekcji.
     */
     void DeleteObjects() { Map4DescGeomObjs::DeleteObjects(); }
  };

}

#endif
