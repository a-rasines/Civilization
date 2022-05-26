/*
 * menuEjemplo.cpp
 *
 *  Created on: 12 may 2022
 *      Author: Marian
 */

#include "menuEjemplo.h"
#include "MapWindow.h"
#include "Example.h"
#include "winuser.h"
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
	inicioS = generateButton("Inicio Sesion/Registro", 250, 500, 500, 50);
	usuario = generateTextField(400, 560, 200, 40);
	contrasena = generateTextField(400, 600, 200, 40);
	textButton = generateButton("Acceder", 400, 640, 200, 40);
	startG = generateButton("Start game", 250, 500, 500, 50);
	loadG = generateButton("Load game", 250, 600, 500, 50);
	quitG = generateButton("Quit game", 250, 700, 500, 50);

	view = generateView(0, 0, 1000, 1000);
	SFMLView1.create(view);
	SFMLView1.display();
	//SFMLView1.setVisible(false);
	std::string file = "resources/LOGO.PIC_256.png";
	background.loadFromFile(file);
	text.setString("Usuario");
	text.setFont(Fonts::ARIAL);
	text.setCharacterSize(20);
	text.setPosition(325, 568);
	text.setFillColor(sf::Color::White);

	text2.setString("Contrasena");
	text2.setFont(Fonts::ARIAL);
	text2.setCharacterSize(20);
	text2.setPosition(290, 608);
	text2.setFillColor(sf::Color::White);

	ShowWindow(usuario, (int) SW_HIDE);
	ShowWindow(contrasena, (int) SW_HIDE);
	ShowWindow(textButton, (int) SW_HIDE);

	text.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);

	ShowWindow(startG, (int) SW_HIDE);
	ShowWindow(loadG, (int) SW_HIDE);
	ShowWindow(quitG, (int) SW_HIDE);

}

void menuEjemplo::update(){
	SFMLView1.clear();
	SFMLView1.draw(text);
	SFMLView1.draw(text2);
	sf::RectangleShape rect;
	rect.setTexture(&background, true);
	rect.setPosition(250,-100);
	rect.setSize( sf::Vector2f(600,600));
	SFMLView1.draw(rect);
	SFMLView1.display();

	}

void menuEjemplo::onButtonPress(HWND button){
	if (button == inicioS){
		ShowWindow(inicioS, (int) SW_HIDE);
		text.setFillColor(sf::Color::White);
		text2.setFillColor(sf::Color::White);

		ShowWindow(usuario, (int) SW_SHOW);
		ShowWindow(contrasena, (int) SW_SHOW);
		ShowWindow(textButton, (int) SW_SHOW);
	}
	else if (button == textButton){
		if (getComponentText(usuario) != "" && getComponentText(contrasena) != ""){
		//mandar datos inicio sesión
		ShowWindow(inicioS, (int) SW_HIDE);
		ShowWindow(usuario, (int) SW_HIDE);
		ShowWindow(contrasena, (int) SW_HIDE);
		ShowWindow(textButton, (int) SW_HIDE);

		text.setFillColor(sf::Color::Black);
		text2.setFillColor(sf::Color::Black);

		ShowWindow(startG, (int) SW_SHOW);
		ShowWindow(quitG, (int) SW_SHOW);
		ShowWindow(loadG, (int) SW_SHOW);


		} else if (getComponentText(usuario) == ""){
			 MessageBox(NULL, "Ingrese un nombre de usuario valido", NULL, MB_OK);
		}
	}
	else if(button == startG)Window::manager = new WindowManager("Civilization", 1200, 1000, new MapWindow());
	else if (button == quitG)manager->stopConnection();

}
int main(){
	Window::manager = new WindowManager("S", 1000, 1000, new menuEjemplo());
}
