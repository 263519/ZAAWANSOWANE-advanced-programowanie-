#include "gsv-Cuboid.hh"
#include "gtsDebug.hh"
#include <iostream>
#include <sstream>
#include <QGLViewer/qglviewer.h>

using namespace std;


inline
unsigned short int MakeBrighter(unsigned short int Lum)
{
  #define SHIFT  20
  
  if (Lum > (255-SHIFT)) return 255;
  return Lum+SHIFT;
}

void gsv::Cuboid::DrawGL() const
{
  const Vector3d   &rPos_m = GetPosition_m();
  const RGB        &rColor = GetRGB();
  //  Vector3d         Size_m = GetSize_m();
  const gsv::Vector3d  &rScale=GetScale();
  const gsv::Vector3d  &rShift=GetShift_bsc();
  //  Size_m /= 2;

#define Vx(Sign) (Sign 0.5)
#define COORDS3(Vec)  Vec[0],Vec[1],Vec[2]
#define OPO_COORDS3(Vec)  -Vec[0],-Vec[1],-Vec[2]
#define REV_COORD(Val) (Val ? 1/Val:0)
#define REV_COORDS3(Vec)  REV_COORD(Vec[0]),REV_COORD(Vec[1]),REV_COORD(Vec[2])
  
  glTranslatef(COORDS3(rPos_m));  
  glRotatef(GetAng_Yaw_deg(), 0.0, 0.0, 1.0);
  glRotatef(GetAng_Pitch_deg(), 0.0, 1.0, 0.0);
  glRotatef(GetAng_Roll_deg(), 1.0, 0.0, 0.0);
  glScalef(COORDS3(rScale));  
  glTranslatef(COORDS3(rShift));


  glBegin(GL_QUADS);
   glColor3ub(rColor.GetColor_Red(),rColor.GetColor_Green(),rColor.GetColor_Blue());
   glNormal3f(-1,0,0);
   glVertex3f( Vx(-), Vx(-),  Vx(-));  // Boczna x=-1
   glVertex3f( Vx(-), Vx(+),  Vx(-));
   glVertex3f( Vx(-), Vx(+),  Vx(+));
   glVertex3f( Vx(-), Vx(-),  Vx(+));

   
   glNormal3f(0,-1,0);
   glVertex3f( Vx(-), Vx(-),  Vx(-));  // Boczna y=-1
   glVertex3f( Vx(+), Vx(-),  Vx(-));
   glVertex3f( Vx(+), Vx(-),  Vx(+));
   glVertex3f( Vx(-), Vx(-),  Vx(+));

   glNormal3f(0,1,0);
   glVertex3f( Vx(-), Vx(+),  Vx(-));  // Boczna y=+1
   glVertex3f( Vx(+), Vx(+),  Vx(-));
   glVertex3f( Vx(+), Vx(+),  Vx(+));
   glVertex3f( Vx(-), Vx(+),  Vx(+));   


   glNormal3f(0,0,-1);
   glVertex3f( Vx(-), Vx(-),  Vx(-));  // Boczna z=-1
   glVertex3f( Vx(+), Vx(-),  Vx(-));
   glVertex3f( Vx(+), Vx(+),  Vx(-));
   glVertex3f( Vx(-), Vx(+),  Vx(-));

   glNormal3f(0,0,1);
   glVertex3f( Vx(-), Vx(-),  Vx(+));  // Boczna z=+1
   glVertex3f( Vx(+), Vx(-),  Vx(+));
   glVertex3f( Vx(+), Vx(+),  Vx(+));
   glVertex3f( Vx(-), Vx(+),  Vx(+));   

   glColor3ub(MakeBrighter(rColor.GetColor_Red()),
	      MakeBrighter(rColor.GetColor_Green()),
	      MakeBrighter(rColor.GetColor_Blue()));   
   glNormal3f(1,0,0);
   glVertex3f( Vx(+), Vx(-),  Vx(-));  // Boczna x=+1
   glVertex3f( Vx(+), Vx(+),  Vx(-));
   glVertex3f( Vx(+), Vx(+),  Vx(+));
   glVertex3f( Vx(+), Vx(-),  Vx(+));

   glEnd();

   glTranslatef(OPO_COORDS3(rShift));   
   glScalef(REV_COORDS3(rScale));
}

#define DISP_COOR( vec, index ) setw(4) << vec[index] << " "
#define DISP_VECT( vec ) DISP_COOR(vec,0) <<  DISP_COOR(vec,1) <<  DISP_COOR(vec,2)

std::string gsv::Cuboid::BuildCmd() const
{
  ostringstream  OStrm;

  OStrm << "UpdateObj "// <<  DISP_VECT(GetSize_m()) << "  "
	<< DISP_VECT(GetPosition_m()) << "  "
	<< GetAng_Roll_deg() << " "
	<< GetAng_Pitch_deg() << " "
	<< GetAng_Yaw_deg() << "  "
	<< GetColorRGB();
  return OStrm.str();
}
