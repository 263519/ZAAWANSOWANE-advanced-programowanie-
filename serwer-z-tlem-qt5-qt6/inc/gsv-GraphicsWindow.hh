#ifndef GSV_GRAPHICSWINDOW_HH
#define GSV_GRAPHICSWINDOW_HH

// #ifdef __GNUG__
// # pragma interface
// # pragma implementation
// #endif


#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include "gsv-BufferedScene.hh"


/*!
 * \file
 * \brief Zawiera definicje klasę MainWindow4Server
 */



namespace gsv {

/*!
 * \brief Główne okno aplikacji
 */
 class MainWindow4Server: public QMainWindow { //------------------------------
   Q_OBJECT
  public:
   MainWindow4Server(gsv::BufferedScene *pBuffScn, QWidget *pParent = nullptr);
							    
   public slots:
    void ShowMessage(const QString &);
 }; //------------------------------------------------------------------

}

#endif
