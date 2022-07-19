/*
 * SocketMessageHolder.h
 *
 *  Created on: 19 jul 2022
 *      Author: algtc
 */

#ifndef SOCKETMESSAGEHOLDER_H_
#define SOCKETMESSAGEHOLDER_H_

#include <string.h>
#include <string>

#include "database.h"

enum SocketMessage{
	INITIAL_TROOP_SYNC,
	MOVE,
	ADD_TROOP,
	ACTION,
	BUILD_CITY
};
enum Position{
	N = 38,
	NE = 33,
	E = 39,
	SE = 34,
	S = 40,
	SW = 35,
	W = 37,
	NW = 36
};
enum Action {
	SENTRY = 's',
	DISBAND = 'D',
	WAIT = 'w',
	PILLAGE = 'P',
	BUILD_ROAD = 'r',
	BUILD_FOREST = 'm',
	BUILD_FORTRESS = 'f'
};
namespace message{
	char* action(Action acc){
		std::string str;
		str += (int)SocketMessage::ACTION;
		str += ":";
		str += (int)acc;
		char end[6]; // 3:115\0
		str += " "; //Make sure no other number gets in
		strcpy(end, str.substr(0, 5).c_str());
		return end;
	}
	char* movement(Position newPos){
		std::string str;
		str += (int)SocketMessage::MOVE;
		str += ":";
		str += (int)newPos;
		char end[5]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
}



#endif /* SOCKETMESSAGEHOLDER_H_ */
