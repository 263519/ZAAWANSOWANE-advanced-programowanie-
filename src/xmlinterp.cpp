#include <xercesc/util/PlatformUtils.hpp>
#include "xmlinterp.hh"
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include "Scene.hh"

int a;
using namespace std;


/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 */
XMLInterp4Config::XMLInterp4Config(Set4LibInterfaces &libSet,  Scene &scene) : _libSet(libSet), _scene(scene) {}



/*!
 * Metoda wywoływana jest bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::startDocument()
{
  cout << "*** Rozpoczecie przetwarzania dokumentu XML." << endl;
}


/*!
 * Metoda wywoływana jest bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::endDocument()
{
  cout << "=== Koniec przetwarzania dokumentu XML." << endl;
}





/*!
 * Analizuje atrybuty elementu XML \p "Lib" i odpowiednio je interpretuje.
 * \param[in] rAttrs - atrybuty elementu XML \p "Lib".
 */
void XMLInterp4Config::ProcessLibAttrs(const xercesc::Attributes  &rAttrs)
{
 if (rAttrs.getLength() != 1) {
      cerr << "Zla ilosc atrybutow dla \"Lib\"" << endl;
      exit(1);
 }

 char* sParamName = xercesc::XMLString::transcode(rAttrs.getQName(0));

 if (strcmp(sParamName,"Name")) {
      cerr << "Zla nazwa atrybutu dla Lib" << endl;
      exit(1);
 }         

 XMLSize_t  Size = 0;
 char* sLibName = xercesc::XMLString::transcode(rAttrs.getValue(Size));

 cout << "  Nazwa biblioteki: " << sLibName << endl;

 //Tu trzeba wpisać własny kod ...
  auto libInterface = std::make_shared<LibInterface>();
  if (!libInterface->Init(sLibName)) {
      std::cerr << "Nie udało się zainicjalizować biblioteki: " << sLibName << std::endl;
      return; 
  }
  _libSet.AddLibInterface(sLibName, libInterface);
 // Tu trzeba wpisać własny kod ...
 xercesc::XMLString::release(&sParamName);
 xercesc::XMLString::release(&sLibName);
}



Vector3D ParseVector3D(const std::string &str) {
    Vector3D vec;
    std::istringstream istr(str);
    if (!(istr >> vec[0] >> vec[1] >> vec[2])) {
        std::cerr << "Error parsing Vector3D from string: \"" << str << "\"" << std::endl;
        vec = Vector3D(0, 0, 0); 
    }
    return vec;
}

/*!
 * Analizuje atrybuty. Sprawdza czy ich nazwy są poprawne. Jeśli tak,
 * to pobiera wartości atrybutów (w postaci napisów) i przekazuje ...
 * \param[in] rAttrs - atrybuty elementu XML \p "Cube".
 */
