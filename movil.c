#include "castle.h"

void mov_drw(movil_t m) {
    spr_drw(m.spr,m.pal,m.x,m.y,m.pdi);
}

static int chk_mov(movil_t m,int pfx,int pfy) {
    //dice si un movil puede moverse a la nueva posicon
    int lxmin=0;
    int lxmax=PANW-SPRD;
    int lymin=2*SPRD;
    int lymax=7*SPRD;
    room_t* r=cst_get(m.px,m.py);
    if(r->sal & 2) lymax=PANW-2*SPRD;
    if(r->sal & 4) lymin=SPRD;
    return (pfx>=lxmin && pfx<lxmax && pfy>=lymin && pfy<lymax);
}

static int fnd_dir(char dir,char* d) {
    char* pd=d;
    while(*pd!='\0') {
        if(*pd==dir) return 1;
        pd++;
    }
    return 0;
}

int mov_mov(movil_t* m,char* d) {
    int mov=0;
    int vx=0;
    int vy=0;
    if(fnd_dir('u',d) && m->vy==0) vy=-1;
    else if(fnd_dir('d',d) && m->vy==0) vy=1;
    if(fnd_dir('l',d)) vx=-1;
    else if(fnd_dir('r',d)) vx=1;
    int fpx=m->x+vx*PIXDIM;
    int fpy=m->y+vy*PIXDIM;
    if(m->vy<0 && m->y<=m->hjm) m->vy=1;
    vy=(m->vy!=0)?m->vy:vy; 
    if(vx!=0 && chk_mov(*m,fpx,m->y)) {
        m->x=fpx;
        mov=1;
    }
    if(vy!=0 && chk_mov(*m,m->x,fpy)) {
        m->y=fpy;
        mov=1;
    }
    return mov;
}

int mov_jmp(movil_t* m) {
    if(m->vy==0) {
        m->vy=-1;
        return 1;
    }
    return 0;
}

