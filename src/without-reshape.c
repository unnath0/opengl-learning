#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POLYGON);
  
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-1.0, -1.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(1.0, -1.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0, 1.0);

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

  glutMainLoop();

  return 0;
}
