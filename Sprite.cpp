/*
 * Sprite.cpp
 *
 *  Created on: 18 may 2022
 *      Author: algtc
 */

#include "Sprite.h"
using namespace Sprite;
//0 16 32 48 64 80 96 112 128 144 160 176 192 208 224 240 256 272 288 304 320
NonStackableTerrainTypes NonStackableTerrainTypes::RIVER = NonStackableTerrainTypes(80, "SP257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::NOT_FROZEN_SEA = NonStackableTerrainTypes(64, "SPRITES.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::FROZEN_RIVER = NonStackableTerrainTypes(80, "SPRITES.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::NOT_SEA = NonStackableTerrainTypes(160, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::MOUNTAIN = NonStackableTerrainTypes(80, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::MOUNT = NonStackableTerrainTypes(64, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::ICE = NonStackableTerrainTypes(112, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::CROPS = NonStackableTerrainTypes(16, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::FOREST = NonStackableTerrainTypes(48, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::SWAMP = NonStackableTerrainTypes(128, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::WATERFOREST = NonStackableTerrainTypes(144, "TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::RIVER_SEA = NonStackableTerrainTypes(176 ,"TER257.PIC_256.gif");
NonStackableTerrainTypes NonStackableTerrainTypes::BIG_CROPS = NonStackableTerrainTypes(0, "TER257.PIC_256.gif");
Connections Connections::NONE = Connections(0);
Connections Connections::UP = Connections(1);
Connections Connections::DOWN = Connections(2);
Connections Connections::LEFT = Connections(4);
Connections Connections::RIGHT = Connections(8);
