#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../header-files/stb-image.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void init();
void loadTextures();
void display();
void reshape(int width, int height);
void keyCallback(unsigned char key, int x, int y);
void drawCube(GLfloat center_posx, GLfloat center_posy, GLfloat center_posz, GLfloat edge_length);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

GLuint textures[6];

int main (int argc, char *argv[]) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(500, 500);
  glutCreateWindow("Rotate the cube");

  init();
  loadTextures();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyCallback);
  glutIdleFunc(display);

  glutMainLoop();

  return 0;
}

void init(){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DEPTH);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  //glFrontFace(GL_CCW);
}

void loadTextures() {
  const char* filenames[6] = {
    "front.jpg",
    "back.jpg",
    "left.jpg",
    "right.jpg",
    "top.jpg",
    "bottom.jpg"
  };

  glGenTextures(6, textures);

  for (int i = 0; i < 6; ++i) {
    int width, height, channels;
    unsigned char* data = stbi_load(filenames[i], &width, &height, &channels, 0);

    if (data) {
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      stbi_image_free(data);
    } else {
      printf("Failed to load texture %s\n", filenames[i]);
    }
  }
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

void drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edge_length)
{
  GLfloat halfSideLength = edge_length * 0.5;

  GLfloat vertices[] = {
    // Front face
    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,

    // Back face
    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

    // Left face
    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,

    // Right face
    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,

    // Top face
    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength,
    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,
    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength,

    // Bottom face
    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength,
    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength,
    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength
  };

  GLfloat texCoords[] = {
    // Front face
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    // Back face
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    // Left side face
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    // Right side face
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    // Top face
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    // Bottom face
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
  };

  glEnable(GL_TEXTURE_2D);

  for (int i = 0; i < 6; ++i) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices + i * 12);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords + i * 8);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }

  glDisable(GL_TEXTURE_2D);
}

