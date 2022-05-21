/*
 * MapWindow.cpp
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#include "MapWindow.h"
#include <cstdio>
#include "MapHolder.h"
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
	setResizable(true);
}
void MapWindow::update(){
}
int count = 0;
void MapWindow::reposition(float x, float y){
	WindowManager::Dimension size = Window::manager->getWindowSize();
	activeCells.clear();
	sf::Texture tex;
	count++;
	y = -y;
	for(TerrainType row[100] : foreground){
		std::list<sf::RectangleShape> rowList = std::list<sf::RectangleShape>();
		y += row[0].sizeY;
		if(y >= size.y)break;
		else if(y<0)continue;
		int cx = -x;
		for(TerrainType cell : row){
			cx += cell.sizeX;
			if(cx >= size.x)break;
			else if(cx<0)continue;
			std::string file = "resources/" + (std::string)cell.file;
			tex.loadFromFile(file, sf::IntRect(cell.textureX, cell.textureY, cell.sizeX, cell.sizeY));
			sf::RectangleShape rect(sf::Vector2f(cell.sizeX*zoom, cell.sizeY*zoom));
			rect.setTexture(&tex, false);

		}
		activeCells.push_back(rowList);
	}
	std::cout << count << "\n";
}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
MapWindow::~MapWindow() {}

int main(){
	Window::manager = new WindowManager("S", 0, 0, 1200, 1000, new MapWindow());
}
