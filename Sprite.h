/*
 * Sprite.h
 *
 *  Created on: 18 may 2022
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include <string>
namespace Sprite{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              INICIO DE TROPAS
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	struct TroopData{
		int textureX;
		int textureY;
		int sizeX;
		int sizeY;
		int damage;
		int defense;
		int movements;
		int cost;
	};
	struct TransporterData : public TroopData{
		TransporterData(int textureX, int textureY, int sizeX, int sizeY, int damage, int defense, int movements, int cost, int capacity){
			TroopData::textureX = textureX;
			TroopData::textureY = textureY;
			TroopData::sizeX = sizeX;
			TroopData::sizeY = sizeY;
			TroopData::damage = damage;
			TroopData::defense = defense;
			TroopData::movements = movements;
			TroopData::cost = cost;
			TransporterData::capacity = capacity;
		}
		int capacity;
	};
	struct WaterTroopData : public TroopData{
		WaterTroopData(int textureX, int textureY, int sizeX, int sizeY, int damage, int defense, int movements, int cost){
			TroopData::textureX = textureX;
			TroopData::textureY = textureY;
			TroopData::sizeX = sizeX;
			TroopData::sizeY = sizeY;
			TroopData::damage = damage;
			TroopData::defense = defense;
			TroopData::movements = movements;
			TroopData::cost = cost;
		}
	};
	struct AirTroopData : public TroopData{
		AirTroopData(int textureX, int textureY, int sizeX, int sizeY, int damage, int defense, int movements, int cost){
			TroopData::textureX = textureX;
			TroopData::textureY = textureY;
			TroopData::sizeX = sizeX;
			TroopData::sizeY = sizeY;
			TroopData::damage = damage;
			TroopData::defense = defense;
			TroopData::movements = movements;
			TroopData::cost = cost;
		}
	};
	enum class TroopType{
		SETTLER,
		MILITIA,
		PHALANX,
		LEGION,
		MUSKETEER,
		RIFLEMEN,
		CAVALRY,
		KNIGHT,
		CATAPULT,
		CANNON,
		CHARIOT,
		ARMOR,
		MECH_INF,
		ARTILLERY,
		FIGHTER,
		BOMBER,
		TRIREME,
		SAIL,
		FRIGATE,
		IRONCLAD,
		CRUISER,
		BATTLESHIP,
		SUBMARINE,
		CARRIER,
		TRANSPORT,
		NUCLEAR,
		DIPLOMAT,
		CARAVAN,
		NONE //Valor para tener constancia del tamaño del enum

	};
	const TroopData Troop[(int)TroopType::NONE] = {
			(TroopData) {1,161,15,15, 0, 1, 1, 40},//Settler
			(TroopData) {17, 161, 15, 15, 1, 1, 1, 10},//Militia
			(TroopData) {33, 161, 15, 15, 1, 2, 1, 20},//Phalanx
			(TroopData) {49, 161, 15, 15, 3, 1, 1, 20},//Legion
			(TroopData) {65, 161, 15, 15, 2, 3, 1, 30},//Musketeer
			(TroopData) {81, 161, 15, 15, 3, 5, 1, 30},//Riflemen
			(TroopData) {97, 161, 15, 15, 2, 1, 2, 20},//Cavalry
			(TroopData) {113, 161, 15, 15, 4, 2, 2, 40},//Knight
			(TroopData) {129, 161, 15, 15, 6, 1, 1, 40},//Catapult
			(TroopData) {145, 161, 15, 15, 8, 1, 1, 40},//Cannon
			(TroopData) {161, 161, 15, 15, 4, 1, 2, 40},//Chariot
			(TroopData) {177, 161, 15, 15, 10, 5, 3, 80},//Armor
			(TroopData) {193, 161, 15, 15, 6, 6, 3, 50},//Mech_inf
			(TroopData) {209, 161, 15, 15, 12, 2, 2, 60},//Artillery
			(AirTroopData) {225, 161, 15, 15, 4, 2, 10, 60},//Fighter
			(AirTroopData) {241, 161, 15, 15, 12, 1, 8, 120},//Bomber
			(TransporterData) {257, 161, 15, 15, 1, 0, 3, 40, 2},//Trireme
			(TransporterData) {273, 161, 15, 15, 1, 1, 3, 40, 3},//Sail
			(TransporterData) {289, 161, 15, 15, 2, 2, 3, 40, 4},//Frigate
			(WaterTroopData) {305, 161, 15, 15, 4, 4, 4, 60},//Ironclad
			(WaterTroopData) {1, 177, 15, 15, 6, 6, 6, 80},//Cruiser
			(WaterTroopData) {17, 177, 15, 15, 18, 12, 4, 160},//Battleship
			(WaterTroopData) {33, 177, 15, 15, 8, 2, 3, 50},//Submarine
			(TransporterData) {49, 177, 15, 15, 1, 12, 5, 160, 8},//Carrier
			(TransporterData) {65, 177, 15, 15, 0, 3, 4, 50, 8},//Transport
			(TroopData) {81, 177, 15, 15, 99, 0, 16, 160},//Nuclear
			(TroopData) {97, 177, 15, 15, 0, 0, 2, 30},//Diplomat
			(TroopData) {113, 177, 15, 15, 0, 1, 1, 50} //Caravan
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              FIN DE TROPAS
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              INICIO DE TERRENOS
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	class AllowedTroopTypes{
		public:
			AllowedTroopTypes(){
				value = 0;
			}
			bool isAllowed(AllowedTroopTypes other){
				if(other.value == value)return true;
				else if(other.value > value)return false;
				return compare(other.value);
			}
			static AllowedTroopTypes
				AIR,
				GROUND,
				WATER,
				NONE;
			AllowedTroopTypes operator+(AllowedTroopTypes other){
				return AllowedTroopTypes(value + other.value);
			}
		private:
			int value;
			std::string toBinary(int n){
				std::string r;
				while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
				return r;
			}
			bool compare(int otherValue){
				std::string v1 = toBinary(value);
				std::string v2 = toBinary(otherValue);
				for(unsigned int i = 0; i < (v1.length()>v2.length()? v2.length():v1.length());i++){
					if(v1[i] == 1 && v2[i] == 0)return false;
				}
				return true;
			}
			AllowedTroopTypes(int val){
				value = val;
			}
//			enum {
//				NONE = 0,
//				GROUND = 1,
//				AIR = 2,
//				//GROUND + AIR = 3
//				WATER = 4,
//				//GROUND + WATER = 5
//				//AIR + WATER = 6
//				//GROUND + AIR + WATER = 7
//				ALL = 8
	};
	struct TerrainType{
		TerrainType(){
			this->textureX = 0;
			this->textureY = 0;
			this->file = "";
			this->allowedTroops = new AllowedTroopTypes();
		}
		TerrainType(int textureX, int textureY, const char* file, AllowedTroopTypes *allowedTroops){
			this->textureX = textureX;
			this->textureY = textureY;
			this->file = file;
			this->allowedTroops = allowedTroops;
		}
		int textureX;
		int textureY;
		const int sizeX = 16;
		const int sizeY = 16;
		const char* file;
		AllowedTroopTypes *allowedTroops; //Valor de AllowedTroopTypes
	};
	class Connections {
		public:
			Connections(){

				value = 0;
			}
			virtual ~Connections(){

			}
			operator int() const {
				return x[value];
			}
			Connections operator+(Connections other) const{
				return Connections(this->value + other.value);
			}
			Connections(int value){
				this->value = value;
			}
		private:
			int value;
			static constexpr const int x[]= {0, 16, 64, 80, 128, 144, 192, 208, 32, 48, 96, 112, 160, 176, 224, 240};
	};
	enum class StackableConnections{
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_RIGHT,
		UP_LEFT,
		DOWN_RIGHT,
		DOWN_LEFT
	};
	class NonStackableTerrainType : public TerrainType{
		public:
			NonStackableTerrainType(){

			}
			NonStackableTerrainType(int y, const char* file, AllowedTroopTypes *allowedTroops){
				this->file = file;
				textureY = y;
				textureX = 0;
				this->allowedTroops = allowedTroops;
			};
			TerrainType generate(Connections con){
				return (TerrainType){(int) con, textureY, file, allowedTroops};
			}
			NonStackableTerrainType operator+ (Connections c){
				return NonStackableTerrainType(textureY, (int) c, file, allowedTroops);
			}
		private:
			NonStackableTerrainType(int y, int x, const char* file, AllowedTroopTypes *allowedTroops){
				this->file = file;
				textureY = y;
				textureX = x;
				this->allowedTroops = allowedTroops;
			};
	};
	class StackedTerrainType : public TerrainType{
		public:
			enum{
				ROAD,
				RAIL
			};
	};
	static const Connections
		NONE(0),
		UP(1),
		DOWN(2),
		LEFT(4),
		RIGHT(8);
	static const NonStackableTerrainType
	RIVER(80, "SP257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	NOT_FROZEN_SEA(64, "SPRITES.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::WATER)),
	FROZEN_RIVER(80, "SPRITES.PIC_256.gif",new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	NOT_SEA(160, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::WATER)),
	MOUNTAIN(80, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	MOUNT(64, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	ICE(96, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	SNOW(112, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	CROPS(16, "TER257.PIC_256.gif",new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	FOREST(48, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	SWAMP(128, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	WATERFOREST(144, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR)),
	RIVER_SEA(176 ,"TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR + AllowedTroopTypes::WATER)),
	BIG_CROPS(0, "TER257.PIC_256.gif", new (AllowedTroopTypes)(AllowedTroopTypes::GROUND + AllowedTroopTypes::AIR));

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//                              FIN DE TERRENOS
	/////////////////////////////////////////////////////////////////////////////////////////////////////
};

#endif /* SPRITE_H_ */
