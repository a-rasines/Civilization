#include <stdio.h>
#include "usuario.h"
#include "database.h"
#include "xml.h"
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
		printf("opcion=%d", opcion);
		switch (opcion) {
			case 0:
				end();
				return 0;
			case 1:
				break;
			case 2:
				break;
			case 3:
				if(user.admin) modificarUsuarioAdm();
				break;
			case 4:
				banUsuario();
				break;
			default:
				break;
		}
	}
	printf("close");
	end();

	return 0;
}
