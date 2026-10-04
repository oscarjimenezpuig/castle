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

#define NPX CASW //posiciones nulas de la pantalla de los moviles
#define NPY CASH

#define PJXI 0
#define PJYI 5

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
    int x,y; //posicion en la pantalla
    int hjm; //altura donde llegaba el salto
    uc_t px,py; //pantalla en la que esta el movil
    struct {
        uc_t jmp : 1; //bandera que indica que salta
        uc_t dwn : 1; //bandera que indica que baja
        uc_t str : 1; //bandera que indica que esta en la escalera
        uc_t act : 1; //dice si esta o no activo
        uc_t jug : 1; //dice si es jugador
        uc_t vue : 1; //dice si vuela
    };
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

extern uc_t quit;

// Funciones

void graf_ini();
//definicion de graficos

void graf_end();
//liberamos espacio de los graficos

room_t* cst_get(uc_t c,uc_t r);
//da un puntero a la habitacion que se encuentra en c,t

void cst_ini();
//inicia el mapa del castillo

void cst_fix_drw(uc_t c,uc_t r);
//dibuja las paredes de la habitacion (solo cuando se entra en la habitacion)

void cst_nfix_drw(uc_t c,uc_t r);
//dibuja escaleras y decoracion de la habitacion

movil_t mov_new(sprite_t s,palette_t p,int hjm,uc_t vue,uc_t jug);
//se define un movil nuevo

void mov_plc(movil_t* m,int x,int y,uc_t pcx,uc_t pcy);
//se situa un movil en una posicion

void mov_unact(movil_t* m);
//se hace inactivo al movil

void mov_drw(movil_t m);
//se dibuja un movil

void mov_era(movil_t m);
//se borra de la pantalla el movil

int mov_mov(movil_t* m,char* dir);
//se hace un movimiento en la direccion dir u: arriba, d: abajo, l: izquierda, r: derecha
//u,d no funcionaran en caso de salto

void jug_ini();
//definimos el jugador

void jug_act();
//control de movimiento del jugador
