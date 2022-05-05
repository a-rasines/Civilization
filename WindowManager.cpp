/*
 * WindowManager.cpp
 *
 *  Created on: 3 may 2022
 *      Author: algtc
 */

#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
	LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
		switch (message){
				// Quit when we close the main window
			case WM_CLOSE:{
				PostQuitMessage(0);
				break;
			}case WM_COMMAND:{

			}
		}
		return DefWindowProc(handle, message, wParam, lParam);
	}
	WindowManager::EmptyMapEntry::EmptyMapEntry(){

	}
	WindowManager::EmptyMapEntry::~EmptyMapEntry(){

	}
	WindowManager::MapEntry::MapEntry(HWND *key, void(*func)()){
		this->key = key;
		this->func = func;
		this->next = EmptyMapEntry();
	}
	WindowManager::MapEntry::MapEntry(){
		this->key = '\0';
		this->func = '\0';
		this->next = EmptyMapEntry();
	}
	void WindowManager::MapEntry::run(){
		func();
	}
	WindowManager::MapEntry WindowManager::MapEntry::addValue(HWND *key, void (*func)()){
		MapEntry temp = MapEntry(key, func);
		return temp;
	}
	WindowManager::MapEntry::~MapEntry(){
		key = '\0';
		func = NULL;
	}
//	WNDPROC CALLBACK WindowManager::onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
//		switch (message)
//			{
//				// Quit when we close the main window
//				case WM_CLOSE:
//				{
//					PostQuitMessage(0);
//					break;
//				}
//				case WM_COMMAND:{
//					for(MapEntry b : button){
//						if(*(b.key) == reinterpret_cast<HWND>(lParam)){
//							b.run();
//						}
//					}
//				}
//			}
//	}
	WindowManager::Component::Component(){
		window = NULL;
		instance = NULL;
	}
	WindowManager::Component::Component(HWND window, HINSTANCE instance){
		this->window = window;
		this->instance = instance;
	}
	HWND WindowManager::Component::generateButton(char* title, int posX, int posY, int width, int height){
		return CreateWindow(TEXT("BUTTON"), TEXT(title), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
	}
	HWND WindowManager::Component::generateView(int posX, int posY, int width, int height){
		return CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, posX,  posY, width, height, window, NULL, instance, NULL);
	}
	WindowManager::WindowManager(const char* title, int posX, int posY, int width, int height) {
		instance = GetModuleHandle(NULL);
		// Define a class for our main window
		WNDCLASS windowClass;
		windowClass.style         = 0;
		windowClass.lpfnWndProc   = &onEvent;
		windowClass.cbClsExtra    = 0;
		windowClass.cbWndExtra    = 0;
		windowClass.hInstance     = instance;
		windowClass.hIcon         = NULL;
		windowClass.hCursor       = 0;
		windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
		windowClass.lpszMenuName  = NULL;
		windowClass.lpszClassName = TEXT("SFML App");
		RegisterClass(&windowClass);

		// Let's create the main window
		window = CreateWindow(TEXT("SFML App"), TEXT(title), WS_SYSMENU | WS_VISIBLE, posX, posY, width, height, NULL, NULL, instance, NULL);
		component = Component(window, instance);
		// Create a clock for measuring elapsed time
		sf::Clock clock;

		// Loop until a WM_QUIT message is received
	}
	void WindowManager::end(){
		UnregisterClass(TEXT("SFML App"), instance);
		DestroyWindow(window);
	}

	void WindowManager::registerButton(HWND *button, void(*func)()){
		if(button == NULL)
			this->button = MapEntry(button, func);
		else
			this->button = this->button.addValue(button, func);
		buttonCount++;
	}
	WindowManager::~WindowManager() {
	}
	int main(){
		//Se crea la ventana
		WindowManager window("Test", 0, 0, 1000, 1000);
		//Se crea una ventana de render (un container dentro de la ventana donde se pueden meter sprites)
		sf::RenderWindow SFMLView1(window.component.generateView(0, 100, 1000, 900));
		//Se muetra
		SFMLView1.display();
		//Esto representa un circulo
		sf::CircleShape shape(100.f);
		//Se define la cantidad de vertices
		shape.setPointCount(128);
		//El color a rellenar el circulo
		shape.setFillColor(sf::Color::Green);
		//Objeto que recoge los eventos de la ventana
		float x = 0;
		float y = 0;
		float v = 1;
		MSG message;
		//Reloj para calcular el deltatime y tiempo transcurrido
		sf::Clock clock;
		message.message = static_cast<UINT>(~WM_QUIT);
		while (message.message != WM_QUIT)
			//Aqui busca los eventos no recogidos
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
				TranslateMessage(&message);
				DispatchMessage(&message);
			} else{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x != -1)
					x = 1;
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x != 1)
					x = -1;
				else
					x = 0;
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y != -1)
					y = 1;
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y != 1)
					y = -1;
				else
					y = 0;
				shape.setOrigin(sf::Vector2<float>(shape.getOrigin().x + x*v, shape.getOrigin().y + y*v));
				SFMLView1.clear();
				SFMLView1.draw(shape);
				SFMLView1.display();
	        }

	}
