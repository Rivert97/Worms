#include "funciones.h"

//_______________________________________________________________________ Paleta de colores (CORREGIR)
const float PaletaColor[NCOLORES][3] = {0,0,0,/**/0,0,0.5,/**/0,0,1,/**/
								0,1,1,/**/0,0.5,1,/**/0,0.5,0.5,/**/
								0,1,0.5,/**/0,1,0,/**/0,0.5,0,/**/
								0.5,0,0,/**/1,0,0,/**/0.5,0,0.5,/**/
								1,0,0.5,/**/0.5,0,1,/**/1,0,1,/**/
								0.5,0.5,0,/**/1,0.5,0,/**/0.5,1,0,/**/
								1,1,0,/**/0.5,0.5,0.5,/**/0.75,0.75,0.75,/**/1,0.5,0.5,/**/
								0.5,1,0.5,/**/0.5,0.5,1,/**/0.5,1,1,/**/
								1,0.5,1,/**/1,1,0.5,/**/1,1,1};					//27 combinaciones


//_______________________________________________________________ Dibujado de figuras
void Rectangulo(RECTANGULO *r, float offX, float offY)
{
	if(r->x + r->ancho < -offX || r->x > -offX + ANCHO_PANTALLA) return;
	AsignaColor(r->color);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(r->factor_linea, r->tipo_linea);
	glLineWidth(r->ancho_linea);
	glPointSize(r->ancho_linea);
	glPolygonMode(GL_FRONT, r->tipo);



	glRectf(offX + r->x, offY + r->y, offX + r->x+r->ancho, offY + r->y+r->alto);
	
	ResetOptions();
}

void DibujarGusanos(WORM * gusanos, int num, float offX, float offY)
{
	int i;

	for(i = 0; i < num; i++)
	{
		if(gusanos[i].isAlive == 0) continue;
		if(gusanos[i].x + gusanos[i].grueso < -offX || gusanos[i].x > -offX + ANCHO_PANTALLA) continue;
		AsignaColor(gusanos[i].color);
		
		if(gusanos[i].isUp == 1)	//Gusano caminando
		{
			glRectf(offX + gusanos[i].x, offY + gusanos[i].y, offX + gusanos[i].x + gusanos[i].largo*0.3, offY + gusanos[i].y + gusanos[i].grueso);//Frente
			glRectf(offX + gusanos[i].x + gusanos[i].largo*0.5, offY + gusanos[i].y, offX + gusanos[i].x + gusanos[i].largo*0.8, offY + gusanos[i].y + gusanos[i].grueso);//Atras
			glRectf(offX + gusanos[i].x + gusanos[i].largo*0.2, offY + gusanos[i].y + gusanos[i].grueso, offX + gusanos[i].x + gusanos[i].largo*0.6, offY + gusanos[i].y + gusanos[i].grueso*2.0);//Parte de arriba
		}
		else
		{
			glRectf(offX + gusanos[i].x, offY + gusanos[i].y, offX + gusanos[i].x + gusanos[i].largo, offY + gusanos[i].y + gusanos[i].grueso);//Tail
		}
		
		glRectf(offX + gusanos[i].x, offY + gusanos[i].y, offX + gusanos[i].x - Signo(gusanos[i].largo)*gusanos[i].grueso, offY + gusanos[i].y + gusanos[i].alto);//Head
		
		AsignaColor(NEGRO);
		glPointSize(2);
		glBegin(GL_POINTS);//Ojo
		glVertex2f(offX + gusanos[i].x - Signo(gusanos[i].largo)*gusanos[i].grueso*0.8, offY + gusanos[i].y + gusanos[i].alto*0.8);
		glEnd();

		glLineWidth(2);
		glBegin(GL_LINE_STRIP);	//Boca
		if(gusanos[i].isAtacking == 1)//Gusano atacando
		{
			MedioCirculo(gusanos[i].grueso*0.4, offX + gusanos[i].x - Signo(gusanos[i].largo)*gusanos[i].grueso, offY + gusanos[i].y + gusanos[i].alto*0.5, Signo(gusanos[i].largo));
		}
		else
		{
			glVertex2f(offX + gusanos[i].x - Signo(gusanos[i].largo)*gusanos[i].grueso, offY + gusanos[i].y + gusanos[i].alto*0.5);
			glVertex2f(offX + gusanos[i].x - Signo(gusanos[i].largo)*gusanos[i].grueso*0.4, offY + gusanos[i].y + gusanos[i].alto*0.5);
		}
		glEnd();
		glPointSize(1);
		glLineWidth(10);
		//_________________________________________ Arma
		if(gusanos[i].isAtacking == 1)
		{
			glBegin(GL_LINES);
			glVertex2f(offX + gusanos[i].x + cos(gusanos[i].angle*PI/180.0)*20.0, offY + gusanos[i].y + gusanos[i].alto*0.5 + sin(gusanos[i].angle*PI/180.0)*20);
			glVertex2f(offX + gusanos[i].x - cos(gusanos[i].angle*PI/180.0)*20.0, offY + gusanos[i].y + gusanos[i].alto*0.5 - sin(gusanos[i].angle*PI/180.0)*20);
			glEnd();
		}
		glLineWidth(1);
	}
}

