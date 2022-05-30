/*
 * MapWindow.cpp
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#include "MapWindow.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "MapHolder.h"
float MapWindow::x;
float MapWindow::y;
int MapWindow::zoom;
using namespace std;
sf::Texture MapWindow::background;
MapWindow::MapWindow() {
	x = 0;
	y = 0;
	zoom = 5;
	lastMovement = 0;
}
void MapWindow::troopMove(TropaInst *toca, int x, int y){
	if(posibleMove(*toca,x,y)){
		toca->posicionX=x;
		toca->posicionY=y;
	}
}
bool MapWindow::posibleMove(TropaInst t ,int x, int y){
	return foreground[y][x].allowedTroops->isAllowed(t.data.type);
}
void MapWindow::guardarTropas(const char* fileName){
	fstream file_out;
	file_out.open(fileName);
	if(!file_out.is_open()){
		cout<<"No se ha podido abrir el fichero"<< fileName<<"\n";
	}else{
		for(TropaInst tr: activeTroops){
			file_out << tr.idServidor+','+tr.idJugador+','+tr.idTropa+
					','+tr.estado+','+tr.mejorada+','+tr.posicionX+
					','+tr.posicionY+','+tr.tipo+','+tr.vida+'\n'<< endl;
			cout <<"Escritura terminada"<< endl;
		}
	}

}
void MapWindow::cargarTropas(const char* fileName){
	ifstream file;
	file.open(fileName);
	for(std::string line;getline(file,line);){
		int numeros[10];
		int index = 0;
		for(char n: line){
			if(n!=','||n!='\n'){
				int number = n-'0';
				numeros[index] = n;
			}
			index++;
		}
		TropaInst t = {numeros[0],numeros[1],numeros[2],numeros[3],numeros[4],numeros[5],numeros[6],numeros[7],numeros[8]};
		activeTroops.push_back(t);
	}
}
void MapWindow::start(){
	cargarTropas("resources/troopSave.dat");
	WindowManager::Dimension size = Window::manager->getWindowSize();
	mapView.create(generateView(0, 0, size.x, size.y));
	setResizable(true);
	std::string file = "resources/" + (std::string)RIVER.file;
	background.loadFromFile(file, sf::IntRect(RIVER.textureX, RIVER.textureY, RIVER.sizeX, RIVER.sizeY));
	TropaInst t1 = {0, 0, 0, 1, 5, 5};
	TropaInst t2 = {0, 0, 1, 16, 18,18};
	activeTroops.push_back(t1);
	activeTroops.push_back(t2);
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
	for(TropaInst t: activeTroops){
		sf::Texture tex;
		sprite::TroopData coso = sprite::Troop[t.tipo];
		tex.loadFromFile("resources/SP257.PIC_256.gif",sf::IntRect(coso.textureX,coso.textureY,coso.sizeX,coso.sizeY));
		sf::RectangleShape rect;
		rect.setTexture(&tex, false);
		rect.setSize(sf::Vector2f(coso.sizeX*zoom, coso.sizeY*zoom));
		rect.setPosition(sf::Vector2f(t.posicionX*16*zoom-x, t.posicionY*16*zoom-y));
		mapView.draw(rect);
	}
	mapView.display();
}
void MapWindow::reposition(int x, int y){
	this->x=x;
	this->y=y;
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
		}	}
}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
void MapWindow::onKeyDown(int keycode){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
	   sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
	   sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
	   sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		TropaInst troop = activeTroops.front();
		troopMove(&troop,
			troop.posicionX + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
			troop.posicionY + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		);
		Window::manager->sendMessage("tropa a posicion:("+troop.posicionX+","+troop.posicionY+")");
		activeTroops.remove(troop);
		activeTroops.push_back(troop);
		troop = activeTroops.front();
		reposition((troop.posicionX-7)*16*zoom, (troop.posicionY-6)*16*zoom);
	}
}
MapWindow::~MapWindow() {}

/*int main(){
	Window::manager = new WindowManager("Civilization", 1200, 1000, new MapWindow());
}
*/
