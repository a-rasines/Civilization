#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "database.h"
#include "xml.h"
int main(void){
	setup();
	printf("%i", regenerarBaseDatos());
	int terminarAutent = 0;
	Usuario user;
	char answ;
	while(!terminarAutent){
		if(answ != '\n')
			printf("Tienes un usuario registrado? (s/n)\n");
		scanf("%c", &answ);
		if(answ == 's'){
			user = autentificarse();
			terminarAutent = 1;
		}else if(answ == 'n'){
			user = registrarse();
			terminarAutent = 1;
		}

	}
	imprimirUsuario(user);
	int hacerCosas=0;
	int opcion;
	while(!hacerCosas){
		if(user.admin) opcion = opcionesAdmin();
		else opcion=opcionesNormales();
		char* input;
		int id;
		switch (opcion) {
			case 0:
				end();
				return 0;
			case 1:
				printStats(user.id);
				break;
			case 2:
				if(user.admin)modificarUsuarioAdm();
				else{
					printf("Introduce el nuevo nombre a ponerse: \n");
					input = malloc(sizeof(char)*20);
					scanf("%s", input);
					modificarUsuario(user.id, input);
				}
				break;
			case 3:
				printf("Introduce el nombre del usuario a banear: \n");
				input = malloc(sizeof(char)*20);
				scanf("%s", input);
				id = getUsuarioAdm(input).id;
				banAction(id, !isBaneado(id));
				break;
			case 4:
				printf("Introduce el nombre del archivo / Ruta si no se encuentra en la carpeta del ejecutable: \n");
				input = malloc(sizeof(char)*20);
				scanf("%s", input);
				cargarServidorEnBD(input);
				break;
			case 5:
				printf("Introduce el id del servidor a guardar: \n");
				scanf("%i", &id);
				guardarServidorEnXML(id);
				break;
			default:
				break;
		}
	}
	printf("close");
	end();

	return 0;
}
