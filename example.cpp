/*
 * example.cpp
 *
 *  Created on: 5 may 2022
 *      Author: algtc
 */
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include "example.h"
#include "window.h"
#include "WindowManager.h"

sf::CircleShape shape(100.f);
float x = 0;
float y = 0;
float v = 1;
HWND blue;
HWND red;
HWND green;
sf::RenderWindow SFMLView1;
void Example::start(){
	//Se crea una ventana de render (un container dentro de la ventana donde se pueden meter sprites)
	SFMLView1.create(comp.generateView(0, 100, 1000, 900));
	//Se muetra
	SFMLView1.display();
	//Se define la cantidad de vertices
	shape.setPointCount(128);
	//El color a rellenar el circulo
	shape.setFillColor(sf::Color::Green);
	blue = comp.generateButton("Azul", 0, 0, 200, 100);
	red = comp.generateButton("Rojo", 200, 0, 200, 100);
	green = comp.generateButton("Verde", 400, 0, 200, 100);

}
void Example::update(){
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
	shape.setOrigin(sf::Vector2<float>(shape.getOrigin().x + x*v, shape.getOrigin().y + y*v));
	SFMLView1.clear();
	SFMLView1.draw(shape);
	SFMLView1.display();
}
void Example::onButtonPress(HWND button){
	if(button == red)shape.setFillColor(sf::Color::Red);
	else if(button == blue)	shape.setFillColor(sf::Color::Blue);
	else if(button == green) shape.setFillColor(sf::Color::Green);
}
int main(){
	Example e;
	WindowManager man("Ejemplo", 0, 0, 1000, 1000, &e);
}
