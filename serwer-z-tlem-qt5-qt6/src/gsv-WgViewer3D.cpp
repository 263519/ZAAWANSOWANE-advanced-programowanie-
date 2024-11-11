#include <iostream>
#include "gsv-WgViewer3D.hh"
#include <SOIL/SOIL.h>
#include "gsv-BackgroundImage.h"

using namespace std;



static GLuint Texture4Bg;


//====================================================================
//===                  WgViewier3D
//===


/*!
 *
 */
gsv::WgViewer3D::WgViewer3D(QWidget *pParent, gsv::BufferedScene  *pBScn):
  QGLViewer(pParent),  _pBuffScn(pBScn)
{
  setAttribute(Qt::WA_DeleteOnClose);
  _Timer.setInterval(50);
  connect(&_Timer,SIGNAL(timeout()),this,SLOT(PeriodicSceneUpdate()));
  _Timer.start();
}




void gsv::WgViewer3D::PeriodicSceneUpdate()
{
  if (_pBuffScn->IsChanged()) update();
}



void CreateBackground()
{
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 
  glBindTexture(GL_TEXTURE_2D, Texture4Bg);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  
  glLoadIdentity();
  glDepthMask(GL_FALSE);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  glOrtho(0,1,1,0,-1,1);

  glBegin(GL_QUADS);  // Tworzenie kwadratu, na którym będzie
    glTexCoord2f(0,0); // rozpięta tekstura tła.
    glVertex2f(0,0);

    glTexCoord2f(1,0);
    glVertex2f(1,0);

    glTexCoord2f(1,1);
    glVertex2f(1,1);

    glTexCoord2f(0,1);
    glVertex2f(0,1);
  glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}






void gsv::WgViewer3D::init()
{
  // Restore previous viewer state.
  restoreStateFromFile();
  glEnable(GL_DEPTH_TEST);

   /*------------
    *  Tworzenie tekstury tła
    */
  Texture4Bg = SOIL_load_OGL_texture(
		FILE_BACKGROUND_IMAGE,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	       );

  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
}




void gsv::WgViewer3D::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
   /*-----------------------------------------------------
    *  Tworzenie tła wypełnionego wygenerowaną teksturą
    */
  CreateBackground();
  glDisable(GL_TEXTURE_2D);
  
  glDepthMask(GL_TRUE);

  
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
 
  glScalef( 0.2, 0.2, 0.2 );

  _pBuffScn->LockAccessToCurrScn();
  /* 
  cout << "----- Nodes Tree ___ Start --------------" << endl;
  _pBuffScn->GetCurrScn().PrintNodeTree();
  cout << "----- Nodes Tree ___ End ----------------" << endl;
  */

  _pBuffScn->GetCurrScn().DrawSceneGL();
  _pBuffScn->CancelTrace0Change();
  _pBuffScn->UnlockAccessToCurrScn();
 glFlush();
 glDisable(GL_TEXTURE_2D);  
}



QString gsv::WgViewer3D::helpString() const
{
  QString text("<h2>V i e w e r 3 D</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}



//===
//===                  WgViewier3D
//====================================================================
