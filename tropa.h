#ifndef TROPA_H_
#define TROPA_H_

#include "usuario.h"
#include "partida.h"

typedef struct
{
	int idServidor;
	int idJugador;
	enum tipo;
	int vida;
	int mejorada;//bool no existe en c
	int estado;
	int posicionX;
	int posicionY;
} Tropa;


#endif /* USUARIO_H_ */
