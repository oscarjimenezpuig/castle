#include "castle.h"

movil_t mov_new(sprite_t s,palette_t p,int hjm,uc_t vue,uc_t jug) {
    movil_t m;
    m.spr=s;
    for(int k=0;k<PALDIM;k++) m.pal[k]=p[k];
    m.x=m.y=-1;
    m.px=NPX;
    m.py=NPY;
    m.jmp=m.dwn=m.str=m.act=0;
    m.jug=jug;
    m.vue=(m.jug==0)?vue:0;
    m.hjm=(m.vue)?0:hjm;
    return m;
}

#define LIX SPRD
#define LSX (7*SPRD)
#define LIY (2*SPRD)
#define LSY (6*SPRD)

#define INGP(X,Y) ((X)>=LIX && (X)<=LSX && (Y)>=LIY && (Y)<=LSY)

void mov_plc(movil_t* m,int x,int y,uc_t px,uc_t py) {
    if(px<CASW && py<CASH && INGP(x,y)) {
        m->px=px;
        m->py=py;
        m->x=x;
        m->y=y;
        m->act=1;
    }
}

void mov_unact(movil_t* m) {
    m->px=NPX;
    m->py=NPY;
    m->x=m->y=-1;
    m->act=0;
}

void mov_drw(movil_t m) {
    spr_drw(m.spr,m.pal,m.x,m.y,PIXDIM);
}

void mov_era(movil_t m) {
    spr_era(m.spr,m.x,m.y,PIXDIM);
}

static int mov_hor(movil_t* m,char d) {
    int fx=m->x;
    if(d=='l') fx+=PIXDIM;
    else fx-=PIXDIM;
    if(INGP(fx,m->y)) {
        m->x=fx;
        return 1;
    }
    return 0;
}

static int mov_ver(movil_t* m,char d) {
    int fy=m->y;
    if(m->vue || m->str) {
        if(d=='i') fy-=PIXDIM;
        else fy+=PIXDIM;
    } else {
        if(m->jmp) {
            fy-=PIXDIM;
            if(fy>m->hjm) {
                fy=m->y;
                m->jmp=0;
                m->dwn=1;
            }
        } else if(m->dwn) {
            fy+=m->y;
        } else {
            m->jmp=1;
        }
    }
    if(INGP(m->x,fy)) {
        m->y=fy;
        return 1;
    } else {
        m->dwn=0;
        return 0;
    }
}
    
int mov_mov(movil_t* m,char* d) {
    char* p=d;
    int ret=0;
    while(*p!='\0') {
        if(*p=='i' || *p=='k') ret|=mov_ver(m,*p);
        else if(*p=='j' || *p=='l') ret|=mov_hor(m,*p);
        p++;
    }
    return ret;
}
