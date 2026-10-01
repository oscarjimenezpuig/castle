#include "castle.h"

void mov_pal(movil_t* m,palette_t pal) {
    for(int k=0;k<PALDIM;k++) {
        m->pal[k]=pal[k];
    }
}

void mov_drw(movil_t m) {
    spr_drw(m.spr,m.pal,m.x,m.y,m.pdi);
}

void mov_era(movil_t m) {
    spr_era(m.spr,m.x,m.y,m.pdi);
}

static int chk_mov(movil_t m,int pfx,int pfy) {
    //dice si un movil puede moverse a la nueva posicon
    int lxmin=SPRD;
    int lxmax=8*SPRD;
    int lymin=2*SPRD;
    int lymax=7*SPRD;
    room_t* r=cst_get(m.px,m.py);
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
    if(fnd_dir('u',d) && m->vjy==0) vy=-1;
    else if(fnd_dir('d',d) && m->vjy==0) vy=1;
    if(fnd_dir('l',d)) vx=-1;
    else if(fnd_dir('r',d)) vx=1;
    if(m->vjy<0 && m->y<=m->hjm) m->vjy=1;
    vy=(m->vjy!=0)?m->vjy:vy; 
    int fpx=m->x+vx*PIXDIM;
    int fpy=m->y+vy*PIXDIM;
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
    if(m->vjy==0) {
        m->vjy=-1;
        return 1;
    }
    return 0;
}

