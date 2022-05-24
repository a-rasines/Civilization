/*
 * MapWindow.h
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#ifndef MAPWINDOW_H_
#define MAPWINDOW_H_
#include "WindowObjects/Window.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <list>
#include "Sprite.h"
#include "tropa.h"
#include"Ejemplo2.h"
class MapWindow : public Window{
public:
	MapWindow();
	void troopMove(Tropa t, int x, int y);
	bool posibleMove(Tropa t,int x, int y);
	void start(); //Esta funcion se llama al cambiar de pantalla
	void update();//Esta funcion se llama cada vez que de una vuelta al bucle
	void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
	void reposition(int x, int y);//Se llama para mover el mapa
	void onResize(int newWidth, int newHeight);//Esta funcion se llama cuando la ventana cambia de tamaño
	struct Cell{
		int posX;
		int posY;
		int sizeX;
		int sizeY;
		std::string file;
		sf::IntRect texData;

	};
	struct TropaDos : public Tropa{
		bool operator == (Tropa t){
			return idTropa==t.idTropa;
		}
	};
	virtual ~MapWindow();
	static int zoom;
private:
	sf::RenderWindow mapView;
	static float x;
	static float y;
	std::vector<Cell> activeCells;
	std::list<TropaDos> activeTroops;
	static sf::Texture background;
};

#endif /* MAPWINDOW_H_ */
