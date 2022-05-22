/*
 * WindowManager.h
 * Esta clase simplifica las interacciones con SFML
 *  Created on: 3 may 2022
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <windows.h>
#include <list>
class Window;
class WindowManager {
	public:
		WindowManager(){
			window = '\0';
		}
		/** Genera una ventana de SFML con el título definido
		 * 	title -> Titulo de la ventana
		 */
		WindowManager(const char* title, int posX, int posY, int width, int height, Window *window);
		~WindowManager(){

		}
		/**
		 * Esta clase contiene los generadores de los elementos de SFML
		 */
		void runButton(HWND button);
		void setWindow(Window *w);
		struct Dimension{
			int x;
			int y;
		};
		void startTCPServer();
		void startTCPClient(sf::IpAddress ip);
		void stopConnection();
		Dimension getWindowSize();
		void repaint();
		void sendMessage(const char* message);
		class TCPConnectionHandler {
			public:
				TCPConnectionHandler(){
					ip = "127.0.0.0";
					port = 50001;
					client = true;
				}
				TCPConnectionHandler(sf::IpAddress ip, long long port);
				void main();
				std::list<const char*> pendingMessages;
				std::list<char*> receivedMessages;
				sf::IpAddress ip;
			private:

				int port;
				bool client;
		};
	protected:
	private:
		HWND window;
		HINSTANCE instance = GetModuleHandle(NULL);
};
#endif /* WINDOWMANAGER_H_ */
