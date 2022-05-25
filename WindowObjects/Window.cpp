/*
 * Window.cpp
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */
#include "Window.h"
#include "CommCtrl.h"
#include "string.h"
#include <list>
#include "windowsx.h"
HINSTANCE Window::instance;
HWND Window::window;
WindowManager* Window::manager;
std::list<HWND> components;
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
HWND Window::generateTextField(const char* text, int posX, int posY, int width, int height){
	HWND comp = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(text), WS_CHILD | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
	components.push_back(comp);
	return comp;
}
HWND Window::generateTextField(int posX, int posY, int width, int height){
	return generateTextField("", posX, posY, width, height);
}
HWND Window::generateComboBox(int posX, int posY, int width, int height, std :: initializer_list <const char*> values){
	HWND comp = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, posX, posY, width, height, window, NULL, instance, NULL);
	for(const char* str : values)
		ComboBox_AddItemData(comp, str);
	components.push_back(comp);
	return comp;
}
void Window::removeComponent(HWND comp){
	DestroyWindow(comp);
	components.remove(comp);
}
void Window::destroyComponents(){
	for(HWND comp : components){
		DestroyWindow(comp);
	}
	components.clear();
}
void Window::setResizable(bool resizable){
	if(resizable)
		SetWindowLongPtr(window, GWL_STYLE,  WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_VISIBLE);
	else
		SetWindowLongPtr(window, GWL_STYLE,  WS_SYSMENU | WS_VISIBLE);
}
void Window::move(int x, int y){
	WindowManager::Dimension d = this->manager->getWindowSize();
	SetWindowPos(this->window, NULL, x, y, d.x, d.y, SWP_DRAWFRAME);
}
void Window::resize(int width, int height){
	WindowManager::Dimension d = this->manager->getWindowPosition();
	SetWindowPos(this->window, NULL, d.x, d.y, width, height, SWP_DRAWFRAME);
}
void Window::resize(int width, int height, int x, int y){
	SetWindowPos(this->window, NULL, x, y, width, height, SWP_DRAWFRAME)
}
char* Window::getComponentText(HWND component){
	char* text = new char[GetWindowTextLengthA(component)+1];
	GetWindowTextA(component, text, GetWindowTextLengthA(component)+1);
	return text;
}


