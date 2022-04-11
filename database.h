/*
 * database.h
 *
 *  Created on: 10 abr 2022
 *      Author: algtc
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include "usuario.h"

void setup();
void end();
int regenerarBaseDatos();
Usuario getUsuario(char* nombre, char* contrasena);
Usuario addUsuario(char* nombre, char* contrasena);
int existsNombre(char* nombre);
int banUsuario(int id);
int unbanUsuario(int id);
int modificarUsuario(Usuario prev, Usuario post);
int limpiarServidor(int id);
int borrarUsuario(int id);
Usuario addAdmin(char* nombre, char* contrasena);


#endif /* DATABASE_H_ */
