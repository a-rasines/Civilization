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
	printf("%i\n", regenerarBaseDatos());
	printf("%i\n", existsNombre("a"));
	int terminarAutent = 0;
	Usuario user;
	char answ;
	while(!terminarAutent){
		if(answ != '\n')
			printf("Tienes un usuario registrado? (s/n)\n");
		answ = getchar();
		if(answ == 's'){
			user = autentificarse();
			terminarAutent = 1;
		}else if(answ == 'n'){
			user = registrarse();
			terminarAutent = 1;
		}

	}
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
			case 3:
				if(user.admin) modificarUsuarioAdm();
			default:
				break;
		}
	}
	printf("close");
	end();

	return 0;
}
