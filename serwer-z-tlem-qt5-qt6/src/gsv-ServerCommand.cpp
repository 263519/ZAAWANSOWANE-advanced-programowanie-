#include "gsv-ServerCommand.hh"
#include <utility>
#include <memory>
#include "gsv-Scene.hh"
#include "gsv-Cuboid.hh"
#include "gtsDebug.hh"

using namespace std;







/*!
 *  Czyta z napisu, interpretuje i wykonuje polecenie.
 *  \param[in] rCmdText - zawiera treść polecenia przesłanego do serwera,
 *  \param[in,out] rScn - scena robocza, dla której ma zostać wykonane dane polecenie.
 *  \retval true - gdy wykonanie polecenia zakończyło się pomyślnie,
 *  \retval false - w przypadku przeciwnym.
 */
bool gsv::ServerCommand::ReadCmd_Exec(const std::string &rCmdText, Scene &rScn)
{
  istringstream  IStrm(rCmdText);

  if ((IStrm >> *this).fail()) return false;
  return ExecCmd(rScn);
}



/*!
 *  Wstawia do sceny nowy obiekt.
 *  \param[in,out] rScn - scena robocza, dla której ma zostać wykonane dane polecenie.
 *  \retval true - gdy wykonanie polecenia zakończyło się pomyślnie,
 *  \retval false - w przypadku przeciwnym.
 */
bool gsv::ServerCommand::InsertNewObj(Scene &rScn)
{
  shared_ptr<GraphObject>  PObj = make_shared<Cuboid>();
  PObj->UseParams().Update(_ObjParams);
  PObj->UseParams().AbsorbChanges();
  return rScn.InsertNoNameGraphObj_UseQualifiedName(GetQName(),PObj);
}




/*!
 *  Wyszukuje obiekt na scenie i aktualizuje jego parametry.
 *  Wyszukiwanie jest realizowane na podstawie pamiętanej nazwy obiektu.
 *  \param[in,out] rScn - scena robocza, dla której ma zostać wykonane dane polecenie.
 *  \retval true - gdy wykonanie polecenia zakończyło się pomyślnie,
 *  \retval false - w przypadku przeciwnym.
 */
bool gsv::ServerCommand::UpdateObj(Scene &rScn)
{
  GraphObject* pObj = rScn.FindNode(GetQName());
  if (pObj == nullptr) return false;
  pObj->UseParams().Update(_ObjParams);
  pObj->UseParams().AbsorbChanges();
  return true;
}




/*!
 *  Wykonuje polecenie, którego parametry znajdują się w obiekcie, dla którego
 *  wywoływna jest ta metoda.
 *  Na czas wykonania polecenie, scena jest blokowana.
 *  \param[in,out] rScn - scena robocza, dla której ma zostać wykonane dane polecenie.
 *  \retval true - gdy wykonanie polecenia zakończyło się pomyślnie,
 *  \retval false - w przypadku przeciwnym.
 */
bool gsv::ServerCommand::ExecCmd(Scene &rScn)
{
  switch (GetCmdID()) {
    case CI_Nothing: return true;
    case CI_AddObj:
      return InsertNewObj(rScn);
      
    case CI_UpdateObj:
      return UpdateObj(rScn);

    case CI_Clear:
      rScn.ClearScene();
      return true;
      
    case CI_Display:
    case CI_Close:
      break;      
  }
  return true;
}



/*!
 * \brief Wczytuje identyfikator polecenia ze strumienia
 */
std::istream &operator >> (std::istream &rIStrm, gsv::Enum_CommandIndentifier &rCmdID)
{
#define MAKE_PAIR( Name ) { #Name, gsv::CI_##Name }
  typedef std::pair<std::string,gsv::Enum_CommandIndentifier> Pair4CmdID;
  Pair4CmdID  PairTab[] = { MAKE_PAIR( Nothing ),
			    MAKE_PAIR( AddObj ),
			    MAKE_PAIR( UpdateObj ),
			    MAKE_PAIR( Display ),
			    MAKE_PAIR( Close ),
			    MAKE_PAIR( Clear )
                          };
    
  std::string  Keyword;

  if ((rIStrm >> Keyword).fail()) { return rIStrm; }

  for (const Pair4CmdID &rPair : PairTab ) {
    if (rPair.first == Keyword) { rCmdID = rPair.second; return rIStrm; }
  }
  CErr_1(" Unknown command keyword: " << Keyword);
  return rIStrm;
}



/*!
 * \brief Zapisuje identyfikator polecenia do strumienia
 */
std::ostream &operator << (std::ostream &rOStrm, gsv::Enum_CommandIndentifier CmdID)
{
  const char *IDsName[] = {
			   "Nothing",
                           "AddObj",
                           "UpdateObj",
			   "Display",
			   "Close",
			   "Clear"
                         };
  return rOStrm << IDsName[CmdID];
}




/*!
 * \brief Wczytuje polecenie ze strumienia
 */
std::istream &operator >> (std::istream &rIStrm, gsv::ServerCommand &rCmd)
{
  std::string  Keyword;
  std::string  Line;  
  gsv::Enum_CommandIndentifier  CmdID;

  
  if ((rIStrm >> CmdID).fail()) return rIStrm;
  rCmd.SetCmdID(CmdID);
  if (CmdID != gsv::CI_AddObj && CmdID != gsv::CI_UpdateObj) return rIStrm;

  if (getline(rIStrm,Line,'=').fail()) return rIStrm;

  istringstream IStrm_tmp(Line);
  IStrm_tmp >> Keyword;
  if (Keyword != "Name") {
    CErr_1(" Unknown keyword: \"" << Keyword << "\"" << endl <<
	   " It was expected the word \"Name\"");
    return rIStrm;
  }

  std::string  Name;
  if ((rIStrm >> Name).fail()) return rIStrm;
  rCmd.SetQName(Name);
  return rIStrm >> rCmd.UseParams();
}




/*!
 * \brief Zapisuje polecenie do strumienia
 */
std::ostream &operator << (std::ostream &rOStrm, const gsv::ServerCommand &rCmd)
{
  rOStrm << rCmd.GetCmdID();
  switch (rCmd.GetCmdID()) {
     case gsv::CI_Nothing:
     case gsv::CI_Close:
     case gsv::CI_Clear:
     case gsv::CI_Display: return rOStrm;
       
     case gsv::CI_AddObj:
     case gsv::CI_UpdateObj: break;
     default: return rOStrm << "Unknown command ID!!!";
  }
  return rOStrm << " Name=" << rCmd.GetQName() << ' ' << rCmd.GetParams();
}




