#ifndef GSV_GRAPHOBJECT_HH
#define GSV_GRAPHOBJECT_HH


#include <string>
#include <memory>
#include "gsv-Map4DescGeomObjs.hh"
#include "gsv-GeomParams.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy GraphObject
 *
 * Plik zawiera definicję klasy GraphObject.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */



namespace gsv {
   /*!
    * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
    * Nazwy metod są obowiązujące.
    * \f[
         \mbox{\bf p}' =  R_z(\psi)\cdot R_y(\theta)\cdot R_x(\phi)\cdot(Scale\cdot(\mbox{\bf p}+Shift))+T
      \f]
    */
    class GraphObject: public gsv::GeomParams, private gsv::Map4DescGeomObjs {
        /*!
         * \brief Nazwa własna obiektu, która go indentyfikuje.
         *
         * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
         * musi to być nazwa unikalna wśród wszystkich obiektów danego poziomu.
	 * Nazwa obiektu nie może zawierać znaków kropka '.', które przeznaczone
	 * są do separacji nazw własnych obiektów w łańcuchu kinematycznym.
         */
       std::string  _Name;
      
     public:
      /*!
       * \brief Inicjalizuje z domyślnymi ustawieniami.
       */
      GraphObject() {}
      /*!
       * \brief Udostępnia nazwę własną obiektu graficznego.
       *
       *  Udostępnia nazwę własną obiektu graficznego.
       *  Nazwa ta nie może zawierać znaków takich jak kropka, które przeznaczone
       *  są do separacji nazw własnych obiektów w łańcuchu kinematycznym.
       */
      const std::string &GetName() const { return _Name; }
      /*!
       * \brief Udostępnia parametry geometryczne obiektu do odczytu.
       */
      const gsv::GeomParams &GetParams() const { return *this; }
      /*!
       * \brief Udostępnia parametry geometryczne obiektu do modyfikacji.
       */
      gsv::GeomParams &UseParams() { return *this; }
      /*!
      * \brief Zmienia nazwę obiektu. Nazwa nie może zawierać znaków '.'.
      *
      *  Zmienia nazwę obiektu.
      *  \param[in] sName - nowa nazwa obiektu.
      */
      void SetName(const char* sName) { _Name = sName; }
     /*!
      * \brief Zmienia nazwę obiektu. Nazwa nie może zawierać znaków '.'.
      *
      *  Zmienia nazwę obiektu.
      *  \param[in] rName - nowa nazwa obiektu.
      */
      void SetName(const std::string &rName) { _Name = rName; }
      /*!
       * \brief Udostępnia zbiór potomków bieżącego obiektu.
       *
       * Udostępnia zbiór potomków bieżącego obiektu. 
       */
      const gsv::Map4DescGeomObjs &GetDescMap() const { return *this; }
      /*!
       * \brief Udostępnia zbiór potomków bieżącego obiektu.
       *
       * Udostępnia zbiór potomków bieżącego obiektu. 
       */
      gsv::Map4DescGeomObjs &UseDescMap() { return *this; }
      /*!
       * \brief Inicjalizuje wartościami współrzędnych pozycji i kątów orientacji.
       *
       *  Inicjalizuje wartościami współrzędnych pozycji i kątów orientacji.
       *  \param[in] rPos_m - współrzędne pozycji środka obiektu. Przyjmuje się,
       *                     że wartości współrzędnych wyrażone są w metrach.
       *  \param[in] rAngles_deg - kąty orientacji obiektu w reprezentacji
       *                      \e Roll-Pitch-Yaw. Przyjmuje się, że wartości kątów
       *                      wyrażone są w stopniach.
       *  \param[in]  rColor  - kolor we współrzędnych RGB.
       */
      GraphObject(const gsv::Vector3d &rPos_m, const AnglesRPY &rAngles_deg, const RGB   &rColor)
      { _AngRPY_deg.Use() = rAngles_deg;  _Trans_m.Use() = rPos_m;  _ColorRGB.Use() = rColor;
	gsv::GeomParams::AbsorbChanges();
      }
      

      /*!
       * \brief Generuje kod, który pozwala rysować obiekt w OpenGL.
       */
       virtual void DrawGL() const = 0;

      /*!
       * \brief Generuje polecenia tworzenia obiektu, które odpowiada temu odebranym przez serwer.
       */
      virtual std::string BuildCmd() const = 0;

      /*!
       * \brief Wyświetla parametry obiektu.
       */
      void PrintObj() const;
    };

}
#endif
