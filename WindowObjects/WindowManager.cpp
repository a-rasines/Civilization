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
#include "windowsx.h"
#include "Fonts.h"
sf::Mutex GlobalMutex;
WindowManager *windowInstance;
Window *activeWindow;
WindowManager::TCPConnectionHandler tcpHandler;
sf::Thread *commThread;
WindowManager::Dimension wm_size;
WindowManager::Dimension wm_position;
bool isClient = false;
bool isServer = false;
LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
			// Quit when we close the main window
		case WM_CLOSE:
			activeWindow->onClose();
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			if(std::find(activeWindow->menuid.begin(), activeWindow->menuid.end(), LOWORD(wParam))!= activeWindow->menuid.end())
				activeWindow->onMenu(LOWORD(wParam));
			activeWindow->onButtonPress(reinterpret_cast<HWND>(lParam));
			break;
		case WM_PAINT:
			windowInstance->repaint();
			break;
		case WM_SIZE:
			wm_size.x = LOWORD(lParam);
			wm_size.y = HIWORD(lParam);
			activeWindow->onResize(wm_size.x, wm_size.y);
			break;
		case WM_KEYDOWN:
			activeWindow->onKeyDown(wParam);
			break;
		case WM_KEYUP:
			activeWindow->onKeyUp(wParam);
			break;
		case WM_MBUTTONDOWN:
			activeWindow->onMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		case WM_MBUTTONUP:
			activeWindow->onMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
	}
	return DefWindowProc(handle, message, wParam, lParam);
}
MSG message;
WindowManager::WindowManager(const char* title, int posX, int posY, int width, int height, Window *window) {
	wm_size.x = width;
	wm_size.y = height;
	wm_position.x = posX;
	wm_position.y = posY;
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
			GlobalMutex.lock();
			if(tcpHandler.receivedMessages.size() != 0){
				std::cout.flush();
				activeWindow->onMessage(tcpHandler.receivedMessages.front());
				tcpHandler.receivedMessages.pop_front();
			}
			GlobalMutex.unlock();
			activeWindow->update();
		}
	}

	DestroyWindow(this->window);
	UnregisterClass(TEXT("SFML App"), instance);
	// Loop until a WM_QUIT message is received
}
WindowManager::WindowManager(const char* title, int width, int height, Window *window){
	this->window = '\0';//Esta linea es solo para cargarme el warning de que no esta inicializada
	new (this) WindowManager(title, (sf::VideoMode::getDesktopMode().width-width)/2, (sf::VideoMode::getDesktopMode().height-height)/2, width, height, window);
}
void WindowManager::setWindow(Window *w){
	activeWindow->destroyComponents();
	activeWindow->destroyMenu();
	activeWindow = w;
	activeWindow->start();
	if(isClient){
		activeWindow->onClientStart();
	}else if(isServer){
		activeWindow->onServerStart();
	}
}
WindowManager::Dimension WindowManager::getWindowSize(){
	return wm_size;
}
WindowManager::Dimension WindowManager::getWindowPosition(){
	return wm_position;
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
		std::cout << "Starting listener\n";
		if (listener.listen(port) != sf::Socket::Done || listener.accept(socket) != sf::Socket::Done){
			std::cout.flush();
			std::cout << "Error starting server";
			return;
		}
		std::cout.flush();
		std::cout << "Listening port " << port << "\n";
		lastMessage = true;
	}else{
		std::cout << "Connecting to " << ip << ":" << port << "\n";
		if (socket.connect(ip, port) != sf::Socket::Done)
			return;
		std::cout << "Connected\n";
		lastMessage = false;
	}
	while(true){
		if(pendingMessages.size() != 0 && !lastMessage){ //Si no hay mensaje que mandar o no ha recibido respuesta no se ejecuta
			GlobalMutex.lock();
			std::cout << "sending= " << pendingMessages.front();
			sf::Socket::Status status = socket.send(pendingMessages.front().c_str(), 128);
			if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
				return;
			pendingMessages.pop_front();
			lastMessage = true;
			GlobalMutex.unlock();
		}
		if(lastMessage){ //Si ha mandado un mensaje espera la respuesta
			char in[128];
			std::size_t received;
			if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
				return;
			lastMessage = false;
			std::cout << " received " << in << "\n";
			GlobalMutex.lock();
			receivedMessages.push_back(in);
			GlobalMutex.unlock();
		}
		sf::sleep(sf::milliseconds(10));
	}
}
void WindowManager::sendMessage(const char* message){
	GlobalMutex.lock();
	std::cout << "frontsize= " << tcpHandler.pendingMessages.size() << ", newMessage=" << message << "\n";
	tcpHandler.pendingMessages.push_back(std::string(message));
	GlobalMutex.unlock();
}
void WindowManager::startTCPServer(){
	commThread = new sf::Thread(&TCPConnectionHandler::main, &tcpHandler);
	commThread->launch();
	activeWindow->onServerStart();
	isServer = true;
}

void WindowManager::stopConnection(){
	commThread->terminate();
}
void WindowManager::startTCPClient(sf::IpAddress ip){
	tcpHandler = TCPConnectionHandler(ip, 50001);
	commThread = new sf::Thread(&TCPConnectionHandler::main, &tcpHandler);
	commThread->launch();
	isClient = true;
	activeWindow->onClientStart();
}
void WindowManager::repaint(){
	PAINTSTRUCT ps;
	BeginPaint( window, &ps);
	EndPaint( window, &ps );
}
