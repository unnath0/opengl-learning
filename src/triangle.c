#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-10, 10, -10, 10);
  glMatrixMode(GL_MODELVIEW);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glBegin(GL_POLYGON);
  
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-5, -5);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(5, -5);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0, 5);

  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

  glutInitWindowPosition(200, 100);
  glutInitWindowSize(500, 500);

  glutCreateWindow("1JS21CS024 | triangle");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  init();

  glutMainLoop();

  return 0;
}
