#ifndef GSV_SCENE_HH
#define GSV_SCENE_HH

#include <memory>
#include <list>
//#include "Vector3D.hh"
#include "gsv-GraphObject.hh"
#include "gsv-Map4SceneGeomObjs.hh"
#include <mutex>

/*!
 * \file 
 * \brief Definicja klasy Scene 
 */

namespace gsv {
/*!
 * \brief Modeluje scenę, na której umieszczony jest zbiór obiektów
 *        graficznych.
 */
 class Scene {
    /*!
     * \brief Zbiór obiektów graficznych, które mają być wizualizowane
     *        na scenie.
     */
     gsv::Map4SceneGeomObjs  _Map4GeomObjs;
   public:
     /*!
     * \brief Tworzy obiekt na podstawie pełnej kwalifkowanej jego nazwy.
     */
     bool InsertNoNameGraphObj_UseQualifiedName( const std::string                  &rQName,
					 	 std::shared_ptr<gsv::GraphObject>  &rPObj
					       );
    /*!
     * \brief Wyszukuje węzeł wg jego nazwy kwalifikowanej.
     *
     * Wyszukuje węzeł wg jego adresu, tj. nazwy kawlifikowanej. Adresem jest ciąg
     * słów rozdzielonych znakami kropki, np.
\verbatim
     Podstawa.Ramie1.Ramie2.Chwytak
\endverbatim
     * \param[in] rQName - pełna kwalifikowana nazwa obiektu.
     *                     Jest ona adresem węzła, który ma zostać znaleziony.
     * \return Jeśli węzeł zostanie znaleziony, to zwracany jest jego wskaźnik.
     *         W przypadku przeciwnym zwracany jest adres \p nullptr.
     */
    const gsv::GraphObject* FindNode(const std::string &rQName) const
                                      { return _Map4GeomObjs.FindNode(rQName); }
    /*!
     * \brief Wyszukuje węzeł wg jego nazwy kwalifikowanej (adresu).
     *
     * Wyszukuje węzeł wg jego adresu, tj. nazwy kawlifikowanej. Adresem jest ciąg
     * słów rozdzielonych znakami kropki, np.
\verbatim
     Podstawa.Ramie1.Ramie2.Chwytak
\endverbatim
     * \param[in] rQName - pełna kwalifikowana nazwa obiektu.
     *                     Jest ona adresem węzła, który ma zostać znaleziony.
     * \return Jeśli węzeł zostanie znaleziony, to zwracany jest jego wskaźnik.
     *         W przypadku przeciwnym zwracany jest adres \p nullptr.
     */
    gsv::GraphObject* FindNode(const std::string &rQName)
                                      { return _Map4GeomObjs.FindNode(rQName); }
    /*!
     * \brief Wyświetla drzewo wszystkich węzłów.
     */
     void PrintNodeTree() const {  _Map4GeomObjs.PrintNodeTree(); }
   /*!
    * \brief Generuje instrukcje dla OpenGL resyującą całą scenę.
    */
    void DrawSceneGL() const { _Map4GeomObjs.DrawSceneGL(); }
   /*!
    * \brief Usuwa wszystkie elementy sceny
    */
    void ClearScene() { _Map4GeomObjs.DeleteObjects(); }
 };
}

#endif
