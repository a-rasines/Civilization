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
sqlite3* getDB();
int regenerarBaseDatos();
Usuario getUsuario(char* nombre, char* contrasena);
Usuario getUsuarioAdm(char* nombre);
Usuario addUsuario(char* nombre, char* contrasena);
int existsNombre(char* nombre);
int banUsuario();
int unbanUsuario(int id);
int modificarUsuario();
int limpiarServidor(int id);
int borrarUsuario(int id);
Usuario addAdmin(char* nombre, char* contrasena);
int borrarCiudad(int id);
int borrarTropa(int id);
int reiniciarUsuario(int id);
int eliminarUsuarioDeServidor(int idUsuario, int idServidor);


#endif /* DATABASE_H_ */
