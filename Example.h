/*
 * example.h
 *
 *  Created on: 5 may 2022
 *      Author: algtc
 */

#ifndef EXAMPLE_H_
#define EXAMPLE_H_
#include "WindowObjects/Window.h"

#include <windows.h>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
class Example: public Window {
public:
	Example(){};
	virtual void start();
	virtual void update();
	virtual void onButtonPress(HWND button);
	virtual ~Example(){};
private:
	sf::RenderWindow SFMLView1;
	HWND blue;
	HWND red;
	HWND green;
	HWND next;
	HWND view;
	HWND textField;
	HWND textButton;
	float x = 0;
	float y = 0;
	float v = 1;
	sf::CircleShape shape = sf::CircleShape(100.f);
};


#endif /* EXAMPLE_H_ */
