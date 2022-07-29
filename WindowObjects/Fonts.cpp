/*
 * Fonts.cpp
 *
 *  Created on: 12 may 2022
 *      Author: algtc
 */

#include "Fonts.h"

#include <SFML/Graphics.hpp>
#include <cstring>

Font::Font(){
	filename = "\0";
}
Font::Font(std::map<char, CharacterRender> map, char* filename){
	this->renderMap = map;
	this->filename = filename;
}
bool Font::canLoad(char* text){
	for(int i = 0, c = text[0]; i < strlen(text); i++, c = text[i])
		if(!renderMap.count((char)c))return false;
	return true;
}
bool Font::leftSided(char* text, int size, sf::RenderWindow rw, int posX, int posY){
	for(int i = 0, c = text[0]; i < strlen(text); i++, c = text[i]){
		if(!renderMap.count((char)c))return false;
		sf::Texture tex;
		CharacterRender ch = renderMap[(char)c];
		tex.loadFromFile(filename, sf::IntRect(ch.posX0, ch.posY0, ch.sizeX, ch.sizeY));
		sf::RectangleShape rect;
		rect.setTexture(&tex, false);
		rect.setSize(sf::Vector2f(ch.sizeX, ch.sizeY));
		rect.setScale(size, size);
		rw.draw(rect);
		posX += ch.sizeX * size;
	}
	return true;
}
bool Font::centered(char* text, int size, sf::RenderWindow rw, int posX, int posY){
	int s = 0;
	for(int i = 0, c = text[0]; i < strlen(text); i++, c = text[i]){
		if(!renderMap.count((char)c))return false;
		s += renderMap[(char)c].sizeX * size;
	}
	return leftSided(text, size, rw, posX - s/2, posY);
}

sf::Font Font::ARIAL;
Font static Font::CIV1;
Font static Font::CIV2;
Font static Font::CIV3;
Font static Font::CIV4;
Font static Font::CIV5;
Font static Font::CIV6;
Font static Font::CIV7;
Font static Font::CIV8;

