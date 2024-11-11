#ifndef GEOMVECTOR_HH
#define GEOMVECTOR_HH

/*!
 * \file
 * \brief Definicja szablonu wektora N-wymiarowego.
 *
 * Szablon jest wykorzystywany na potrzeby definiowana wektorów o dowolnym rozmiarze.
 * \author      Bogdan Kreczmer
 * \date        2003.12
 *
 */


#ifdef __GNUG__
#pragma interface
#endif
#include <iostream>
#include <cmath>
#include <cassert>


/*!
 * \file
 * \brief Definition of the vector template with parametric dimention.
 */


namespace geom {

 /*!
  * \brief Przyjęta wartość błędu obliczeń.
  *
  * Przyjęta wartość błędu obliczeń, która wynika ze skończonej
  * reprezentacji liczb rzeczywistych.
  */
#define ERR_DOUBLE   1e-9

  /*!
   * \brief Sprawdza znak wartości uwzględniając błąd obliczeń.
   *
   * Sprawdza znak wartości uwzględniając błąd obliczeń zdefiniowany
   * przez stałą \link geomVector.hh::ERR_DOUBLE ERR_DOUBLE\endlink.
   * \param[in] Val - wartość liczbowa, której znak ma być sprawdzony.
   * \retval 1 - gdy Val > \link geomVector.hh::ERR_DOUBLE ERR_DOUBLE\endlink,
   * \retval 0 - gdy Val jest w przedziale 
   *             [\link geomVector.hh::ERR_DOUBLE -ERR_DOUBLE\endlink,
   *              \link geomVector.hh::ERR_DOUBLE ERR_DOUBLE\endlink],
   * \retval -1 - gdy Val < \link geomVector.hh::ERR_DOUBLE -ERR_DOUBLE\endlink,
   * 
   */
  inline
  int Sgn(double Val) { return Val > ERR_DOUBLE ? 1 : Val < -ERR_DOUBLE ? -1 : 0; }
  
/*!
 * \brief Model wektora N-wymiarowego
 *
 * Jest to szablon wektora N-wymiarowego.
 * \param Type - typ współrzędnej wektora,
 * \param Size - rozmiar wektora.
 */
 template<typename Type, unsigned int Size>
 class Vector {

    /*!
     * \brief Tablica współrzędnych wektora
     *
     *  W tablicy tej zapisywane są wartości kolejnych współrzędnych.
     */
   Type  _Coord[Size];

  public:

    /*!
     * \brief Współrzędne wektora są zerowane.
     *
     * Wszystkim współrzędnym przypisana jest wartość 0.
     */
   Vector() { for (Type &Val : _Coord) Val = 0; }

    /*!
     * \brief Dostęp do wybranej składowej wektora.
     *
     *  Dostęp do wybranej składowej wektora.
     *  Dostęp jest w trybie \e modyfikacji.
     *  \param  Ind - indeks składowej wektora.
     *  \pre 0 <= Ind < Size.
     *  \post Referencja do żądanej składowej wektora.
     */
   Type  &operator [](unsigned int Ind) { assert(Ind < Size); return _Coord[Ind]; }

    /*!
     *  \brief Dostęp do wybranej składowej wektora.
     *
     *  Dostęp do wybranej składowej wektora.
     *  Dostęp jest w trybie \e tylko \e do \e odczytu.
     *  \param  Ind - indeks składowej wektora.
     *  \pre 0 <= Ind < Size.
     *  \post  Referencja do żądanej składowej wektora.
     */
   Type operator [](unsigned int Ind) const { assert(Ind < Size); return _Coord[Ind]; }


    /*! 
     *  \brief Dostęp do wybranej składowej wektora.
     *
     *  Operacja implementuje sumę wektorów.
     *  \param   rSkl2 - drugi składnik.
     *  \retval  Vector<Type,Size> - obiekt zawierający wartość sumy
     *                           dwóch wektorów \b *this i \e V.
     */
    Vector<Type,Size>  operator  + (Vector<Type,Size> const &rSkl2) const;