void XMLInterp4Config::ProcessCubeAttrs(const xercesc::Attributes  &rAttrs)
{
 if (rAttrs.getLength() < 1) {
      cerr << "Zla ilosc atrybutow dla \"Cube\"" << endl;
      exit(1);
 }

 /*
  *  Tutaj pobierane sa nazwy pierwszego i drugiego atrybuty.
  *  Sprawdzamy, czy na pewno jest to Name i Value.
  */

    char* sName_Name = xercesc::XMLString::transcode(rAttrs.getQName(0));
    char* sName_Scale = xercesc::XMLString::transcode(rAttrs.getQName(1));
    char* sName_RGB = xercesc::XMLString::transcode(rAttrs.getQName(2));
    char* sName_Shift = xercesc::XMLString::transcode(rAttrs.getQName(3));
    char* sName_RotXYZ = xercesc::XMLString::transcode(rAttrs.getQName(4));
    char* sName_Trans = xercesc::XMLString::transcode(rAttrs.getQName(5));


char* sValue_Name = xercesc::XMLString::transcode(rAttrs.getValue(static_cast<XMLSize_t>(0)));
char* sValue_Scale = xercesc::XMLString::transcode(rAttrs.getValue(static_cast<XMLSize_t>(1)));
char* sValue_RGB = xercesc::XMLString::transcode(rAttrs.getValue(static_cast<XMLSize_t>(2)));
char* sValue_Shift = xercesc::XMLString::transcode(rAttrs.getValue(static_cast<XMLSize_t>(3)));
char* sValue_RotXYZ = xercesc::XMLString::transcode(rAttrs.getValue(static_cast<XMLSize_t>(4)));
char* sValue_Trans = xercesc::XMLString::transcode(rAttrs.getValue(static_cast<XMLSize_t>(5)));



 //-----------------------------------------------------------------------------
 // Wyświetlenie nazw atrybutów i ich "wartości"
 //
   cout << "Atrybuty:" << endl
         << "    " << sName_Name << " = \"" << sValue_Name << "\"" << endl
         << "    " << sName_Scale << " = \"" << sValue_Scale << "\"" << endl
         << "    " << sName_RGB << " = \"" << sValue_RGB << "\"" << endl
         << "    " << sName_Shift << " = \"" << sValue_Shift << "\"" << endl
         << "    " << sName_RotXYZ << " = \"" << sValue_RotXYZ << "\"" << endl
         << "    " << sName_Trans << " = \"" << sValue_Trans << "\"" << endl
         << endl;
 //-----------------------------------------------------------------------------
 // Przykład czytania wartości parametrów
 // Ten przykład jest zrobiony "na piechotę" wykorzystując osobne zmienne.
 // Skala powinna być wektorem. Czytanie powinno być rezlizowane z wykorzysaniem
 // wektorów, np.
 //
 //
 // istringstream IStrm;
 // IStrm.str(sValue_Scale);
 // Vector3D  Scale;
 //
 // IStrm >> Scale;
 //


 // Tu trzeba wstawić odpowiednio własny kod ...

  istringstream IStrm;
    Vector3D scale, rgb, shift, rotXYZ, translation;


    IStrm.str(sValue_Scale);
    IStrm >> scale[0] >> scale[1] >> scale[2];
    IStrm.clear();


    IStrm.str(sValue_RGB);
    IStrm >> rgb[0] >> rgb[1] >> rgb[2];
    IStrm.clear();

    IStrm.str(sValue_Shift);
    IStrm >> shift[0] >> shift[1] >> shift[2];
    IStrm.clear();


    IStrm.str(sValue_RotXYZ);
    IStrm >> rotXYZ[0] >> rotXYZ[1] >> rotXYZ[2];
    IStrm.clear();


    IStrm.str(sValue_Trans);
    IStrm >> translation[0] >> translation[1] >> translation[2];
    IStrm.clear();


    cout << "Pobrane wartosci:" << endl
         << "    Scale: " << scale << endl
         << "    RGB: " << rgb << endl
         << "    Shift: " << shift << endl
         << "    RotXYZ: " << rotXYZ << endl
         << "    Translation: " << translation << endl;

 
    std::shared_ptr<Cuboid> cuboid = std::make_shared<Cuboid>();
    //cuboid->SetPosition_m(Vector3D());
    cuboid->SetShift(shift);
    cuboid->SetScale(scale);
    cuboid->SetRotation(rotXYZ);
    cuboid->SetTranslation(translation);
    cuboid->SetRGB(rgb);
    cuboid->SetName(sValue_Name);

    try {
        _scene.AddMobileObj(cuboid);
    } catch (const std::exception &e) {
        cerr << "Wyjatek podczas dodawania Cuboida: " << e.what() << endl;
    }

    // Zwolnienie pamięci
    xercesc::XMLString::release(&sName_Name);
    xercesc::XMLString::release(&sName_Scale);
    xercesc::XMLString::release(&sName_RGB);
    xercesc::XMLString::release(&sName_Shift);
    xercesc::XMLString::release(&sName_RotXYZ);
    xercesc::XMLString::release(&sName_Trans);
    xercesc::XMLString::release(&sValue_Name);
    xercesc::XMLString::release(&sValue_Scale);
    xercesc::XMLString::release(&sValue_RGB);
    xercesc::XMLString::release(&sValue_Shift);
    xercesc::XMLString::release(&sValue_RotXYZ);
    xercesc::XMLString::release(&sValue_Trans);
}








