#include "castle.h"

static void castle_init() {
    scr_ini(PANW,PANH);
    graf_ini();
    cst_ini();
    jug_ini();
};

static void castle_end() {
    scr_end();
    graf_end();
}

#include <stdio.h>

void prueba_sprites() { //dbg
    spr_drw(sescalera,pescalera,200,200,PIXDIM);
    spr_drw(sespada[0],pespada,300,200,PIXDIM);
    spr_drw(sheroe[2],pheroe,400,200,PIXDIM);
    scr_fls();
}

void prueba_mapa() {
    for(int r=0;r<CASH;r++) {
        for(int c=0;c<CASW;c++) {
            room_t* h=cst_get(c,r);
            if(h->esp) printf("\033[7m");
            printf("%02i\033[0m ",h->sal);
        }
        printf("\n");
    }
}

int main() {
    castle_init();
    cst_fix_drw(jugador.px,jugador.py);
    while(!quit) {
        cst_nfix_drw(jugador.px,jugador.py);
        mov_drw(jugador);
        scr_fls();
        pause(0.01);
        mov_era(jugador);
        jug_act();
    }
    castle_end();
    return 0;
}

