/*
 * usuario.h
 *
 *  Created on: 10 abr. 2022
 *      Author: eneko
 */

#ifndef USUARIO_H_
#define USUARIO_H_

typedef struct
{
	char* nombre;
	int id;
	int admin;
} Usuario;

int opcionesNormales();
int opcionesAdmin();
Usuario autentificarse();
Usuario registrarse();
int seleccion(char a, char b);
#endif /* USUARIO_H_ */
