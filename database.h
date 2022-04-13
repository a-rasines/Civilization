/*
 * database.h
 *
 *  Created on: 10 abr 2022
 *      Author: algtc
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include "usuario.h"
#include "sqlite3.h"

void setup();
void end();
int update(char* seq);
sqlite3* getDB();
int regenerarBaseDatos();
Usuario getUsuario(char* nombre, char* contrasena);
Usuario getUsuarioAdm(char* nombre);
Usuario addUsuario(char* nombre, char* contrasena);
int isBaneado(int id);
int existsNombre(char* nombre);
void printStats(int id);
int banAction(int id, int status);
int modificarUsuarioAdm();
int modificarUsuario(int id, char* nuevoNombre);
int limpiarServidor(int id);
int borrarUsuario(int id);
Usuario addAdmin(char* nombre, char* contrasena);
int borrarCiudad(int id);
int borrarTropa(int id);
int reiniciarUsuario(int id);
int eliminarUsuarioDeServidor(int idUsuario, int idServidor);


#endif /* DATABASE_H_ */
