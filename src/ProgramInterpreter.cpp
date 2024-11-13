#include "ProgramInterpreter.hh"
#include <iostream>
#include "Configuration.hh"
#include <fstream>
#include <iostream>
#include "xmlinterp.hh"
#include <iostream>



using namespace xercesc;
using namespace std;


// bool ProgramInterpreter::Read_XML_Config(const char *FileName) {
//     Configuration  Config;
//     if (!ReadFile(FileName,Config)) return 1;
 
    
//     return true; 
// }



bool ProgramInterpreter::Read_XML_Config(const char *FileName, Set4LibInterfaces &libSet,  Scene &scene)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException &e)
    {
        char *message = XMLString::transcode(e.getMessage());
        std::cerr << "Błąd inicjalizacji Xerces: " << message << std::endl;
        XMLString::release(&message);
        return false;
    }

    SAX2XMLReader *pParser = XMLReaderFactory::createXMLReader();

    pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    pParser->setFeature(XMLUni::fgXercesDynamic, false);
    pParser->setFeature(XMLUni::fgXercesSchema, true);
    pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
    pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

    DefaultHandler *pHandler = new XMLInterp4Config(libSet, scene);
    pParser->setContentHandler(pHandler);
    pParser->setErrorHandler(pHandler);

    try
    {
        if (!pParser->loadGrammar("config/config.xsd", xercesc::Grammar::SchemaGrammarType, true))
        {
            std::cerr << "Blad." << std::endl;
            return false;
        }
        
        pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);
        pParser->parse(FileName);
    }
    catch (const XMLException &e)
    {
        char *message = XMLString::transcode(e.getMessage());
        std::cerr << "Błąd podczas parsowania: " << message << std::endl;
        XMLString::release(&message);
        return false;
    }
    catch (const SAXParseException &e)
    {
        char *message = XMLString::transcode(e.getMessage());
        char *systemId = xercesc::XMLString::transcode(e.getSystemId());

        std::cerr << "Błąd! Plik: " << systemId << ", Linia: " << e.getLineNumber()
                  << ", Kolumna: " << e.getColumnNumber() << ", Informacja: " << message << std::endl;

        XMLString::release(&message);
        XMLString::release(&systemId);
        return false;
    }
    catch (...)
    {
        std::cerr << "Wystąpił nieoczekiwany błąd!" << std::endl;
        return false;
    }

    delete pParser;
    delete pHandler;

    try
    {
        XMLPlatformUtils::Terminate();
    }
    catch (const XMLException &e)
    {
        char *message = XMLString::transcode(e.getMessage());
        std::cerr << "Błąd podczas zakończenia Xerces: " << message << std::endl;
        XMLString::release(&message);
        return false;
    }


    std::cout<<"KONIEC\n";
    return true;
}


bool ProgramInterpreter::ExecProgram(const char *FileName_Prog) {

    



    return true; 
}
