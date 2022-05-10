/*
 * Window.cpp
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */
#include "Window.h"
#include <list>
HINSTANCE Window::instance;
HWND Window::window;
WindowManager* Window::manager;
std::list<HWND> components;
void Window::removeComponent(HWND comp){
	DestroyWindow(comp);
	components.remove(comp);
}
HWND Window::generateView(int posX, int posY, int width, int height){
	HWND comp = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, posX,  posY, width, height, window, NULL, instance, NULL);
	components.push_back(comp);
	return comp;
}
HWND Window::generateButton(const char* title, int posX, int posY, int width, int height){
	HWND comp = CreateWindow(TEXT("BUTTON"), TEXT(title), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
	components.push_back(comp);
	return comp;
}
void Window::destroyComponents(){
	for(HWND comp : components){
		DestroyWindow(comp);
	}
	components.clear();
}


