/*
 * Window.h
 *	Esta clase es la padre de las ventanas del juego
 *  Created on: 5 may 2022
 *      Author: algtc
 */

#ifndef WINDOW_H_
#define WINDOW_H_
class Window {
	public:
		class Component{
				public:
					/**
					 * Este constructor solo se llama desde WindowManager. No usar
					 * window Ventana de los objetos (contenido en WindowManager)
					 */
					Component(){
						window = NULL;
						instance = NULL;
					}
					Component(HWND window, HINSTANCE instance){
						this->window = window;
						this->instance = instance;
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
						return CreateWindow(TEXT("BUTTON"), TEXT(title), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
					}
					/**
					 * Genera una vista en la que pintar sprites
					 *
					 */
					HWND generateView(int posX, int posY, int width, int height){
						return CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, posX,  posY, width, height, window, NULL, instance, NULL);
					}
					HWND window;
				private:
					HINSTANCE instance;
			};
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones a copiar
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void start(){}; //Esta funcion se llama al cambiar de pantalla
		virtual void update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
		virtual void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones internas
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Window(){};
		virtual ~Window(){};
		void init(Component comp){
			this->comp = comp;
			start();
						}
	protected:
		Component comp;
};

#endif /* WINDOW_H_ */
