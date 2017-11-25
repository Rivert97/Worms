#include "funciones.h"

int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(ANCHO_MUNDO,ALTO_MUNDO);
	glutCreateWindow("Worms?");
	glClearColor(0,0.5,1,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,ANCHO_MUNDO,0,ALTO_MUNDO);
	glutIdleFunc(&Animate);

	//ASIGNACION DE CALLBACKS
	glutDisplayFunc(&display);

	//Inicialización de variables
	CrearTerreno();
	Px = 0;
	Py = 0;

	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	AsignaColor(AZUL);
	DibujarTerreno(Px,Py);
	glFlush();
}

void Animate()
{
	static float vel = 0.5;
	Px += vel;
	glutPostRedisplay();
}