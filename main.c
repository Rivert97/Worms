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
	glutMouseFunc(&Mouse);

	//Inicialización de variables
	srand(time(NULL));
	CrearTerreno();
	CrearGusanos();

	Px = -ANCHO_MUNDO + ANCHO_PANTALLA/2;
	Py = 0;
	allyIndex = 0;
	enemyIndex = 0;
	currentWorm = &allies[allyIndex];
	CrearBala();
	CrearBoton();
	turno = -1;
	velocidad = 0;
	fase = 0;

	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	char texto[30];
	static float randomNumber = 0.5;
	glClear(GL_COLOR_BUFFER_BIT);

	DibujarTerreno(Px, Py);
	DibujarGusanos(allies, NUM_WORMS, Px, Py);//Dibujar aliados
	DibujarGusanos(enemies, NUM_WORMS, Px, Py);//Dibujar enemigos
	DibujarBala(Px,Py);
	
	AsignaColor(NEGRO);
	switch (turno)
	{
		case -2:
			if(-Px < (currentWorm->x - ANCHO_PANTALLA/2))
				Px--;
			else
				turno = 0;
			break;
		case -1:
			if(-Px > (currentWorm->x - ANCHO_PANTALLA/2))
				Px++;
			else
				turno = 0;
			break;
		case 0://Momento de mover
			sprintf(texto, "Muevete con 'a' y 'd'");
			DibujarTexto(texto, ANCHO_PANTALLA/2 - 80, ALTO_PANTALLA-30);
			sprintf(texto, "Atacar [Enter]");
			DibujarBoton(texto);
			break;

		case 1://Momento de atacar
			sprintf(texto, "Apunta con 'w' y 's'");
			DibujarTexto(texto, ANCHO_PANTALLA/2 - 80, ALTO_PANTALLA-30);
			sprintf(texto, "Disparar [Enter]");
			DibujarBoton(texto);
			break;

		case 2://Cargando
			sprintf(texto, "Enter para disparar");
			DibujarTexto(texto, ANCHO_PANTALLA/2 - 80, ALTO_PANTALLA - 30);
			DibujarVelocidad(velocidad, Px, Py);
			break;
			//3->Bala en el aire
			//4->animación de estrellado de la bala
		case 5://Ganaste
			sprintf(texto, "¡EQUIPO ROJO ANIQUILADO!");
			AsignaColor(VERDE);
			DibujarTexto(texto, ANCHO_PANTALLA/2 - 150, ALTO_PANTALLA/2);
			sprintf(texto, "Jugar de nuevo");
			DibujarBoton(texto);
			break;

		case 6://Perdiste
			sprintf(texto, "¡EQUIPO VERDE ANIQUILADO!");
			AsignaColor(ROJO);
			DibujarTexto(texto, ANCHO_PANTALLA/2 - 150, ALTO_PANTALLA/2);
			sprintf(texto, "Jugar de nuevo");
			DibujarBoton(texto);
			break;
		default:
			break;
	}

	glFlush();
}

