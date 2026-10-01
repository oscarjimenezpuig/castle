#include "castle.h"

castle_t castle;

room_t* cst_get(uc_t c,uc_t r) {
    if(c<CASW && r<CASH) return castle+(c+CASW*r);
    return NULL;
}

static void sal_cmp(uc_t c,uc_t r,room_t* h) {
    //completa las salidas
    room_t* rn;
    if(r>0) {
        rn=cst_get(c,r-1);
        if(rn->sal & 1) h->sal|=8;
    }
    if(c>0) {
        rn=cst_get(c-1,r);
        if(rn->sal & 2) h->sal|=4;
    }
}

static void hab_def() {
    //define las habitaciones del castillo
    const uc_t LAB[]={  1,3,0,1,2,2,1,2,1,1,
                        2,3,2,2,2,2,3,1,3,1,
                        2,3,3,2,2,1,1,0,1,1,
                        2,0,1,2,1,1,3,3,0,1,
                        3,2,2,2,2,0,1,3,1,0,
                        2,2,3,1,1,1,0,1,2,0,
                        3,1,1,0,3,2,2,2,3,1,
                        1,3,2,3,0,3,2,2,1,1,
                        1,2,1,1,1,1,2,1,1,1,
                        0,2,0,2,0,2,2,0,0,0
    }; //salidas iniciales
    const uc_t ESP[]={3,27,30,33,56,59,63,86,91,99}; //habitaciones especiales
    const uc_t ESPS=10; //numero de habitaciones especiales;
    room_t* pc=castle;
    const uc_t* pl=LAB;
    const uc_t* pe=ESP;
    for(uc_t r=0;r<CASH;r++) {
        for(uc_t c=0;c<CASH;c++) {
            pc->sal=*pl;
            sal_cmp(c,r,pc);
            uc_t nor=pc-castle;
            pc->esp=0;
            while(pe!=ESP+ESPS && *pe<=nor) {
                if(*pe==nor) pc->esp=1;
                pe++;
            }
            pc++;
            pl++;
        }
    }
}

void cst_ini() {
    hab_def();
}

void cst_fix_drw(uc_t cl,uc_t rw) {
    const uc_t SOTANO=5;
    const uc_t SUBSUELO=8;
    room_t* r=cst_get(cl,rw);
    uc_t deep=rw;
    uc_t sal=r->sal;
    palette_t* pal=(deep>=SUBSUELO)?ppared+2:(deep>=SOTANO)?ppared+1:ppared;
    //techo Y suelo
    int col=0;
    while(col<PANW) {
       spr_drw(spared[3],*pal,col,SPRD,PIXDIM);
       uc_t spar=1;
       if(col==0) spar=0;
       spr_drw(spared[spar],*pal,col,7*SPRD,PIXDIM);
       col+=SPRD;
    }
    //paredes
    int fil=2*SPRD;
    while(fil<PANH-3*SPRD) {
        if((sal & 4)==0) spr_drw(spared[2],*pal,0,fil,PIXDIM);
        if((sal & 2)==0) spr_drw(spared[2],*pal,PANW-SPRD,fil,PIXDIM);
        fil+=SPRD;
    }
}

void cst_nfix_drw(uc_t c,uc_t r) {
    uc_t sal=cst_get(c,r)->sal;
    //escalera superior
    if(sal & 8) {
        spr_era(spared[3],4*SPRD,SPRD,PIXDIM);
        for(int fil=SPRD;fil<=6*SPRD;fil+=SPRD) spr_drw(sescalera,pescalera,4*SPRD,fil,PIXDIM);
    }
    //escalera inferior
    if(sal & 1) {
        spr_era(spared[1],4*SPRD,7*SPRD,PIXDIM);
        for(int fil=6*SPRD;fil<=7*SPRD;fil+=SPRD) spr_drw(sescalera,pescalera,4*SPRD,fil,PIXDIM);
    }
}



                        
    
