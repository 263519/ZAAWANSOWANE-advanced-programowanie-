#ifndef SGV_WGVIEWER3D_HH
#define SGV_WGVIEWER3D_HH

#include <QGLViewer/qglviewer.h>
#include <QTimer>
#include "gsv-BufferedScene.hh"

/*!
 * \file
 * \brief Widget wizualizujący obiekty 3D
 *
 * Zawiera definicję klasy wizualizującej obiekty 
 */


namespace gsv {
/*!
 * \brief Widget wizualizujący obiekty 3D
 */
 class WgViewer3D : public QGLViewer
 {
    Q_OBJECT
   /*!
    * \brief Aktuwuje okresowe sprawdzanie zawartości sceny
    *
    * Aktuwuje okresowe sprawdzanie zawartości sceny.
    * W przypadku jej zmiany, wymusza jej odrysowanie.
    */
   QTimer   _Timer;

   /*!
    * \brief Wskaźnik na scenę, której obiekty mają być wizualizowane.
    */
   gsv::BufferedScene  *_pBuffScn = nullptr;
  
  protected :
   virtual void draw() override;
   virtual void init() override;
   virtual QString helpString() const override;
  public:
   WgViewer3D(QWidget *pParent, gsv::BufferedScene  *_pBScn);

  public slots:
  /*!
   * \brief Okresowa aktualizacja sceny
   */
   void PeriodicSceneUpdate();
 };
}

#endif
