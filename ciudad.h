/*
 * ciudad.h
 *
 *  Created on: 09 may. 2022
 *      Author: daniel
 */

#include "usuario.h"
#ifndef CIUDAD_H_
#define CIUDAD_H_

typedef struct
{
	int idPartida;
    int idJugador;
	enum tipo;
    char* nombre; 
    int edificios;
    int comida;
    int dinero;
    int produccion;
    int posicionX;
    int posicionY;
} Ciudad;

#endif /* CIUDAD_H_ */
