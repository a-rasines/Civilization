/*
 * menuEjemplo.h
 *
 *  Created on: 12 may 2022
 *      Author: Marian
 */

#ifndef MENUEJEMPLO_H_
#define MENUEJEMPLO_H_

#include "WindowObjects/Window.h"

class menuEjemplo: public Window  {
public:
	menuEjemplo();
	virtual ~menuEjemplo();
	virtual void start();
	virtual void update();
	virtual void onButtonPress(HWND button);//Esta funcion se llama cuando un boton sea pulsado
private:
	sf::Text text, text2;
	HWND view;
	HWND startG, loadG, quitG, inicioS;
	HWND usuario;
	HWND contrasena;
	HWND textButton;
	sf::RenderWindow SFMLView1;
	HBITMAP hImage;
	static sf::Texture background;

};

#endif /* MENUEJEMPLO_H_ */
