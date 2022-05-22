/*
 * WindowManager.cpp
 *
 *  Created on: 3 may 2022
 *      Author: algtc
 */

#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include "Window.h"
#include "Fonts.h"
WindowManager *windowInstance;
Window *activeWindow;
WindowManager::TCPConnectionHandler tcpHandler;
sf::Thread *commThread;
int wWidth;
int wHeight;
LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
			// Quit when we close the main window
		case WM_CLOSE:{
			PostQuitMessage(0);
			break;
		}case WM_COMMAND:{
			activeWindow->onButtonPress(reinterpret_cast<HWND>(lParam));
			break;
		}case WM_PAINT:{
			windowInstance->repaint();
			break;
		}case WM_SIZE:{
			wWidth = LOWORD(lParam);
			wHeight = HIWORD(lParam);
			activeWindow->onResize(wWidth, wHeight);

		}
	}
	return DefWindowProc(handle, message, wParam, lParam);
}
MSG message;
WindowManager::WindowManager(const char* title, int posX, int posY, int width, int height, Window *window) {
	wWidth = width;
	wHeight = height;
	activeWindow = window;
	instance = GetModuleHandle(NULL);
	windowInstance = this;
	// Define a class for our main window
	WNDCLASS windowClass;
	windowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc   = &onEvent;
	windowClass.cbClsExtra    = 0;
	windowClass.cbWndExtra    = 0;
	windowClass.hInstance     = instance;
	windowClass.hIcon         = NULL;
	windowClass.hCursor       = 0;
	windowClass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	windowClass.lpszMenuName  = NULL;
	windowClass.lpszClassName = TEXT("SFML App");
	RegisterClass(&windowClass);
	// Let's create the main window
	this->window = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, TEXT("SFML App"), TEXT(title), WS_SYSMENU | WS_VISIBLE, posX, posY, width, height, NULL, NULL, instance, NULL);
	//Reloj para calcular el deltatime y tiempo transcurrido
	sf::Clock clock;
	float timeElapsed = clock.getElapsedTime().asMilliseconds();
	message.message = static_cast<UINT>(~WM_QUIT);
	Window::instance = instance;
	Window::window = this->window;
	Fonts::load();
	window->start();
	while (message.message != WM_QUIT){
		//Aqui busca los eventos no recogidos
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		} else{
			float time = clock.getElapsedTime().asMilliseconds();
			activeWindow->deltatime = (-timeElapsed) + time;
			timeElapsed = time;
			if(tcpHandler.receivedMessages.size() != 0){
				activeWindow->onMessage(tcpHandler.receivedMessages.front());
				tcpHandler.receivedMessages.pop_front();
			}
			activeWindow->update();
		}
	}
	DestroyWindow(this->window);
	UnregisterClass(TEXT("SFML App"), instance);
	// Loop until a WM_QUIT message is received
}
void WindowManager::setWindow(Window *w){
	activeWindow->destroyComponents();
	activeWindow = w;
	activeWindow->start();
}
WindowManager::Dimension WindowManager::getWindowSize(){
	return (WindowManager::Dimension){wWidth, wHeight};
}
WindowManager::TCPConnectionHandler::TCPConnectionHandler(sf::IpAddress ip, long long port){
	this->ip = ip;
	this->port = port;
	client = false;
}
void WindowManager::TCPConnectionHandler::main(){
	bool lastMessage;
	sf::TcpSocket socket;
	if(client){
		sf::TcpListener listener;
		if (listener.listen(port) != sf::Socket::Done || listener.accept(socket) != sf::Socket::Done)return;
		pendingMessages.push_back("Connected");
		lastMessage = false;
	}else{
		if (socket.connect(ip, port) != sf::Socket::Done)
			return;
		lastMessage = true;
	}
	while(true){
		if(pendingMessages.size() != 0 && !lastMessage){ //Si no hay mensaje que mandar o no ha recibido respuesta no se ejecuta
				char* msg = (char*)pendingMessages.front();
				std::cout << msg << "\n";
				pendingMessages.pop_front();
			if (socket.send(msg, 128) != sf::Socket::Done)
				return;
			lastMessage = true;
		}
		if(lastMessage){ //Si ha mandado un mensaje espera la respuesta
			char in[128];
			std::size_t received;
			if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
				return;
			lastMessage = false;
			receivedMessages.push_back(in);
		}
		sf::sleep(sf::milliseconds(1000));
	}
}
void WindowManager::sendMessage(const char* message){
	tcpHandler.pendingMessages.push_back((char*)message);
}
void WindowManager::startTCPServer(){
	commThread = new sf::Thread(&TCPConnectionHandler::main, &tcpHandler);
	commThread->launch();

}
void WindowManager::stopConnection(){
	commThread->terminate();
}
void WindowManager::startTCPClient(sf::IpAddress ip){
	tcpHandler = TCPConnectionHandler(ip, 50001);
	commThread = new sf::Thread(&TCPConnectionHandler::main, &tcpHandler);
	commThread->launch();

}
void WindowManager::repaint(){
	PAINTSTRUCT ps;
	BeginPaint( window, &ps);
	EndPaint( window, &ps );
}
