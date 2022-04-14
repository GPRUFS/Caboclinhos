//-------------------------------------------------------------------------
/*
 * Arquivo: Ball.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Ball
 * Linguagem: C++
 *
 * (c) Copyright GPRUFS 2015
 * Endereço:
 *    UFS
 *
 * Autor: GPRUFS
 * E-Mail:
 *
 *
 * Descrição: Esse arquivo possui a definição de algumas funções
 *            responsáveis pelo envio de comandos, a partir do rádio
 *            conectado na porta serial, para os robôs.
 *
*/
//-----------------------------------------------------------------------

#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_


#include <stdio.h>
#include <string>
#include <windows.h>
#include <assert.h>
#include <commctrl.h>


int inicia_comunicacao_serial();
void encerra_comunicacao_serial();
void envia_comandos_robo(unsigned char *);
int RS232_OpenComport(int, int, const char *);
int RS232_SendByte(int, unsigned char);
int RS232_SendBuf(int, unsigned char *, int);
void RS232_CloseComport(int);



#endif /* SERIALCOMM_H_ */
