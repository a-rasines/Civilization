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
	LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
		switch (message){
				// Quit when we close the main window
				case WM_CLOSE:{
				PostQuitMessage(0);
				break;
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
		WindowManager window("Test", 0, 0, 1000, 1000);
		sf::RenderWindow SFMLView1(window.component.generateView(0, 100, 100, 100));
		SFMLView1.display();

		MSG message;
		message.message = static_cast<UINT>(~WM_QUIT);
		printf("Starts");
		while (message.message != WM_QUIT)
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
				TranslateMessage(&message);
				DispatchMessage(&message);
			}

	}
