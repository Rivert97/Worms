#include "funciones.h"

int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(ANCHO,ALTO);
	glutCreateWindow("Worms?");
	glClearColor(1,1,1,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,ANCHO,0,ALTO);

	//ASIGNACION DE CALLBACKS
	glutDisplayFunc(&display);

	//Inicialización de variables
	CrearTerreno();
	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	AsignaColor(AZUL);
	DibujarTerreno(0,0);
	glFlush();
}
