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
#include "WindowManager.h"
class Window {
	public:
		WindowManager static *manager;
		HINSTANCE static instance;
		HWND static window;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones a copiar
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void start(){}; //Esta funcion se llama al cambiar de pantalla
		virtual void update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
		virtual void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
		virtual void onResize(int newWidth, int newHeight){};//Esta funcion se llama cuando la ventana cambia de tamaño
		virtual void onMessage(char* message){};//Esta función se llama cuando un mensaje TCP es recibido
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones internas
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HWND generateButton(const char* title, int posX, int posY, int width, int height);
		/**
		 * Genera una vista en la que pintar sprites
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 */
		HWND generateView(int posX, int posY, int width, int height);
		/**
		 * Genera un TextBox (AKA TextField en Java) vacio
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 */
		HWND generateTextField(int posX, int posY, int width, int height);
		/**
		 * Genera un TextBox (AKA TextField en Java) con el texto metiod
		 *  text -> Texto inicial
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 */
		HWND generateTextField(const char* text, int posX, int posY, int width, int height);
		/**
		 * Genera un ComboBox con los valores indicados en el parametro 5
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 *	values -> Valores del comboBox
		 */
		HWND generateComboBox(int posX, int posY, int width, int height, std :: initializer_list <const char*> values);
		/**
		 * Devuelve el texto dentro de cualquier componente de la ventana (Botones, textbox, combobox...).
		 * component -> componente del que sacar el texto
		 */
		void setResizable(bool resizable);
		char* getComponentText(HWND component);
		/**
		 * Elimina todos los componentes presentes en la ventana
		 */
		void destroyComponents();
		/**
		 * Elimina un componente de la ventana.
		 * comp -> Componente a eliminar
		 */
		void removeComponent(HWND comp);
		/**
		 * Tiempo desde el anterior frame
		 */
		float deltatime = 0;
		Window(){
		};
		virtual ~Window(){};
};

#endif /* WINDOW_H_ */
