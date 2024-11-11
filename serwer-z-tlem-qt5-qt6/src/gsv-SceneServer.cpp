#include <sys/types.h>
#include <sys/socket.h>
#include "gsv-SceneServer.hh"
#include "gtsDebug.hh"
#include <thread>
#include <cstring>
#include <iostream>

using namespace std;

#define BUFF_SIZE  10000

/*!
 * Nasłuchuje poleceń dla interpretera, czyta je i wstawia
 * do bufora poleceń.
 */
void gsv::SceneServer::Listing4InterpCmds(int Socket)
{
  ssize_t  RecvCount;
  char     Buff[BUFF_SIZE+1];
  char    *pCurrBuff = Buff, *pTerm;
  ssize_t  CurrSize = BUFF_SIZE;
  ssize_t  CurrCount = 0;
  
  Buff[BUFF_SIZE] = 0;  // Prawdziwy rozmiar to: BUFF_SIZE+1
  _CmdInterp.MarkContinueListening();

  while (ShouldContinueLooping() && ShouldContinueListening()) {
    RecvCount = recv(Socket,pCurrBuff,CurrSize,MSG_DONTWAIT);
    if (RecvCount == -1) {
      if (errno != EAGAIN) {
        CWarning_1(":( Blad odczytu polecenia dla serwera z gniazda sieciowego.");
      };
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      continue;
    }
    if (RecvCount == 0) {
      _CmdInterp.AddCmd("Close");
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      continue;
    }
    
    CurrCount += RecvCount;
    *(pCurrBuff+CurrCount) = 0;
    /*
    for (int Idx = 0; Idx < CurrCount; ++Idx) {
      cout << "   Byte[" << Idx << "] = " << static_cast<int>(pCurrBuff[Idx]) << endl;
    }
    */
    while ((pTerm = strchr(pCurrBuff,'\n')) != nullptr) {
      *pTerm = 0; // Aby stworzyć napis w sensie C.
      _CmdInterp.AddCmd(pCurrBuff);
      ++pTerm;  CurrCount -= pTerm-pCurrBuff;
      pCurrBuff = pTerm;
    }
    if (CurrCount > 0) {
      if (*pCurrBuff == 0 || *pCurrBuff == -1) {
	_CmdInterp.AddCmd("Close");
	CurrCount = 0;
	pCurrBuff = Buff;
	continue;
      }
      strcpy(Buff,pCurrBuff); // Na końcu jest zero, gdyż wstawione wcześniej
      pCurrBuff = Buff+CurrCount;
      CurrSize = BUFF_SIZE-CurrCount;
      continue;
    }
    assert(CurrCount == 0);
    pCurrBuff = Buff;
    CurrSize = BUFF_SIZE;
  }
  cout << " Polaczenie zostalo zamkniete" << endl;
}



/*!
 * Wykonuje plecenia pobierając je z bufora poleceń.
 */
void gsv::SceneServer::ExecCmds()
{
  while (ShouldContinueLooping()) {
    if (_CmdInterp.ExecCmd(_BuffScn)) continue;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }  
}
