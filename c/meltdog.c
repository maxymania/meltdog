#include "meltdog.h"

const int i8[8] = {2,6,5,4,7,1,0,3};
const int i4[4] = {1,3,0,2};
const uint8_t bvec[8] = {84, 87, 81, 93, 186, 138, 234, 42};

void meltdog_feistelfunc(uint8_t* d,uint8_t* k,uint8_t* dbuf){
    uint8_t kbuf[4];
    int i,j,d2k,k2k,d2d,k2d;

    d2k = (int)(d[0]^d[1]^d[2]^d[3]^d[4]^d[5]^d[6]^d[7]);
    d2k = (d2k^(d2k>>4));
    d2k = (d2k^(d2k>>2))&3;

    k2k = (int)(k[0]^k[1]^k[2]^k[3]);
    k2k = (k2k^(k2k>>4));
    k2k = (k2k^(k2k>>2))&3;

    d2d = (int)(d[0]^d[1]^d[2]^d[3]^d[4]^d[5]^d[6]^d[7]);
    d2d = (d2d^(d2d>>3)^(d2d>>6))&7;

    k2d = (int)(k[0]^k[1]^k[2]^k[3]);
    k2d = (k2d^(k2d>>3)^(k2d>>6))&7;
    for(i=0 ; i<4 ; i++){
        j = i4[i^d2k]^k2k;
        kbuf[i] = k[j];
        j = i4[j^k2k]^d2k;
        kbuf[i] ^= bvec[j];
    }
    for(i=0 ; i<8 ; i++){
        j = i8[i^k2d]^d2d;
        dbuf[i] = d[j];
        j = i8[j^k2d]^d2d;
        dbuf[i] ^= bvec[j];
        j = i8[j];
        dbuf[i] ^= kbuf[j&3];
    }
}
#define copy(d,s) {d[0]=s[0];d[1]=s[1];d[2]=s[2];d[3]=s[3];d[4]=s[4];d[5]=s[5];d[6]=s[6];d[7]=s[7];}
#define copy2(d,s) {d[8]=s[8];d[9]=s[9];d[10]=s[10];d[11]=s[11];d[12]=s[12];d[13]=s[13];d[14]=s[14];d[15]=s[15];}
void meltdog_encrypt(uint8_t* dest,uint8_t* src,uint8_t* key,int keylen){
    int i,j,n;
    uint8_t L[16],T[8],H[8];
    uint8_t* R=L+8;

    copy(L,src);
    copy2(L,src);

    n = keylen/4;// number of 32 bit parts of the key
    for(i=0;i<n;i++){
        copy(T,L);
        copy(L,R);
        meltdog_feistelfunc(R,key+(i*4),H);
        for(j=0;j<8;j++) T[j]^=H[j];
        copy(R,T);
    }
    copy(dest,L);
    copy2(dest,L);
}
void meltdog_decrypt(uint8_t* dest,uint8_t* src,uint8_t* key,int keylen){
    int i,j;
    uint8_t L[16],T[8],H[8];
    uint8_t* R=L+8;

    copy(L,src);
    copy2(L,src);

    i = keylen/4;// number of 32 bit parts of the key
    while(i){
        i--;
        copy(T,R);
        copy(R,L);
        meltdog_feistelfunc(R,key+(i*4),H);
        for(j=0;j<8;j++) T[j]^=H[j];
        copy(L,T);
    }
    copy(dest,L);
    copy2(dest,L);
}

