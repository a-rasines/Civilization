/*
 * Fonts.h
 *
 *  Created on: 12 may 2022
 *      Author: algtc
 */

#ifndef WINDOWOBJECTS_FONTS_H_
#define WINDOWOBJECTS_FONTS_H_
#include <SFML/Graphics.hpp>
#include <map>
struct CharacterRender{
	int posX0;
	int posY0;
	int sizeX;
};
class Font{
	public:
		sf::Font static ARIAL;
		Font static CIV1;
		Font static CIV2;
		Font static CIV3;
		Font static CIV4;
		Font static CIV5;
		Font static CIV6;
		Font static CIV7;
		Font static CIV8;
		void static load();
		Font();
		Font(std::map<char, CharacterRender> map, char* filename, int size);
		bool canLoad(char* text);
		bool leftSided(char* text, int size, sf::RenderWindow rw, int posX, int posY);
		bool centered(char* text, int size, sf::RenderWindow rw, int posX, int posY);
	private:
		std::map<char, CharacterRender> renderMap;
		char* filename;
		int sizeY;

};

#endif /* WINDOWOBJECTS_FONTS_H_ */
