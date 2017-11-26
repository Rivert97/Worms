#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ANCHO_PANTALLA 1200
#define ALTO_PANTALLA 650
#define ANCHO_MUNDO 2580
#define ALTO_MUNDO 650
#define NCOLORES 28
#define ANCHO_REC_TERR 10
#define NUM_REC_TERR (ANCHO_MUNDO-100)/ANCHO_REC_TERR
#define NUM_WORMS 4
#define PI 3.14159265
#define L_LINE 0xFFFF
#define L_DOT 0xAAAA
#define L_DOTDASH 0xC9C9
#define L_DASH 0x6666
#define L_LONGDOTDASH 0xBEBE

//__________________________________________________Paleta de colores
typedef enum{			//Enumeración de colores
	NEGRO,
	AZUL_FUERTE,
	AZUL,
	CIAN,
	AZUL_CLARO,
	AZUL_OPACO,
	VERDE_AZUL,
	VERDE,
	VERDE_FUERTE,
	MARRON,
	ROJO,
	MORADO_FUERTE,
	VIOLETA,
	MORADO,
	MAGENTA,
	ORO,
	ANARANJADO,
	VERDE_CLARO,
	AMARILLO,
	GRIS,
	GRIS_CLARO,
	ROSA_MEXICANO,
	VERDE_PASTEL,
	AZUL_PASTEL,
	CIAN_CLARO,
	ROSA,
	AMARILLO_MOSTAZA,
	BLANCO
}COLOR;
//_______________________________________________ estructuras
typedef struct 
{
	float x;
	float y;
	float ancho;
	float alto;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}RECTANGULO;

typedef struct               //Estructura círculo
{
	float x;
	float y;
	float r;
	int isActive;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}CIRCULO;

typedef struct OPCIONES	//Opciones con las que se puede dibujar cada figura
{
	COLOR color;	//PaletaColor
	int tipo_linea;	//Patrón
	int llenado;		//fill, line, point
	int ancho_linea;
	int factor_linea;
}OPCIONES;

typedef struct WORM
{
	float x;
	float y;
	float largo;
	float grueso;
	float alto;
	int isAlive;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
	int isUp;
	int isAtacking;
	float angle;
}WORM;

//________________________________________________ Variables globales
RECTANGULO terreno[NUM_REC_TERR];
WORM allies[NUM_WORMS];
WORM enemies[NUM_WORMS];
WORM * currentWorm;
CIRCULO bullet;
float Px, Py;

//________________________________________________ Prototipos
//Callbacks
void display();
void Animate();
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
//Creación de figuras
RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op);
//Dibujado de figuras
void Rectangulo(RECTANGULO *r, float offX, float offY);
void ResetOptions();
void DibujarGusanos(WORM * gusanos, int num, float offX, float offY);
void DibujarBala(float offX, float offY);
//Extras
void AsignaColor(COLOR color);
void DibujarTerreno(float offX, float offY);
void CrearTerreno();
void CrearGusanos();
void CrearBala();
float Signo(float num);
void MedioCirculo(float r, float x, float y, int dir);
void UpdateBullet();