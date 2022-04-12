/*
 * usuario.c
 *
 *  Created on: 10 abr. 2022
 *      Author: eneko
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "database.h"
char* stringOpcionesNormales =
		"Selecciona una de las siguientes opciones: \
		\t1)Exportar partida. \
		\t2)Importar partida. \
		\t3)Modificar Usuarios. \n";
char endNormales = '3';
char endAdmin = '4';
char* stringOpcionesAdmin =
		"4)Banear usuarios\n";
char* opcionesGenericas = "\t0)Salir.\n";
void imprimirUsuario(Usuario user){
	printf("Usuario: Id->%i, Nombre->'%s', Admin->%i", user.id,user.nombre, user.admin);
}
int opciones(char*title, char first, char end){
	printf(title);
	return seleccion(first, end);
}
int opcionesNormales(){
	char* send = malloc(sizeof(char) *(strlen(stringOpcionesNormales) + strlen(opcionesGenericas)));
	sprintf(send, "%s%s", stringOpcionesNormales, opcionesGenericas);
	return opciones(send, '0', endNormales);
}
int seleccion(char a, char b){
	char c = getchar();
	while(c<=a || c>=b){
		c=getchar();
	}
	return c-'0';
}
int opcionesAdmin(){
	char* send = malloc(sizeof(char) *(strlen(stringOpcionesNormales) + strlen(stringOpcionesNormales) + strlen(opcionesGenericas)));
	sprintf(send, "%s%s%s", stringOpcionesNormales, stringOpcionesAdmin, opcionesGenericas);
	return opciones(send, '0', endAdmin);
}

Usuario autentificarse(){
	printf("Introduce tu nombre de usuario:\n");
	char * nombre = malloc(sizeof(char)*20);
	scanf("%s",nombre);
	printf("Introduce tu contrasena: ");
	char* contrasena = malloc(sizeof(char)*20);
	scanf("%s",contrasena);
	Usuario us = getUsuario(nombre, contrasena);
	if(nombre == '\0'){
		printf("toca registrarse \n");
		return registrarse();
	}else if(us.admin){
		printf("Bienvenido Admin \n");
		return us;
	}else {
		printf("Existes, sigue adelante \n");
		return us;
	}
}

Usuario registrarse(){
	Usuario nuevo;
	while(1){
		printf("introduce tu nombre de usuario: ");
		char * nombre = malloc(sizeof(char)*20);
		scanf("%s",nombre);
		printf("Introduce tu contrasena: ");
		char* contrasena = malloc(sizeof(char)*20);
		scanf("%s",contrasena);
		printf("Confirma tu contrasena: ");
		char* contrasena2 = malloc(sizeof(char)*20);
		scanf("%s",contrasena2);
		if(strcmp(contrasena,contrasena2)==0){
			return addUsuario(nombre, contrasena);
		}else printf("Las contrasenas no son las mismas vuelve a registrarte");
	}
}
