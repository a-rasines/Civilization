#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "database.h"
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
	char*label = malloc(sizeof(char)*(last - first));
	for(int i = first; i<last;i++){
		if(line[i] == '>'){
			label[i-first] ='\0';
			return label;
		}
		label[i-first] = line[i];
	}
}
char* getValue(char* line){
	int first = indexOf(line, '>', 1);
	int last = indexOf(line, '<', 2);
	char*label = malloc(sizeof(char)*(last - first));
	for(int i = first; i<last;i++){
		if(line[i] == '<'){
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
	return indexOf(text, '<', 1) + 1 == indexOf(text, '/', 1);
}
XMLObject getAttributeByLabel(XMLObject parent, char* label){
	for(int i = 0; i < parent.childrenCount; i++){
		if(strcmp(parent.children[i].label, label) == 0)return parent.children[i];
	}
}
XMLObject* loadXML(char* plainText){
	XMLObject root;
	int lineCount = countLines(plainText);
	root.label = getLabelName(nextLine(plainText, 1));
	XMLObject *childList = malloc(sizeof(XMLObject) * lineCount-3);
	XMLObject *actual = &root;
	for (int i = 2; i < lineCount; i++){
		char* line = nextLine(plainText, i);
		if(getLabelName(line)[0] != '/'){//Si no es una linea de fin de atributo padre es una linea de atributo
			actual->childrenCount++;
			XMLObject atribute;
			atribute.parent = actual;
			actual = &atribute;
			actual->label = getLabelName(line);
			actual->value = getValue(line);
			actual->childrenCount=0;
			//TODO Asignar valores al nuevo atributo
		}
		if(isLabelEnd(line)){//Si se acaba la lista de atributos, se vuelve al padre
			actual = actual->parent;
		}else{//Si no se acaba tiene atributos hijo
			actual->children = malloc(sizeof(XMLObject)*(lineCount - 1/*<-Cierre de root*/)-i);
		}
	}
}
void writeXMLrec(XMLObject obj, FILE *out){
	fprintf(out, "\n<%s>", obj.label);
	if(obj.childrenCount > 0){
		for(int i = 0; i < obj.childrenCount;i++){
			writeXMLrec(*(obj.children + i), out);
		}
		free(obj.children);
		fprintf(out, "\n</%s>", obj.label);
	}else{
		fprintf(out, "%s</%s>", obj.value, obj.label);
	}
}
void writeXML(XMLObject toExport, char* name){
	FILE *out = fopen(name, "w");
	fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	writeXMLrec(toExport, out);
}
char* readFile(char* nombre, int initialspace){
	FILE* f = fopen(nombre, "r");
    char c;
    int count = 0;
    char* end = malloc(sizeof(char) * initialspace);
	while ((c = fgetc(f)) != EOF)
	{
		if(count==initialspace)return readFile(nombre, initialspace * 2);
		*(end + count) = c;
		count++;
	}
	fclose(f);
	return end;
}
/*
 * <root>
 *     <ID> int </ID>
 *     <Tropas>
 *         <Tropa>
 *             <Usuario> int </Usuario>
 *             <ID> int </ID>
 *             <Tipo> char* </Tipo>
 *             <Vida> int </Vida>
 *             <Mejorada> int </Mejorada>
 *             <PosicionX> int </PosicionX>
 *             <PosicionY> int </PosicionY>
 *         </Tropa>
 *         ...
 *     </Tropas>
 *     <Ciudades>
 *         <Ciudad>
 *             <Usuario> int </Usuario>
 *             <ID> int </ID>
 *             <Nombre> char* </Nombre>
 *             <Edificios> char* </Edificios>
 *             <Comida> int </Comida>
 *             <Dinero> int </Dinero>
 *             <Produccion> int </Produccion>
 *             <PosicionX> int </PosicionX>
 *             <PosicionY> int </PosicionY>
 *        </Ciudad>
 *        ....
 *    </Ciudades>
 *    <Partidas>
 *        <Partida>
 *            <Jugador> int </Jugador>
 *			  <ID> int </ID>
 *			  <Politica> int </Politica>
 *			  <Investigaciones> char* </Investigaciones>
 *			  <Alianzas> char* </Alianzas>
 *        </Partida>
 *        ...
 *    </Partidas>
 *</root>
 */
int cargarServidorEnBD(char* archivo){
	XMLObject *obj = loadXML(readFile(archivo, 1000));
	int id;
	sprintf("%i", obj->children[0].label);
	sqlite3_stmt *stmt;
	char seq[200];
	sprintf(seq, "INSERT INTO Servidor(ID) VALUES (%i)",id);
	update(seq);
	free(seq);
	//Tropas
	XMLObject tropas = obj->children[1];
	for(int i = 0; i < tropas.childrenCount;i++){
		seq[200];
		sprintf(seq, "INSERT INTO Tropa(Usuario, Servidor, ID, Tipo, Vida, Mejorada, PosicionX, PosicionY) VALUES (%s, %s, %s, %s, %s, %s, %s)",
			getAttributeByLabel(tropas.children[i], "Usuario"),
			id,
			getAttributeByLabel(tropas.children[i], "ID"),
			getAttributeByLabel(tropas.children[i], "Tipo"),
			getAttributeByLabel(tropas.children[i], "Vida"),
			getAttributeByLabel(tropas.children[i], "Mejorada"),
			getAttributeByLabel(tropas.children[i], "PosicionX"),
			getAttributeByLabel(tropas.children[i], "PosicionY")
		);
		update(seq);
		free(seq);
	}
	//Ciudades
	XMLObject ciudades = obj->children[2];
	for(int i = 0; i < ciudades.childrenCount;i++){
		seq[200];
		sprintf(seq, "INSERT INTO Ciudad(Usuario, Servidor, ID, Nombre, Edificios, Comida, Dinero, Produccion, PosicionX, PosicionY) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)",
			getAttributeByLabel(ciudades.children[i], "Usuario"),
			id,
			getAttributeByLabel(ciudades.children[i], "ID"),
			getAttributeByLabel(ciudades.children[i], "Nombre"),
			getAttributeByLabel(ciudades.children[i], "Edificios"),
			getAttributeByLabel(ciudades.children[i], "Comida"),
			getAttributeByLabel(ciudades.children[i], "Dinero"),
			getAttributeByLabel(ciudades.children[i], "Produccion"),
			getAttributeByLabel(ciudades.children[i], "PosicionX"),
			getAttributeByLabel(ciudades.children[i], "PosicionY")
		);
		update(seq);
		free(seq);
	}
	//Partidas
	XMLObject partidas = obj->children[3];
	for(int i = 0; i < ciudades.childrenCount;i++){
		seq[200];
		sprintf(seq, "INSERT INTO Ciudad(Jugador, Servidor, ID, Politica, Investigaciones, Alianzas) VALUES (%s, %s, %s, %s, '%s', '%s')",
			getAttributeByLabel(partidas.children[i], "Jugador"),
			id,
			getAttributeByLabel(partidas.children[i], "ID"),
			getAttributeByLabel(partidas.children[i], "Politica"),
			getAttributeByLabel(partidas.children[i], "Investigaciones"),
			getAttributeByLabel(partidas.children[i], "Alianzas")
		);
		update(seq);
		free(seq);
	}
}
void guardarServidorEnXML_obtenerDatos(int id, char* datos, char* tabla, sqlite3_stmt stmt){
	char seq[100];
	sprintf(seq, "SELECT %s FROM %s WHERE Servidor = %i", datos, tabla, id);
	if (sqlite3_prepare_v2(getDB(), seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al encontrar las tropas\n");
		printf("%s\n", sqlite3_errmsg(getDB()));
	}
	free(seq);
}
int guardarServidorEnXML(int id){
	XMLObject servidor;
	servidor.label = "root";
	servidor.children = malloc(sizeof(XMLObject)*4);
	sprintf(servidor.children[0].label, "%i", id);
	servidor.children[0].parent = &servidor;
	servidor.children[0].childrenCount = 0;

	servidor.children[1].parent = &servidor;
	servidor.children[1].label = "Tropas";
	sqlite3_stmt *stmt;
	int q;
	guardarServidorEnXML_obtenerDatos(id, "Count(*)", "Tropa", stmt);
	int i =sqlite3_step(stmt);
	q = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	servidor.children[1].children = malloc(sizeof(XMLObject)*q);
	servidor.children[1].childrenCount = q;

	guardarServidorEnXML_obtenerDatos(id, "*", "Tropa", stmt);
	int c = 0;
	i =sqlite3_step(stmt);
	while(i == SQLITE_ROW){
		XMLObject *actual = &servidor.children[1].children[c];
		actual->label = "Tropa";
		actual->parent = &servidor.children[1];
		actual->children = malloc(sizeof(XMLObject)*7);
		actual->childrenCount = 7;

		actual->children[0].label = "Usuario";
		actual->children[0].parent = actual;
		actual->children[0].childrenCount = 0;
		sprintf(actual->children[0].value, "%i", sqlite3_column_int(stmt, 1));

		actual->children[1].label = "ID";
		actual->children[1].parent = actual;
		actual->children[1].childrenCount = 0;
		sprintf(actual->children[1].value, "%i", sqlite3_column_int(stmt, 2));

		actual->children[2].label = "Tipo";
		actual->children[2].parent = actual;
		actual->children[2].childrenCount = 0;
		sprintf(actual->children[2].value, "'%s'", sqlite3_column_text(stmt, 3));

		actual->children[3].label = "Vida";
		actual->children[3].parent = actual;
		actual->children[3].childrenCount = 0;
		sprintf(actual->children[3].value, "%i", sqlite3_column_int(stmt, 4));

		actual->children[4].label = "Mejorada";
		actual->children[4].parent = actual;
		actual->children[4].childrenCount = 0;
		sprintf(actual->children[4].value, "%i", sqlite3_column_int(stmt, 5));

		actual->children[5].label = "PosicionX";
		actual->children[5].parent = actual;
		actual->children[5].childrenCount = 0;
		sprintf(actual->children[5].value, "%i", sqlite3_column_int(stmt, 6));

		actual->children[6].label = "PosicionY";
		actual->children[6].parent = actual;
		actual->children[6].childrenCount = 0;
		sprintf(actual->children [6].value, "%i", sqlite3_column_int(stmt, 7));
	}
	sqlite3_finalize(stmt);

	servidor.children[2].parent = &servidor;
	servidor.children[2].label = "Ciudades";
	guardarServidorEnXML_obtenerDatos(id, "Count(*)", "Ciudad", stmt);
	i =sqlite3_step(stmt);
	q = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	servidor.children[2].children = malloc(sizeof(XMLObject)*q);
	servidor.children[2].childrenCount = q;

	guardarServidorEnXML_obtenerDatos(id, "*", "Ciudad", stmt);
	c = 0;
	i =sqlite3_step(stmt);
	while(i == SQLITE_ROW){
		XMLObject *actual = &servidor.children[1].children[c];
		actual->label = "Ciudad";
		actual->parent = &servidor.children[1];
		actual->children = malloc(sizeof(XMLObject)*9);
		actual->childrenCount = 9;

		actual->children[0].label = "Usuario";
		actual->children[0].parent = actual;
		actual->children[0].childrenCount = 0;
		sprintf(actual->children[0].value, "%i", sqlite3_column_int(stmt, 1));

		actual->children[1].label = "ID";
		actual->children[1].parent = actual;
		actual->children[1].childrenCount = 0;
		sprintf(actual->children[1].value, "%i", sqlite3_column_int(stmt, 2));

		actual->children[2].label = "Nombre";
		actual->children[2].parent = actual;
		actual->children[2].childrenCount = 0;
		sprintf(actual->children[2].value, "'%s'", sqlite3_column_text(stmt, 3));

		actual->children[3].label = "Edificios";
		actual->children[3].parent = actual;
		actual->children[3].childrenCount = 0;
		sprintf(actual->children[3].value, "'%s'", sqlite3_column_text(stmt, 4));

		actual->children[4].label = "Comida";
		actual->children[4].parent = actual;
		actual->children[4].childrenCount = 0;
		sprintf(actual->children[4].value, "%i", sqlite3_column_int(stmt, 5));

		actual->children[5].label = "Dinero";
		actual->children[5].parent = actual;
		actual->children[5].childrenCount = 0;
		sprintf(actual->children[5].value, "%i", sqlite3_column_int(stmt, 6));

		actual->children[6].label = "Produccion";
		actual->children[6].parent = actual;
		actual->children[6].childrenCount = 0;
		sprintf(actual->children[6].value, "%i", sqlite3_column_int(stmt, 7));

		actual->children[7].label = "PosicionX";
		actual->children[7].parent = actual;
		actual->children[7].childrenCount = 0;
		sprintf(actual->children[7].value, "%i", sqlite3_column_int(stmt, 7));

		actual->children[8].label = "PosicionY";
		actual->children[8].parent = actual;
		actual->children[8].childrenCount = 0;
		sprintf(actual->children[8].value, "%i", sqlite3_column_int(stmt, 7));
	}
	sqlite3_finalize(stmt);

	servidor.children[2].parent = &servidor;
		servidor.children[2].label = "Ciudades";
		guardarServidorEnXML_obtenerDatos(id, "Count(*)", "Ciudad", stmt);
		i =sqlite3_step(stmt);
		q = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);

		servidor.children[1].children = malloc(sizeof(XMLObject)*q);
		servidor.children[1].childrenCount = q;
		guardarServidorEnXML_obtenerDatos(id, "*", "Partidas", stmt);
		c = 0;
		i =sqlite3_step(stmt);
		while(i == SQLITE_ROW){
			XMLObject *actual = &servidor.children[1].children[c];
			actual->label = "Partida";
			actual->parent = &servidor.children[1];
			actual->children = malloc(sizeof(XMLObject)*5);
			actual->childrenCount = 5;

			actual->children[0].label = "Jugador";
			actual->children[0].parent = actual;
			actual->children[0].childrenCount = 0;
			sprintf(actual->children[0].value, "%i", sqlite3_column_int(stmt, 0));

			actual->children[1].label = "ID";
			actual->children[1].parent = actual;
			actual->children[1].childrenCount = 0;
			sprintf(actual->children[1].value, "%i", sqlite3_column_int(stmt, 2));

			actual->children[2].label = "Politica";
			actual->children[2].parent = actual;
			actual->children[2].childrenCount = 0;
			sprintf(actual->children[2].value, "%i", sqlite3_column_int(stmt, 3));

			actual->children[3].label = "Investigaciones";
			actual->children[3].parent = actual;
			actual->children[3].childrenCount = 0;
			sprintf(actual->children[3].value, "'%s'", sqlite3_column_text(stmt, 4));

			actual->children[4].label = "Alianzas";
			actual->children[4].parent = actual;
			actual->children[4].childrenCount = 0;
			sprintf(actual->children[4].value, "%i", sqlite3_column_int(stmt, 5));
		}
		sqlite3_finalize(stmt);
}
