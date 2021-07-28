#ifndef TRATAMENTO_H
#define TRATAMENTO_H

#include "auxiliar.h"
#include "config.h"

bits camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par(bits mensagem); 
bits camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_impar(bits mensagem);
bits camada_enlace_dados_transmissora_controle_de_erro_CRC(bits mensagem);
bits camada_enlace_dados_transmissora_controle_de_erro(bits mensagem); 

bits camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par(bits mensagem);
bits camada_enlace_dados_receptora_controle_de_erro_bit_paridade_impar(bits mensagem);
bits camada_enlace_dados_receptora_controle_de_erro_CRC(bits mensagem);
bits camada_enlace_dados_receptora_controle_de_erro(bits mensagem); 

#endif