void Animate()
{
	static float vel = 1;
	static float dir = 1;
	static unsigned int prevTime = 0;
	unsigned int deltaTime = glutGet(GLUT_ELAPSED_TIME) - prevTime;

	if(turno == 2)
	{
		if(velocidad < 0 && dir == -1 || velocidad > 100 && dir == 1)
			dir*=-1;
		velocidad+=dir*vel;
	}
	if(turno == 3)
	{
		bullet.t += deltaTime/1000.0;
		UpdateBulletPosition();
		if(bullet.x > ANCHO_PANTALLA/2)
			Px = -bullet.x + ANCHO_PANTALLA/2;
		
	}
	if(turno == 4)
	{
		if(glutGet(GLUT_ELAPSED_TIME) - bullet.destTime > 1000)
		{
			if(fase == 0)
			{
				enemyIndex = GetNextIndex(enemies, NUM_WORMS, enemyIndex);
				if(enemyIndex == -1)
				{
					turno = 5;
					glutPostRedisplay();
					return;
				}
				currentWorm = &enemies[enemyIndex];
				fase = 1;
			}
			else
			{
				allyIndex = GetNextIndex(allies, NUM_WORMS, allyIndex);
				if(allyIndex == -1)
				{
					turno = 6;
					glutPostRedisplay();
					return;
				}
				currentWorm = &allies[allyIndex];
				fase = 0;
			}
			Px = -currentWorm->x + ANCHO_PANTALLA/2;
			CrearBala();
			turno = 0;
		}
	}

	prevTime = glutGet(GLUT_ELAPSED_TIME);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	//if(fase == 1) return;
	static float vel = 0.5; //unidades
	static float velAng = 5;
	static unsigned int prevTime = 0;
	static unsigned int nextUpWorm = 0;
	unsigned int deltaTime = glutGet(GLUT_ELAPSED_TIME) - prevTime;

	switch(key)
	{
		case 'a':
		if(currentWorm != NULL && turno == 0)
		{
			currentWorm->x -= vel;
			if(fase == 0)
			{
				if(currentWorm->x < 30)
					currentWorm->x = 30;
			}
			else
			{
				if(currentWorm->x < ANCHO_MUNDO/2 + 40)
					currentWorm->x = ANCHO_MUNDO/2 + 40;
			}
			UpdateBullet();
			if(nextUpWorm < glutGet(GLUT_ELAPSED_TIME))
			{
				currentWorm->isUp = !currentWorm->isUp;
				nextUpWorm = glutGet(GLUT_ELAPSED_TIME) + 300;
			}
		}
		break;

		case 'd':
		if(currentWorm != NULL && turno == 0)
		{
			currentWorm->x += vel;
			if(fase == 1)
			{
				if(currentWorm->x > ANCHO_MUNDO - 40)
					currentWorm->x = ANCHO_MUNDO - 40;
			}
			else
			{
				if(currentWorm->x > ANCHO_MUNDO/2 - 30)
					currentWorm->x = ANCHO_MUNDO/2 - 30;
			}
			UpdateBullet();
			if(nextUpWorm < glutGet(GLUT_ELAPSED_TIME))
			{
				currentWorm->isUp = !currentWorm->isUp;
				nextUpWorm = glutGet(GLUT_ELAPSED_TIME) + 300;
			}
		}
		break;

		case 'w':
		if(currentWorm->isAtacking == 1 && turno == 1)
		{
			if(fase == 0)
				currentWorm->angle += velAng;
			else
				currentWorm->angle -= velAng;
			UpdateBullet();
		}
		break;

		case 's':
		if(currentWorm->isAtacking == 1 && turno == 1)
		{
			if(fase == 0)
				currentWorm->angle -= velAng;
			else
				currentWorm->angle += velAng;
			UpdateBullet();
		}
		break;

		case 13://enter
		if(currentWorm->isAtacking == 1 && turno == 2)
		{
			turno = 3;
			SetUpAttack();
		}
		if(turno == 0)
		{
			turno = 1;
			currentWorm->isAtacking = 1;
			bullet.isActive = 1;
		}
		else if (turno == 1)
		{
			turno = 2;
		}
		break;

		case ' ':
		if(currentWorm->isAtacking == 1 && turno == 2)
		{
			turno = 3;
			SetUpAttack();
		}
		break;
	}

	prevTime = glutGet(GLUT_ELAPSED_TIME);
}

void SpecialKeyboard(int key, int x, int y)
{
	static float velCam = 10;
	switch(key)
	{
		case GLUT_KEY_LEFT:
			if(Px > ANCHO_PANTALLA/2)
				return;
			Px += velCam;
			break;

		case GLUT_KEY_RIGHT:
			if(Px < -(ANCHO_MUNDO - ANCHO_PANTALLA/2))
				return;
			Px -= velCam;
			break;

		/*case GLUT_KEY_UP:
			Py -= velCam;
			break;

		case GLUT_KEY_DOWN:
			Py += velCam;
			break;*/
	}
}

void Mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(x > btDisparar.x && x < btDisparar.x + btDisparar.ancho)
			if(y < ALTO_PANTALLA - btDisparar.y && y > ALTO_PANTALLA - btDisparar.y - btDisparar.alto)
			{
				if(turno == 0)
				{
					turno = 1;
					currentWorm[allyIndex].isAtacking = 1;
					bullet.isActive = 1;
				}
				else if (turno == 1)
				{
					turno = 2;
				}
				else if (turno == 5 || turno == 6)
				{
					CrearGusanos();
					Px = 0;
					Py = 0;
					allyIndex = 0;
					enemyIndex = 0;
					currentWorm = &allies[allyIndex];
					CrearBala();
					CrearBoton();
					turno = 0;
					velocidad = 0;
					fase = 0;
				}
			}
	}
}