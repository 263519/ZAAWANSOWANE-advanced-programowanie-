#include "gsv-GeomParams.hh"
#include <sstream>

using namespace std;


/*!
 * Wpisuje do strumienia listę parametrów geometrycznych.
 * Przykład zapisu pełnej listy parametrów.
\verbatim
  Shift=(0.2, 0.1, 0)  Scale=(1, 0.5, 1)  RotXYZ_deg=(10, 15, 4)  Trans_m=(1, 0, 2)  RGB=(200,50,180)
\endverbatim
 *
 * \param[in,out] rOStrm - strumień, do którego zapisywane są parametry,
 * \param[in]     rParams - parametry geometryczne, które mają być zapisane
 *                          do strumienia.
 * \return Strumień, który jest parametrem wywołania.
 */
std::ostream &operator << (std::ostream &rOStrm, const gsv::GeomParams &rParams)
{
  rOStrm << "Shift=" << rParams.GetShift_bsc() << " Scale=" << rParams.GetScale()
	 << " RotXYZ_deg=" << rParams.GetAnglesXYZ_deg() << " Trans_m=" << rParams.GetTrans_m()
	 << " RGB=" << rParams.GetColorRGB();
  return rOStrm;
}

/*!
 * \brief Czyta ze strumienia listę parametrów geometrycznych.
 *
 * Czyta ze strumienia listę parametrów geometrycznych.
 * Przyjmuje się, że w strumieniu kolejne grupy parametrów mogą być w różnej kolejności.
 * Nie muszą też występować wszystkie z nich.
 * Przykład pełnej listy parametrów do wczytania.
\verbatim
  Shift=(0.2, 0.1, 0)  Scale=(1, 0.5, 1)  RotXYZ_deg=(10, 15, 4)  Trans_m=(1, 0, 2)  RGB=(200,50,180)
\endverbatim
 *
 *
 * \param[in,out] rIStrm - strumień, z którego czytane są parametry,
 * \param[out]     rParams - do niego wczytywane są parametry geoemtryczne ze strumienia.
 * \return Strumień, który jest parametrem wywołania.
 */
std::istream &operator >> (std::istream &rIStrm, gsv::GeomParams &rParams)
{
  std::istringstream  IStrm_tmp;
  std::string         Line, Keyword;

#define READ_PARAM( Key, Method ) \
    if (Keyword == Key) {         \
      rIStrm >> rParams.Method();     \
      if (rIStrm.fail()) { cerr << "Error: Blad odczytu parametru " Key << endl; return rIStrm; } \
      continue;                       \
    }  

  /*
  if (getline(rIStrm,Line).fail()) {
     cout << "Cos poszlo nie tak" << endl;
  } else {
     cout << "Tresc linii: \"" << Line << "\"" << endl;
  }
  //  rIStrm.setstate(std::ios::failbit);
  rIStrm.clear();
  return rIStrm;  
  */
  
  while (!getline(rIStrm,Line,'=').fail()) {
    IStrm_tmp.clear();
    IStrm_tmp.str(Line);
    IStrm_tmp >> Keyword;
    if (IStrm_tmp.fail()) continue;
    READ_PARAM("Shift", UseShift_bsc);
    READ_PARAM("Scale", UseScale);
    READ_PARAM("RotXYZ_deg", UseAnglesXYZ_deg);
    READ_PARAM("Trans_m", UseTrans_m);
    READ_PARAM("RGB", UseColorRGB);
    std::cerr << "Error: Napotkano nieznane slowo kluczowe: " << Keyword << std::endl;
    rIStrm.setstate(std::ios::failbit);
    return rIStrm;
  }
  rIStrm.clear();
  return rIStrm;
}




/*!
 * Przepisuje te wartości, które uległy modyfikacji.
 * \param[in] rParams - parametry, których wartości są przepisywane, o ile
 *                      uległy zmianie w stosunku do wartości wcześniejszych.
 */
void gsv::GeomParams::Update(const GeomParams &rParams)
{
#define  UPDATE_IF_CHANGED( Field ) \
  if (rParams.Field.IsChanged()) Field.Use() = rParams.Field.Get();

  UPDATE_IF_CHANGED(_AngRPY_deg);
  UPDATE_IF_CHANGED(_Trans_m);
  UPDATE_IF_CHANGED(_ColorRGB);
  UPDATE_IF_CHANGED(_Shift_bsc);
  UPDATE_IF_CHANGED(_Scale);
  AbsorbChanges();
}
