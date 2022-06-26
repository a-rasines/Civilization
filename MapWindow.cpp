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
#include "WindowObjects/WindowManager.h"

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
void MapWindow::onClientStart(){
	for(TropaInst tr : activeTroops)
		Window::manager->sendMessage((string("1Te envio tropa:"+to_string(tr.idServidor)+string(",")+to_string(tr.idJugador)+string(",")+to_string(tr.idTropa)+
				string(",")+to_string(tr.estado)+string(",")+to_string(tr.mejorada)+string(",")+to_string(tr.posicionX)+
				string(",")+to_string(tr.posicionY)+string(",")+to_string(tr.tipo)+string(",")+to_string(tr.vida))).c_str());
	Window::manager->sendMessage("2Terminado envio de tropas");
	activeTroops.clear();
}
void MapWindow::onMessage(char* message){
	if(message[0]=='0'){
		int x,y;
		sscanf(message,"0tropa a posicion:(%i,%i)",&x,&y);
		if(activeTroops.front().idJugador!=menuEjemplo::logeado.id){
			TropaInst actual = activeTroops.front();
			troopMove(&activeTroops.front(), x, y);
			activeTroops.erase(activeTroops.begin());
			activeTroops.push_back(actual);
			if(activeTroops.front().idJugador!=menuEjemplo::logeado.id){
				Window::manager->sendMessage("ACK");
			}
		}
	}else if(message[0]=='1'){
		int a,b,c,d,e,f,g,h,i;
		sscanf(message,"1Te envio tropa:%i,%i,%i,%i,%i,%i,%i,%i,%i",&a,&b,&c,&d,&e,&f,&g,&h,&i);
		TropaInst t = {a,b,c,d,e,f,g,h,i};
		activeTroops.push_back(t);
		Window::manager->sendMessage("ACK");
	}else if(message[0]=='2'){
		for(TropaInst tr : activeTroops)
			Window::manager->sendMessage((string("1Te envio tropa:"+to_string(tr.idServidor)+string(",")+to_string(tr.idJugador)+string(",")+to_string(tr.idTropa)+
			string(",")+to_string(tr.estado)+string(",")+to_string(tr.mejorada)+string(",")+to_string(tr.posicionX)+
			string(",")+to_string(tr.posicionY)+string(",")+to_string(tr.tipo)+string(",")+to_string(tr.vida))).c_str());
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
void MapWindow::start(){
	reposition(x, y);
	WindowManager::Dimension size = Window::manager->getWindowSize();
	mapView.create(generateView(0, 0, size.x, size.y));
	setResizable(true);
	std::string file = "resources/" + (std::string)RIVER.file;
	background.loadFromFile(file, sf::IntRect(RIVER.textureX, RIVER.textureY, RIVER.sizeX, RIVER.sizeY));
	TropaInst t1 = {0, menuEjemplo::logeado.id, 0, 1, 5, 5};
	TropaInst t2 = {0, menuEjemplo::logeado.id, 1, 16, 18,18};
	activeTroops.push_back(t1);
	activeTroops.push_back(t2);
}
float MapWindow::round(float number, int decimals){
	number *= pow(10, decimals);
	number -= remainder(number, 1) * (-(number < 0) + (number >= 0));
	return number / pow(10, decimals);

}
bool moving = false;
bool repos = false;
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
	moving = false;
	for(unsigned int i = 0; i < activeTroops.size(); i++){
		sf::Texture tex;
		TropaInst* t = &(activeTroops[i]);
		sprite::TroopData coso = sprite::Troop[t->tipo];
		tex.loadFromFile("resources/SP257.PIC_256.gif",sf::IntRect(coso.textureX,coso.textureY,coso.sizeX,coso.sizeY));
		sf::RectangleShape rect;
		rect.setTexture(&tex, false);
		rect.setSize(sf::Vector2f(coso.sizeX*zoom, coso.sizeY*zoom));
		if(t->renderingPositionX != t->posicionX || t->renderingPositionY != t->posicionY){
			moving = true;
			std::cout << "positionStatus: x= " << (t->renderingPositionX != t->posicionX) << ", y= " << (t->renderingPositionY != t->posicionY) << " real( x= " << t->posicionX << ", y= " << t->posicionY << "), rendering( x= " << t->renderingPositionX << ", y= " << t->renderingPositionY << ")\n";
			t->renderingPositionX = round(t->renderingPositionX + 0.2 * (t->renderingPositionX < t->posicionX) - 0.2 * (t->renderingPositionX > t->posicionX), 1);
			t->renderingPositionY = round(t->renderingPositionY + 0.2 * (t->renderingPositionY < t->posicionY) - 0.2 * (t->renderingPositionY > t->posicionY), 1);
			std::cout << "newRendering( x= " << t->renderingPositionX << ", y= " << t->renderingPositionY << ")\n";
		}
		rect.setPosition(sf::Vector2f(t->renderingPositionX*16*zoom-x, t->renderingPositionY*16*zoom-y));
		mapView.draw(rect);
	}
	if(!moving && repos){
		TropaInst troop = activeTroops.front();
		reposition((troop.posicionX-7)*16*zoom, (troop.posicionY-6)*16*zoom);
		repos = false;
	}
	mapView.display();
}

void MapWindow::onClose(){
	guardarTropas("resources/troopSave.dat");
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
		}
	}
}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
void MapWindow::onKeyDown(int keycode){
	if(activeTroops.front().idJugador==menuEjemplo::logeado.id && !moving && (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left))){
		TropaInst troop = activeTroops.front();
		troopMove(&troop,
			troop.posicionX + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
			troop.posicionY + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		);
		const char* messagea = (string("0tropa a posicion:(")+to_string(troop.posicionX)+string(",")+to_string(troop.posicionY)+string(")")).c_str();
		cout << "Movimiento: " << messagea << "\n";
		Window::manager->sendMessage(messagea);
		activeTroops.erase(activeTroops.begin());
		activeTroops.push_back(troop);
		repos = true;
	}
}
MapWindow::~MapWindow() {}

/*int main(){
	Window::manager = new WindowManager("Civilization", 1200, 1000, new MapWindow());
}
*/
