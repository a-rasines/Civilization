/*
 * datatype.h
 *	Contenedor de las estructuras de datos presentes en la base de datos
 *  Created on: 12 abr 2022
 *      Author: algtc
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

typedef struct{
	int servidor;
	int usuario;
	int id;
	char* nombre;
	char* edificios;
	int comida;
	int dinero;
	int produccion;
	int posicionX;
	int posicionY;
}Ciudad;
typedef struct{
	int servidor;
	int usuario;
	int id;
	char* tipo;
	int vida;
	int mejorada;
	int posicionX;
	int posicionY;
}Tropa;
typedef struct{
	int jugador;
	int servidor;
	int id;
}Partida;



#endif /* DATATYPE_H_ */
