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
#include "Sprite.h"
#include"Ejemplo2.h"
class MapWindow : public Window{
public:
	MapWindow();
	void start(); //Esta funcion se llama al cambiar de pantalla
	void update();//Esta funcion se llama cada vez que de una vuelta al bucle
	void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
	void reposition(float x, float y);//Se llama para mover el mapa
	void onResize(int newWidth, int newHeight);//Esta funcion se llama cuando la ventana cambia de tamaño
	struct Cell{
		int posX;
		int posY;
		int sizeX;
		int sizeY;
		std::string file;
		sf::IntRect texData;

	};
	virtual ~MapWindow();
	static int zoom;
private:
	sf::RenderWindow mapView;
	static float x;
	static float y;
	std::vector<Cell> activeCells;
};

#endif /* MAPWINDOW_H_ */
