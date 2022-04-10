/*
 * usuario.c
 *
 *  Created on: 10 abr. 2022
 *      Author: eneko
 */
#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
int opcionesNormales(){
	printf("Selecciona una de las siguientes opciones:\n");
	printf("Opciones:\n1)Exportar partida.\n2)Importar partida.\n3)Modificar Usuarios.\n0)Para salir.\n");
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
	printf("Opciones:\n1)Exportar partida.\n2)Importar partida.\n3)Modificar Usuarios.\n4)Banear usuarios\n0)Para salir.\n");
	return seleccion('0','4');
}
void autentificarse(){
	printf("Introduce tu nombre de usuario:\n");
	char * nombre = malloc(sizeof(char)*20);
	scanf("%s",nombre);
	printf("Introduce tu contrase�a: ");
	char* contrasena = malloc(sizeof(char)*20);
	scanf("%s",contrasena);
	int existe=0; //llamar a la funcion de inicio.
	if(existe == 1){
		printf("Existes, sigue adelante \n");
	}else if(existe == 2){
		printf("Bienvenido Admin \n");
	}else{
		printf("toca registrarse \n");
		registrarse();
	}
}

void registrarse(){
	int registroHecho=0;
	Usuario nuevo;
	while(!registroHecho){
		printf("Toca registrarse; introduce tu nombre de usuario: ");
		char * nombre = malloc(sizeof(char)*20);
		scanf("%s",nombre);
		printf("Introduce tu contrase�a: ");
		char* contrasena = malloc(sizeof(char)*20);
		scanf("%s",contrasena);
		printf("Confirma tu contrase�a: ");
		char* contrasena2 = malloc(sizeof(char)*20);
		scanf("%s",contrasena2);
		if(contrasena==contrasena2){
			//registramos en la BD;
			//nuevo = (llamaos a la funcion select de la base de datos);
			registroHecho = 1;
		}else printf("Las contrasenas no son las mismas vuelve a registrarte");
	}
	//llamar a la funcion de registro.
}
