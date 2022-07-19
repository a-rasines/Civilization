/*
 * SocketMessageHOlder.cpp
 *
 *  Created on: 19 jul 2022
 *      Author: algtc
 */

#include "SocketMessageHolder.h"
namespace message{
	char* action(Action acc){
		std::string str = "" + std::to_string(SocketMessage::ACTION) + ":"
							 + std::to_string(acc);
		char* end =new char[str.length() + 1]; // 3:115\0
		strcpy(end, str.c_str());
		return end;
	}
	char* movement(Position newPos){
		std::string str = "" + std::to_string(SocketMessage::MOVE) + ":"
							 + std::to_string(newPos);
		char* end =new char[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
	char* desentry(int id){
		std::string str = "" + std::to_string(SocketMessage::DESENTRY) + ":"
							 + std::to_string(id);
		char* end =new char[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
	char* initialTroopSync(MapWindow::TropaInst* troop){
		std::string str = "" + std::to_string(SocketMessage::INITIAL_TROOP_SYNC) + ":"
							 + std::to_string(troop->idJugador) + ":"
							 + std::to_string(troop->idTropa) + ":"
							 + std::to_string(troop->estado) + ":"
							 + std::to_string(troop->mejorada) + ":"
							 + std::to_string(troop->posicionX) + ":"
							 + std::to_string(troop->posicionY) + ":"
							 + std::to_string(troop->tipo) + ":"
							 + std::to_string(troop->vida) + ":"
							 + std::to_string(troop->estacionada);
		char* end =new char[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
	char* infoSync(InfoSync type, int value){
		std::string str = "" + std::to_string(SocketMessage::INFO_SYNC) + ":"
							 + std::to_string(type) + ":"
							 + std::to_string(value);
		char* end =new char[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
	char* other(SocketMessage acc){
		std::string str = "" + std::to_string(acc);
		char* end =new char[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
}
