/*
 * Window.h
 *	Esta clase es la padre de las ventanas del juego
 *  Created on: 5 may 2022
 *      Author: algtc
 */

#ifndef WINDOW_H_
#define WINDOW_H_
#include "windows.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "WindowManager.h"
class Window {
	public:
		enum ItemType{
			DropMenu = MF_POPUP,
			String = MF_STRING,
			Separator = MF_SEPARATOR,
			MenuBreak = MF_MENUBREAK,
			MenuBarBreak = MF_MENUBARBREAK
		};
		struct MenuItem{
			MenuItem(){
				type = ItemType::Separator;
				name = NULL;
				children = new MenuItem[0];
				childCount = 0;
				id = 0;
			}
			MenuItem(ItemType t){
				type = t;
				name = NULL;
				children = new MenuItem[0];
				childCount = 0;
				id = 0;
			}
			MenuItem(const wchar_t * name, UINT_PTR id){
				this-> type = ItemType::String;
				this -> name = name;
				this -> children = new MenuItem[0];
				this -> childCount = 0;
				this-> id = id;
			}
			MenuItem(const wchar_t * name, MenuItem children[]){
				this->type = ItemType::DropMenu;
				this->name = name;
				this->children = children;
				this->childCount = sizeof(children) / sizeof(children[0]);
				this->id = 0;
			}
			MenuItem(const wchar_t* name, std::initializer_list<MenuItem> children){
				this->type = ItemType::DropMenu;
				this->name = name;
				this->children = new MenuItem[children.size()];
				std::copy(children.begin(), children.end(), this->children);
				this->childCount = children.size();
				this->id = 0;
			}
			MenuItem(const MenuItem& other){
				this->type = other.type;
				this->name = other.name;
				this->childCount = other.childCount;
				this->children = other.children;
				this->id = other.id;
			}
			ItemType type;
			const wchar_t* name;
			UINT_PTR id;
			int childCount;
			MenuItem *children;
		};
		struct MenuStructure{
			MenuStructure(const wchar_t* name, UINT_PTR id,	ItemType type, int childCount, MenuStructure *children){
				this->name = name;
				this->id = id;
				this->type = type;
				this->childCount = childCount;
				this->children = children;
			}
			MenuStructure(){
				this->name = L"";
				this->id = 0;
				this->type = ItemType::Separator;
				this->childCount = 0;
				this->children = new MenuStructure[0];
			}
			const wchar_t* name;
			UINT_PTR id;
			ItemType type;
			int childCount;
			MenuStructure *children;
		};
		WindowManager static *manager;
		HINSTANCE static instance;
		HWND static window;
		std::vector<UINT_PTR> menuid;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TODO                                            Funciones a copiar
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void onClientStart(){};//Esta funcion se llama cuando se inicia el cliente
		virtual void onServerStart(){};//Esta funcion se llama cuando se inicia el servidor
		virtual void start(){};//Esta funcion se llama al cambiar de pantalla
		virtual void update(){};//Esta funcion se llama cada vez que de una vuelta al bucle
		virtual void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
		virtual void onResize(int newWidth, int newHeight){};//Esta funcion se llama cuando la ventana cambia de tamaño
		virtual void onMessage(char* message){};//Esta función se llama cuando un mensaje TCP es recibido
		virtual void onKeyDown(int keycode){};//Esta función se llama cuando una tecla es pulsada
		virtual void onKeyUp(int keycode){};//Esta función se llama cuando una tecla es soltada
		virtual void onMouseDown(int mouseButton, int x, int y){};//Esta funcion se llama cuando se pulsa una tecla del raton. El botón se saca mediante or binario
		virtual void onMouseUp(int mouseButton, int x, int y){};//Esta funcion se llama cuando se suelta una tecla del raton. El botón se saca mediante or binario
		virtual void onClose(){};//Esta funcion se llama al cerrar la ventana
		virtual void onMenu(UINT_PTR menuId){};//Esta funcion se llama cuando un menu es clickado
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
		 * Genera un TextBox (AKA TextField en Java) con el texto metido
		 *  text -> Texto inicial
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 */
		HWND generateTextField(const char* text, int posX, int posY, int width, int height);

		/**
		 * Genera un TextBox (AKA TextField en Java) de contraseña con el texto metido
		 *  text -> Texto inicial
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 */
		HWND generatePasswordField(const char* text, int posX, int posY, int width, int height);
		/**
		 * Genera un TextBox (AKA TextField en Java) de contraseña vacio
		 *  text -> Texto inicial
		 *	posX -> Posicion de las esquinas izquierdas.
		 *	posY -> Posicion de las esquinas superiores.
		 *	width -> Anchura de la vista
		 *	height -> Altura de la vista
		 */
		HWND generatePasswordField(int posX, int posY, int width, int height);
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
		 * Anade una seccion de menu
		 * item -> Estructura del nuevo menu
		 */
		MenuStructure addMenuItem(Window::MenuItem item);
		/**
		 * Elimina el menu existente en la ventana
		 */
		void destroyMenu();
		/**
		 * Devuelve el texto dentro de cualquier componente de la ventana (Botones, textbox, combobox...).
		 * component -> componente del que sacar el texto
		 */
		char* getComponentText(HWND component);
		/**
		 * Establece si la ventana se debe poder redimensionar o no
		 */
		void setResizable(bool resizable);
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
		 * Mueve la ventana a una nueva posicion
		 * x -> Nueva posicion X de la ventana
		 * y -> Nueva posicion Y de la ventana
		 */
		void move(int x, int y);
		/**
		 * Cambia el tamaño de la ventana
		 * width -> Nueva anchura
		 * height -> Nueva altura
		 */
		void resize(int width, int height);
		/**
		 * Cambia el tamaño y posición de la ventana
		 * width -> Nueva anchura
		 * height -> Nueva altura
		 * x -> Nueva posicion X de la ventana
		 * y -> Nueva posicion Y de la ventana
		 */
		void resize(int width, int height, int x, int y);
		/**
		 * Tiempo desde el anterior frame
		 */
		float deltatime = 0;
		Window(){
			menu = CreateMenu();
		};
		virtual ~Window(){};
	private:
		void addMenuItemRec(Window::MenuItem parent, HMENU hMenu, MenuStructure* struc);
		HMENU menu;
};

#endif /* WINDOW_H_ */
