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
class WindowManager;
class Window {
	public:
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones a copiar
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void start(){}; //Esta funcion se llama al cambiar de pantalla
		virtual void update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
		virtual void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones internas
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND generateButton(const char* title, int posX, int posY, int width, int height){
			HWND comp = CreateWindow(TEXT("BUTTON"), TEXT(title), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
			components.push_back(comp);
			return comp;
		}
		/**
		 * Genera una vista en la que pintar sprites
		 *
		 */
		HWND generateView(int posX, int posY, int width, int height){
			HWND comp = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, posX,  posY, width, height, window, NULL, instance, NULL);
			components.push_back(comp);
			return comp;
		}
		void destroyComponents(){
			for(HWND comp : components){
				DestroyWindow(comp);
				components.clear();
			}
		}
		void removeComponent(HWND comp){
			DestroyWindow(comp);
			components.remove(comp);
		}

		float deltatime = 0;
		Window(){};
		virtual ~Window(){};
		void init(HINSTANCE instance, HWND window){
			this->instance = instance;
			this->window = window;
			start();
		}
	private:
		HINSTANCE instance;
		HWND window;
		std::list<HWND> components;
};

#endif /* WINDOW_H_ */
