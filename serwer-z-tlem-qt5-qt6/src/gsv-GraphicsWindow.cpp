#include <QStatusBar>
#include "gsv-GraphicsWindow.hh"
#include "gsv-WgViewer3D.hh"





//============================================================
//................ OknoGlowne ................................


void gsv::MainWindow4Server::ShowMessage(const QString &Napis)
{
  statusBar()->showMessage(Napis);
}


gsv::MainWindow4Server::MainWindow4Server(
				      gsv::BufferedScene *pBuffScn,
				      QWidget            *pParent
				    ):
  QMainWindow(pParent)
{
  //SceneView *wOkno = new SceneView(Wiadomosc,this);
  WgViewer3D  *pViewer = new WgViewer3D(this,pBuffScn);
  setCentralWidget(pViewer);
  setStatusBar(new QStatusBar());
}

//................ OknoGlowne ................................
//============================================================
