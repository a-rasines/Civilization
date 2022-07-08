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
#include <cstdio>
#ifdef __cplusplus
extern "C" {
#endif
#include "usuario.h"
#include "database.h"
#include "xml.h"
//Usuario getUsuario(char* nombre, char* contrasena);
#ifdef __cplusplus
}
#endif

using namespace std;
sf::Texture menuEjemplo::background;
int terminarAutent = 0;
Usuario user;
MapWindow mw;
Usuario menuEjemplo::logeado;

menuEjemplo::menuEjemplo() {

}

menuEjemplo::~menuEjemplo() {

}

void menuEjemplo::start(){
	inicioS = generateButton("Inicio Sesion/Registro", 250, 500, 500, 50);
	usuario = generateTextField(400, 560, 200, 40);
	contrasena = generatePasswordField(400, 600, 200, 40);
	textButton = generateButton("Acceder", 400, 640, 200, 40);

	server = generateButton("Iniciar como servidor", 250, 500, 500, 50);
	client = generateButton("Iniciar como cliente", 250, 600, 500, 50);
	ip = generateTextField(350, 650, 275, 40);
	textButton2 = generateButton("Aceptar", 620, 650, 200, 40);

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

	text3.setString("Ingrese IP");
	text3.setFont(Fonts::ARIAL);
	text3.setCharacterSize(20);
	text3.setPosition(250, 655);
	text3.setFillColor(sf::Color::White);

	ShowWindow(usuario, (int) SW_HIDE);
	ShowWindow(contrasena, (int) SW_HIDE);
	ShowWindow(textButton, (int) SW_HIDE);

	text.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);
	text3.setFillColor(sf::Color::Black);

	ShowWindow(server, (int) SW_HIDE);
	ShowWindow(client, (int) SW_HIDE);
	ShowWindow(ip, (int) SW_HIDE);
	ShowWindow(textButton2, (int) SW_HIDE);

	ShowWindow(startG, (int) SW_HIDE);
	ShowWindow(loadG, (int) SW_HIDE);
	ShowWindow(quitG, (int) SW_HIDE);

}

void menuEjemplo::update(){
	SFMLView1.clear();
	SFMLView1.draw(text);
	SFMLView1.draw(text2);
	SFMLView1.draw(text3);
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
		if (strcmp(getComponentText(usuario),"") && strcmp(getComponentText(contrasena),"") != 0){
			if (not existeUsuario(getComponentText(usuario))){
				const int opcion = MessageBox(NULL, "Usuario no encontrado, �desea registrarse?", NULL, MB_YESNO);
				switch (opcion) {
					case IDYES:
						addUsuario(getComponentText(usuario), getComponentText(contrasena));
						break;
					case IDNO:
						break;
				}
			} else if (existeUsuario(getComponentText(usuario))){
				logeado = getUsuario(getComponentText(usuario), getComponentText(contrasena));
				if (logeado.nombre == '\0'){
					MessageBox(NULL, "La contrase�a es erronea", NULL, MB_OK);
				}else{
					ShowWindow(inicioS, (int) SW_HIDE);
					ShowWindow(usuario, (int) SW_HIDE);
					ShowWindow(contrasena, (int) SW_HIDE);
					ShowWindow(textButton, (int) SW_HIDE);

					text.setFillColor(sf::Color::Black);
					text2.setFillColor(sf::Color::Black);

					ShowWindow(server, (int) SW_SHOW);
					ShowWindow(client, (int) SW_SHOW);

				}
			}

		} else if (strcmp(getComponentText(usuario),"") == 0){
			 MessageBox(NULL, "Ingrese un nombre de usuario valido", NULL, MB_OK);

		} else if (strcmp(getComponentText(contrasena),"") == 0){
			 MessageBox(NULL, "Ingrese una contrasena valido", NULL, MB_OK);
		}
	}
	else if(button == startG)Window::manager->setWindow(&mw);
	else if (button == loadG){
		mw.cargarTropas("resources/troopSave.dat");
		Window::manager->setWindow(&mw);
	}
	else if (button == quitG){
		manager->stopConnection();
		DestroyWindow(window);
	}
	else if (button == server){
		ShowWindow(server, (int) SW_HIDE);
		ShowWindow(client, (int) SW_HIDE);

		ShowWindow(startG, (int) SW_SHOW);
		ShowWindow(quitG, (int) SW_SHOW);
		ShowWindow(loadG, (int) SW_SHOW);
		Window::manager->startTCPServer();
	}
	else if (button == client){
		ShowWindow(server, (int) SW_HIDE);
		ShowWindow(client, (int) SW_HIDE);

		text3.setFillColor(sf::Color::White);
		ShowWindow(ip, (int) SW_SHOW);
		ShowWindow(textButton2, (int) SW_SHOW);
	}
	else if (button == textButton2){
		if (strcmp(getComponentText(ip),"") !=0){
			Window::manager->startTCPClient(getComponentText(ip));
			Window::manager->setWindow(&mw);

		}else if (strcmp(getComponentText(ip),"") == 0){
			 MessageBox(NULL, "Ingrese una IP valida", NULL, MB_OK);
		}
	}
}
int main(){
	setup();
	Window::manager = new WindowManager("S", 1000, 1000, new menuEjemplo());
}
