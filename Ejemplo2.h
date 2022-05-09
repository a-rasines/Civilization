/*
 * Ejemplo2.h
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */

#ifndef EJEMPLO2_H_
#define EJEMPLO2_H_

#include "Window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>

class Ejemplo2: public Window {
public:
	Ejemplo2();
	virtual void start(); //Esta funcion se llama al cambiar de pantalla
	virtual void update();//Esta funcion se llama cada vez que de una vuelta al bucle
	virtual void onButtonPress(HWND button);//Esta funcion se llama cuando un boton sea pulsado
	virtual ~Ejemplo2();
};

#endif /* EJEMPLO2_H_ */