void DibujarBala(float offX, float offY)
{
	if(bullet.isActive == 0) return;

	AsignaColor(bullet.color);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(bullet.factor_linea, bullet.tipo_linea);
	glLineWidth(bullet.ancho_linea);
	glPointSize(bullet.ancho_linea);
	glPolygonMode(GL_FRONT, bullet.tipo);

	glBegin(GL_POLYGON);
	MedioCirculo(bullet.r, offX + bullet.x, offY + bullet.y, 1);
	MedioCirculo(bullet.r, offX + bullet.x, offY + bullet.y, -1);	
	glEnd();

	ResetOptions();
}

void DibujarBoton(char * text)
{
	AsignaColor(btDisparar.color);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(btDisparar.factor_linea, btDisparar.tipo_linea);
	glLineWidth(btDisparar.ancho_linea);
	glPointSize(btDisparar.ancho_linea);
	glPolygonMode(GL_FRONT, btDisparar.tipo);

	glRectf(btDisparar.x, btDisparar.y, btDisparar.x + btDisparar.ancho, btDisparar.y + btDisparar.alto);
	
	AsignaColor(NEGRO);	
	DibujarTexto(text, btDisparar.x + 2, btDisparar.y + 8);

	ResetOptions();
}

void DibujarVelocidad(int vel, float offX, float offY)
{
	int x;
	//Barra
	glBegin(GL_TRIANGLES);
	AsignaColor(VERDE);
	glVertex2f(offX + currentWorm->x - 30, offY + currentWorm->y + 50);
	AsignaColor(ROJO);
	glVertex2f(offX + currentWorm->x + 20, offY + currentWorm->y + 50);
	glVertex2f(offX + currentWorm->x + 20, offY + currentWorm->y + 70);
	glEnd();
	
	//Linea indicador
	x = currentWorm->x - 30 + vel/2;
	glLineWidth(3);
	AsignaColor(NEGRO);
	glBegin(GL_LINES);
	glVertex2f(offX + x, offY + currentWorm->y + 50);
	glVertex2f(offX + x, offY + currentWorm->y + 70);
	glEnd();
	ResetOptions();
}

//____________________________________________________________ Funciones extras
void CrearTerreno()
{
	/*OPCIONES op;
	op.color = VERDE;
	op.tipo_linea = L_LINE;
	op.llenado = GL_FILL;
	op.ancho_linea = 1;
	op.factor_linea = 1;*/
	int i;

	for (i = 0; i < NUM_REC_TERR; ++i)
	{
		if(i > NUM_REC_TERR/2)
			terreno[i].x = 100 + i*ANCHO_REC_TERR;
		else
			terreno[i].x = i*ANCHO_REC_TERR;			
		terreno[i].y = 0.0;
		terreno[i].ancho = ANCHO_REC_TERR;
		terreno[i].alto = 150;
		terreno[i].color = VERDE;
		terreno[i].tipo_linea = L_LINE;
		terreno[i].ancho_linea = 1;
		terreno[i].tipo = GL_FILL;
		terreno[i].factor_linea = 1;
	}

}

