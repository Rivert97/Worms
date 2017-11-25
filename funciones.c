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


//__________________________________________________________ Creación de figuras
RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op)
{
	RECTANGULO *aux;

	aux = (RECTANGULO*)malloc(sizeof(RECTANGULO));
	aux->x = x;
	aux->y = y;
	aux->ancho = 50;
	aux->alto = 20;
	aux->color = op.color;
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

	return aux;
}

//_______________________________________________________________ Dibujado de figuras
void Rectangulo(RECTANGULO *r, float offX, float offY)
{
	if(r->x + r->ancho < abs(offX) || r->x > abs(offX) + ANCHO_PANTALLA) return;
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
		if(gusanos[i].x + gusanos[i].grueso < abs(offX) || gusanos[i].x > abs(offX) + ANCHO_PANTALLA) continue;
		AsignaColor(gusanos[i].color);
		glRectf(offX + gusanos[i].x, offY + gusanos[i].y, offX + gusanos[i].x + gusanos[i].largo, offY + gusanos[i].y + gusanos[i].grueso);//Tail
		glRectf(offX + gusanos[i].x, offY + gusanos[i].y, offX + gusanos[i].x + gusanos[i].grueso, offY + gusanos[i].y + gusanos[i].alto);//Head
	}
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
			terreno[i].x = 80 + i*ANCHO_REC_TERR;
		else
			terreno[i].x = i*ANCHO_REC_TERR;			
		terreno[i].y = 0.0;
		terreno[i].ancho = ANCHO_REC_TERR;
		terreno[i].alto = 250;
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
		allies[i].x = 50 + i*ANCHO_MUNDO/5.0;
		allies[i].y = 250;
		allies[i].color = VERDE_AZUL;
		allies[i].tipo_linea = L_LINE;
		allies[i].ancho_linea = 1;
		allies[i].tipo = GL_FILL;
		allies[i].factor_linea = 1;
	}

	//___________________________________ Enemigos
	for(i=0; i < NUM_WORMS; i++)
	{
		enemies[i].largo = 40;
		enemies[i].alto = 30;
		enemies[i].grueso = 10;
		enemies[i].isAlive = 1;
		enemies[i].x = ANCHO_MUNDO - 50 - i*ANCHO_MUNDO/5.0;
		enemies[i].y = 250;
		enemies[i].color = ROJO;
		enemies[i].tipo_linea = L_LINE;
		enemies[i].ancho_linea = 1;
		enemies[i].tipo = GL_FILL;
		enemies[i].factor_linea = 1;
	}
}


void DibujarTerreno(float offX, float offY)
{
	int i;

	for (i = 0; i < NUM_REC_TERR; ++i)
	{
		Rectangulo(terreno + i, offX, offY);
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