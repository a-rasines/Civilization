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

namespace WindowInternals{
	MapEntry::MapEntry(HWND key, void(*func)()){
		this->key = key;
		this->func = func;
	}
	void MapEntry::run(){
		func();
	}
	virtual MapEntry::~MapEntry(){
		key = '\0';
		func = NULL;
	}
	void(& func)();
	void WindowManager::onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
		switch (message)
			{
				// Quit when we close the main window
				case WM_CLOSE:
				{
					PostQuitMessage(0);
					break;
				}

				// Quit when we click the "quit" button
				case WM_COMMAND:
				{
					if (reinterpret_cast<HWND>(lParam) == button)
					{
						PostQuitMessage(0);
						break;
					}
				}
			}
	}
	WindowManager::WindowManager(char* title) {
		button = new MapEntry(0);
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


	WindowManager::~WindowManager() {
		// TODO Auto-generated destructor stub
	}
}
