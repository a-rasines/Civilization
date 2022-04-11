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

int opcionesNormales(){
	printf("Selecciona una de las siguientes opciones:\n");
	printf("1)Exportar partida.\n2)Importar partida.\n3)Modificar Usuarios.\n0)Para salir.\n");
	return seleccion('0','3');
}
int seleccion(char a, char b){
	char c = getchar();
	while(c<=a || c>=b){
		c=getchar();
	}
	return c-'0';
}
int opcionesAdmin(){
	printf("Selecciona una de las siguientes opciones:\n");
	printf("1)Exportar partida.\n2)Importar partida.\n3)Modificar Usuarios.\n4)Banear usuarios\n0)Para salir.\n");
	return seleccion('0','4');
}

Usuario autentificarse(){
	printf("Introduce tu nombre de usuario:\n");
	char * nombre = malloc(sizeof(char)*20);
	scanf("%s",nombre);
	printf("Introduce tu contrase�a: ");
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
		printf("Toca registrarse; introduce tu nombre de usuario: ");
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
