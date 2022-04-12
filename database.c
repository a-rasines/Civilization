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

/*
 * FUNCIONES DE CONFIGURACION
 */
void setup(){
	sqlite3_open("database.db", &db);
}
void end(){
	sqlite3_close(db);
}
/*
 * FUNCIONES GENERICAS
 */
int update(char* query){
	sqlite3_stmt *stmt;
	int i = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return i;
}
int borrar(char* tabla, int id){
	sqlite3_stmt *stmt;
	char* seq[100];
	sprintf(seq, "DELETE FROM %s WHERE ID = %i", tabla, id);
	update(seq);
	free(seq);
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
				UNIQUE(Nombre), \
				PRIMARY KEY(ID))"
	    ) != SQLITE_OK) {
	        printf("Error al crear la tabla UsuarioRaw\n");
	        return 0;
	    }else if (update("CREATE VIEW IF NOT EXISTS Usuario AS SELECT Nombre, ID, Contrasena, Admin FROM UsuarioRaw WHERE Ban = 0") != SQLITE_OK) {
			printf("Error al crear la vista Usuario\n");
			sqlite3_finalize(stmt);
			return 0;
	    }else if(update(
				"CREATE TABLE IF NOT EXISTS Servidor( \
				ID SMALLINT NOT NULL, \
				UltimoConectado TEXT NOT NULL, \
				CantidadConectados SMALLINT NOT NULL, \
				PRIMARY KEY (ID))"
		) != SQLITE_OK){
			printf("Error al crear la tabla Servidor\n");
			return 0;
	    }else if(update(
				"CREATE TABLE IF NOT EXISTS Partida( \
				Jugador INT NOT NULL,\
				Servidor SMALLINT NOT NULL, \
				ID SMALLINT, \
				FOREING KEY Servidor REFERENCES Servidor(ID) ON DELETE CASCADE, \
				PRIMARY KEY(ID))"
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
				FOREING KEY ID REFERENCES Servidor(ID) ON DELETE CASCADE, Jugador REFERENCES UsuarioRaw(ID) ON DELETE CASCADE, \
				PRIMARY KEY(ID))"
	    ) != SQLITE_OK){
	    	printf("Error al crear la tabla Tropa\n");
	    	return 0;
	   }else if(update(
				"CREATE TABLE IF NOT EXISTS Ciudad( \
				Servidor SMALLINT NOT NULL,\
				Usuario INT NOT NULL, \
				ID SMALLINT AUTO_INCREMENT,\
				Nombre TEXT, \
				Edificios TEXT, \
				Comida INT DEFAULT 0, \
				Dinero INT DEFAULT 0, \
				Produccion INT DEFAULT 0, \
				PosicionX INT DEFAULT 0, \
				PosicionY INT DEFAULT 0, \
				FOREING KEY Servidor REFERENCES Servidor(ID) ON DELETE CASCADE, Jugador REFERENCES UsuarioRaw(ID) ON DELETE CASCADE ON UPDATE CASCADE, \
				PRIMARY KEY(ID))"
	    ) != SQLITE_OK){
	    	printf("Error al crear la tabla Ciudad\n");
	    	return 0;
	   }
    return 1;
}
Usuario getUsuario(char* nombre, char* contrasena){
	sqlite3_stmt *stmt;
    Usuario end;
	char seq[100];
	sprintf(seq, "SELECT * FROM Usuario WHERE Nombre = '%s' AND Contrasena = '%s'", nombre, encrypt(contrasena));

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el usuario\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Usuario){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Usuario){'\0', 0, 0};
	}
	end.nombre = malloc(sizeof(char)*20);
	strcpy(end.nombre, (char *) sqlite3_column_text(stmt, 0));
	end.id = sqlite3_column_int(stmt, 1);
	end.admin = sqlite3_column_int(stmt, 3);
	return end;
}
Usuario addUsuarioRaw(char* nombre, char* contrasena, int admin){
	sqlite3_stmt *stmt;
	char seq[200];
	sprintf(seq, "INSERT INTO UsuarioRaw(Nombre, Contrasena, Admin) VALUES ('%s', '%s', %d)",nombre, encrypt(contrasena), admin);
	update(seq);
	return getUsuario(nombre, contrasena);
}
Usuario addUsuario(char* nombre, char* contrasena){
	return addUsuarioRaw(nombre, contrasena, 0);
}
Usuario addAdmin(char* nombre, char* contrasena){
	return addUsuarioRaw(nombre, contrasena, 1);
}
int existsNombre(char* nombre){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT Count(Nombre) FROM Usuario WHERE Nombre = '%s'", nombre);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al buscar el nombre\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return 0;
	}
	int end = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return end;
}
int banAction(int id, int status){
	sqlite3_stmt *stmt;
	char seq[200];
	sprintf(seq,"UPDATE UsuarioRaw SET Ban = %d WHERE ID = %d",status, id);
	return update(seq);
}
int banUsuario(){
	Usuario ban;
	printf("Primero busquemos al usuario que se quiere modificar\n");
	printf("Introduce su nombre: \n");
	//Buscar Usuario;
	return banAction(1, ban.id);
}
int unbanUsuario(int id){
	return banAction(0, id);
}
int modificarUsuarioAdm(){
	sqlite3_stmt *stmt;
	Usuario ini;
	Usuario end;
	char seq[100];
	printf("Primero busquemos al usuario que se quiere modificar\n");
	printf("Introduce su nombre: ");
	char * nombre = malloc(sizeof(char)*20);
	scanf("%s",nombre);
	//REVISAR;
	sprintf(seq, "SELECT * FROM Usuario WHERE Nombre = '%s'", nombre);
	ini.nombre = malloc(sizeof(char)*20);
	strcpy(end.nombre, (char *) sqlite3_column_text(stmt, 0));
	ini.id = sqlite3_column_int(stmt, 1);
	ini.admin = sqlite3_column_int(stmt, 3);
	imprimirUsuario(ini);
	printf("introduce el nuevo nombre para el usuario: ");
	char * newNombre = malloc(sizeof(char)*20);
	scanf("%s",newNombre);
	end.nombre=newNombre;
	end.id=10;
	end.admin=1;
	printf("llego");
	free(seq);
	sprintf(seq, "UPDATE UsuarioRaw SET Nombre='%s', ID=%i, Admin=%i WHERE Nombre = '%s' AND ID = '%s' ",end.nombre,end.id, end.admin, ini.nombre, ini.id);
	printf("llego2");
	sprintf(seq, "SELECT * FROM Usuario WHERE Nombre = '%s'", end.nombre);
	ini.nombre = malloc(sizeof(char)*20);
	strcpy(ini.nombre, (char *) sqlite3_column_text(stmt, 0));
	ini.id = sqlite3_column_int(stmt, 1);
	ini.admin = sqlite3_column_int(stmt, 3);
	imprimirUsuario(ini);
	return update(seq);
}
int limpiarServidor(int id){
	sqlite3_stmt *stmt;

	//Comprobamos que existe
	char seq[100];
	sprintf(seq, "SELECT ID FROM Servidor WHERE ID = %d", id);
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el usuario\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return 0;
	}
	sqlite3_finalize(stmt);
	free(seq);

	//Eliminamos el servidor para eliminar todas las entradas dependientes
	borrar("Server",id);

	//Volvemos a crear el servidor
	seq[100];
	sprintf(seq, "INSERT INTO Servidor(ID) VALUES %i", id);
	update(seq);
	free(seq);
}
int borrarUsuario(int id){
	return borrar("UsuarioRaw", id);
}
int borrarCiudad(int id){
	return borrar("Ciudad", id);
}
int borrarTropa(int id){
	return borrar("Tropa", id);
}
int reiniciarUsuario(int id){
	sqlite3_stmt *stmt;
		char seq[100];
		sprintf(seq, "SELECT ID FROM Tropa WHERE Usuario = %i", id);
		if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al buscar ciudades\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
		int i =sqlite3_step(stmt);
		while(i == SQLITE_ROW){
			borrarTropa(sqlite3_column_int(stmt,0));
			i = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		free(seq);
		seq[100];
		sprintf(seq, "SELECT ID FROM Ciudad WHERE Usuario = %i", id);
		if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al buscar tropas\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
		i =sqlite3_step(stmt);
		while(i == SQLITE_ROW){
			borrarCiudad(sqlite3_column_int(stmt,0));
			i = sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		free(seq);
		return 1;
}
int eliminarUsuarioDeServidor(int idUsuario, int idServidor){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT ID FROM Tropa WHERE Usuario = %i AND Servidor = %i", idUsuario, idServidor);
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al buscar ciudades\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	int i =sqlite3_step(stmt);
	while(i == SQLITE_ROW){
		borrarTropa(sqlite3_column_int(stmt,0));
		i = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	free(seq);
	seq[100];
	sprintf(seq, "SELECT ID FROM Ciudad WHERE Usuario = %i AND Servidor = %i", idUsuario, idServidor);
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al buscar tropas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	i =sqlite3_step(stmt);
	while(i == SQLITE_ROW){
		borrarCiudad(sqlite3_column_int(stmt,0));
		i = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	free(seq);
	return 1;
}

