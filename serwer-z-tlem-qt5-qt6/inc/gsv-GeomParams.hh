#ifndef GSV_GEOMPARAMS_HH
#define GSV_GEOMPARAMS_HH


/*!
 * \file
 * \brief Zawiera definicję klasy gsv::GeomParams
 */

#include "gsv-Vector3d.hh"
#include "gsv-RGB.hh"
#include "gsv-AnglesRPY.hh"
#include <iostream>
#include <cassert>


namespace gsv {

  /*!
   * \brief Wartość z nadzorem kontrolującym modyfikację.
   */
  template <typename ValType>
  class WatchedValue {
    ValType  _Val;
    bool     _Changed = false;
   public:
    void Reset() { _Changed = false; }
    bool IsChanged() const { return _Changed; }
    const ValType &Get() const { return _Val; }
    /*!
     * \brief Dostęp do pola z możliwością modyfikacji.
     *
     *   Dostęp do pola z możliwością modyfikacji.
     *   Zakłada się, że w takiej sytuacji zawsze następuje modyfikacja wartości.
     */
    ValType &Use() { _Changed = true; return _Val; }
  };

  /*!
   * \brief Modeluje zestaw parametrów opisujących obiekt geometryczny
   *
   *  Modeluje zestaw parametrów opisujących obiekt geometryczny.
   */
  class GeomParams {
    protected:
      /*!
       * \brief Kąty \e Roll-Pitch-Yaw (XYZ) określające orientację obiektu.
       */
       WatchedValue<AnglesRPY>  _AngRPY_deg;
       /*!
        * \brief Współrzędne translacji odpowiadające aktualnej pozycji obiektu
	*        w układzie współrzędnych rodzica.
	*
	* Współrzędne translacji odpowiadające aktualnej pozycji obiektu
	* w układzie współrzędnych rodzica.
	* Przyjmuje się, że współrzędne wyrażone są w metrach.
        */
       WatchedValue<gsv::Vector3d>  _Trans_m;
      /*!
       * \brief Przesunięcie środka geometrycznego przed zastosowaniem skalowania.
       */
       WatchedValue<gsv::Vector3d>  _Shift_bsc;
      /*!
       * \brief Skale względem trzech osi.
       */
       WatchedValue<gsv::Vector3d>  _Scale;
      /*!
       * \brief Kolor we współrzędnych RGB.
       */
       WatchedValue<RGB>      _ColorRGB;


     public:
     /*!
      * \brief Inicjalizuje wartości domyślne.
      *
      *  Inicjalizuje wartości domyślne.
      *  Pola \link gsv::GeomParams::_AngRPY_deg _AngRPY_deg\endlink,
      *  \link gsv::GeomParams::_Trans_m _Trans_m\endlink oraz
      *  \link gsv::GeomParams::_Shift_bsc _Shift_bsc\endlink.
      *  Natomiast współrzędne pole \link gsv::GeomParams::_Scale _Scale\endlink
      *  inicjalizowane są wartościami 1,
      *  zaś pola \link gsv::GeomParams::_ColorRGB _ColorRGB\endlink
      *  wartościami 128,
      */
      GeomParams()
        {
	  gsv::Vector3d  &rScale = _Scale.Use();
	  
	  rScale[0] = rScale[1] = rScale[2] = 1;
	  gsv::Vector3i  &rVecRGB = _ColorRGB.Use().UseColorRGB();
	  rVecRGB[0] = rVecRGB[1] = rVecRGB[2] = 128;
	  AbsorbChanges();
	}
     /*!
      * \brief Absorbuje zmiany i traktuje wszystkie wartości jako wartości, które
      *        nie uległy zmianie.
      */
      void AbsorbChanges()
        {
	  _AngRPY_deg.Reset();  _Trans_m.Reset();
	  _ColorRGB.Reset();  _Shift_bsc.Reset();  _Scale.Reset();
	}
    /*!
     * \brief Przepisuje te wartości, które uległy modyfikacji.
     */
     void Update(const GeomParams &rParams);
     /*!
      * \brief Udostępnia wektor kątów rotacji do odczytu.
      *
      * Udostępnia wektor kątów rotacji do odczytu.
      * Współrzędne wektora zawierają kąty rotacji względem kolejnych osi,
      * tzn OX, OY i OZ.
      * Wartości kątów wyrażone są w stopniach.
      */
     const gsv::Vector3d &GetAnglesXYZ_deg() const
                            { return _AngRPY_deg.Get().GetAnglesXYZ_deg(); }
     /*!
      * \brief Udostępnia wektor kątów rotacji do modyfikacji.
      *
      * Udostępnia wektor kątów rotacji do modyfikacji.
      * Współrzędne wektora zawierają kąty rotacji względem kolejnych osi,
      * tzn OX, OY i OZ.
      * Wartości kątów wyrażone są w stopniach.
      */
      gsv::Vector3d &UseAnglesXYZ_deg()
                            { return _AngRPY_deg.Use().UseAnglesXYZ_deg(); }

