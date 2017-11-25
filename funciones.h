#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define ANCHO 1200
#define ALTO 650
#define NCOLORES 28
#define NUM_REC_TERR 200
#define ANCHO_REC_TERR 10
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

typedef struct OPCIONES	//Opciones con las que se puede dibujar cada figura
{
	COLOR color;	//PaletaColor
	int tipo_linea;	//Patrón
	int llenado;		//fill, line, point
	int ancho_linea;
	int factor_linea;
}OPCIONES;

//________________________________________________ Variables globales
RECTANGULO terreno[NUM_REC_TERR];

//________________________________________________ Prototipos
//Callbacks
void display();
//Creación de figuras
RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op);
//Dibujado de figuras
void Rectangulo(RECTANGULO *r);
void ResetOptions();
//Extras
void AsignaColor(COLOR color);
void DibujarTerreno(float x, float y);
void CrearTerreno();