/*
 * Sprite.cpp
 *
 *  Created on: 18 may 2022
 *      Author: algtc
 */

#include "Sprite.h"
using namespace Sprite;
//0 16 32 48 64 80 96 112 128 144 160 176 192 208 224 240 256 272 288 304 320
AllowedTroopTypes AllowedTroopTypes::AIR = AllowedTroopTypes(1);
AllowedTroopTypes AllowedTroopTypes::GROUND = AllowedTroopTypes(2);
AllowedTroopTypes AllowedTroopTypes::WATER = AllowedTroopTypes(4);
AllowedTroopTypes AllowedTroopTypes::NONE = AllowedTroopTypes(0);
NonStackableTerrainType NonStackableTerrainType::RIVER = NonStackableTerrainType(80, "SP257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::NOT_FROZEN_SEA = NonStackableTerrainType(64, "SPRITES.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::WATER));
NonStackableTerrainType NonStackableTerrainType::FROZEN_RIVER = NonStackableTerrainType(80, "SPRITES.PIC_256.gif",new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::NOT_SEA = NonStackableTerrainType(160, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::WATER));
NonStackableTerrainType NonStackableTerrainType::MOUNTAIN = NonStackableTerrainType(80, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::MOUNT = NonStackableTerrainType(64, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::ICE = NonStackableTerrainType(112, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::CROPS = NonStackableTerrainType(16, "TER257.PIC_256.gif",new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::FOREST = NonStackableTerrainType(48, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::SWAMP = NonStackableTerrainType(128, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::WATERFOREST = NonStackableTerrainType(144, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
NonStackableTerrainType NonStackableTerrainType::RIVER_SEA = NonStackableTerrainType(176 ,"TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR + AllowedTroopTypes::WATER));
NonStackableTerrainType NonStackableTerrainType::BIG_CROPS = NonStackableTerrainType(0, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));
Connections Connections::NONE = Connections(0);
Connections Connections::UP = Connections(1);
Connections Connections::DOWN = Connections(2);
Connections Connections::LEFT = Connections(4);
Connections Connections::RIGHT = Connections(8);