     /*!
       * \brief Udostępnia do odczytu pole koloru.
       */
      const RGB& GetRGB() const { return _ColorRGB.Get(); }        
      /*!
       * \brief Udostępnia do odczytu składowe koloru w konwencji RGB
       */
      const gsv::Vector3i& GetColorRGB() const { return _ColorRGB.Get().GetColorRGB(); }    
      /*!
       * \brief Udostępnia do modyfikacje składowe koloru w konwencji RGB
       */
      gsv::Vector3i& UseColorRGB() { return _ColorRGB.Use().UseColorRGB(); }    

     /*!
      * \brief Udostępnia do odczytu przesunięcie środka geometrycznego
      *        przed zastosowaniem skalowania.
      */
      const gsv::Vector3d &GetShift_bsc() const { return _Shift_bsc.Get(); }
     /*!
      * \brief Udostępnia do odczytu przesunięcie środka geometrycznego
      *        przed zastosowaniem skalowania.
      *
      * Udostępnia do odczytu przesunięcie środka geometrycznego
      * przed zastosowaniem skalowania.
      * \param[in] Idx - indeks osi. Osi OX, OY, OX są po kolei
      *                  indeksowane od 0 do 2.
      * \return Współczynnik przesunięcia.
      */
      double GetShift_bsc(unsigned int Idx) const
                        { assert(Idx < 3);  return _Shift_bsc.Get()[Idx]; }

    /*!
      * \brief Udostępnia do modyfikacji przesunięcie środka geometrycznego
      *        przed zastosowaniem skalowania.
      */
      gsv::Vector3d &UseShift_bsc() { return _Shift_bsc.Use(); }
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
      double GetAng_Roll_deg() const
                         { return _AngRPY_deg.Get().GetAng_Roll_deg(); }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       double GetAng_Pitch_deg() const
                         { return _AngRPY_deg.Get().GetAng_Pitch_deg(); }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       double GetAng_Yaw_deg() const
                         { return _AngRPY_deg.Get().GetAng_Yaw_deg(); }

      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg) // Metoda do usunięcia
                          { _AngRPY_deg.Use().SetAng_Roll_deg(Ang_Roll_deg); }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch
       *                            wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg) // Metoda do usunięcia
                     { _AngRPY_deg.Use().SetAng_Pitch_deg(Ang_Pitch_deg); }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
      void SetAng_Yaw_deg(double Ang_Yaw_deg) // Metoda do usunięcia
                    { _AngRPY_deg.Use().SetAng_Yaw_deg(Ang_Yaw_deg); }

      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko
       *        do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
      const gsv::Vector3d & GetPosition_m() const { return _Trans_m.Get(); }
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko
       *        do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
      const gsv::Vector3d & GetTrans_m() const { return _Trans_m.Get(); }
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
      gsv::Vector3d & UseTrans_m() { return _Trans_m.Use(); }
      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
      void SetTrans_m(const gsv::Vector3d &rPos_m) { _Trans_m.Use() = rPos_m; }
      /*!
       * \brief Udostępnia do odczytu wektor współczynników skali
       *        dla poszczególnych osi.
       *
       * Udostępnia do odczytu wektor współczynników skali dla poszczególnych osi.
       */
       const gsv::Vector3d &GetScale() const { return _Scale.Get(); }
      /*!
       * \brief Udostępnia do odczytu wektor współczynników skali
       *        dla poszczególnych osi.
       *
       * Udostępnia do odczytu wektor współczynników skali dla poszczególnych osi.
       * 
       * \param[in] Idx - indeks osi. Osi OX, OY, OX są po kolei
       *                  indeksowane od 0 do 2.
       * \return Współczynnik skali danej osi.
       */
      double GetScale(unsigned int Idx) const
                   { assert(Idx < 3); return _Scale.Get()[Idx]; }

      /*!
       * \brief Udostępnia do modyfikacji wektor współczynników skali
       *        dla poszczególnych osi.
       *
       * Udostępnia do modyfikacji wektor współczynników skali
       * dla poszczególnych osi.
       */
       gsv::Vector3d &UseScale() { return _Scale.Use(); }

  };

}


/*!
 * \brief Wpisuje do strumienia listę parametrów geometrycznych.
 */
std::ostream &operator << (std::ostream &rOStrm, const gsv::GeomParams &rParams);

/*!
 * \brief Czyta ze strumienia listę parametrów geometrycznych.
 */
std::istream &operator >> (std::istream &rIStrm, gsv::GeomParams &rParams);




#endif
