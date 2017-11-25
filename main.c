#include "funciones.h"

int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(ANCHO_PANTALLA,ALTO_PANTALLA);
	glutCreateWindow("Worms?");
	glClearColor(0,0.5,1,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,ANCHO_PANTALLA,0,ALTO_PANTALLA);
	glutIdleFunc(&Animate);

	//ASIGNACION DE CALLBACKS
	glutDisplayFunc(&display);

	//Inicialización de variables
	CrearTerreno();
	CrearGusanos();
	Px = 0;
	Py = 0;

	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	DibujarTerreno(Px, Py);
	DibujarGusanos(allies, NUM_WORMS, Px, Py);//Dibujar aliados
	DibujarGusanos(enemies, NUM_WORMS, Px, Py);//Dibujar enemigos
	glFlush();
}

void Animate()
{
	static float vel = 0.1;
	Px -= vel;
	glutPostRedisplay();
}