    /*! 
     *  \brief Dodaje wektora i przypisuje wynik sumy.
     *
     *  Dodaje współrzędne wektora do wektora reprezentowanego przez obiekt,
     *  dla którego ta opieracja zostałą wywołana.
     *  \param  rSkl2 - drugi argument operacji.
     *  \retval *this - referencja do pierwszego argumentu.
     */
    Vector<Type,Size> &operator += (Vector<Type,Size> const &rSkl2);

    /*! 
     * \brief Różnica dwóch wektorów.
     *
     *  Operacja implementuje różnicę wektorów.
     *  \param   rOdj - odjemnik.
     *  \retval  Vector<Type,Size> - obiekt będący różnicą dwóch wektorów
     *                                  \b *this i \e V.
     */
   Vector<Type,Size>  operator  - (Vector<Type,Size> const &rOdj) const;

    /*! 
     * \brief Różnica dwóch wektorów i przypisanie wyniku.
     *
     *  Operacja implementuje różnicę wektorów i przypisanie wyniku
     *  operacji do odjemnej.
     *
     *  \param  rOdj - odjemnik.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje nową wartość będącą 
     *                 różnicą dwóch wektorów \b *this i \e V.
     */
   Vector<Type,Size> &operator -= (Vector<Type,Size> const &rOdj);


     /*!
      * \brief Mnożenie wektora przez liczbę
      *
      * Operator implementuje mnożenie wektora przez liczbę.
      * \param   Mnoznik - drugi czynnik iloczynu (liczba).
      * \retval  Vector<Type,Size>  - obiekt będący  iloczynu wektora
      *                            \b *this i liczby \e Mnoznik.
      */
   Vector<Type,Size>  operator  * (Type Mnoznik) const;

     /*!
      * \brief Mnożenie wektora przez liczbę i przypisanie wyniku
      *
      * Operator implementuje iloczyn wektora przez liczbę i przypisanie
      * wyniku do lewego argumentu.
      *
      * \param   Mnoznik - drugi czynnik iloczynu (liczba).
      * \retval *this  - referencję do samego siebie.
      *              Obiekt przyjmuje nową wartość będącą
      *              produktem iloczynem \b *this i liczby \e Mnoznik.
      */
   Vector<Type,Size> &operator *= (Type Mnoznik);

     /*!
      * \brief Dzielenie wektora przez liczbę
      *
      * Operator implementuje iloraz wektora przez liczbę.
      * \param   Dzielnik - dzielnik wektora (liczba).
      * \retval  Vector<Type,Size>  - obiekt będący ilorazem
      *                            \b *this (wektor) / \e Dzielnik (liczba).
      */
   Vector<Type,Size>  operator  / (Type Dzielnik) const;

     /*!
      * \brief Dzielenie wektora przez liczbę i przypisanie wyniku
      *
      * Operator implementuje iloraz wektora przez liczbę
      * i przypisanie wyniku lewemu argumentowi (wektorowi).
      * \param   Dzielnik - dzielnik wektora (liczba).
      * \retval *this  - referencję do samego siebie.
      *              Obiekt przyjmuje nową wartość będącą
      *              ilorazem \b *this i liczby \e Dzielnik.
      */
   Vector<Type,Size> &operator /= (Type Dzielnik);

     /*!
      * \brief Iloczyn skalarny
      *
      * Operator implementuje iloczyn skalarny dwóch wektorów.
      * \param rVec - drugi czynnik iloczynu skalarnego.
      * \return Wartość będącą iloczynem skalarnym wektorów \b *this
      *         i \e rVec.
      */
   Type  operator & (Vector<Type,Size> const &rVec) const;      // skalar product


    /*!
     * \brief Porównanie dwóch wektorów.
     *
     *  Dokonuje porównania dwóch wektorów.
     *  \param[in] rArg2 - prawy argument operacji porównania.
     *  \retval  true - jeśli odpowiadające składowej są sobie równe.
     *              w sensie funkcji geom::Sgn().
     *              pozwala to uwzględnić (przynajmniej częściowo) błędy
     *              obliczeń,
     *  \retval  false - w przypadku przeciwnym.
     */
   bool          operator == (Vector<Type,Size> const &rArg2);



