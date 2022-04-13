/*
 * usuario.c
 *
 *  Created on: 10 abr. 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "database.h"
char* stringOpcionesNormales =
		"Selecciona una de las siguientes opciones: \
		\n1)Acceso a estadisticas. \
		\n2)Modificar Usuario. \n";
char endNormales = '3';
char endAdmin = '6';
char* stringOpcionesAdmin =
		"3)Banear usuarios\
		 \n4)Importar servidor.\
		 \n5)Generar backup de servidor\
		 \n6)Reparar base de datos.\n";
char* opcionesGenericas = "0)Salir.\n";
void imprimirUsuario(Usuario user){
	printf("Usuario: Id->%i, Nombre->'%s', Admin->%i\n", user.id,user.nombre, user.admin);
}
int seleccion(char a, char b){
	char* c = malloc(sizeof(char)*10);
	scanf("%s", c);
	while((int)c[0]<(int)a || (int)c[0]>(int)b){
		scanf("%s", c);
	}
	return (int)(c[0]-'0');
}
int opciones(char*title, char first, char end){
	printf(title);
	return seleccion(first, end);
}
int opcionesNormales(){
	char* send = malloc(sizeof(char) *(strlen(stringOpcionesNormales) + strlen(opcionesGenericas)+1));
	sprintf(send, "%s%s", stringOpcionesNormales, opcionesGenericas);
	return opciones(send, '0', endNormales);
}

int opcionesAdmin(){
	char* send = malloc(sizeof(char) *(strlen(stringOpcionesNormales) + strlen(stringOpcionesNormales) + strlen(opcionesGenericas)+1));
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
	if(us.nombre == '\0'){
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
	while(1){
		printf("introduce tu nombre de usuario: ");
		char* nombre = malloc(sizeof(char)*20);
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
