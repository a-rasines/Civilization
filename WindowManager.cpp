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
		return 0;
	}
	MapEntry WindowManager::MapEntry::next;
	WindowManager::MapEntry::MapEntry(HWND *key, void(*func)()){
		this->key = key;
		this->func = func;
		this->next = empty;
	}
	WindowManager::MapEntry::MapEntry(){
		this->key = '\0';
		this->func = '\0';
		this->next = empty;
	}
	void WindowManager::MapEntry::run(){
		func();
	}
	WindowManager::MapEntry WindowManager::MapEntry::addValue(HWND *key, void (*func)()){
		MapEntry temp = MapEntry(key, func);
		temp.next = this;
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
	WindowManager::WindowManager(char* title) {
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
			window = CreateWindow(TEXT("SFML App"), TEXT(title), WS_SYSMENU | WS_VISIBLE, 200, 200, 660, 520, NULL, NULL, instance, NULL);
			component = Component(window, instance);
			// Create a clock for measuring elapsed time
			sf::Clock clock;

			// Loop until a WM_QUIT message is received
			MSG message;

			message.message = static_cast<UINT>(~WM_QUIT);
			while (message.message != WM_QUIT)
				if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
				{
					// If a message was waiting in the message queue, process it
					TranslateMessage(&message);
					DispatchMessage(&message);
				}

			// Destroy the main window (all its child controls will be destroyed)
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
		WindowManager window = WindowManager("Test");
		window.component.generateView(100, 100, 50, 50);
	}
