/*
 * xml.h
 *
 *  Created on: 13 abr 2022
 *      Author: algtc
 */

#ifndef XML_H_
#define XML_H_
#include "sqlite3.h"
char* nextLine(char* string, int line);
char* getLabelName(char* line);
int cargarServidorEnBD(char* archivo);
int guardarServidorEnXML(int id);

#endif /* XML_H_ */
