#ifndef TROPA_H_
#define TROPA_H_

#include "usuario.h"
#include "partida.h"

typedef struct
{
	int idServidor;
	int idJugador;
	int idTropa;
	int tipo;
	int vida;
	int mejorada;
	int estado;
	int posicionX;
	int posicionY;
	bool estacionada;
} Tropa;


#endif /* USUARIO_H_ */