/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] rElemName - nazwa elementu XML.
 * \param[in] rAttrs - atrybuty napotkanego elementu XML.
 */
void XMLInterp4Config::WhenStartElement( const std::string           &rElemName,
		                         const xercesc::Attributes   &rAttrs
                                       )
{
  if (rElemName == "Lib") {
    ProcessLibAttrs(rAttrs);   return;   
  }

  if (rElemName == "Cube") {
    ProcessCubeAttrs(rAttrs);  return;
  }
}




/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pURI - (Uniform Resource Identifier) jeżeli nie jest on wyspecyfikowany
 *                    poprzez użycie atrybutów \p xmlns (o ile jego użycie jest przewidziane w gramatyce,
 *                    w tym przykładzie nie jest to przewidziane), to będzie to napis pusty.
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] pQName - pełna kwalifikowana nazwa. To ma znaczenie, gdy użyta jest przestrzeń nazwa.
 *                      Wówczas poprzez ten parametr można otrzymać nazwę elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeśli przestrzeń nazw nie jest użyta (taka jak w tym
 *                      przykładzie), to \p pQName i \p pLocalName dostaczają identyczne napisy.
 *  \param[in] rAttrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLInterp4Config::startElement(  const   XMLCh* const            pURI,
                                      const   XMLCh* const            pLocalName,
                                      const   XMLCh* const            pQName,
				      const   xercesc::Attributes&    rAttrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  cout << "+++ Poczatek elementu: "<< sElemName << endl;

  WhenStartElement(sElemName, rAttrs);

  xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Lib Name="Rotate">
     </Lib>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika:
 * \verbatim</Lib>\endverbatim
 * Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pURI - (Uniform Resource Identifier) jeżeli nie jest on wyspecyfikowany
 *                    poprzez użycie atrybutów \p xmlns (o ile jego użycie jest przewidziane w gramatyce,
 *                    w tym przykładzie nie jest to przewidziane), to będzie to napis pusty.
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Lib".
 *  \param[in] pQName - pełna kwalifikowana nazwa. To ma znaczenie, gdy użyta jest przestrzeń nazwa.
 *                      Wówczas poprzez ten parametr można otrzymać nazwę elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeśli przestrzeń nazw nie jest użyta (taka jak w tym
 *                      przykładzie), to \p pQName i \p pLocalName dostaczają identyczne napisy.
 *                      
 */
void XMLInterp4Config::endElement(  const   XMLCh* const    pURI,
                                    const   XMLCh* const    pLocalName,
                                    const   XMLCh* const    pQName
                                 )
{
   char* sURI =  xercesc::XMLString::transcode(pURI);
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   char* sQName =  xercesc::XMLString::transcode(pQName);
   cout << "   URI: " << sURI << endl;
   cout << " QName: " << sQName << endl;
   cout << "----- Koniec elementu: "<< sElemName << endl;

   xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 * \param[in] rException - zawiera informacje dotyczące błędu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::fatalError(const xercesc::SAXParseException&  rException)
{
   char* sMessage = xercesc::XMLString::transcode(rException.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(rException.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << rException.getLineNumber() << endl
        << " Kolumna: " << rException.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] rException - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLInterp4Config::error(const xercesc::SAXParseException&  rException)
{
  cerr << "Blad ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}


/*!
 * Metoda wywołana jest w przypadku błędów, które nie są fatalne
 * i mogą być traktowane jako ostrzeżenia.
 * \param[in] rException - zawiera informacje dotyczące błędu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::warning(const xercesc::SAXParseException&  rException)  
{
  cerr << "Ostrzezenie ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}
