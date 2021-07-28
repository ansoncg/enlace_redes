#include <stdio.h>
#include <stdlib.h>
#include "tratamento.h"

/* ### CONTROLES DE ERRO ### */

bits camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par(bits mensagem) {
    bool bit_paridade = false;  

    for (size_t i = 0; i < mensagem.tamanho; i++) {
        if (mensagem.bit[i])
            bit_paridade = !bit_paridade;
    }
    mensagem.bit[mensagem.tamanho++] = bit_paridade;
    printf("Camada transmissora -> Bit de paridade calculado %d\n", bit_paridade);
    return mensagem;
}

bits camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_impar(bits mensagem) {
    bool bit_paridade = true;  

    for (size_t i = 0; i < mensagem.tamanho; i++) {
        if (mensagem.bit[i])
            bit_paridade = !bit_paridade;
    }
    mensagem.bit[mensagem.tamanho++] = bit_paridade;
    printf("Camada transmissora -> Bit de paridade calculado %d\n", bit_paridade);
    return mensagem;
}

/* CRC-32 (IEEE 802) */
bits camada_enlace_dados_transmissora_controle_de_erro_CRC(bits mensagem) {
    bits crc = mensagem;
    size_t len = mensagem.tamanho;

    for (size_t i = 0; i < len; i++) {
        if (crc.bit[i]) {
            for (size_t j = 0; j < 32; j++) 
                crc.bit[i + j] = ((POL & (1L << j)) != 0) != crc.bit[i + j];
        }
    }
    for (size_t i = len; i < len + 32; i++)
        mensagem.bit[mensagem.tamanho++] = crc.bit[i];
    printf("CRC: ");
    imprime_bits(mensagem, len);
    return mensagem;
}

bits camada_enlace_dados_transmissora_controle_de_erro(bits mensagem) {
    switch (TIPO_CONTROLE) {
        case 0: // Paridade par
            mensagem = camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par(mensagem);
            break;
        case 1: // Paridade impar 
            mensagem = camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_impar(mensagem);
            break;
        case 2: // CRC
            mensagem = camada_enlace_dados_transmissora_controle_de_erro_CRC(mensagem);
            break;
    }
    return mensagem;
}

// -----------

bits camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par(bits mensagem) {
    bool bit_paridade = false;  

    for (size_t i = 0; i < mensagem.tamanho - 1; i++) {
        if (mensagem.bit[i])
            bit_paridade = !bit_paridade;
    }
    printf("Camada receptora    -> Bit de paridade calculado %d / recebido %d\n", bit_paridade, mensagem.bit[mensagem.tamanho - 1]);
    if (mensagem.bit[mensagem.tamanho - 1] != bit_paridade)
        printf("Erro na mensagem!   -> Tipo de controle: Paridade par\n");
    mensagem.tamanho--;
    return mensagem;
}

bits camada_enlace_dados_receptora_controle_de_erro_bit_paridade_impar(bits mensagem) {
    bool bit_paridade = true;  

    for (size_t i = 0; i < mensagem.tamanho - 1; i++) {
        if (mensagem.bit[i])
            bit_paridade = !bit_paridade;
    }
    printf("Camada receptora    -> Bit de paridade calculado %d / recebido %d\n", bit_paridade, mensagem.bit[mensagem.tamanho - 1]);
    if (mensagem.bit[mensagem.tamanho - 1] != bit_paridade)
        printf("Erro na mensagem!   -> Tipo de controle: Paridade impar\n");
    mensagem.tamanho--;
    return mensagem;
}

/* CRC-32 (IEEE 802) */
bits camada_enlace_dados_receptora_controle_de_erro_CRC(bits mensagem) {
    bits crc = {0};
    size_t len = mensagem.tamanho - 32;
    for (size_t i = 0; i < len; i++)
        crc.bit[i] = mensagem.bit[i];
    crc.tamanho = mensagem.tamanho;

    for (size_t i = 0; i < len; i++) {
        if (crc.bit[i]) {
            for (size_t j = 0; j < 32; j++) 
                crc.bit[i + j] = ((POL & (1L << j)) != 0) != crc.bit[i + j];
        }
    }
    for (size_t i = len; i < len + 32; i++) {
        if (mensagem.bit[i] != crc.bit[i]) {
            printf("Erro\n");
            break;
        }
    }
    printf("CRC: ");
    imprime_bits(crc, len);
    mensagem.tamanho = len;
    return mensagem;
}

bits camada_enlace_dados_receptora_controle_de_erro(bits mensagem) {
    switch (TIPO_CONTROLE) {
        case 0: // Paridade par
            mensagem = camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par(mensagem);
            break;
        case 1: // Paridade impar
            mensagem = camada_enlace_dados_receptora_controle_de_erro_bit_paridade_impar(mensagem);
            break;
        case 2: // CRC
            mensagem = camada_enlace_dados_receptora_controle_de_erro_CRC(mensagem);
            break;
    }
    return mensagem;
}
