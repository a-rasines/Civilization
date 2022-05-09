/*
 * Ejemplo2.cpp
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include "Ejemplo2.h"
HWND button;
sf::RenderWindow SFMLView2;
void Ejemplo2::start(){
	button = generateButton("A", 10, 0, 200, 100);
//	SFMLView2.create(comp.generateView(10, 100, 1000, 900));
//	SFMLView2.display();
}; //Esta funcion se llama al cambiar de pantalla
void Ejemplo2::update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
void Ejemplo2::onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
Ejemplo2::Ejemplo2() {
	printf("a");
}

Ejemplo2::~Ejemplo2() {
	// TODO Auto-generated destructor stub
}

