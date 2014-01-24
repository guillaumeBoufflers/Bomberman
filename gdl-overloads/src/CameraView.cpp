
#include	"CameraView.hh"

CameraView::CameraView() : twoCams(0)
{
  _x = 0;
  _y = 0;
  _z = 0;
}

CameraView::~CameraView()
{

}

bool  CameraView::isDualMode() { return (twoCams); }
void  CameraView::setDualMode(bool dual) { twoCams = dual; }

void	CameraView::initialize3d()
{
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void  CameraView::initialize2d()
{
  this->setDualMode(false);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, (GLdouble)W_WIDTH, 0.0, (GLdouble)W_HEIGHT);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);
}

//DualScreen
void  CameraView::setPosAndRot(float x, float y, float z)
{
  _x = x + 000;
  _y = y + 2800;
  _z = z + 1000;
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (isDualMode())
    gluPerspective(70, (float)W_WIDTH / ((float)2.0) / (float)W_HEIGHT, 1, 10000);
  else
    gluPerspective(70, (float)W_WIDTH / W_HEIGHT, 1, 10000);
  gluLookAt(x + 000, y + 2800, z + 1000, x, y, z, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
}

//MonoScreen
void  CameraView::setPosAndRot(float x1, float y1, float z1, float x2, float y2, float z2)
{
  float posMidX = (x1 + x2) / 2;
  float posMidY = (y1 + y2) / 2;
  float posMidZ = (z1 + z2) / 2;

  _x = posMidX + 000;
  _y = posMidY + 2800;
  _z = posMidZ + 1000;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (isDualMode())
    gluPerspective(70, (float)W_WIDTH / ((float)2.0) / W_HEIGHT, 1, 10000);
  else
    gluPerspective(70, (float)W_WIDTH / W_HEIGHT, 1, 10000);
  gluLookAt(posMidX + 000, posMidY + 2800, posMidZ + 1000, posMidX, posMidY, posMidZ, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
}

float	CameraView::getX() const
{
  return (this->_x);
}

float	CameraView::getY() const
{
  return (this->_y);
}

float	CameraView::getZ() const
{
  return (this->_z);
}
