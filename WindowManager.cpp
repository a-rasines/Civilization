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

	WindowManager::MapEntry::MapEntry(HWND *key, void(*func)()){
		this->key = key;
		this->func = func;
	}
	void WindowManager::MapEntry::run(){
		func();
	}
	virtual WindowManager::MapEntry::~MapEntry(){
		key = '\0';
		func = NULL;
	}
	void WindowManager::onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
		switch (message)
			{
				// Quit when we close the main window
				case WM_CLOSE:
				{
					PostQuitMessage(0);
					break;
				}
				case WM_COMMAND:{
					for(MapEntry b : button){
						if(b.key == reinterpret_cast<HWND>(lParam)){
							b.run();
						}
					}
				}
			}
	}
	WindowManager::Component::Component(HWND window){
		this->window = window;
	}
	HWND WindowManager::Component::generateButton(char* title, int posX, int posY, int width, int height){
		return CreateWindow(TEXT("BUTTON"), TEXT(title), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
	}
	WindowManager::WindowManager(char* title) {
		button = NULL;
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
			component = new Component(window);
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
		if(button != NULL){
			MapEntry temp[] = new MapEntry[buttonCount+1];
			for(int i = 0; i < buttonCount; i++){
				temp[i] = button[i];
			}
			temp[buttonCount] = new MapEntry(button, func);
			button = temp;
			buttonCount++;
		}


		if(button == NULL){
			button = new MapEntry[1];
			button[0] = new MapEntry(button, func);
		}
	}
	WindowManager::~WindowManager() {
		// TODO Auto-generated destructor stub
	}
