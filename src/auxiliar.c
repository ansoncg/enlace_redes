#include <stdio.h>
#include "auxiliar.h"

void imprime_bits(bits mensagem, size_t bitoff) {
    for (size_t i = bitoff; i < mensagem.tamanho; i++) {
        printf("%d", mensagem.bit[i]);
        if (!((i + 1) % BYTESIZE))
            putchar(' ');
    }
    putchar('\n');
    return;
}