void CrearGusanos()
{
	int i;
	//________________________________- Aliados
	for(i=0; i < NUM_WORMS; i++)
	{
		allies[i].largo = -40;
		allies[i].alto = 30;
		allies[i].grueso = 10;
		allies[i].isAlive = 1;
		//allies[i].x = 50 + i*ANCHO_MUNDO/(float)(NUM_WORMS+3);
		allies[i].x = 50 + 1.0*rand()/RAND_MAX*(ANCHO_MUNDO/2 - 90);
		allies[i].y = 150;
		allies[i].color = VERDE_AZUL;
		allies[i].tipo_linea = L_LINE;
		allies[i].ancho_linea = 1;
		allies[i].tipo = GL_FILL;
		allies[i].factor_linea = 1;
		allies[i].isUp = 0;
		allies[i].isAtacking = 0;
		allies[i].angle = 45;
	}

	//___________________________________ Enemigos
	for(i=0; i < NUM_WORMS; i++)
	{
		enemies[i].largo = 40;
		enemies[i].alto = 30;
		enemies[i].grueso = 10;
		enemies[i].isAlive = 1;
		//enemies[i].x = ANCHO_MUNDO - 50 - i*ANCHO_MUNDO/(float)(NUM_WORMS + 3);
		enemies[i].x = ANCHO_MUNDO - 1.0*rand()/RAND_MAX*(ANCHO_MUNDO/2 - 90);
		enemies[i].y = 150;
		enemies[i].color = ROJO;
		enemies[i].tipo_linea = L_LINE;
		enemies[i].ancho_linea = 1;
		enemies[i].tipo = GL_FILL;
		enemies[i].factor_linea = 1;
		enemies[i].isUp = 0;
		enemies[i].isAtacking = 0;
		enemies[i].angle = 135;
	}
}

void CrearBala()
{
	bullet.x = currentWorm->x + cos(currentWorm->angle*PI/180.0)*20.0;
	bullet.y = currentWorm->y + currentWorm->alto*0.5 + sin(currentWorm->angle*PI/180.0)*20;
	bullet.r = 10;
	bullet.isActive = 0;
	bullet.color = AZUL;
	bullet.tipo_linea = L_LINE;
	bullet.tipo = GL_FILL;
	bullet.factor_linea = 1;
	bullet.ancho_linea = 1;
}

void CrearBoton()
{
	btDisparar.x = 20;
	btDisparar.y = ALTO_PANTALLA-40;
	btDisparar.ancho = 160;
	btDisparar.alto = 30;
	btDisparar.color = ROJO;
	btDisparar.tipo_linea = L_LINE;
	btDisparar.tipo = GL_FILL;
	btDisparar.ancho_linea = 1;
	btDisparar.factor_linea = 1;
}

void DibujarTerreno(float offX, float offY)
{
	int i;

	for (i = 0; i < NUM_REC_TERR; ++i)
	{
		Rectangulo(terreno + i, offX, offY);
	}

	//Nubes?
	AsignaColor(BLANCO);
	for(i=0; i<5;i++)
	{
		/*glBegin(GL_POLYGON);
		glVertex2f(offX + ANCHO_MUNDO/4 * i + 20, offY + ALTO_PANTALLA - 60);
		glVertex2f(offX + ANCHO_MUNDO/4 * i - 20, offY + ALTO_PANTALLA - 60);
		glVertex2f(offX + ANCHO_MUNDO/4 * i - 20, offY + ALTO_PANTALLA - 80);
		glVertex2f(offX + ANCHO_MUNDO/4 * i - 40, offY + ALTO_PANTALLA - 80);
		glVertex2f(offX + ANCHO_MUNDO/4 * i - 40, offY + ALTO_PANTALLA - 80);
		glVertex2f(offX + ANCHO_MUNDO/4 * i - 60, offY + ALTO_PANTALLA - 100);
		glVertex2f(offX + ANCHO_MUNDO/4 * i + 60, offY + ALTO_PANTALLA - 100);
		glVertex2f(offX + ANCHO_MUNDO/4 * i + 40, offY + ALTO_PANTALLA - 80);
		glVertex2f(offX + ANCHO_MUNDO/4 * i + 20, offY + ALTO_PANTALLA - 80);
		glEnd();*/
		glBegin(GL_POLYGON);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i - 20, offY + ALTO_PANTALLA - 60, 1);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i - 20, offY + ALTO_PANTALLA - 60, 0);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i - 40, offY + ALTO_PANTALLA - 80, 1);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i - 40, offY + ALTO_PANTALLA - 80, 0);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i - 60, offY + ALTO_PANTALLA - 100, 1);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i - 60, offY + ALTO_PANTALLA - 100, 0);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i + 20, offY + ALTO_PANTALLA - 60, 1);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i + 20, offY + ALTO_PANTALLA - 60, 0);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i + 40, offY + ALTO_PANTALLA - 80, 1);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i + 40, offY + ALTO_PANTALLA - 80, 0);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i + 60, offY + ALTO_PANTALLA - 100, 1);
		MedioCirculo(20, offX + ANCHO_MUNDO/4*i + 60, offY + ALTO_PANTALLA - 100, 0);
		glEnd();
		glRectf(offX + ANCHO_MUNDO/4*i - 60, offY + ALTO_PANTALLA - 120, offX + ANCHO_MUNDO/4*i + 60, offY + ALTO_PANTALLA - 80);
	}

}

