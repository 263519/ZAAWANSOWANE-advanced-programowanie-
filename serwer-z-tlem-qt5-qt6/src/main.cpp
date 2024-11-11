
// #ifdef __GNUG__
// # pragma interface
// # pragma implementation
// #endif


#include <QApplication>
#include <iostream>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QStatusBar>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <errno.h>
#include "gsv-CommandInterpreter.hh"
#include "gsv-WgViewer3D.hh"
#include "gsv-SceneServer.hh"
#include "gtsDebug.hh"
#include "gsv-Const.h"
#include "gsv-GraphicsWindow.hh"
#include "gsv-GeomParams.hh"
#include "gsv-ServerCommand.hh"
#include <signal.h>

using namespace std;

bool  g_ContinueListen = true;
int   g_Socket4Connect;
bool  g_SocketError = false;

#define SHOW( x ) \
  case x: cout << "  Nazwa bledu: " #x << endl;  break;

void ShowError()
{
  cout << "  Error: " << errno << endl;
  switch (errno) {
    SHOW(EACCES);
    SHOW(EAFNOSUPPORT);
    SHOW(EINVAL);
    SHOW(ENFILE);
    SHOW(ENOBUFS);
    SHOW(EPROTONOSUPPORT);
    SHOW(ENOMEM);
  }
}



void Handler_SigTerminate(int SigID)
{
  cerr << "Terminated ... Signal: " << SigID << endl;
  exit(0);
}

/*!
 * Nasłuchuje nowych połączeń i jeśli się pojawi, to uruchamia jego obsługę.
 * \param[in] Port - numer portu, na którym ma być prowadzony nasłuch
 *                   nowych połączeń.
 * \param[in] pScnServ - wskaźnik na obiekt serwera sceny roboczej
 *                   wykorzystywanej do obsługi nowego połączenia. 
 * \retval  0 - zakończono poprawnie pętlę nasłuchu,
 * \retval -1 - nie może utowrzyć gniazda dla nasłuchu,
 * \retval -2 - brak możliwości dowiązania do portu,
 * \retval -3 - błąd wykonania polecenie listen,
 * \retval -4 - błąd połączenia.
 */
int StartListening(int Port, gsv::SceneServer  *pScnServ)
{
  int  Socket4Listening; 
  int  Socket4Connect;

  struct sockaddr_in    cli_addr, serv_addr;
  socklen_t  ClAddrLen;



  if ((Socket4Listening = socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK,0)) < 0) {
    cerr << " Blad otwarcia gniazda do nasluchu." << endl;
    g_SocketError = true;
    return -1;
  }

  bzero((char *)&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(Port);

  if (bind(Socket4Listening,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
    cerr << " Blad powiazania gniazda z adresem" << endl;
    close(Socket4Listening);
    g_SocketError = true;
    return -2;
  }

  ClAddrLen = sizeof(cli_addr);

  if (listen(Socket4Listening,5) < 0) {
    cerr << " Blad rozpoczecia nasluchiwania." << endl;
    close(Socket4Listening);
    g_SocketError = true;
    return -3;
  }

   while (g_ContinueListen) {
    Socket4Connect = accept(Socket4Listening,(struct sockaddr *)&cli_addr,&ClAddrLen);
    if (Socket4Connect < 0) {
      if (errno == EAGAIN ) {
         usleep(10000); continue;
      }
      close(Socket4Listening);
      g_SocketError = true;
      return -4;
    }
    cout << " Nowe polaczenie" << endl;
    pScnServ->Listing4InterpCmds(Socket4Connect);

    shutdown(Socket4Connect,SHUT_RDWR);
    close(Socket4Connect);
   }

  int err = shutdown(Socket4Listening,SHUT_RDWR);
  if (err) {
    cerr << " Shutdown err: " << errno << endl;
  }
  err = close(Socket4Listening);
  if (err) {
    cerr << " Close err: " << errno << endl;
  }
  return 0;
}



/*!
 * Funkcja wątku nasłuchiwania nowych połączeń.
 * \param[in] pScnServ - wskaźnik na obiekt serwera sceny roboczej
 *                   wykorzystywanej do obsługi nowego połączenia. 
 */
void *Listen4Connect(void *pScnServ)
{
  StartListening(PORT,reinterpret_cast<gsv::SceneServer*>(pScnServ));
  return nullptr;
}


/*!
 * Funkcja wątku obsługi poleceń, których efekt realizacji
 * ma być przekazany do serwera graficznego. Efektem tym
 * są nowe współrzędne obiektów sceny.
 * \param[in] pScnServ - wskaźnik na obiekt serwera sceny roboczej
 *                   wykorzystywanej, na które modyfikowane są położenia
 *                   obiektów sceny.
 */
void Fun_CmdsExecutor(gsv::SceneServer  *pScnServ)
{
  pScnServ->ExecCmds();
}


void SetSignalHandler(int SigID)
{
  signal(SigID,Handler_SigTerminate);
}

int main( int argc, char * argv[] ) 
{
  cout << "Port nasluchu: " << PORT << endl;

  SetSignalHandler(SIGTERM);
  SetSignalHandler(SIGURG);
  SetSignalHandler(SIGPIPE);
  
  
  gsv::SceneServer    ScnServ;

  std::thread          Th4CmdInterp(Fun_CmdsExecutor,&ScnServ);
  
  pthread_t            Thread_Receiving;

  pthread_create(&Thread_Receiving,NULL,Listen4Connect,&ScnServ);

  usleep(400000);
  if (g_SocketError) {
    cerr << " Problem z rozpoczeciem nasluchiwania." << endl;
    g_ContinueListen = false;

    ScnServ.FinishLooping();
    Th4CmdInterp.join();
    pthread_join(Thread_Receiving,NULL);
    return 100;
  }
  
  QApplication             App(argc,argv);
  gsv::MainWindow4Server   Win4Serv(&ScnServ.UseBuffScn());
  Win4Serv.setWindowTitle(QObject::tr("Serwer Graficzny"));
  Win4Serv.show();
  int Result = App.exec();
  
  ScnServ.FinishLooping();
  
  g_ContinueListen = false;
  Th4CmdInterp.join();
  pthread_join(Thread_Receiving,NULL);

  return Result;
}
