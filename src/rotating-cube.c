#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void init();
void display();
void reshape(int width, int height);
void keyCallback(unsigned char key, int x, int y);
void drawCube(GLfloat center_posx, GLfloat center_posy, GLfloat center_posz, GLfloat edge_length);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main (int argc, char *argv[]) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(500, 500);
  glutCreateWindow("Rotate the cube");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyCallback);
  glutIdleFunc(display);

  glutMainLoop();

  return 0;
}

void init(){
  glEnable(GL_DEPTH);
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLfloat half_screen_width = SCREEN_WIDTH * 0.5;
  GLfloat half_screen_height = SCREEN_HEIGHT * 0.5;

  glPushMatrix();

  glTranslatef(half_screen_width, half_screen_height, -500);

  glRotatef(rotationX, 1, 0, 0);
  glRotatef(rotationY, 0, 1, 0);

  glTranslatef(-half_screen_width, -half_screen_height, 500);

  drawCube(half_screen_width, half_screen_height, -500, 200);

  // Try out commenting out glPopMatrix() to see if it uses the current matrix
  // values
  // not popping the matrix results in some wacky stuff
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(int width, int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1000, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyCallback(unsigned char key, int x, int y){
  const GLfloat rotation_speed = 10.0f;

  switch(key){
    case 'w':
      rotationX += rotation_speed;
      break;
    case 's':
      rotationX -= rotation_speed;
      break;
    case 'a':
      rotationY += rotation_speed;
      break;
    case 'd':
      rotationY -= rotation_speed;
      break;
  }

  glutPostRedisplay();
}

void drawCube(GLfloat center_posx, GLfloat center_posy, GLfloat center_posz, GLfloat edge_length)
{
  GLfloat half_side_length = edge_length * 0.5;

  GLfloat vertices[] = {
    // front face
    center_posx - half_side_length, center_posy + half_side_length, center_posz + half_side_length, // top left
    center_posx + half_side_length, center_posy + half_side_length, center_posz + half_side_length, // top right
    center_posx + half_side_length, center_posy - half_side_length, center_posz + half_side_length, // bottom right
    center_posx - half_side_length, center_posy - half_side_length, center_posz + half_side_length, // bottom left

    // back face
    center_posx - half_side_length, center_posy + half_side_length, center_posz - half_side_length, // top left
    center_posx + half_side_length, center_posy + half_side_length, center_posz - half_side_length, // top right
    center_posx + half_side_length, center_posy - half_side_length, center_posz - half_side_length, // bottom right
    center_posx - half_side_length, center_posy - half_side_length, center_posz - half_side_length, // bottom left

    // left side face
    center_posx - half_side_length, center_posy + half_side_length, center_posz - half_side_length, // top left
    center_posx - half_side_length, center_posy + half_side_length, center_posz + half_side_length, // top right
    center_posx - half_side_length, center_posy - half_side_length, center_posz + half_side_length, // bottom right
    center_posx - half_side_length, center_posy - half_side_length, center_posz - half_side_length, // bottom left

    // right side face
    center_posx + half_side_length, center_posy + half_side_length, center_posz + half_side_length, // top left
    center_posx + half_side_length, center_posy + half_side_length, center_posz - half_side_length, // top right
    center_posx + half_side_length, center_posy - half_side_length, center_posz - half_side_length, // bottom right
    center_posx + half_side_length, center_posy - half_side_length, center_posz + half_side_length, // bottom left

    // top face
    center_posx - half_side_length, center_posy + half_side_length, center_posz - half_side_length, // top left
    center_posx + half_side_length, center_posy + half_side_length, center_posz - half_side_length, // top right
    center_posx + half_side_length, center_posy + half_side_length, center_posz + half_side_length, // bottom right
    center_posx - half_side_length, center_posy + half_side_length, center_posz + half_side_length, // bottom left

    // bottom face
    center_posx - half_side_length, center_posy - half_side_length, center_posz + half_side_length, // top left
    center_posx + half_side_length, center_posy - half_side_length, center_posz + half_side_length, // top right
    center_posx + half_side_length, center_posy - half_side_length, center_posz - half_side_length, // bottom right
    center_posx - half_side_length, center_posy - half_side_length, center_posz - half_side_length, // bottom left
  };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
}
