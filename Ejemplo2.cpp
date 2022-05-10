/*
 * Ejemplo2.cpp
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */
#include <SFML/Graphics.hpp>
#include "Ejemplo2.h"
#include "example.h"
sf::CircleShape shape(100.f);
float x = 0;
float y = 0;
float v = 1;
HWND blue;
HWND red;
HWND green;
HWND next;
HWND view;
sf::RenderWindow SFMLView1;
Ejemplo2::Ejemplo2(){

}
Ejemplo2::~Ejemplo2(){

}
void Ejemplo2::start(){
	//Se crea una ventana de render (un container dentro de la ventana donde se pueden meter sprites)
	view = generateView(0, 100, 1000, 900);
	SFMLView1.create(view);
	//Se muetra
	SFMLView1.display();
	//Se define la cantidad de vertices
	shape.setPointCount(128);
	//El color a rellenar el circulo
	shape.setFillColor(sf::Color::Green);
	blue = generateButton("Textura1", 0, 0, 200, 100);
	red = generateButton("Textura2", 200, 0, 200, 100);
	green = generateButton("Textura3", 400, 0, 200, 100);
	next = generateButton("Figura", 600, 0, 200, 100);

}
void Ejemplo2::update(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x != -1)
		x = 1;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x != 1)
		x = -1;
	else
		x = 0;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y != -1)
		y = 1;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y != 1)
		y = -1;
	else
		y = 0;
	shape.setOrigin(sf::Vector2<float>(shape.getOrigin().x + x*v*deltatime, shape.getOrigin().y + y*v*deltatime));
	SFMLView1.clear();
	SFMLView1.draw(shape);
	SFMLView1.display();
}
void Ejemplo2::onButtonPress(HWND button){
	if(button == red)shape.setFillColor(sf::Color::Red);
	else if(button == blue)	shape.setFillColor(sf::Color::Blue);
	else if(button == green) shape.setFillColor(sf::Color::Green);
	else if(button == next) Window::manager->setWindow(new Example());
}

