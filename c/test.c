#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "meltdog.h"

typedef const char* string;
typedef struct { string data,key; } Vec;

int hexdigit(char i){
    if('0'<=i && i<='9')return i-'0';
    if('a'<=i && i<='f')return i+10-'a';
    if('A'<=i && i<='F')return i+10-'A';
    return 0;
}

void fromHex(uint8_t* dest,int len,const char* src){
    while(len--){
        *(dest++) = (hexdigit(src[0])<<4) | hexdigit(src[1]);
        src+=2;
    }
}
void toHex(uint8_t* data,int l){
    while(l--)
        printf("%02X",*(data++));
}

Vec vectors[5];
void init(){
    vectors[0]=(Vec){"00000000000000000000000000000000","30000000000000001000000000000001"};
    vectors[1]=(Vec){"FF00FFFF00FF0F0F000FFFFFF00FFFF0","30000000000000001000000000000001"};
    vectors[2]=(Vec){"30000000000000001000000000000001","0123456789ABCDEF0123456789ABCDEF"};
    vectors[3]=(Vec){"30000000000000001000000000000001","0123456789ABCDEFF0E1D2C3B4A59687"};
    vectors[4]=(Vec){"7CA110454A1A6E571F08260D1AC2465E","49E95D6D4CA229BF6B056E18759F5CCA"};
}

uint8_t data[16];
uint8_t key[16];
uint8_t crypt[16];
uint8_t decrypt[16];

int main()
{
    init();
    int i;
    for(i=0;i<5;++i){
        fromHex(data,16,vectors[i].data);
        fromHex(key,16,vectors[i].key);
        meltdog_encrypt(crypt,data,key,16);
        meltdog_decrypt(decrypt,crypt,key,16);

        //printf("%s %s ",vectors[i].data,vectors[i].key);
        //toHex(crypt,16);
        //printf("\n");
        toHex(data,16);
        printf(" ");
        toHex(decrypt,16);
        printf("\n");
        // printf("%s %s \n",vectors[i].data,vectors[i].key);
    }
    return 0;
}
