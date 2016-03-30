// Compilar con: -L/usr/X11R6/lib/ -lGL -lGLU -lglut

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ELEMENTOS		200
#define WIDTH_PLANO		3000
#define HEIGHT_PLANO 	3000

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
	gluOrtho2D (0.0, WIDTH_PLANO, 0.0, HEIGHT_PLANO);
}

float Fuerza(Cuerpo a, Cuerpo b){
	float G = 1;
	float norma = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);

	if (norma < 1){
		return 0.0;
	}


	return  G * a.masa * b.masa / pow(sqrt(norma), 3);
}

void gen_cumulo(Cuerpo *cuerpos){
	int i;

	for (i = 0; i < ELEMENTOS; ++i)
	{

		cuerpos[i].fuerza[0] = 0;
		cuerpos[i].fuerza[1] = 0;

		cuerpos[i].vel[0] = 0;
		cuerpos[i].vel[1] = 0;

		cuerpos[i].masa = 1;

		srand(time(NULL)*i);
		cuerpos[i].x =  WIDTH_PLANO/2 + rand()%200;
		cuerpos[i].y = HEIGHT_PLANO/2 + rand()%200;

		i++;
		cuerpos[i].fuerza[0] = 0;
		cuerpos[i].fuerza[1] = 0;

		cuerpos[i].vel[0] = 0;
		cuerpos[i].vel[1] = 0;

		cuerpos[i].masa = 1;

		srand(time(NULL)*i);
		cuerpos[i].x =  WIDTH_PLANO/2 + rand()%200 - 200;
		cuerpos[i].y = HEIGHT_PLANO/2 + rand()%200 - 200;
	}
}

void itera(Cuerpo *cuerpos){
	int i, j;
	float k, r;

	for (i = 0; i < ELEMENTOS - 1; ++i) {
		for (j = i; j < ELEMENTOS; ++j) {
			k = Fuerza(cuerpos[i], cuerpos[j]);
			
			r = k * (cuerpos[i].x - cuerpos[j].x);
			cuerpos[i].fuerza[0] -= r;
			cuerpos[j].fuerza[0] += r;

			r = k * (cuerpos[i].y - cuerpos[j].y);
			cuerpos[i].fuerza[1] -= r;
			cuerpos[j].fuerza[1] += r;
		}
	}

	for (i = 0; i < ELEMENTOS; ++i)
	{
		// Actualizamos la velocidad
		cuerpos[i].vel[0] += cuerpos[i].fuerza[0]/cuerpos[i].masa;
		cuerpos[i].vel[1] += cuerpos[i].fuerza[1]/cuerpos[i].masa;

		// Actualizamos la posición
		cuerpos[i].x += cuerpos[i].vel[0];
		cuerpos[i].y += cuerpos[i].vel[1];

		cuerpos[i].fuerza[0] = 0;
		cuerpos[i].fuerza[1] = 0;


	}
}

void display(){
	// Almacenamos lista de cuerpos
	Cuerpo *cuerpos;
	cuerpos = (Cuerpo *) malloc(ELEMENTOS * sizeof(Cuerpo));

	if (cuerpos == NULL){
		printf("Error creando cuerpos\n");
		exit(0);
	}

	int i;

	printf(">> %f\n", cuerpos[0].masa);
	gen_cumulo(cuerpos);

	do{
		// printf("-- %f\n", cuerpos[0].masa);
		// Limpiamos pantalla
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);

		for (i = 0; i < ELEMENTOS; ++i){
			glVertex2i(cuerpos[i].x , cuerpos[i].y);
		}


		glEnd();
		
		// Actualizamos pantalla
		glFlush();
		
		itera(cuerpos);

		// sleep(1);
		
	} while(1);



	free(cuerpos);
}

int main(int argc, char *argv[])
{
	// Iniciamos openGL
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (100, 100);
	
	glutCreateWindow ("n Cuerpos");

	// Iniciamos el dibujado 2D
	init2D(0.0,0.0,0.0);
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}