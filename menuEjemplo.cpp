/*
 * menuEjemplo.cpp
 *
 *  Created on: 12 may 2022
 *      Author: Marian
 */

#include "menuEjemplo.h"
#include "Example.h"
#include <SFML/Graphics.hpp>
#include "WindowObjects/Fonts.h"

menuEjemplo::menuEjemplo() {

}

menuEjemplo::~menuEjemplo() {

}

void menuEjemplo::start(){
	view = generateView(0, 100, 1000, 900);
	SFMLView1.create(view);
	SFMLView1.display();
	text.setString("Hello world");
	text.setFont(Fonts::ARIAL);
	text.setCharacterSize(35);
	text.setPosition(20, 20);
	text.setFillColor(sf::Color::Yellow);

}

void menuEjemplo::update(){
	SFMLView1.clear();
	SFMLView1.draw(text);
	SFMLView1.display();
}