    /*!
     *  \brief Length of this vector is computed.
     *
     * Length of this vector is computed.
     * \return A value of vector length is returned.
     */
    Type Length() const;

    /*!
     *  \brief Zmienia znak wszystkich składowych
     *
     *  Zmienia znak wszystkich składowych wektora na przeciwny.
     *  \return\b *this - zwraca referencję do samego siebie.
     */
    Vector<Type,Size> &Inverse() { for (Type &Crd : _Coord ) Crd = -Crd; return *this; }



    /*!
     * \brief Zeruje wszystkie współrzędne wektora.
     *
     *  Wszystkim współrzędnym wektora przypisana zostaj wartość 0.
     */
    void SetZero() { for (Type &Crd : _Coord ) Crd = 0;  }


    /*!
     * \brief Sprawdza czy wektor jest wektorem zerowym.
     *
     * Sprawdza czy dany wektor jest wektorem zerowym. Przyjmuje
     * się, że pole ma wartość 0 jeśli funkcja sgn zwróci wartość 0.
     * Wspomniana funkcja uwzględnia błędy obliczeń zdefiniowane
     * poprzez stałą ERROR_LEVEL.
     * \return true - jeśli sgn zwróci dla wszystkich pól zero,
     * \return false - w przypadku przeciwnym.
     */
    bool IsZero() const  { for (Type Crd : _Coord ) if (Crd) return false;  return true; }


    /*!
     * \brief Sprawdza czy zadana współrzędna znajduje się wewnątrz danego przedziału.
     *
     * Sprawdza czy współrzędna o indeksie \e Ind znajduje się wewnątrz przedziału.
     * \param Ind - indeks wybranej współrzędnej wektora.
     * \param x_min - dolny kraniec przedziału.
     * \param x_max - górny kraniec przedziału.
     * \return true - jeśli wartość pola \e _x jest wewnątrz przedziału
     *               (\e x_min, \e x_max).
     * \return false - w przypadku przeciwnym.
     */
   bool IsInside(unsigned int Ind, Type x_min, Type x_max) const
     { return (x_min < _Coord[Ind]) && (_Coord[Ind] < x_max);}

    /*!
     * \brief Sprawdza czy dany punkt jest wewnątrz prostopadłościanu.
     * Sprawdza czy punkt, reprezentowany przez wektor, jest wewnątrz prostopadłościanu.
     * Zakłada się, że ścianki prostopadłościanu są równoległe do jednej
     * z płaszczyzn kartezjańskiego układu współrzędnych OXY.
     * \param Min - zawiera współrzędne wierzchołka, którego składowe
     *              mają minimalne wartości spośród składowych tego 
     *              samego typu wszystkich wierzchołków
     *              tego prostopadłościanu.
     * \param Max - zawiera współrzędne wierzchołka, którego składowe
     *              mają maksymalne wartości spośród składowych tego 
     *              samego typu wszystkich wierzchołków
     *              tego prostopadłościanu.
     *              prostopadłościanu.
     * \return  true  - jeśli punkt jest wewnątrz prostopadłościanu.
     * \return  false - w przypadku przeciwnym.
     */
   bool IsInside(Vector<Type,Size> const &Min, Vector<Type,Size> Max) const;

    /*!
     * \brief Normalizuje wektor
     *
     * Metoda normalizuje wektor.
     * Po tej operacji długość wektora bardzo bliska wartości 1.
     * Ewentualne odchyłki są związane z błędami obliczeń
     * będących następstwem skończonej reprezentacji liczb rzeczywistych.
     */
   void Normalize() 
     { Type d = Length(); for (Type &Crd : _Coord) Crd /= d; }
 };

 
 template<typename Type, unsigned int Size>
 inline
 bool Vector<Type,Size>::IsInside(Vector<Type,Size> const &Min, Vector<Type,Size> Max) const
 {
   for (unsigned Ind = 0; Ind < Size; ++Ind) {
     if (!IsInside(Ind,Min[Ind],Max[Ind])) return false;
   }
   return true;
 }



