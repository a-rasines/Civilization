/*
 * menuEjemplo.h
 *
 *  Created on: 12 may 2022
 *      Author: Marian
 */

#ifndef MENUEJEMPLO_H_
#define MENUEJEMPLO_H_

#include "WindowObjects/Window.h"
#include "usuario.h"
class menuEjemplo: public Window  {
public:
	static Usuario logeado;
	menuEjemplo();
	virtual ~menuEjemplo();
	virtual void start();
	virtual void update();
	virtual void onButtonPress(HWND button);//Esta funcion se llama cuando un boton sea pulsado
private:
	sf::Text text, text2, text3;
	HWND view;
	HWND client, server, startG, loadG, quitG, inicioS;
	HWND ip;
	HWND usuario;
	HWND contrasena;
	HWND textButton, textButton2;
	sf::RenderWindow SFMLView1;
	HBITMAP hImage;
	static sf::Texture background;

};

#endif /* MENUEJEMPLO_H_ */
