#include "castle.h"

movil_t jugador;
uc_t quit=0;

void jug_ini() {
    mov_pal(&jugador,pheroe);
    jugador.spr=sheroe[0];
    jugador.pdi=PIXDIM;
    jugador.x=SPRD;
    jugador.y=6*SPRD;
    jugador.hjm=4*SPRD;
    jugador.vjy=0;
    jugador.px=PJXI;
    jugador.py=PJYI;
    jugador.jug=1;
}

void jug_act() {
    key_lis();
    char key[10];
    char* pkey=key;
    if(key_in('j')) *pkey++='l';
    else if(key_in('l')) *pkey++='r';
    *pkey='\0';
    mov_mov(&jugador,key);
    if(key_in('z')) mov_jmp(&jugador);
    if(key_in('q')) quit=1;
}


