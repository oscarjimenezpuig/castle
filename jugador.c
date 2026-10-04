#include "castle.h"

movil_t jugador;
uc_t quit=0;

void jug_ini() {
    jugador=mov_new(sheroe[0],pheroe,2*SPRD,0,1);
    mov_plc(&jugador,SPRD,6*SPRD,PJXI,PJYI);
}

#include <stdio.h> //dbg

static int in_stair(char key) {
    int ret=0;
    room_t* r=cst_get(jugador.px,jugador.py);
    if(key=='k' && (r->sal & 1)) ret=-1;
    else if(key=='i' && (r->sal & 8)) ret=1;
    printf("%c %i=%i\n",key,r->sal,ret);//dbg
    return ret;
}

void jug_act() {
    const char* KEYS="ijkl";
    key_lis();
    char key[10];
    char* pks=key;
    const char* pkl=KEYS;
    while(*pkl!='\0') {
        if(key_in(*pkl)) *pks++=*pkl;
        pkl++;
    }
    *pks='\0';
    mov_mov(&jugador,key);
    if(key_in('q')) quit=1;
}


