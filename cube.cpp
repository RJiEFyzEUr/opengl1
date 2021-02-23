// #include <chrono>
// #include <thread>
// #include <unistd.h>

# include <cstdlib>
# include <cmath>
# include <iostream>
# include <iomanip>
# include <fstream>

# include "GL/glut.h"
# include "GL/freeglut.h"

using namespace std;

GLfloat vertices[][3] = {
  { -1.0, -1.0, -1.0 },
  {  1.0, -1.0, -1.0 },
  {  1.0,  1.0, -1.0 },
  { -1.0,  1.0, -1.0 },
  { -1.0, -1.0,  1.0 },
  {  1.0, -1.0,  1.0 },
  {  1.0,  1.0,  1.0 },
  { -1.0,  1.0,  1.0 } };

GLfloat normals[][3] = {
  { -1.0, -1.0, -1.0 },
  {  1.0, -1.0, -1.0 },
  {  1.0,  1.0, -1.0 },
  { -1.0,  1.0, -1.0 },
  { -1.0, -1.0,  1.0 },
  {  1.0, -1.0,  1.0 },
  {  1.0,  1.0,  1.0 },
  { -1.0,  1.0,  1.0 } };

GLfloat colors[][3] = {
  { 0.0, 0.0, 0.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 1.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { 0.0, 1.0, 1.0 } };

static GLint axis = 2;
static GLfloat theta[4] = { 0.0, 0.0, 0.0, 0.0 };
static GLfloat scale = 1.0;

int main ( int argc, char *argv[] );
void colorcube ( );
void display ( );
void mouse ( int btn, int state, int x, int y );
void myReshape ( int w, int h );
void polygon ( int a, int b, int c, int d );
void spinCube ( );

/* Called back when timer expired */
void Timer(int value) {
  theta[axis] = theta[axis] + 1.0;
  if ( 360.0 < theta[axis] ) 
  {
    theta[axis] = theta[axis] - 360.0;
  }
  
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(10, Timer, 0); // next Timer call milliseconds later
}

/* Callback handler for special-key event */
void specialKeys(int key, int x, int y) {
   switch (key) {
      case GLUT_KEY_LEFT:    
         scale -= 0.1;
         break;
      case GLUT_KEY_RIGHT:    
         scale += 0.1;
         break;
   }
}

int main ( int argc, char *argv[] )
{
  glutInit ( &argc, argv );
  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize ( 500, 500 );
  glutInitWindowPosition ( 0, 0 );
  glutCreateWindow ( "Rotating cube" );
  glutReshapeFunc ( myReshape );
  glutDisplayFunc ( display );
  // glutIdleFunc ( spinCube );
  glutTimerFunc(0, Timer, 0);
  glutMouseFunc ( mouse );
  glutSpecialFunc(specialKeys);

  glEnable ( GL_DEPTH_TEST );
  glutMainLoop ( );

  return 0;
}

void colorcube ( )
{
  polygon ( 1, 2, 0, 3 );
  polygon ( 2, 3, 7, 6 );
  polygon ( 0, 4, 7, 3 );
  polygon ( 1, 2, 6, 5 );
  polygon ( 4, 5, 6, 7 );
  polygon ( 0, 1, 5, 4 );

  return;
}

void display ( )
{

  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity ( );
  
  glRotatef ( theta[0], 1.0, 0.0, 0.0 );
  glRotatef ( theta[1], 0.0, 1.0, 0.0 );
  glRotatef ( theta[2], 0.0, 0.0, 1.0 );

  glScalef(scale, scale, scale);
  
  colorcube ( );

  glutSwapBuffers ( );

  return;
}

bool axis0 = false, axis1 = false, axis2 = false;
// true = stop

void mouse ( int btn, int state, int x, int y )
{
  if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
  {
    axis0 = !axis0;
    if(axis0) axis = 4;
    else axis = 0;
  }
  if ( btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
  {
    axis1 = !axis1;
    if(axis1) axis = 4;
    else axis = 1;
  }
  if ( btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
  {
    axis2 = !axis2;
    if(axis2) axis = 4;
    else axis = 2;
  }

  return;
}

void myReshape ( int w, int h )
{
  
  glViewport ( 0, 0, w, h );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity ( );

  if ( w <= h )
  {
    glOrtho ( 
      -2.0, 2.0, 
      -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w, 
      -10.0, 100.0 );
  }
  else
  {
    glOrtho ( 
      -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w,  
      -2.0, 2.0, 
      -10.0, 100.0 );
  }

  glMatrixMode ( GL_MODELVIEW );

  return;
}

void polygon ( int a, int b, int c, int d )
{
  glBegin ( GL_POLYGON );
    glColor3fv ( colors[a] );
    // glNormal3fv ( normals[a] );
    glVertex3fv ( vertices[a] );
    glColor3fv ( colors[b] );
    // glNormal3fv ( normals[b] );
    glVertex3fv ( vertices[b] );
    glColor3fv ( colors[c] );
    // glNormal3fv ( normals[c] );
    glVertex3fv ( vertices[c] );
    glColor3fv ( colors[d] );
    // glNormal3fv ( normals[d] );
    glVertex3fv ( vertices[d] );
  glEnd ( );

  glBegin(GL_LINES); // draw line from a to c
    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv ( vertices[a] );
    glVertex3fv ( vertices[c] );
  glEnd();

  return;
}

void spinCube ( )
{

  theta[axis] = theta[axis] + 0.1;
  if ( 360.0 < theta[axis] ) 
  {
    theta[axis] = theta[axis] - 360.0;
  }
  glutPostRedisplay ( );

  return;
}