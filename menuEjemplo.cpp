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
#include <iostream>
using namespace std;
sf::Texture menuEjemplo::background;

menuEjemplo::menuEjemplo() {

}

menuEjemplo::~menuEjemplo() {

}

void menuEjemplo::start(){
	startG = generateButton("Start game", 250, 500, 500, 50);
	loadG = generateButton("Load game", 250, 600, 500, 50);
	quit = generateButton("Quit game", 250, 700, 500, 50);
	view = generateView(0, 0, 1000, 1000);
	SFMLView1.create(view);
	SFMLView1.display();
	//SFMLView1.setVisible(false);
	std::string file = "resources/LOGO.PIC_256.png";
	background.loadFromFile(file);
	text.setString("Hello world");
	text.setFont(Fonts::ARIAL);
	text.setCharacterSize(35);
	text.setPosition(20, 20);
	text.setFillColor(sf::Color::Yellow);

}

void menuEjemplo::update(){
	SFMLView1.clear();
	//SFMLView1.draw(text);
	sf::RectangleShape rect;
	rect.setTexture(&background, true);
	rect.setPosition(250,-100);
	rect.setSize( sf::Vector2f(500,500));
	SFMLView1.draw(rect);
	SFMLView1.display();
}

void menuEjemplo::onButtonPress(HWND button){
	if(button == startG) cout << "Hello World!";

}
/*int main(){
	Window::manager = new WindowManager("S", 0, 0, 1200, 1000, new menuEjemplo());
}*/
