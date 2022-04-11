/*
 * database.c
 *
 *  Created on: 10 abr 2022
 *      Author: algtc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "usuario.h"
#include "sqlite3.h"
#include "md5.h"
sqlite3 *db;
void setup(){
	sqlite3_open("database.db", &db);
}
void end(){
	sqlite3_close(db);
}
int update(char* query, sqlite3_stmt *stmt){
	int i = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return i;
}
int regenerarBaseDatos(){
	sqlite3_stmt *stmt;
	    if (
			update(
				"CREATE TABLE IF NOT EXISTS UsuarioRaw( \
				Nombre TEXT NOT NULL,\
				ID INT,\
				Contrasena TEXT NOT NULL,\
				Admin BIT DEFAULT 0, \
				Ban BIT DEFAULT 0, \
				PRIMARY KEY(Nombre, Contrasena, ID))", stmt
	    ) != SQLITE_OK) {
	        printf("Error al crear la tabla UsuarioRaw\n");
	        return 0;
	    }else if (update("CREATE VIEW IF NOT EXISTS Usuario AS SELECT Nombre, ID, Contrasena, Admin FROM UsuarioRaw WHERE Ban = 0", stmt) != SQLITE_OK) {
			printf("Error al crear la vista Usuario\n");
			sqlite3_finalize(stmt);
			return 0;
	    }else if(update(
				"CREATE TABLE IF NOT EXISTS Servidor( \
				ID SMALLINT NOT NULL, \
				PRIMARY KEY (ID))", stmt
		) != SQLITE_OK){
			printf("Error al crear la tabla Servidor\n");
			return 0;
	    }else if(update(
				"CREATE TABLE IF NOT EXISTS Partida( \
				Jugador TEXT NOT NULL,\
				Servidor SMALLINT, \
				Contrasena TEXT NOT NULL,\
				Admin BIT DEFAULT 0, \
				Ban BIT DEFAULT 0, \
				FOREING KEY Servidor REFERENCES Servidor(ID), \
				PRIMARY KEY(Jugador, Servidor))", stmt
	    ) != SQLITE_OK){
	    	printf("Error al crear la tabla Partida\n");
	    	return 0;
	   }else if(update(
				"CREATE TABLE IF NOT EXISTS Tropa( \
				Servidor SMALLINT NOT NULL, \
				Usuario TEXT NOT NULL, \
				ID SMALLINT AUTO_INCREMENT, \
				Tipo TEXT NOT NULL, \
				Vida BIT DEFAULT 0, \
				Mejorada BIT DEFAULT 0, \
				PosicionX INT DEFAULT 0, \
				PosicionY INT DEFAULT 0, \
				FOREING KEY ID REFERENCES Servidor(ID), Jugador REFERENCES UsuarioRaw(ID), \
				PRIMARY KEY(ID))", stmt
	    ) != SQLITE_OK){
	    	printf("Error al crear la tabla Tropa\n");
	    	return 0;
	   }else if(update(
				"CREATE TABLE IF NOT EXISTS Ciudad( \
				Servidor SMALLINT NOT NULL,\
				Usuario TEXT NOT NULL, \
				ID SMALLINT AUTO_INCREMENT,\
				Nombre TEXT, \
				Edificios TEXT, \
				Comida INT DEFAULT 0, \
				Dinero INT DEFAULT 0, \
				Produccion INT DEFAULT 0, \
				PosicionX INT DEFAULT 0, \
				PosicionY INT DEFAULT 0, \
				FOREING KEY Servidor REFERENCES Servidor(ID), Jugador REFERENCES UsuarioRaw(ID), \
				PRIMARY KEY(ID))", stmt
	    ) != SQLITE_OK){
	    	printf("Error al crear la tabla Ciudad\n");
	    	return 0;
	   }
    return 1;
}
Usuario getUsuario(char* nombre, char* contrasena){
    sqlite3_stmt *stmt;
    Usuario end;
	char seq[100] = "SELECT * FROM Usuario WHERE Nombre = '";
	strcat(seq, nombre);
	strcat(seq, "' AND Contrasena = '");
	strcat(seq, contrasena);
	strcat(seq, "'");

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el usuario\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Usuario){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Usuario){'\0', 0, 0};
	}
	strcpy(end.nombre, (char *) sqlite3_column_text(stmt, 0));
	char* temp;
	strcpy(temp, (char *) sqlite3_column_text(stmt, 1));
	sscanf(temp, "%i", &end.id);
	strcpy(temp, (char *) sqlite3_column_text(stmt, 3));
	sscanf(temp, "%i", &end.admin);
	return end;
}
Usuario addUsuarioRaw(char* nombre, char* contrasena, int admin){
	sqlite3_stmt *stmt;
	char seq[200] = "INSERT INTO UsuarioRaw(Nombre, Contrasena, Admin) VALUES ('";
	strcat(seq, nombre);
	strcat(seq, "','");
	char cont_crypt[20];
	strcpy(cont_crypt, contrasena);
	strcat(seq, encrypt(cont_crypt));
	strcat(seq, "', ");
	char temp[1];
	sprintf(temp, "%d", admin);
	strcat(seq, temp);
	strcat(seq, ")");
	update(seq, stmt);
	return getUsuario(nombre, contrasena);
}
Usuario addUsuario(char* nombre, char* contrasena){
	return addUsuarioRaw(nombre, contrasena, 0);
}
Usuario addAdmin(char* nombre, char* contrasena){
	return addUsuarioRaw(nombre, contrasena, 1);
}