void Font::load(){
	Font::ARIAL.loadFromFile("Fonts/ARIAL.TTF");
	CIV1 = Font({
		{'!',  CharacterRender{ 11,  1, 2, 8}},
		{'"',  CharacterRender{ 21,  1, 3, 8}},
		{'♀',  CharacterRender{ 31,  1, 7, 8}},
		{'☻',  CharacterRender{ 41,  1, 6, 8}},
		{'%',  CharacterRender{ 51,  1, 6, 8}},
		{'&',  CharacterRender{ 61,  1, 5, 8}},
		{'\'', CharacterRender{ 71,  1, 1, 8}},
		{'{',  CharacterRender{ 81,  1, 3, 8}},
		{'}',  CharacterRender{ 91,  1, 3, 8}},
		{'*',  CharacterRender{101,  1, 5, 8}},
		{'+',  CharacterRender{111,  1, 5, 8}},
		{',',  CharacterRender{121,  1, 2, 8}},
		{'-',  CharacterRender{131,  1, 5, 8}},
		{'.',  CharacterRender{141,  1, 1, 8}},
		{'/',  CharacterRender{151,  1, 4, 8}},
		{'0',  CharacterRender{161,  1, 5, 8}},
		{'1',  CharacterRender{171,  1, 4, 8}},
		{'2',  CharacterRender{181,  1, 5, 8}},
		{'3',  CharacterRender{191,  1, 5, 8}},
		{'4',  CharacterRender{201,  1, 5, 8}},
		{'5',  CharacterRender{211,  1, 5, 8}},
		{'6',  CharacterRender{221,  1, 5, 8}},
		{'7',  CharacterRender{231,  1, 5, 8}},
		{'8',  CharacterRender{241,  1, 5, 8}},
		{'9',  CharacterRender{251,  1, 5, 8}},
		{':',  CharacterRender{261,  1, 2, 8}},
		{';',  CharacterRender{271,  1, 2, 8}},
		{'<',  CharacterRender{281,  1, 5, 8}},
		{'=',  CharacterRender{291,  1, 5, 8}},
		{'>',  CharacterRender{301,  1, 5, 8}},
		{'?',  CharacterRender{311,  1, 5, 8}},

		{'A',  CharacterRender{ 11, 11, 6, 8}},
		{'B',  CharacterRender{ 21, 11, 6, 8}},
		{'C',  CharacterRender{ 31, 11, 6, 8}},
		{'D',  CharacterRender{ 41, 11, 6, 8}},
		{'E',  CharacterRender{ 51, 11, 6, 8}},
		{'F',  CharacterRender{ 61, 11, 6, 8}},
		{'G',  CharacterRender{ 71, 11, 6, 8}},
		{'H',  CharacterRender{ 81, 11, 6, 8}},
		{'I',  CharacterRender{ 91, 11, 6, 8}},
		{'J',  CharacterRender{101, 11, 6, 8}},
		{'K',  CharacterRender{111, 11, 6, 8}},
		{'L',  CharacterRender{121, 11, 6, 8}},
		{'M',  CharacterRender{131, 11, 6, 8}},
		{'N',  CharacterRender{141, 11, 6, 8}},
		{'O',  CharacterRender{151, 11, 6, 8}},
		{'P',  CharacterRender{161, 11, 6, 8}},
		{'Q',  CharacterRender{171, 11, 6, 8}},
		{'R',  CharacterRender{181, 11, 6, 8}},
		{'S',  CharacterRender{191, 11, 6, 8}},
		{'T',  CharacterRender{201, 11, 6, 8}},
		{'U',  CharacterRender{211, 11, 6, 8}},
		{'V',  CharacterRender{221, 11, 6, 8}},
		{'W',  CharacterRender{231, 11, 6, 8}},
		{'X',  CharacterRender{241, 11, 6, 8}},
		{'Y',  CharacterRender{251, 11, 6, 8}},
		{'Z',  CharacterRender{261, 11, 6, 8}},
		{'[',  CharacterRender{271, 11, 3, 8}},
		{'☺',  CharacterRender{281, 11, 7, 8}},
		{']',  CharacterRender{291, 11, 3, 8}},
		{'√',  CharacterRender{301, 11, 6, 8}},
		{'·',  CharacterRender{311, 11, 8, 8}},

		{'a',  CharacterRender{ 11, 21, 5, 8}},
		{'b',  CharacterRender{ 21, 21, 5, 8}},
		{'c',  CharacterRender{ 31, 21, 5, 8}},
		{'d',  CharacterRender{ 41, 21, 5, 8}},
		{'e',  CharacterRender{ 51, 21, 5, 8}},
		{'f',  CharacterRender{ 61, 21, 5, 8}},
		{'g',  CharacterRender{ 71, 21, 5, 8}},
		{'h',  CharacterRender{ 81, 21, 5, 8}},
		{'i',  CharacterRender{ 91, 21, 5, 8}},
		{'j',  CharacterRender{101, 21, 5, 8}},
		{'k',  CharacterRender{111, 21, 5, 8}},
		{'l',  CharacterRender{121, 21, 5, 8}},
		{'m',  CharacterRender{131, 21, 5, 8}},
		{'n',  CharacterRender{141, 21, 5, 8}},
		{'o',  CharacterRender{151, 21, 5, 8}},
		{'p',  CharacterRender{161, 21, 5, 8}},
		{'q',  CharacterRender{171, 21, 5, 8}},
		{'r',  CharacterRender{181, 21, 5, 8}},
		{'s',  CharacterRender{191, 21, 5, 8}},
		{'t',  CharacterRender{201, 21, 5, 8}},
		{'u',  CharacterRender{211, 21, 5, 8}},
		{'v',  CharacterRender{221, 21, 5, 8}},
		{'w',  CharacterRender{231, 21, 5, 8}},
		{'x',  CharacterRender{241, 21, 5, 8}},
		{'y',  CharacterRender{251, 21, 5, 8}},
		{'z',  CharacterRender{261, 21, 5, 8}},
		{'┬',  CharacterRender{271, 21, 7, 8}},
		{'○',  CharacterRender{281, 21, 5, 8}},
		{'↨',  CharacterRender{291, 21, 7, 8}},
		{'℗',  CharacterRender{301, 21, 7, 8}},
		{' ',  CharacterRender{311, 21, 4, 8}}
	}, "resources/FONTS.gif");
}
