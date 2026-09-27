// CASTLE: Juego que aprovecha la libreria sprites

// Includes

#include "sprite.h"

// Constantes

#define PIXDIM 8 //tamaño standard de los pixels

#define PANW (3*3*8*PIXDIM) //aancho de la pantalla
#define PANH (PANW+2) //alto de la pantalla

#define CASW 10
#define CASH 10
#define CASDIM (CASW*CASH)

// Tipos

typedef unsigned char uc_t;

typedef struct {
    uc_t sal : 4; //salidas
    uc_t esp : 1; //habitacion especial
} room_t;

typedef room_t castle_t[CASDIM];

// variables

extern sprite_t spared[4];
extern sprite_t sescalera;
extern sprite_t sespada[2];
extern sprite_t sheroe[3];

extern palette_t ppared;
extern palette_t pescalera;
extern palette_t pespada;
extern palette_t pheroe;

extern castle_t castle;

// Funciones

void graf_ini();
//definicion de graficos

void graf_end();
//liberamos espacio de los graficos

room_t* cst_get(uc_t c,uc_t r);
//da un puntero a la habitacion que se encuentra en c,t

void cst_ini();
//inicia el mapa del castillo

