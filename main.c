// Compilar con: -L/usr/X11R6/lib/ -lGL -lGLU -lglut

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
	float fuerza[2];
	float vel[2];
	float x;
	float y;
	float masa;
} Cuerpo;

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void itera(){
	// pass
}

void display(){
	// Limpiamos pantalla
	glClear(GL_COLOR_BUFFER_BIT);

	// Actualizamos pantalla
	glFlush();
}

int main(int argc, char *argv[])
{
	// Iniciamos openGL
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	
	glutCreateWindow ("n Cuerpos");

	// Iniciamos el dibujado 2D
	init2D(0.0,0.0,0.0);
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}