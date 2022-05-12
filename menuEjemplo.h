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
private:
	sf::Text text;
	HWND view;
	sf::RenderWindow SFMLView1;
};

#endif /* MENUEJEMPLO_H_ */
