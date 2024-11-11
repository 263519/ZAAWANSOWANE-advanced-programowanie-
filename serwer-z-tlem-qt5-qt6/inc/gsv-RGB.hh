#ifndef GSV_RGB_HH
#define GSV_RGB_HH

/*!
 * \file
 * \brief Zawiera definicję klasy RGB
 *
 */




#include <iostream>
#include "gsv-Vector3i.hh"




namespace gsv {

/*!
 * \brief Modeluje zestaw współrzędnych koloru w notacji RGB
 */
 class RGB {
      /*!
       * \brief Zestaw współrzędnych określających trzy składowe koloru.
       *
       *  Zestaw współrzędnych określających trzy składowe koloru.
       *  Zakres każdej ze składowych może mieścić się w zakresie [0,255].
       */
       gsv::Vector3i  _ColorRGB;

   public:
     /*!
      * \brief Udostępnia do odczytu wektor współrzędnych koloru
      */
      const gsv::Vector3i &GetColorRGB() const { return _ColorRGB; }
     /*!
      * \brief Udostępnia do modyfikacji wektor współrzędnych koloru
      */
      gsv::Vector3i &UseColorRGB() { return _ColorRGB; }

      /*!
       * \brief Udostępia wartość koloru czerwonego.
       */
       unsigned short int GetColor_Red() const { return _ColorRGB[0]; }
      /*!
       * \brief Udostępia wartość koloru zielonego.
       */
       unsigned short int GetColor_Green() const { return _ColorRGB[1]; }
       /*!
       * \brief Udostępia wartość koloru niebieskiego.
       */
       unsigned short int GetColor_Blue() const { return _ColorRGB[2]; }
  
      /*!
       * \brief Zmienia wartość koloru czerwonego.
       *
       * Zmienia wartość koloru czerwonego.
       * \param[in] Color_Red - nowa wartość koloru czerwonego.
       */
       void SetColor_Red(unsigned short int Color_Red) { _ColorRGB[0] = Color_Red; }
      /*!
       * \brief Zmienia wartość koloru zielonego.
       *
       * Zmienia wartość koloru zielonego.
       * \param[in] Color_Green - nowa wartość koloru zielonego.
       */
       void SetColor_Green(unsigned short int Color_Green) { _ColorRGB[1] = Color_Green; }
      /*!
       * \brief Zmienia wartość koloru niebieskiego.
       *
       * Zmienia wartość koloru niebieskiego.
       * \param[in] Color_Blue - nowa wartość koloru niebieskiego.
       */
       void SetColor_Blue(unsigned short int Color_Blue) { _ColorRGB[2] = Color_Blue; }  
 };
}



inline
std::istream & operator >> (std::istream & IStrm, gsv::RGB &rColors)
{
  unsigned short int  Color_Red, Color_Green, Color_Blue;

  IStrm >> Color_Red >> Color_Green >> Color_Blue;
  if (IStrm.fail()) return IStrm;
  rColors.SetColor_Red(Color_Red);
  rColors.SetColor_Green(Color_Green);
  rColors.SetColor_Blue(Color_Blue);
  return IStrm;
}


inline
std::ostream & operator << (std::ostream & OStrm, const gsv::RGB &rColors)
{
  OStrm << rColors.GetColor_Red() << " " << rColors.GetColor_Green()
	<< " " << rColors.GetColor_Blue();
  return OStrm;
}

#endif
