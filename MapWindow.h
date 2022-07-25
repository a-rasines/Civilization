/*
 * MapWindow.h
 *
 *  Created on: 21 may 2022
 *      Author: algtc
 */

#ifndef MAPWINDOW_H_
#define MAPWINDOW_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "ciudad.h"
#include "SocketMessageHolder.h"
#include "Sprite.h"
#include "tropa.h"
#include "WindowObjects/Window.h"

class MapWindow : public Window{
public:
	enum MenuOption{
		TAX_RATE,
		LUXURIES_RATE,
		FIND_CITY,
		OPTIONS,
		SAVE_GAME,
		REVOLUTION,
		RETIRE,
		QUIT,

		NO_ORDERS,
		FOUND_NEW_CITY,
		BUILD_ROAD,
		CHANGE_TO_FOREST,
		BUILD_FORTRESS,
		WAIT,
		SENTRY,
		GOTO,
		PILLAGE,
		DISBAND_UNIT,

		CITY_STATUS,
		MILITARY_ADVISOR,
		INTELLIGENCE_ADVISOR,
		ATTITUDE_ADVISOR,
		TRADE_ADVISOR,
		SCIENCE_ADVISOR,

		WONDERS_OF_THE_WORLD,
		TOP_5_CITIES,
		CIVILIZATION_SCORE,
		WORLD_MAP,
		DEMOGRAPHICS,
		SPACESHIPS,

		COMPLETE,
		CIVILIZATION_ADVANCES,
		CITY_IMPROVEMENTS,
		MILITARY_UNITS,
		TERRAIN_TYPES,
		MISCELLANEOUS
	};
	struct TropaInst : public Tropa{
		TropaInst(int serverId, int userId, int troopId, int type, int posX, int posY){
			this->idServidor = serverId;
			this->idJugador = userId;
			this->idTropa = troopId;
			this->data = sprite::Troop[type];
			this->estado = 0;
			this->mejorada = 0;
			this->posicionX = posX;
			this->posicionY = posY;
			this->renderingPositionX = posX;
			this->renderingPositionY = posY;
			this->tipo = type;
			this->vida = data.defense;
			this->estacionada = false;
		};
		TropaInst(int serverId, int userId, int troopId,int estado,int mejora, int posX, int posY, int type, int vida, bool estacionada){
					this->idServidor = serverId;
					this->idJugador = userId;
					this->idTropa = troopId;
					this->data = sprite::Troop[type];
					this->estado = estado;
					this->mejorada = mejora;
					this->posicionX = posX;
					this->posicionY = posY;
					this->renderingPositionX = posX;
					this->renderingPositionY = posY;
					this->tipo = type;
					this->vida = vida;
					this->estacionada=estacionada;
				};
		bool operator == (Tropa t){
			return idTropa==t.idTropa && idJugador == t.idJugador;
		}
		virtual void keyPress(int keycode, MapWindow *mw);
		virtual ~TropaInst(){}
		sprite::TroopData data;
		float renderingPositionX;
		float renderingPositionY;
	};
	struct SettlerInst : public TropaInst {
		SettlerInst(int serverId, int userId, int troopId, int posX, int posY) : TropaInst(serverId, userId, troopId, (int)sprite::TroopType::SETTLER, posX, posY){}
		SettlerInst(int serverId, int userId, int troopId,int estado,int mejora, int posX, int posY, int vida, bool estacionada) : TropaInst(serverId, userId, troopId, estado, mejora, posX, posY, (int)sprite::TroopType::SETTLER, vida, estacionada){}
		void keyPress(int keycode, MapWindow *mw);
		virtual ~SettlerInst(){}

	};
	struct CiudadInst : public Ciudad {
		CiudadInst(int idPartida, int idJugador, int idCiudad, char* nombre, int posicionX, int posicionY){
			this->idPartida = idPartida;
			this->idJugador = idJugador;
			this->idCiudad = idCiudad;
			this->nombre = nombre;
			this->posicionX = posicionX;
			this->posicionY = posicionY;
			this->edificios = new char[Edificio::_LAST / 8 + 1];
			strcpy(this->edificios,"\0");
			this->comida = 0;
			this->dinero = 0;
			this->produccion = 0;

		}
		CiudadInst(int idPartida, int idJugador, int idCiudad, char* nombre, char* edificios, int comida, int dinero, int produccion, int posicionX, int posicionY){
			this->idPartida = idPartida;
				this->idJugador = idJugador;
				this->idCiudad = idCiudad;
				this->edificios = new char[Edificio::_LAST / 8 + 1];
				strcpy(this->edificios,edificios);
				this->nombre = new char[strlen(nombre)];
				strcpy(this->nombre,nombre);
				this->comida = comida;
				this->dinero = dinero;
				this->produccion = produccion;
				this->posicionX = posicionX;
				this->posicionY = posicionY;
		}
		bool tieneEdificio(Edificio ed){
			int pos = (int)(ed/8);
			int bit = pow(2,ed%8 + 1);
			return edificios[pos] & bit;
		}
		void addEdificio(Edificio ed){
			int pos = (int)(ed/8);
			int bit = pow(2,ed%8 + 1);
			edificios[pos] |= bit;
		}
		void removeEdificio(Edificio ed){
			int pos = (int)(ed/8);
			int bit = ~((int)pow(2,ed%8 + 1));
			edificios[pos] &= bit;
		}
	};
	void cargarTropas(const char* fichero);
	void guardarTropas(const char* fichero);
	void onClientStart();
	void onServerStart();
	MapWindow();
	void troopMove(TropaInst *t, Position p);
	bool posibleMove(TropaInst t,int x, int y);
	void start(); //Esta funcion se llama al cambiar de pantalla
	void update();//Esta funcion se llama cada vez que de una vuelta al bucle
	void onClose();
	void onButtonPress(HWND button){};//Esta funcion se llama cuando un boton sea pulsado
	void reposition(int x, int y);//Se llama para mover el mapa
	void onResize(int newWidth, int newHeight);//Esta funcion se llama cuando la ventana cambia de tamaño
	void onKeyDown(int keycode);//Esta función se llama cuando una tecla es pulsada
	void onMessage(char * message);
	void onMenu(UINT_PTR menuId);
	struct Cell{
		int posX;
		int posY;
		int sizeX;
		int sizeY;
		std::string file;
		sf::IntRect texData;

	};
	virtual ~MapWindow();
	static int zoom;
	int serverID = 0; //TODO Assing id
private:
	float round(float number, int decimals);
	static sf::Color playerColors[];
	std::map<int, sf::Color> playerColorMap;
	sf::RenderWindow mapView;
	static float x;
	static float y;
	std::vector<Cell> activeCells;
	std::vector<TropaInst> activeTroops;
	std::vector<CiudadInst> activeCities;
	static sf::Texture background;
	int lastMovement;
	bool moving = false;
	bool repos = true;
};

#endif /* MAPWINDOW_H_ */
