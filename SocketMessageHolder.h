/*
 * SocketMessageHolder.h
 *
 *  Created on: 19 jul 2022
 *      Author: algtc
 */

#ifndef SOCKETMESSAGEHOLDER_H_
#define SOCKETMESSAGEHOLDER_H_

#include "tropa.h"

enum SocketMessage{
	CONT,
	INFO_SYNC,
	INITIAL_TROOP_SYNC,
	TROOP_SYNC, // TODO Future anti-cheat (obviously not for server)
	MOVE,
	ADD_TROOP,
	ACTION,
	BUILD_CITY,
	DESENTRY,
	SYNC
};
enum InfoSync {
	SERVER_ID,
	PLAYER_ID,
	PLAYER_COLOR
};
enum Position{
	SKIP = ' ',
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
	NO_ACTION = ' ',
	SENTRY = 's',
	DISBAND = 'D',
	WAIT = 'w',
	PILLAGE = 'P',
	BUILD_ROAD = 'r',
	BUILD_FOREST = 'm',
	BUILD_FORTRESS = 'f'
};
namespace message{
	char* action(Action acc);
	char* movement(Position newPos);
	char* desentry(int id);
	char* initialTroopSync(Tropa* tropa);
	char* infoSync(InfoSync type, int value);
	char* infoSync(InfoSync type, int value1,long int value2);
	char* other(SocketMessage acc);
}



#endif /* SOCKETMESSAGEHOLDER_H_ */
