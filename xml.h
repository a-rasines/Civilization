/*
 * xml.h
 *
 *  Created on: 13 abr 2022
 *      Author: algtc
 */

#ifndef XML_H_
#define XML_H_
#include "sqlite3.h"
typedef struct XMLObject XMLObject;
struct XMLObject{
	char* label;
	char* raw;
	XMLObject **children;
	XMLObject *parent;
	int childrenCount;
	char* value;
};
char* nextLine(char* string, int line);
char* getLabelName(char* line);
int cargarServidorEnBD(char* archivo);
int guardarServidorEnXML(int id);
char* readFile(char* nombre, int initialspace);
XMLObject loadXML(char* plainText);

#endif /* XML_H_ */
