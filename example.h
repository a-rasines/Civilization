/*
 * example.h
 *
 *  Created on: 5 may 2022
 *      Author: algtc
 */

#ifndef EXAMPLE_H_
#define EXAMPLE_H_
#include "window.h"

#include <windows.h>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>

class Example: public Window {
public:
	Example(){};
	void start();
	void update();
	void onButtonPress(HWND button);
	virtual ~Example(){};

};


#endif /* EXAMPLE_H_ */
