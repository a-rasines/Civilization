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

#include "MapWindow.h"


enum SocketMessage{
	INITIAL_TROOP_SYNC,
	MOVE,
	ADD_TROOP,
	ACTION,
	BUILD_CITY,
	DESENTRY
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
	NONE = ' ',
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
		char end[str.length() + 1]; // 3:115\0
		strcpy(end, str.c_str());
		return end;
	}
	char* movement(Position newPos){
		std::string str;
		str += (int)SocketMessage::MOVE;
		str += ":";
		str += (int)newPos;
		char end[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
	char* desentry(int id){
		std::string str;
		str += (int)SocketMessage::DESENTRY;
		str += ":";
		str += id;
		char end[str.length() + 1]; // 1:33\0
		strcpy(end, str.c_str());
		return end;
	}
}



#endif /* SOCKETMESSAGEHOLDER_H_ */
