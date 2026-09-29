// CASTLE: Juego que aprovecha la libreria sprites

// Includes

#include "sprite.h"

// Constantes

#define PIXDIM 8 //tamaño standard de los pixels

#define SPRD (8*PIXDIM) //dimension real de un sprite

#define PANW (3*3*SPRD) //aancho de la pantalla
#define PANH (PANW+2) //alto de la pantalla

#define CASW 10
#define CASH 10
#define CASDIM (CASW*CASH)

#define SPRW 

// Tipos

typedef unsigned char uc_t;

typedef struct {
    uc_t sal : 4; //salidas
    uc_t esp : 1; //habitacion especial
} room_t;

typedef room_t castle_t[CASDIM];

typedef struct {
    sprite_t spr; //sprite actual del movil
    palette_t pal; //paleta del sprite
    uc_t pdi; //dimension del pixel
    int x,y; //posicion en la pantalla
    int hjm; //altura donde llegaba el salto
    int vy; //velocidad de subida (solo en caso de salto)
    int px,py; //pantalla en la que esta el movil
} movil_t;

// variables

extern sprite_t spared[4];
extern sprite_t sescalera;
extern sprite_t sespada[2];
extern sprite_t sheroe[3];

extern palette_t ppared[3];
extern palette_t pescalera;
extern palette_t pespada;
extern palette_t pheroe;

extern castle_t castle;

extern movil_t jugador;

// Funciones

void graf_ini();
//definicion de graficos

void graf_end();
//liberamos espacio de los graficos

room_t* cst_get(uc_t c,uc_t r);
//da un puntero a la habitacion que se encuentra en c,t

void cst_ini();
//inicia el mapa del castillo

void cst_drw(uc_t c,uc_t r);
//dibuja la habitacion con las coordenadas dadas

void mov_drw(movil_t m);
//se dibuja un movil

int mov_mov(movil_t* m,char* dir);
//se hace un movimiento en la direccion dir u: arriba, d: abajo, l: izquierda, r: derecha
//u,d no funcionaran en caso de salto

int mov_jmp(movil_t* m);
//conectamos el salto
