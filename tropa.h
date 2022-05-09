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
	bool mejorada;
	int estado;
	int posicionX;
	int posicionY;
} Tropa;


#endif /* USUARIO_H_ */
