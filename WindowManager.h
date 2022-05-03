/*
 * WindowManager.h
 * Esta clase simplifica las interacciones con SFML
 *  Created on: 3 may 2022
 */

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_
#include <SFML/Graphics.hpp>
#include <windows.h>
namespace WindowInternals{
	class MapEntry{
		public:
			MapEntry(HWND *key, void(*func)());
			void run();
			virtual ~MapEntry();
		private:
			HWND *key;
			void(*func)();
	};
	typedef MapEntry MapEntry;
	class WindowManager {
		public:
			WindowManager(char* title);
			virtual ~WindowManager();
			void end();
			void registerButton(HWND *button, void(*func)());
		private:
			MapEntry button[] = new MapEntry[0];
			HWND window;
			HINSTANCE instance;
			int buttonCount = 0;
			void onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	};

}


#endif /* WINDOWMANAGER_H_ */
