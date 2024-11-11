#ifndef GSV_MAP4DESCGEOMOBJS_HH
#define GSV_MAP4DESCGEOMOBJS_HH


/*!
 * \file
 * \brief Zawiera definicję klasy gsv::Map4DescGeomObjs
 */

#include <map>
#include <string>
#include <memory>



/*!
 * \brief Przestrzeń nazw modułu serwera graficznego.
 *
 * Przestrzeń nazw modułu serwera graficznego. Zawiera definicje struktur,
 * metoda oraz funkcji wykorzystywanych przez aplikację serwera graficznego.
 */
namespace gsv {

  class GraphObject;

  
/*!
 * \brief Zbiór obiektów geometrycznych indeksowany nazwami.
 *
 * Klasa modeluje zbiór obiektów geometrycznych indeksowany nazwami.
 * Zbiór ten jest zbiorem obiektów geometrycznych oraz
 * obiektów potomnych wynikających z danego łańcucha kinetycznego.
 */
  class Map4DescGeomObjs: protected std::map<std::string,std::shared_ptr<GraphObject>> {
    public:
     /*!
      * \brief Wstawia pojedynczy nazwany obiekt graficzny.
      */
      bool InsertNamedGraphObj(std::shared_ptr<GraphObject> &rPObj);
     /*!
      * \brief Odszukuje obiekt o danej nazwie.
      */
      const GraphObject* FindHere(const std::string &rObjName) const;
     /*!
      * \brief Odszukuje obiekt o danej nazwie.
      */
      GraphObject* FindHere(const std::string &rObjName)
       {
         return const_cast<GraphObject*>
	          (const_cast<const Map4DescGeomObjs*>(this)->FindHere(rObjName));
       }
    /*!
     * \brief Wyświetla pełne drzewo wszystkich potomków
     */
    void PrintDescTree(const std::string& rPrevNodeName) const;
    /*!
     * \brief Generuje instrukcje dla OpenGL rysującą wszystkie elementy graficzne.
     */
    void DrawGeomObjsGL() const;
    /*!
     * \brief Usuwa wszystkie obiekty kolekcji.
     */
    void DeleteObjects() { clear(); }
  };
  
}

#endif
