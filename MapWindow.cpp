/*
 * MapWindow.cpp
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#include "MapWindow.h"
#include <cstdio>
float MapWindow::x;
float MapWindow::y;
MapWindow::MapWindow() {
	x = 0;
	y = 0;
}
//int MapWindow::x;
//int MapWindow::y;
void MapWindow::start(){
	WindowManager::Dimension size = Window::manager->getWindowSize();
	mapView.create(generateView(0, 0, size.x, size.y));
	reposition(x, y);
	setResizable(true);
}
void MapWindow::update(){
}
void MapWindow::reposition(float x, float y){
	WindowManager::Dimension size = Window::manager->getWindowSize();
	for(int x = 0; x <= size.x; x++){
			for(int y = 0; y <= size.y; y++){

			}
		}

}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
MapWindow::~MapWindow() {}

int main(){
	Window::manager = new WindowManager("S", 0, 0, 1200, 1000, new MapWindow());
}
