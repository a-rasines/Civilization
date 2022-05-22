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
int MapWindow::zoom;
sf::Texture MapWindow::background;
MapWindow::MapWindow() {
	x = 0;
	y = 0;
	zoom = 5;
}
void MapWindow::start(){
	WindowManager::Dimension size = Window::manager->getWindowSize();
	mapView.create(generateView(0, 0, size.x, size.y));
	setResizable(true);
	std::string file = "resources/" + (std::string)RIVER.file;
	background.loadFromFile(file, sf::IntRect(RIVER.textureX, RIVER.textureY, RIVER.sizeX, RIVER.sizeY));
}
void MapWindow::update(){
	mapView.clear();
	for(Cell cell : activeCells){
		sf::Texture tex;
		std::string file = "resources/" + (std::string)cell.file;
		tex.loadFromFile(file, cell.texData);
		sf::RectangleShape rect;
		rect.setTexture(&background, false);
		rect.setSize(sf::Vector2f(cell.sizeX, cell.sizeY));
		rect.setPosition(sf::Vector2f(cell.posX, cell.posY));
		mapView.draw(rect);
		rect.setTexture(&tex, false);
		mapView.draw(rect);

	}
	mapView.display();

}
void MapWindow::reposition(int x, int y){
	WindowManager::Dimension size = Window::manager->getWindowSize();
	activeCells.clear();
	y = -y;
	for(TerrainType row[100] : foreground){
		y += row[0].sizeY * zoom;
		if(y >= size.y + row[0].sizeY * zoom)break;
		else if(y<0)continue;
		int cx = -x;
		for(TerrainType cell : row){
			cx += cell.sizeX * zoom;
			if(cx >= size.x + cell.sizeX * zoom)break;
			else if(cx<0)continue;
			activeCells.push_back((Cell){
				cx-cell.sizeX*zoom,
				y-cell.sizeY*zoom,
				cell.sizeX * zoom,
				cell.sizeY * zoom,
				cell.file,
				sf::IntRect(
						cell.textureX,
						cell.textureY,
						cell.sizeX,
						cell.sizeY
					)
				}
			);
		}
	}
}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
MapWindow::~MapWindow() {}

//int main(){
//	Window::manager = new WindowManager("S", 0, 0, 1200, 1000, new MapWindow());
//}
