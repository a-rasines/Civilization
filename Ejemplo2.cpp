/*
 * Ejemplo2.cpp
 *
 *  Created on: 9 may 2022
 *      Author: algtc
 */
#include <SFML/Graphics.hpp>
#include "Ejemplo2.h"

#include "Example.h"
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
	 if (!texture1.loadFromFile("resources/TER257.PIC_256.gif", sf::IntRect(16,  80, 16, 16))/* offsetX, offsetY, sizeX, sizeY*/ || !texture2.loadFromFile("resources/image2.jpg") || !texture3.loadFromFile("resources/image3.jpg"))
		 return;
	sprite = sf::Sprite(texture1);
	sprite.setScale(sf::Vector2f(4, 4));
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
	sprite.setOrigin(sf::Vector2<float>(sprite.getOrigin().x + x*v*deltatime, sprite.getOrigin().y + y*v*deltatime));
	SFMLView1.clear();
	SFMLView1.draw(sprite);
	SFMLView1.display();
}
void Ejemplo2::onButtonPress(HWND button){
	if(button == red)sprite.setTexture(texture2, true);//Si la nueva textura tiene otro tamaño y lo quieres redimensionar se pone true, sino false
	else if(button == blue)sprite.setTexture(texture1, false);
	else if(button == green) sprite.setTexture(texture3, true);
//	else if(button == next) Window::manager->setWindow(new Example());
}