void AsignaColor(COLOR color)
{
	glColor3f(PaletaColor[color][0],PaletaColor[color][1],PaletaColor[color][2]);
}

void ResetOptions()
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1);
	glPointSize(1);
}

float Signo(float num)
{
	if(num >= 0)
		return 1;
	else
		return -1;
}

void MedioCirculo(float r, float x, float y, int dir)
{
	float th, x1, y1;
	int ini, fin;

	if(dir == 1)
	{
		ini = 270;
		fin = 450;
	}
	else
	{
		ini = 90;
		fin = 270;
	}

	for(th=ini;th<=fin; th+=1)
	{
		x1 = r * cos(th/180.0 * PI) + x;
		y1 = r * sin(th/180.0 * PI) + y;
		glVertex2f(x1,y1);
	}
}

void UpdateBullet()
{
	bullet.x = currentWorm->x + cos(currentWorm->angle*PI/180.0)*20.0;
	bullet.y = currentWorm->y + currentWorm->alto*0.5 + sin(currentWorm->angle*PI/180.0)*20;
}

void DibujarTexto(char *text, float x, float y)
{
	char* c;
	glRasterPos2f(x,y);

	for(c=text; *c!='\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void SetUpAttack()
{
	bullet.x0 = bullet.x;
	bullet.y0 = bullet.y;
	bullet.v0x = (float)(velocidad/100.0)*MAX_VEL*cos(currentWorm->angle*PI/180.0)*10.0;
	bullet.v0y = (float)(velocidad/100.0)*MAX_VEL*sin(currentWorm->angle*PI/180.0)*10.0;
	bullet.t = 0;
	bullet.dir = 1;
}

void UpdateBulletPosition()
{
	if(bullet.y < 150)
	{
		DestroyBullet();
		currentWorm->isAtacking = 0;
		return;
	}

	bullet.x = bullet.x0 + bullet.v0x * bullet.t;
	bullet.y = bullet.y0 + bullet.v0y * bullet.t - (5*GRAVEDAD*bullet.t*bullet.t);
}

void DestroyBullet()
{
	bullet.r = RADIO_EXPLOSION;
	bullet.tipo = GL_LINE;
	bullet.destTime = glutGet(GLUT_ELAPSED_TIME);
	DestroyWorms();
	turno = 4;
}

void DestroyWorms()
{
	int i;
	for(i = 0; i < NUM_WORMS; i++)
	{
		if(((allies[i].x < (bullet.x + bullet.r)) && (allies[i].x > (bullet.x - bullet.r - allies[i].grueso))) || ((allies[i].x + allies[i].largo) > (bullet.x - bullet.r) && (allies[i].x + allies[i].largo) < (bullet.x + bullet.r)))
		{
			allies[i].isAlive = 0;
		}

		if((enemies[i].x < (bullet.x + bullet.r + enemies[i].grueso) && enemies[i].x > (bullet.x - bullet.r)) || ((enemies[i].x + enemies[i].largo) > (bullet.x - bullet.r) && (enemies[i].x + enemies[i].largo) < (bullet.x + bullet.r)))
		{
			enemies[i].isAlive = 0;
		}
	}
}

int GetNextIndex(WORM* gusanos, int maxIndex, int currentIndex)
{
	int i, j;
	for(j=0;j<2;j++)
	{
		for(i=0; i < maxIndex; i++)
		{
			if(j==0&&i<=currentIndex) continue;
			if(gusanos[i].isAlive == 1) return i;
		}
	}
	return -1;
}