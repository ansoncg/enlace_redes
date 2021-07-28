#ifndef CONFIG_H
#define CONFIG_H

// !!! RODAR MAKE CLEAN DEPOIS DE MUDAR !!!

// Mostra a mensagem em bits durante o processo
#define MOSTRABITS true

// Chance de ocorrer um erro em %
#define PORCENTAGEM_ERROS 10

// Define se é possivel ter erro nos bits de check
#define ERRO_NO_CHECK false

/* Tipos de checks: 
 0 -> Paridade par
 1 -> Paridade impar
 2 -> CRC */
#define TIPO_CONTROLE 0

// Polinomio
#define POL 0x04C11DB7

// Tamaho máximo da mensagem + bits de checagem
#define MAXTAM 2000

// Tamanho do byte
#define BYTESIZE 8

// Valor do maior bit do byte
#define MAXBITVALUE 128

#endif

/* Referencias */
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check#CRC-32_algorithm