 template<typename Type, unsigned int Size>
 inline
 Type Vector<Type,Size>::Length() const
 {
   return sqrt(*this & *this);
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator += (Vector<Type,Size> const &rSkl2)
 {
   for (unsigned int Ind = 0; Ind < Size; ++Ind) _Coord[Ind] += rSkl2[Ind];
   return *this;
 }
  

 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator + (Vector const &rSkl2) const
 {
   return Vector<Type,Size>(*this) += rSkl2;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator -= (Vector<Type,Size> const & rOdj)
 {
   for (unsigned int Ind = 0; Ind < Size; ++Ind) _Coord[Ind] -= rOdj[Ind];
   return *this;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator - (Vector<Type,Size>  const &rOdj) const
 {
   return Vector<Type,Size>(*this) -= rOdj;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator *= (Type Mnoznik)
 {
   for (Type Crd : _Coord ) Crd *= Mnoznik;
   return *this;
 }


 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator * (Type Mnoznik) const
 {
   return Vector<Type,Size>(*this) *= Mnoznik;  
 }



 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> &Vector<Type,Size>::operator /= (Type Digit)
 {
   for (Type Crd : _Coord ) Crd /= Digit;
   return *this;
 }
  

 template<typename Type, unsigned int Size>
 inline
 Vector<Type,Size> Vector<Type,Size>::operator / (Type Dzielnik) const
 {
   return Vector<Type,Size>(*this) /= Dzielnik;    
 }


 template<typename Type, unsigned int Size>
 inline
 bool Vector<Type,Size>::operator == (Vector<Type,Size> const &rArg2)
 {
   for (unsigned int Idx = 0; Idx < Size; ++Idx)
             if (Sgn(_Coord[Idx]-rArg2[Idx]) != 0) return false;
   return true;
 }


 template<typename Type, unsigned int Size>
 inline
 Type Vector<Type,Size>::operator & (Vector<Type,Size> const &rVec) const
 {
   Type Res = 0;
   for (unsigned int Idx = 0; Idx < Size; ++Idx) Res += _Coord[Idx] * rVec[Idx];  
   return Res;
 }

}



/*!
 * \brief Wypisuje współrzędne wektora do tekstowego strumienia wyjściowego.
 *
 *  Wypisuje współrzędne wektora do tekstowego strumienia wyjściowego.
 *  \param rOStrm - strumień wyjściowy, do którego wpisywane są współrzędne wektora,
 *  \param V - wektor, ktorego współrzędne mają zostać wypisane.
 */
template<typename Type, unsigned int Size>
inline
std::ostream & operator << ( std::ostream &rOStrm, const geom::Vector<Type,Size> &V)
{
   rOStrm << "(" << V[0];
   for (unsigned int Ind = 1; Ind < Size; ++Ind) {
     rOStrm << ", " << V[Ind];
   }
   rOStrm << ")";
   return rOStrm;
}




/*!
 * \brief Wczutuje współrzędne wektora do tekstowego strumienia wyjściowego.
 *
 *  Wypisuje współrzędne wektora do tekstowego strumienia wyjściowego.
 *  \param rIStrm - strumień wejściowy, z którego czytane są współrzędne wektora,
 *  \param V - wektor, ktorego współrzędne mają zostać wczytane.
 *  \return Srumień, który jest parametrem wywołania.
 */
template<typename Type, unsigned int Size>
inline
std::istream & operator >> ( std::istream &rIStrm, geom::Vector<Type,Size> &V)
{
  char Ch = 'x';

  rIStrm >> Ch;
  if (Ch != '(') { rIStrm.setstate(std::ios::failbit); return rIStrm; }
  Ch = ',';
  for (unsigned int Ind = 0; Ind < Size; ++Ind) {
    if (Ch != ',') { rIStrm.setstate(std::ios::failbit); return rIStrm; }
    rIStrm >> V[Ind] >> Ch;
  }
  if (Ch != ')') { rIStrm.setstate(std::ios::failbit); }
  return rIStrm;
}


/*
template<typename Type, unsigned int Size>
inline
std::istream & operator >> ( std::istream &IStrm, geom::Vector<Type,Size> &V)
{
   
   for (unsigned int Ind = 0; Ind < Size; ++Ind) {
     IStrm >> V[Ind];
   }
   return IStrm;
}
*/


#endif
