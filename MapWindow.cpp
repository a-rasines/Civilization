/*
 * MapWindow.cpp
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#include "MapWindow.h"

#include <SFML/Graphics.hpp>

#include <windef.h>
#include <cmath>
#include <cstdio>

#include "menuEjemplo.h"
#include "MapHolder.h"
#include "SocketMessageHolder.h"

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
	file_out.open(fileName,fstream::out);
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
				numeros[index] = number;
			}
			index++;
		}
		TropaInst t = {numeros[0],numeros[1],numeros[2],numeros[3],numeros[4],numeros[5],numeros[6],numeros[7],numeros[8]};
		activeTroops.push_back(t);
	}
}
float MapWindow::round(float number, int decimals){
	number *= pow(10, decimals);
	number -= remainder(number, 1) * (-(number < 0) + (number >= 0));
	return number / pow(10, decimals);

}

void MapWindow::reposition(int x, int y){
	this->x=x;
	this->y=y;
	std::cout << x << ":" << y << "\n";
	WindowManager::Dimension size = Window::manager->getWindowSize();
	activeCells.clear();

//	int cell0x = (x - size.x / 2) / (zoom * foreground[0][0].sizeX);
//	int cell0x0 = cell0x;
//	int cell0y = (y - size.y / 2) /(zoom * foreground[0][0].sizeY);
//	int posX = ((x-size.x/2) % (zoom * foreground[0][0].sizeX));
//	int posX0 = posX;
//	int posY = ((y - size.y/2) % (zoom * foreground[0][0].sizeY));
//	std::cout << "position " << x << ":" << y << " first cell " << cell0x << ":" << cell0y << " cellPosition " << posX << ":" << posY << "\n";
//	while(posY <= size.y + zoom * foreground[0][0].sizeY){
//		std::cout << "posy = " << posY << " " << size.y + zoom * foreground[0][0].sizeY <<"\n";
//		while(posX <= size.x + zoom * foreground[0][0].sizeX){
//			std::cout << ((cell0y+50)%50) << " " << ((cell0x+80)%80) << "\n";
//			TerrainType cell = foreground[(cell0y+50)%50][(cell0x+80)%80];
//			activeCells.push_back((Cell){
//				posX,
//				posY,
//				cell.sizeX * zoom,
//				cell.sizeY * zoom,
//				cell.file,
//				sf::IntRect(
//						cell.textureX,
//						cell.textureY,
//						cell.sizeX,
//						cell.sizeY
//					)
//				}
//			);
//			cell0x++;
//			posX += zoom * foreground[0][0].sizeX;
//
//		}
//		cell0x = cell0x0;
//		posX = posX0;
//		cell0y++;
//		posY += zoom * foreground[0][0].sizeY;
//	}
//	std::cout << activeCells.size() << "\n";

	y = -y;
	for(TerrainType row[80] : foreground){
		y += row[0].sizeY * zoom;
		if(y<0)continue;
		else if(y >= size.y + row[0].sizeY * zoom){
			y -= 50 * row[0].sizeY * zoom;
			continue;
		}
		int cx = -x;
		for(TerrainType cell : row){
			cx += cell.sizeX * zoom;
			std::cout << cx << "\n";
			if(cx<0)continue;
			else if(cx >= size.x + cell.sizeX * zoom){
				cx -= 80 * cell.sizeX * zoom;
				std::cout << "reset " << cx << "\n";
				continue;
			}
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
MapWindow::~MapWindow() {}

void MapWindow::TropaInst::keyPress(int keycode, MapWindow *mw){
	switch (keycode){
	case ' ': //NO ORDERS --Skip
		mw->troopMove(this, x, y);
		break;
	case 'w': //WAIT --Put to the back of the player's troop queue
		MapWindow::TropaInst actual = mw->activeTroops[0];

		mw->manager->sendMessage(message::action(Action::WAIT));
	case 's': //SENTRY --No orders wanted

	case 'P': //PILLAGE --Destroy whatever is in that cell

	case 'D': //DISBAND --Delete the troop
		mw->activeTroops.erase(mw->activeTroops.begin());
	}
}
void MapWindow::SettlerInst::keyPress(int keycode, MapWindow *mw){
	TropaInst::keyPress(keycode, mw);
	switch (keycode){
		case 'b': //BUILD CITY

		case 'r': //BUILD ROAD

		case 'm': //BUILD FOREST

		case 'f': //BUILD FORTRESS
			break;
	}
}
/*int main(){
	Window::manager = new WindowManager("Civilization", 1200, 1000, new MapWindow());
}
*/
