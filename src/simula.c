#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auxiliar.h"
#include "tratamento.h"
#include "config.h"

// Transmissão
void aplicacao_transmissora(void);
void camada_de_aplicacao_transmissora(char mensagem[MAXTAM]);
void camada_enlace_dados_transmissora(bits mensagem); 

// Meio
void meio_de_comunicacao(bits mensagem);

// Recepção
void camada_enlace_dados_receptora(bits mensagem); 
void camada_de_aplicacao_receptora(bits mensagem);
void aplicacao_receptora(char mensagem[MAXTAM]);

// -------------------------------------------------------------------

// Inicia
int main() {
    aplicacao_transmissora();
    return EXIT_SUCCESS;
}

/* ### FLUXO DOS DADOS - INICIO ### */

void aplicacao_transmissora(void) {
    char mensagem[MAXTAM];

    printf("Digite uma mensagem:\n");
    fgets(mensagem, MAXTAM, stdin);
    mensagem[strlen(mensagem) - 1] = '\0';  // Tira o new line
    putchar('\n');
    camada_de_aplicacao_transmissora(mensagem);
    return;
}

void camada_de_aplicacao_transmissora(char mensagem_char[MAXTAM]) {
    bits mensagem_bits = {0};

    // Char para bits
    for (size_t i = 0; i < strlen(mensagem_char); i++)   // Para todo byte da mensagem
        for (size_t j = 0; j < BYTESIZE; j++)            // Para todo bit do byte
            mensagem_bits.bit[mensagem_bits.tamanho++]
                = mensagem_char[i] & (MAXBITVALUE >> j);  

    if (MOSTRABITS) {
        printf("Mensagem enviada em binario: ");
        imprime_bits(mensagem_bits, 0);
    }
    camada_enlace_dados_transmissora(mensagem_bits);
    return;
}

void camada_enlace_dados_transmissora(bits mensagem) {
    // Adiciona sinalização
    mensagem = camada_enlace_dados_transmissora_controle_de_erro(mensagem);
    meio_de_comunicacao(mensagem); 
    return;
}

void meio_de_comunicacao(bits mensagem) {
    bits fluxo_bruto_de_bits_ponto_A = mensagem;
    bits fluxo_bruto_de_bits_ponto_B = {0};
    size_t len = fluxo_bruto_de_bits_ponto_A.tamanho;

    // Escolhe se pode ter erro nos bits de check
    if (!ERRO_NO_CHECK) {
        switch (TIPO_CONTROLE) {
            case 0: case 1:
                len--;
                break;
            case 2:
                len -= 32;
                break;
        }
    }

    srand((unsigned int) time(NULL));

    // Cada bit tem chance de mudar igual a PORCENTAGEM_ERROS
    while (fluxo_bruto_de_bits_ponto_B.tamanho != fluxo_bruto_de_bits_ponto_A.tamanho) {
        if (((rand() % 100)) >= PORCENTAGEM_ERROS || fluxo_bruto_de_bits_ponto_B.tamanho >= len) {            
            fluxo_bruto_de_bits_ponto_B.bit[fluxo_bruto_de_bits_ponto_B.tamanho] = 
                fluxo_bruto_de_bits_ponto_A.bit[fluxo_bruto_de_bits_ponto_B.tamanho];
        }
        else { // Inverte
            fluxo_bruto_de_bits_ponto_B.bit[fluxo_bruto_de_bits_ponto_B.tamanho] =
                !fluxo_bruto_de_bits_ponto_A.bit[fluxo_bruto_de_bits_ponto_B.tamanho];
        }
        fluxo_bruto_de_bits_ponto_B.tamanho++;
    }
    camada_enlace_dados_receptora(fluxo_bruto_de_bits_ponto_B);
    return;
}

void camada_enlace_dados_receptora(bits mensagem) {
    // Checa por erros e remove sinalização
    mensagem = camada_enlace_dados_receptora_controle_de_erro(mensagem);
    camada_de_aplicacao_receptora(mensagem);
    return;
}

void camada_de_aplicacao_receptora(bits mensagem_bits) {
    char mensagem_char[MAXTAM] = {0};

    if (MOSTRABITS) {
        printf("Mensagem recebida em binario: ");
        imprime_bits(mensagem_bits, 0);
    }

    // Bits para char
    for (size_t i = 0; i < mensagem_bits.tamanho / BYTESIZE; i++) 
        for (size_t j = 0; j < BYTESIZE; j++) 
            if (mensagem_bits.bit[i*BYTESIZE + j])
                mensagem_char[i] += (char) (MAXBITVALUE >> j);
    aplicacao_receptora(mensagem_char);
}

void aplicacao_receptora(char mensagem[MAXTAM]) {
    printf("\nA mensagem recebida foi: %s\n", mensagem);
}

/* ### FLUXO DOS DADOS - FIM ### */
