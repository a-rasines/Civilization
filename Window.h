/*
 * Window.h
 *	Esta clase es la padre de las ventanas del juego
 *  Created on: 5 may 2022
 *      Author: algtc
 */

#ifndef WINDOW_H_
#define WINDOW_H_
#include "windows.h"
#include <list>
#include <iostream>
class Window {
	public:
		HINSTANCE static instance;
		HWND static window;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones a copiar
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void start(){}; //Esta funcion se llama al cambiar de pantalla
		virtual void update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
		virtual void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones internas
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND generateButton(const char* title, int posX, int posY, int width, int height);
		/**
		 * Genera una vista en la que pintar sprites
		 *
		 */
		HWND generateView(int posX, int posY, int width, int height);
		void destroyComponents();
		void removeComponent(HWND comp);

		float deltatime = 0;
		Window(){
		};
		virtual ~Window(){};
};

#endif /* WINDOW_H_ */
