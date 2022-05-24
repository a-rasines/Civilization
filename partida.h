/*
 * partida.h
 *
 *  Created on: 09 may. 2022
 *      Author: daniel
 */

#ifndef PARTIDA_H_
#define PARTIDA_H_

typedef struct
{
	char* jugador;
	int server;
	//enum politica;
    int investigaciones;
    char* alianzas;
} Partida;

#endif /* PARTIDA_H_ */
