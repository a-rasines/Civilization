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
	filename = (char*)"\0";
	sizeY = 0;
}
Font::Font(std::map<char, CharacterRender> map, char* filename, int size){
	this->renderMap = map;
	this->filename = filename;
	this->sizeY = size;
}
bool Font::canLoad(char* text){
	for(int i = 0, c = text[0]; i < (int)strlen(text); i++, c = text[i])
		if(!renderMap.count((char)c))return false;
	return true;
}
bool Font::leftSided(char* text, int size, sf::RenderWindow rw, int posX, int posY){
	for(int i = 0, c = text[0]; i < (int)strlen(text); i++, c = text[i]){
		if(!renderMap.count((char)c))return false;
		sf::Texture tex;
		CharacterRender ch = renderMap[(char)c];
		tex.loadFromFile(filename, sf::IntRect(ch.posX0, ch.posY0, ch.sizeX, sizeY));
		sf::RectangleShape rect;
		rect.setTexture(&tex, false);
		rect.setSize(sf::Vector2f(ch.sizeX, sizeY));
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
Font Font::CIV1;
Font Font::CIV2;
Font Font::CIV3;
Font Font::CIV4;
Font Font::CIV5;
Font Font::CIV6;
Font Font::CIV7;
Font Font::CIV8;

void Font::load(){
	Font::ARIAL.loadFromFile("Fonts/ARIAL.TTF");
	int y0 = 0;
	CIV1 = Font({
		{'!',  CharacterRender{ 11, (y0+=1), 2}},//1
		{'"',  CharacterRender{ 21, y0      , 3}},
		{'♀',  CharacterRender{ 31, y0      , 7}},
		{'$',  CharacterRender{ 41, y0      , 6}},
		{'%',  CharacterRender{ 51, y0      , 6}},
		{'&',  CharacterRender{ 61, y0      , 5}},
		{'\'', CharacterRender{ 71, y0      , 1}},
		{'(',  CharacterRender{ 81, y0      , 3}},
		{')',  CharacterRender{ 91, y0      , 3}},
		{'*',  CharacterRender{101, y0      , 5}},
		{'+',  CharacterRender{111, y0      , 5}},
		{',',  CharacterRender{121, y0      , 2}},
		{'-',  CharacterRender{131, y0      , 5}},
		{'.',  CharacterRender{141, y0      , 1}},
		{'/',  CharacterRender{151, y0      , 4}},
		{'0',  CharacterRender{161, y0      , 5}},
		{'1',  CharacterRender{171, y0      , 4}},
		{'2',  CharacterRender{181, y0      , 5}},
		{'3',  CharacterRender{191, y0      , 5}},
		{'4',  CharacterRender{201, y0      , 5}},
		{'5',  CharacterRender{211, y0      , 5}},
		{'6',  CharacterRender{221, y0      , 5}},
		{'7',  CharacterRender{231, y0      , 5}},
		{'8',  CharacterRender{241, y0      , 5}},
		{'9',  CharacterRender{251, y0      , 5}},
		{':',  CharacterRender{261, y0      , 2}},
		{';',  CharacterRender{271, y0      , 2}},
		{'<',  CharacterRender{281, y0      , 5}},
		{'=',  CharacterRender{291, y0      , 5}},
		{'>',  CharacterRender{301, y0      , 5}},
		{'?',  CharacterRender{311, y0      , 5}},

		{'A',  CharacterRender{ 11, (y0+=10), 6}},//11
		{'B',  CharacterRender{ 21, y0      , 6}},
		{'C',  CharacterRender{ 31, y0      , 6}},
		{'D',  CharacterRender{ 41, y0      , 6}},
		{'E',  CharacterRender{ 51, y0      , 6}},
		{'F',  CharacterRender{ 61, y0      , 6}},
		{'G',  CharacterRender{ 71, y0      , 6}},
		{'H',  CharacterRender{ 81, y0      , 6}},
		{'I',  CharacterRender{ 91, y0      , 4}},
		{'J',  CharacterRender{101, y0      , 6}},
		{'K',  CharacterRender{111, y0      , 6}},
		{'L',  CharacterRender{121, y0      , 6}},
		{'M',  CharacterRender{131, y0      , 7}},
		{'N',  CharacterRender{141, y0      , 6}},
		{'O',  CharacterRender{151, y0      , 6}},
		{'P',  CharacterRender{161, y0      , 6}},
		{'Q',  CharacterRender{171, y0      , 6}},
		{'R',  CharacterRender{181, y0      , 6}},
		{'S',  CharacterRender{191, y0      , 6}},
		{'T',  CharacterRender{201, y0      , 6}},
		{'U',  CharacterRender{211, y0      , 6}},
		{'V',  CharacterRender{221, y0      , 7}},
		{'W',  CharacterRender{231, y0      , 7}},
		{'X',  CharacterRender{241, y0      , 6}},
		{'Y',  CharacterRender{251, y0      , 6}},
		{'Z',  CharacterRender{261, y0      , 6}},
		{'[',  CharacterRender{271, y0      , 3}},
		{'☺',  CharacterRender{281, y0      , 7}},
		{']',  CharacterRender{291, y0      , 3}},
		{'√',  CharacterRender{301, y0      , 6}},
		{'·',  CharacterRender{311, y0      , 8}},

		{'a',  CharacterRender{ 11, (y0+=10), 5}},//21
		{'b',  CharacterRender{ 21, y0      , 5}},
		{'c',  CharacterRender{ 31, y0      , 4}},
		{'d',  CharacterRender{ 41, y0      , 5}},
		{'e',  CharacterRender{ 51, y0      , 5}},
		{'f',  CharacterRender{ 61, y0      , 3}},
		{'g',  CharacterRender{ 71, y0      , 5}},
		{'h',  CharacterRender{ 81, y0      , 4}},
		{'i',  CharacterRender{ 91, y0      , 3}},
		{'j',  CharacterRender{101, y0      , 4}},
		{'k',  CharacterRender{111, y0      , 4}},
		{'l',  CharacterRender{121, y0      , 3}},
		{'m',  CharacterRender{131, y0      , 5}},
		{'n',  CharacterRender{141, y0      , 4}},
		{'o',  CharacterRender{151, y0      , 5}},
		{'p',  CharacterRender{161, y0      , 5}},
		{'q',  CharacterRender{171, y0      , 5}},
		{'r',  CharacterRender{181, y0      , 5}},
		{'s',  CharacterRender{191, y0      , 5}},
		{'t',  CharacterRender{201, y0      , 4}},
		{'u',  CharacterRender{211, y0      , 5}},
		{'v',  CharacterRender{221, y0      , 5}},
		{'w',  CharacterRender{231, y0      , 5}},
		{'x',  CharacterRender{241, y0      , 4}},
		{'y',  CharacterRender{251, y0      , 4}},
		{'z',  CharacterRender{261, y0      , 4}},
		{'┬',  CharacterRender{271, y0      , 7}},
		{'○',  CharacterRender{281, y0      , 5}},
		{'↨',  CharacterRender{291, y0      , 7}},
		{'℗',  CharacterRender{301, y0      , 7}},
		{' ',  CharacterRender{311, y0      , 4}}
	}, "resources/FONTS.gif", 8);
	CIV2 = Font({
			{'!',  CharacterRender{ 11, (y0+=11), 3}},//32
			{'"',  CharacterRender{ 21, y0      , 3}},
			{'♀',  CharacterRender{ 31, y0      , 3}},
			{'$',  CharacterRender{ 41, y0      , 4}},
			{'%',  CharacterRender{ 51, y0      , 3}},
			{'&',  CharacterRender{ 61, y0      , 3}},
			{'\'', CharacterRender{ 71, y0      , 3}},
			{'(',  CharacterRender{ 81, y0      , 3}},
			{')',  CharacterRender{ 91, y0      , 3}},
			{'*',  CharacterRender{101, y0      , 4}},
			{'+',  CharacterRender{111, y0      , 3}},
			{',',  CharacterRender{121, y0      , 3}},
			{'-',  CharacterRender{131, y0      , 5}},
			{'.',  CharacterRender{141, y0      , 3}},
			{'/',  CharacterRender{151, y0      , 3}},
			{'0',  CharacterRender{161, y0      , 4}},
			{'1',  CharacterRender{171, y0      , 3}},
			{'2',  CharacterRender{181, y0      , 4}},
			{'3',  CharacterRender{191, y0      , 4}},
			{'4',  CharacterRender{201, y0      , 4}},
			{'5',  CharacterRender{211, y0      , 4}},
			{'6',  CharacterRender{221, y0      , 4}},
			{'7',  CharacterRender{231, y0      , 4}},
			{'8',  CharacterRender{241, y0      , 4}},
			{'9',  CharacterRender{251, y0      , 4}},
			{':',  CharacterRender{261, y0      , 3}},
			{';',  CharacterRender{271, y0      , 3}},
			{'<',  CharacterRender{281, y0      , 3}},
			{'=',  CharacterRender{291, y0      , 3}},
			{'>',  CharacterRender{301, y0      , 3}},
			{'?',  CharacterRender{311, y0      , 4}},

			{'A',  CharacterRender{ 11, (y0+=8), 4}},//40
			{'B',  CharacterRender{ 21, y0      , 4}},
			{'C',  CharacterRender{ 31, y0      , 4}},
			{'D',  CharacterRender{ 41, y0      , 4}},
			{'E',  CharacterRender{ 51, y0      , 4}},
			{'F',  CharacterRender{ 61, y0      , 4}},
			{'G',  CharacterRender{ 71, y0      , 4}},
			{'H',  CharacterRender{ 81, y0      , 4}},
			{'I',  CharacterRender{ 91, y0      , 4}},
			{'J',  CharacterRender{101, y0      , 4}},
			{'K',  CharacterRender{111, y0      , 4}},
			{'L',  CharacterRender{121, y0      , 4}},
			{'M',  CharacterRender{131, y0      , 5}},
			{'N',  CharacterRender{141, y0      , 4}},
			{'O',  CharacterRender{151, y0      , 4}},
			{'P',  CharacterRender{161, y0      , 4}},
			{'Q',  CharacterRender{171, y0      , 4}},
			{'R',  CharacterRender{181, y0      , 4}},
			{'S',  CharacterRender{191, y0      , 4}},
			{'T',  CharacterRender{201, y0      , 3}},
			{'U',  CharacterRender{211, y0      , 4}},
			{'V',  CharacterRender{221, y0      , 4}},
			{'W',  CharacterRender{231, y0      , 5}},
			{'X',  CharacterRender{241, y0      , 4}},
			{'Y',  CharacterRender{251, y0      , 4}},
			{'Z',  CharacterRender{261, y0      , 4}},
			{'[',  CharacterRender{271, y0      , 3}},
			{'☺',  CharacterRender{281, y0      , 2}},
			{']',  CharacterRender{291, y0      , 3}},
			{'√',  CharacterRender{301, y0      , 2}},
			{'·',  CharacterRender{311, y0      , 2}},

			{'a',  CharacterRender{ 11, (y0+=8), 4}},//48
			{'b',  CharacterRender{ 21, y0      , 4}},
			{'c',  CharacterRender{ 31, y0      , 4}},
			{'d',  CharacterRender{ 41, y0      , 4}},
			{'e',  CharacterRender{ 51, y0      , 4}},
			{'f',  CharacterRender{ 61, y0      , 4}},
			{'g',  CharacterRender{ 71, y0      , 4}},
			{'h',  CharacterRender{ 81, y0      , 4}},
			{'i',  CharacterRender{ 91, y0      , 3}},
			{'j',  CharacterRender{101, y0      , 4}},
			{'k',  CharacterRender{111, y0      , 4}},
			{'l',  CharacterRender{121, y0      , 3}},
			{'m',  CharacterRender{131, y0      , 5}},
			{'n',  CharacterRender{141, y0      , 4}},
			{'o',  CharacterRender{151, y0      , 4}},
			{'p',  CharacterRender{161, y0      , 4}},
			{'q',  CharacterRender{171, y0      , 4}},
			{'r',  CharacterRender{181, y0      , 4}},
			{'s',  CharacterRender{191, y0      , 4}},
			{'t',  CharacterRender{201, y0      , 3}},
			{'u',  CharacterRender{211, y0      , 4}},
			{'v',  CharacterRender{221, y0      , 4}},
			{'w',  CharacterRender{231, y0      , 5}},
			{'x',  CharacterRender{241, y0      , 4}},
			{'y',  CharacterRender{251, y0      , 4}},
			{'z',  CharacterRender{261, y0      , 4}},
			{'┬',  CharacterRender{271, y0      , 3}},
			{'○',  CharacterRender{281, y0      , 2}},
			{'↨',  CharacterRender{291, y0      , 7}},
			{'℗',  CharacterRender{301, y0      , 2}},
			{' ',  CharacterRender{311, y0      , 2}}
		}, (char*)"resources/FONTS.gif", 6);
}
