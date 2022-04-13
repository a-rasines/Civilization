/*
 * xml.c
 *
 *  Created on: 13 abr 2022
 *      Author: algtc
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct XMLObject XMLObject;
struct XMLObject{
	char* label;
	XMLObject *children;
	XMLObject *parent;
	int childrenCount;
	char* value;
};
int indexOf(char* string, char c, int pos){
	int p = 0;
	while(pos > 0){
		if(string[p] == c)pos--;
		p++;
	}
	return p;
}
char* getLabelName(char* line){
	int first = indexOf(line, '<', 1);
	int last = indexOf(line, '>', 1);
	printf("%i, %i\n", first, last);
	char*label = malloc(sizeof(char)*(last - first));
	for(int i = first; i<last;i++){
		if(line[i] == '>'){
			label[i-first] ='\0';
			return label;
		}
		label[i-first] = line[i];
	}
}
char* nextLine(char* string, int line){
	int count = 0;
	int pos  = line==0?0:indexOf(string, '\n', line);
	char* end = malloc(sizeof(char)*2000);
	while(string[pos] != '\n' && string[pos] != '\0'){
		*(end + count) = *(string + pos);
		count++;
		pos++;
	}
	char* out = malloc(sizeof(char)* count);
	for(int i = 0; i < count; i++){
		*(out + i) = *(end + i);
	}
	*(out + count) = '\0';
	free(end);
	return out;

}
int countLines(char* text){
	int count = 0;
	for(int i = 0; i < strlen(text);i++){
		if(text[i] == '\n') count++;
	}
	return count;
}
int isLabelEnd(char* text){
	return indexOf('<') + 1 == indexOf('\\');
}
XMLObject* loadXML(char* plainText){
	XMLObject root;
	int lineCount = countLines(plainText);
	root.label = getLabelName(nextLine(plainText, 1));
	XMLObject childList = malloc(sizeof(XMLObject) * lineCount-3);
	XMLObject *actual = &root;
	for (int i = 2; i < lineCount; i++){
		char* line = nextLine(plainText, i);
		if(getLabelName(line)[0] != '\\'){//Si no es una linea de fin de atributo padre es una linea de atributo
			actual->childrenCount++;
			XMLObject atribute;
			atribute.parent = actual;
			actual = &atribute;
			//TODO Asignar valores al nuevo atributo
		}
		if(isLabelEnd(line)){//Si se acaba la lista de atributos, se vuelve al padre
			actual = actual->parent;
		}else{//Si no se acaba tiene atributos hijo

		}
	}
}
//<?xml version=\"1.0\" encoding=\"utf-8\"?>
int cargarServidorEnBD(char* archivo){

}
int guardarServidorEnXML(int id);
int crearBackupUsuarios();
int importarUsuarios(char* archivo);
