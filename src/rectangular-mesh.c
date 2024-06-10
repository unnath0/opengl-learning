#include <GL/glut.h>

#define maxx 25
#define maxy 25
#define dx 15
#define dy 15

GLfloat x0 = {10.0}, y01 = {50.0};
GLfloat x[maxx] = {50.0}, y[maxy] = {100.0};

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLint i, j;
	glColor3f(1.0,1.0,1.0);

		for(i = 0; i < maxx; i++)
			x[i] = x0 + i * dx;
		for(j = 0; j < maxx; j++)
			y[j] = y01 + j * dy;
		
		for(i = 0; i < maxx - 1; i++)
			for(j = 0; j < maxy - 1; j++)
			{
				// for chess board
				/*
				if((i + j) % 2 == 0){
					glColor3f(0.0,0.0,0.0);
					glBegin(GL_POLYGON);
						glVertex2f(x[i],y[j]);
						glVertex2f(x[i+1],y[j]);
						glVertex2f(x[i+1],y[j+1]);
						glVertex2f(x[i],y[j+1]);
					glEnd();
				}
				else{
				glColor3f(1.0,1.0,1.0);
					glBegin(GL_LINE_LOOP);
						glVertex2f(x[i],y[j]);
						glVertex2f(x[i+1],y[j]);
						glVertex2f(x[i+1],y[j+1]);
						glVertex2f(x[i],y[j+1]);
					glEnd();
				}
				*/
				
				
				//glColor3f((i+j)%2,(i+j)%2,(i+j)%2); // for chess board
				glColor3f(0.7,0.2,0.7);
				//glBegin(GL_POLYGON);
				glBegin(GL_LINE_LOOP);
					glVertex2f(x[i],y[j]);
					glVertex2f(x[i+1],y[j]);
					glVertex2f(x[i+1],y[j+1]);
					glVertex2f(x[i],y[j+1]);
				glEnd();
			}
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 40);
	glutInitWindowSize(500, 500);
	glutCreateWindow("1JS21CS024 | Rectangular Mesh");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
