#ifndef AUXILIAR_H
#define AUXILIAR_H
    
#include <stdbool.h>
#include <stddef.h>
#include "config.h"


typedef struct {
    bool bit[MAXTAM*BYTESIZE];
    size_t tamanho;
} bits;

void imprime_bits(bits mensagem, size_t bitoff); 

#endif
