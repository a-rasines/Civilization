/*
 * Fonts.cpp
 *
 *  Created on: 12 may 2022
 *      Author: algtc
 */

#include "Fonts.h"
sf::Font Fonts::ARIAL;
void Fonts::load(){
	Fonts::ARIAL.loadFromFile("Fonts/ARIAL.TTF");
}
