/*
 * Sprite.cpp
 *
 *  Created on: 18 may 2022
 *      Author: algtc
 */

#include "Sprite.h"
using namespace sprite;
//0 16 32 48 64 80 96 112 128 144 160 176 192 208 224 240 256 272 288 304 320
AllowedTroopTypes AllowedTroopTypes::AIR = AllowedTroopTypes(1);
AllowedTroopTypes AllowedTroopTypes::GROUND = AllowedTroopTypes(2);
AllowedTroopTypes AllowedTroopTypes::WATER = AllowedTroopTypes(4);
AllowedTroopTypes AllowedTroopTypes::NONE = AllowedTroopTypes(0);
