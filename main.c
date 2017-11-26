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


	//ASIGNACION DE CALLBACKS
	glutDisplayFunc(&display);
	glutIdleFunc(&Animate);
	glutKeyboardFunc(&Keyboard);
	glutSpecialFunc(&SpecialKeyboard);

	//Inicialización de variables
	CrearTerreno();
	CrearGusanos();

	Px = 0;
	Py = 0;
	currentWorm = enemies;
	CrearBala();

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
	DibujarBala(Px,Py);
	glFlush();
}

void Animate()
{
	static float vel = 0.3;
	Px -= vel;
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	static float vel = 0.5; //unidades
	static unsigned int prevTime = 0;
	static unsigned int nextUpWorm = 0;
	unsigned int deltaTime = glutGet(GLUT_ELAPSED_TIME) - prevTime;

	switch(key)
	{
		case 'a':
		if(currentWorm != NULL)
		{
			currentWorm->x -= vel;
			if(nextUpWorm < glutGet(GLUT_ELAPSED_TIME))
			{
				currentWorm->isUp = !currentWorm->isUp;
				nextUpWorm = glutGet(GLUT_ELAPSED_TIME) + 300;
			}
		}
		break;

		case 'd':
		if(currentWorm != NULL)
		{
			currentWorm->x += vel;
			if(nextUpWorm < glutGet(GLUT_ELAPSED_TIME))
			{
				currentWorm->isUp = !currentWorm->isUp;
				nextUpWorm = glutGet(GLUT_ELAPSED_TIME) + 300;
			}
		}
		break;
	}

	prevTime = glutGet(GLUT_ELAPSED_TIME);
}

void SpecialKeyboard(int key, int x, int y)
{
	static float velAng = 5;
	if(currentWorm->isAtacking)
	{
		switch(key)
		{
			case GLUT_KEY_UP:
				currentWorm->angle += velAng;
				UpdateBullet();
				break;

			case GLUT_KEY_DOWN:
				currentWorm->angle -= velAng;
				UpdateBullet();
				break;
		}
	}
}