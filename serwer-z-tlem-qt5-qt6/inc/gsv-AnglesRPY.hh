#ifndef GSV_ANGLESRPY_HH
#define GSV_ANGLESRPY_HH

/*!
 * \file
 * \brief Zawiera definicję klasy AnglesRPY
 */

#include <iostream>
#include "gsv-Vector3d.hh"

/*!
 * \brief Modeluje zestaw kątów typu Roll-Pitch-Yaw
 *
 * Modeluje zestaw kątów typu Roll-Pitch-Yaw. Odpowiadają one kątom
 * roatcji względem kolejnych osi OX, OY i OZ.
 */
class AnglesRPY {
      /*!
       * \brief Kąty rotacji względem osi OX, OY, OZ. Wyrażone są one w stopniach.
       */
       gsv::Vector3d  _AnglesXYZ_deg;

   public:
     /*!
      * \brief Udostępnia wektor kątów rotacji do odczytu.
      *
      * Udostępnia wektor kątów rotacji do odczytu.
      * Współrzędne wektora zawierają kąty rotacji względem kolejnych osi, tzn OX, OY i OZ.
      * Wartości kątów wyrażone są w stopniach.
      */
      const gsv::Vector3d &GetAnglesXYZ_deg() const { return _AnglesXYZ_deg; }
     /*!
      * \brief Udostępnia wektor kątów rotacji do modyfikacji.
      *
      * Udostępnia wektor kątów rotacji do modyfikacji.
      * Współrzędne wektora zawierają kąty rotacji względem kolejnych osi, tzn OX, OY i OZ.
      * Wartości kątów wyrażone są w stopniach.
      */
      gsv::Vector3d &UseAnglesXYZ_deg() { return _AnglesXYZ_deg; }
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll.
       * Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
       * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
       */
       double GetAng_Roll_deg() const { return _AnglesXYZ_deg[0]; }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch.
       * Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
       * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
       */
       double GetAng_Pitch_deg() const { return _AnglesXYZ_deg[1]; }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw.
       * Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
       * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
       */
       double GetAng_Yaw_deg() const { return _AnglesXYZ_deg[2]; }
  
      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg) { _AnglesXYZ_deg[0] = Ang_Roll_deg; }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg) { _AnglesXYZ_deg[1] = Ang_Pitch_deg; }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
       void SetAng_Yaw_deg(double Ang_Yaw_deg) { _AnglesXYZ_deg[2] = Ang_Yaw_deg; }  
};


inline
std::istream & operator >> (std::istream & IStrm, AnglesRPY &rAnglesXYZ_deg)
{
  double  Angle_Roll_deg, Angle_Pitch_deg, Angle_Yaw_deg;

  IStrm >> Angle_Roll_deg >> Angle_Pitch_deg >> Angle_Yaw_deg;
  if (IStrm.fail()) return IStrm;
  rAnglesXYZ_deg.SetAng_Roll_deg(Angle_Roll_deg);
  rAnglesXYZ_deg.SetAng_Pitch_deg(Angle_Pitch_deg);
  rAnglesXYZ_deg.SetAng_Yaw_deg(Angle_Yaw_deg);
  return IStrm;
}


inline
std::ostream & operator << (std::ostream & OStrm, const AnglesRPY &rAnglesXYZ_deg)
{
  OStrm << rAnglesXYZ_deg.GetAng_Roll_deg()
	<< " "
	<< rAnglesXYZ_deg.GetAng_Pitch_deg()
	<< " "
	<< rAnglesXYZ_deg.GetAng_Yaw_deg();
  return OStrm;
}



#endif
