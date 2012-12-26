#ifndef MELTDOG_H_INCLUDED
#define MELTDOG_H_INCLUDED
#include <stdint.h>

void meltdog_feistelfunc(uint8_t* d,uint8_t* k,uint8_t* dbuf);

void meltdog_encrypt(uint8_t* dest,uint8_t* src,uint8_t* key,int keylen);
void meltdog_decrypt(uint8_t* dest,uint8_t* src,uint8_t* key,int keylen);

#endif // MELTDOG_H_INCLUDED
