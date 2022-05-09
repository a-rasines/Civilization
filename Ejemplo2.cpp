/*
 * Ejemplo2.cpp
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */

#include "Ejemplo2.h"
void Ejemplo2::start(){
	comp.generateButton("A", 0, 0, 200, 100);
}; //Esta funcion se llama al cambiar de pantalla
void Ejemplo2::update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
void Ejemplo2::onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
Ejemplo2::Ejemplo2() {
	// TODO Auto-generated constructor stub

}

Ejemplo2::~Ejemplo2() {
	// TODO Auto-generated destructor stub
}

