/*
 * WindowManager.h
 * Esta clase simplifica las interacciones con SFML
 *  Created on: 3 may 2022
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_
#include <SFML/Graphics.hpp>
#include <windows.h>
class WindowManager {
	public:
		/** Genera una ventana de SFML con el título definido
		 * 	title -> Titulo de la ventana
		 */
		WindowManager(char* title);
		virtual ~WindowManager();
		/**
		 * Destruye y quita de cache la ventana
		 */
		void end();
		/**
		 * Algo por el estilo de addActionListener() de java, solo que con punteros a funcion
		 * *button -> pointer al boton del listener
		 * *func -> funcion a ejecutar cuando se pulse
		 */
		void registerButton(HWND *button, void(*func)());
		/**
		 * Esta clase contiene los generadores de los elementos de SFML
		 */
		class Element{
			public:
				/**
				 * Este constructor solo se llama desde WindowManager. No usar
				 * window Ventana de los objetos (contenido en WindowManager)
				 */
				Element(HWND window);
				/**
				 * Genera un botón con las especificaciones indicadas
				 * title -> Texto del botón
				 * posX -> posicion del boton en el eje X
				 * posY -> posicion del boton en el eje Y
				 * width -> tamaño en X
				 * height -> tamaño en Y
				 */
				HWND generateButton(char* title, int posX, int posY, int width, int height);
			private:
				HWND window;
		};
		Element element;
	private:
		class MapEntry{
				public:
					/**
					 * Me da pereza buscar como hacer mapas, asi que me he ideado el mio
					 * *key -> key
					 * *func -> value
					 */
					MapEntry(HWND *key, void(*func)());
					HWND *key;
					/**
					 * Corre la funcion asociada a la llave
					 */
					void run();
					virtual ~MapEntry();
				private:
					void(*func)();
			};
		MapEntry button[] = new MapEntry[0];
		HWND window;
		HINSTANCE instance;
		int buttonCount = 0;
		void onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
};




#endif /* WINDOWMANAGER_H_ */
