/*
 * Component.h
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "windows.h"
#include "WindowManager.h"
class WindowComponent{
	public:

		WindowComponent(){
			instance = NULL;
			window = NULL;
			man = NULL;
		}
		WindowComponent(const WindowComponent &other){
			this->window = other.window;
			this->instance = other.instance;
			this->man = other.man;
		}
		/**
		 * Este constructor solo se llama desde WindowManager. No usar
		 * window Ventana de los objetos (contenido en WindowManager)
		 * instance controlador de la ventana
		 */
		WindowComponent(HWND window, HINSTANCE instance, WindowManager *man){
			this->window = window;
			this->instance = instance;
			this->man = man;
		}
		/**
		 * Genera un botón con las especificaciones indicadas
		 * title -> Texto del botón
		 * posX -> posicion del boton en el eje X
		 * posY -> posicion del boton en el eje Y
		 * width -> tamaño en X
		 * height -> tamaño en Y
		 */
		HWND generateButton(const char* title, int posX, int posY, int width, int height){
			return man->registerComponent(CreateWindow(TEXT("BUTTON"), TEXT(title), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL));
		}
		/**
		 * Genera una vista en la que pintar sprites
		 *
		 */
		HWND generateView(int posX, int posY, int width, int height){
			return man->registerComponent(CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, posX,  posY, width, height, window, NULL, instance, NULL));
		}

	private:
		HWND window;
		HINSTANCE instance;
		WindowManager *man;
};



#endif /* COMPONENT_H_ */
