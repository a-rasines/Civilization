/*
 * menu.c
 *
 *  Created on: 10 abr. 2022
 *      Author: eneko
 */
#include <stdio.h>
#include "usuario.h"
#include "database.h"
int main(void){
	setup();
	printf("%i", regenerarBaseDatos());
	addUsuario("Test", "son 20 caracter");
	end();
	int terminarAutent = 0;
	Usuario user;
//	while(!terminarAutent){
//		printf("Tienes un usuario registrado? (s/n)\n");
//		char answ = getchar();
//		if(answ == 's'){
//			user = autentificarse();
//		}else{
//			user = registrarse();
//		}
//		terminarAutent = 1;
//	}
	int hacerCosas=1;
	int opcion;
	while(!hacerCosas){
		if(user.admin) opcion = opcionesAdmin();
		else opcion=opcionesNormales();
		switch (opcion) {
			case 0:
				hacerCosas=0;
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
	}
	return 0;
}
