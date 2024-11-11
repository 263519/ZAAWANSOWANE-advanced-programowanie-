#ifndef CUBOID_HH
#define CUBOID_HH

/*!
 * \file
 * \brief Zawiera definicję klasy modelującej prostopadłościan
 */

#include "gsv-GraphObject.hh"
//#include "gsv-Vector3d.hh"


namespace gsv {
/*!
 * \brief Modeluje prostopadłościan 
 */
 class Cuboid: public gsv::GraphObject {
   /*==!
    * \brief Rozmiary boków prostopadłościanu
    * 
    * Zawiera wartości rozmiarów boków prostopadłościanu.
    * Przyjmuje się, że wyrażone są one w metrach.
    */
  //   Vector3d  _Size_m;
  public:
  /*!
   * \brief Tworzy prostopadłościan z domyślnymi ustawieniami.
   */
   Cuboid() {}
  /*==!
   * \brief Inicjalizuje obiekt parametrami określającymi rozmiar, pozycję
   *        i orientację obiektu.
   *
   * Inicjalizuje obiekt parametrami określającymi rozmiar, pozycję
   * i orientację obiektu.
   * \param[in] rSize_m - rozmiary boków prostopadłościanu.
   *                      Przyjmuje się, że wyrażone są one w metrach.
   * \param[in] rPos_m - współrzędne pozycji środka obiektu. Przyjmuje się,
   *                     że wartości współrzędnych wyrażone są w metrach.
   * \param[in] rAngles_deg - kąty orientacji obiektu w reprezentacji
   *                      \e Roll-Pitch-Yaw. Przyjmuje się, że wartości kątów
   *                      wyrażone są w stopniach.
   * \param[in] rColors  - kolor we współrzędnych RGB.
   */
  /*
   Cuboid(   const Vector3d   &rSize_m,
	     const Vector3d   &rPos_m,
	     const AnglesRPY  &rAngles_deg,
	     const RGB        &rColors
	  ): GraphObject(rPos_m,rAngles_deg,rColors), _Size_m(rSize_m) {}
  */
   /* !
    * \brief
    */
  //   const Vector3d &  GetSize_m() const { return _Size_m; }
   /* !
    * \brief Zmienia rozmiary boków prostopadłościanu.
    *
    * Zmienia rozmiary boków prostopadłościanu.
    * \param[in] rSize_m - nowe wartości wielkości boków.
    *                      Przyjmuje się, że wielkości boków wyrażone
    *                      są w metrach.
    */
  // void SetSize(const Vector3d &rSize_m) { _Size_m = rSize_m; }

   /*!
    * \brief Generuje kod, który pozwala rysować obiekt w OpenGL.
    */
   virtual void DrawGL() const override;
   /*!
    * \brief Generuje polecenia tworzenia obiektu, które odpowiada temu odebranym przez serwer.
    */
    virtual std::string BuildCmd() const override;  
 };
}

#endif
