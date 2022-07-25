#include "menuEjemplo.h"
#include "MapWindow.h"

using namespace std;
using namespace sprite;
sf::Color MapWindow::playerColors[] = {
		// 0xRRGGBBAA
		sf::Color::Black,
		sf::Color(0xFFFFFFFF),
		sf::Color(0xf75757FF), //In the future this will be for barbarians
		sf::Color(0x5ed85cFF),
		sf::Color(0x7288fcFF),
		sf::Color(0xf04fe1FF),
		sf::Color(0xdeff8fFF)
};
void MapWindow::start(){
	addMenuItem(Window::MenuItem{
		L"&GAME",
		{
			Window::MenuItem{L"&Tax Rate", TAX_RATE},
			Window::MenuItem{L"&Luxuries Rate", LUXURIES_RATE},
			Window::MenuItem{L"&Find City", FIND_CITY},
			Window::MenuItem{L"&Options", OPTIONS},
			Window::MenuItem{L"&Save Game", SAVE_GAME},
			Window::MenuItem{L"&REVOLUTION!", REVOLUTION},
			Window::MenuItem{},
			Window::MenuItem{L"&Retire", RETIRE},
			Window::MenuItem{L"&QUIT", QUIT}
		}
	});
	addMenuItem(Window::MenuItem{
		L"&ORDERS",
		{
			Window::MenuItem{L"&No Orders (space)", NO_ORDERS},
			Window::MenuItem{L"&Found New City (b)", FOUND_NEW_CITY},
			Window::MenuItem{L"&Build Road (r)", BUILD_ROAD},
			Window::MenuItem{L"&Change To Forest (m)", CHANGE_TO_FOREST},
			Window::MenuItem{L"&Build Fortress (f)", BUILD_FORTRESS},
			Window::MenuItem{L"&Wait (w)", WAIT},
			Window::MenuItem{L"&Sentry (s)", SENTRY},
			Window::MenuItem{L"&GoTo", GOTO},
			Window::MenuItem{L"&Pillage (P)", PILLAGE},
			Window::MenuItem{},
			Window::MenuItem{L"&Disband Unit (D)", DISBAND_UNIT}
		}
	});
	addMenuItem(Window::MenuItem{
		L"&ADVISORS",
		{
			Window::MenuItem{L"&City Status (F1)", CITY_STATUS},
			Window::MenuItem{L"&Military Advisor (F2)", MILITARY_ADVISOR},
			Window::MenuItem{L"&Intelligence Advisor (F3)", INTELLIGENCE_ADVISOR},
			Window::MenuItem{L"&Attitude Advisor (F4)", ATTITUDE_ADVISOR},
			Window::MenuItem{L"&Trade Advisor (F5)", TRADE_ADVISOR},
			Window::MenuItem{L"&Science Advisor (F6)", SCIENCE_ADVISOR},
		}
	});
	addMenuItem(Window::MenuItem{
		L"&WORLD",
		{
			Window::MenuItem{L"&Wonders of the World (F7)", WONDERS_OF_THE_WORLD},
			Window::MenuItem{L"&Top 5 Cities (F8)", TOP_5_CITIES},
			Window::MenuItem{L"&Civilization Score (F9)", CIVILIZATION_SCORE},
			Window::MenuItem{L"&World Map (F10)", WORLD_MAP},
			Window::MenuItem{L"&Demographics", DEMOGRAPHICS},
			Window::MenuItem{L"&SpaceShips", SPACESHIPS},
		}
	});
	addMenuItem(Window::MenuItem{
		L"&CIVILOPEDIA",
		{
			Window::MenuItem{L"&Complete", COMPLETE},
			Window::MenuItem{L"&Civilization Advances", CIVILIZATION_ADVANCES},
			Window::MenuItem{L"&City Improvements", CITY_IMPROVEMENTS},
			Window::MenuItem{L"&Military Units", MILITARY_UNITS},
			Window::MenuItem{L"&Terrain Types", TERRAIN_TYPES},
			Window::MenuItem{L"&Miscellaneous", MISCELLANEOUS},
		}
	});
	reposition(x, y);
	WindowManager::Dimension size = Window::manager->getWindowSize();
	mapView.create(generateView(0, 0, size.x, size.y));
	setResizable(true);
	std::string file = "resources/" + (std::string)RIVER.file;
	background.loadFromFile(file, sf::IntRect(RIVER.textureX, RIVER.textureY, RIVER.sizeX, RIVER.sizeY));
}

void MapWindow::onClientStart(){
	manager->sendMessage(message::other(SocketMessage::SYNC));
}
void MapWindow::onServerStart(){
	int color = 0;
	activeCities.push_back(CiudadInst(0, menuEjemplo::logeado.id, 0, (char*)"Test", 0, 0, 0, 0, 5, 6));
	while(playerColors[color] == sf::Color::Black)color = rand() % (sizeof(playerColors) / sizeof(playerColors[0]));
	playerColorMap.insert(std::pair<int,sf::Color>(menuEjemplo::logeado.id, playerColors[color]));
	playerColors[color] = sf::Color::Black; //Way to know if color has been already used
	activeTroops.push_back(SettlerInst(0, menuEjemplo::logeado.id, 0, 5, 5));
}

void MapWindow::onMessage(char* message){
	std::vector<std::string> params;
	std::string str = message;
	int spaceNeeded = 0;
	for(unsigned int i = 0; i < strlen(message); i++){
		if(message[i] == ':'){
			params.push_back(str.substr(i - spaceNeeded , spaceNeeded));
			spaceNeeded = 0;
		}else spaceNeeded++;
	}
	std::cout << "Processing message: ";
	for(unsigned int i = 0; i < params.size(); i++)std::cout << "param" << i << "= " << params[i] << " ";
	std::cout << "\n";
	switch(strtol(params[0].c_str(), NULL, 10)){
		case (int)SocketMessage::SYNC:
			std::cout.flush();
			manager->sendMessage(message::infoSync(InfoSync::SERVER_ID, activeTroops[0].idServidor));
			break;
		case (int)SocketMessage::CONT:
			break;
		case (int)SocketMessage::INFO_SYNC:{
			switch(strtol(params[1].c_str(), NULL, 10)){
				case (int)InfoSync::SERVER_ID:
					this->serverID = strtol(params[2].c_str(), NULL, 10);
					manager->sendMessage(message::infoSync(InfoSync::PLAYER_ID, menuEjemplo::logeado.id));
					break;
				case (int)InfoSync::PLAYER_ID:{
					bool exists = false;
					int id = strtol(params[2].c_str(), NULL, 10);
					for(TropaInst troop : activeTroops){
						if(troop.idJugador == id){
							exists = true;
							break;
						}
					}
					if(!exists){
						activeTroops.push_back(SettlerInst(activeTroops[0].idServidor, id, 0, 5, 5));
						int color = 0;
						while(playerColors[color] == sf::Color::Black)color = rand() % (sizeof(playerColors) / sizeof(playerColors[0]));
						playerColorMap.insert(std::pair<int,sf::Color>(id, playerColors[color]));
						playerColors[color] = sf::Color::Black; //Way to know if color has been already used
					}
					for(std::map<int,sf::Color>::iterator it = playerColorMap.begin(); it != playerColorMap.end(); ++it){
						manager->sendMessage(message::infoSync(InfoSync::PLAYER_COLOR, it->first, it->second.toInteger()));
					}
					for(TropaInst tropa: activeTroops){
						manager->sendMessage(message::initialTroopSync(&tropa));
					}
					break;
				}case (int)InfoSync::PLAYER_COLOR:
						playerColorMap.insert(std::pair<int, sf::Color>(strtol(params[2].c_str(), NULL, 10),sf::Color(strtol(params[3].c_str(), NULL, 10))));
						manager->sendMessage(message::other(SocketMessage::CONT));
						break;
			}
			break;
		}case SocketMessage::INITIAL_TROOP_SYNC:
			if(strtol(params[7].c_str(),NULL,10) == (int)sprite::TroopType::SETTLER){
				activeTroops.push_back(
					SettlerInst(
						serverID,
						strtol(params[1].c_str(),NULL,10),
						strtol(params[2].c_str(),NULL,10),
						strtol(params[3].c_str(),NULL,10),
						strtol(params[4].c_str(),NULL,10),
						strtol(params[5].c_str(),NULL,10),
						strtol(params[6].c_str(),NULL,10),
						strtol(params[8].c_str(),NULL,10),
						strtol(params[9].c_str(),NULL,10) == 0
					)
				);
			}else{
				activeTroops.push_back(
					TropaInst(
						serverID,
						strtol(params[1].c_str(),NULL,10),
						strtol(params[2].c_str(),NULL,10),
						strtol(params[3].c_str(),NULL,10),
						strtol(params[4].c_str(),NULL,10),
						strtol(params[5].c_str(),NULL,10),
						strtol(params[6].c_str(),NULL,10),
						strtol(params[7].c_str(),NULL,10),
						strtol(params[8].c_str(),NULL,10),
						strtol(params[9].c_str(),NULL,10) == 0
					)
				);
			}
			manager->sendMessage(message::other(SocketMessage::CONT));
			break;
		case SocketMessage::MOVE:
			troopMove(&activeTroops.front(),(Position)strtol(params[1].c_str(),NULL,10));
			break;
		case SocketMessage::ACTION:
			//TODO
			break;
		case SocketMessage::ADD_TROOP:
			//TODO
			break;
		case SocketMessage::BUILD_CITY:
			//TODO
			break;
		case SocketMessage::DESENTRY:
			//TODO
			break;
	}
//	if(message[0]=='0'){
//		int x,y;
//		sscanf(message,"0tropa a posicion:(%i,%i)",&x,&y);
//		if(activeTroops.front().idJugador!=menuEjemplo::logeado.id){
//			TropaInst actual = activeTroops.front();
//			troopMove(&actual, x, y);
//			activeTroops.erase(activeTroops.begin());
//			activeTroops.push_back(actual);
//			if(activeTroops.front().idJugador!=menuEjemplo::logeado.id){
//				Window::manager->sendMessage("ACK");
//			}
//		}
//	}else if(message[0]=='1'){
//		int a,b,c,d,e,f,g,h,i;
//		sscanf(message,"1Te envio tropa:%i,%i,%i,%i,%i,%i,%i,%i,%i",&a,&b,&c,&d,&e,&f,&g,&h,&i);
//		TropaInst t = {a,b,c,d,e,f,g,h,i};
//		activeTroops.push_back(t);
//		Window::manager->sendMessage("ACK");
//	}else if(message[0]=='2'){
//		for(TropaInst tr : activeTroops)
//			Window::manager->sendMessage((string("1Te envio tropa:"+to_string(tr.idServidor)+string(",")+to_string(tr.idJugador)+string(",")+to_string(tr.idTropa)+
//			string(",")+to_string(tr.estado)+string(",")+to_string(tr.mejorada)+string(",")+to_string(tr.posicionX)+
//			string(",")+to_string(tr.posicionY)+string(",")+to_string(tr.tipo)+string(",")+to_string(tr.vida))).c_str());
//	}
}
void MapWindow::update(){
	//std::cout << activeTroops.size();
	mapView.clear();
	for(Cell cell : activeCells){
		sf::Texture tex;
		std::string file = "resources/" + (std::string)cell.file;
		tex.loadFromFile(file, cell.texData);
		sf::RectangleShape rect;
		rect.setTexture(&background, false);
		rect.setSize(sf::Vector2f(cell.sizeX, cell.sizeY));
		rect.setPosition(sf::Vector2f(cell.posX, cell.posY));
		mapView.draw(rect);
		rect.setTexture(&tex, false);
		mapView.draw(rect);
	}
	moving = false;
	for(unsigned int i = 1; i < activeTroops.size(); i++){
		sf::Texture tex;
		TropaInst* t = &(activeTroops[i]);
		sprite::TroopData coso = sprite::Troop[t->tipo];
		tex.loadFromFile("resources/SP257.PIC_256.gif",sf::IntRect(coso.textureX,coso.textureY,coso.sizeX,coso.sizeY));
		sf::RectangleShape rect;
		rect.setTexture(&tex, false);
		rect.setFillColor(playerColorMap[t->idJugador]);
		rect.setSize(sf::Vector2f(coso.sizeX*zoom, coso.sizeY*zoom));
		if(t->renderingPositionX != t->posicionX || t->renderingPositionY != t->posicionY){
			moving = true;
			t->renderingPositionX = round(t->renderingPositionX + 0.2 * (t->renderingPositionX < t->posicionX) - 0.2 * (t->renderingPositionX > t->posicionX), 1);
			t->renderingPositionY = round(t->renderingPositionY + 0.2 * (t->renderingPositionY < t->posicionY) - 0.2 * (t->renderingPositionY > t->posicionY), 1);
		}
		rect.setPosition(sf::Vector2f(t->renderingPositionX*16*zoom-x, t->renderingPositionY*16*zoom-y));
		mapView.draw(rect);
	}
	for(unsigned int i = 0; i < activeCities.size(); i++){
		bool troop = false;

		for(TropaInst t : activeTroops)
			if(t.renderingPositionX == activeCities[i].posicionX && t.renderingPositionY == activeCities[i].posicionY){
				troop = true;
				break;
			}
		sf::RectangleShape rect;
		if(troop){
			rect.setSize(sf::Vector2f(16*zoom, 16*zoom));
			rect.setPosition(sf::Vector2f((activeCities[i].posicionX*16 - 1)*zoom-x, (activeCities[i].posicionY*16 - 1)*zoom-y));
			rect.setFillColor(sf::Color::Black);
			mapView.draw(rect);
		}
		rect.setPosition(sf::Vector2f(activeCities[i].posicionX*16*zoom-x, activeCities[i].posicionY*16*zoom-y));
		rect.setSize(sf::Vector2f(14*zoom, 14*zoom));
		rect.setFillColor(playerColorMap[activeCities[i].idJugador]);
		mapView.draw(rect);

		sf::Texture tex;
		tex.loadFromFile("resources/SP257.PIC_256.gif",sf::IntRect(193,113,15,15));
		rect.setPosition(sf::Vector2f(activeCities[i].posicionX*16*zoom-x, activeCities[i].posicionY*16*zoom-y));
		rect.setTexture(&tex, false);
		mapView.draw(rect);
	}
	//The active troop it's the only one to overlay cities
	sf::Texture tex;
	TropaInst* t = &(activeTroops.front());
	sprite::TroopData coso = sprite::Troop[t->tipo];
	tex.loadFromFile("resources/SP257.PIC_256.gif",sf::IntRect(coso.textureX,coso.textureY,coso.sizeX,coso.sizeY));
	sf::RectangleShape rect;
	rect.setTexture(&tex, false);
	rect.setFillColor(playerColorMap[t->idJugador]);
	rect.setSize(sf::Vector2f(coso.sizeX*zoom, coso.sizeY*zoom));
	if(t->renderingPositionX != t->posicionX || t->renderingPositionY != t->posicionY){
		moving = true;
		t->renderingPositionX = round(t->renderingPositionX + 0.2 * (t->renderingPositionX < t->posicionX) - 0.2 * (t->renderingPositionX > t->posicionX), 1);
		t->renderingPositionY = round(t->renderingPositionY + 0.2 * (t->renderingPositionY < t->posicionY) - 0.2 * (t->renderingPositionY > t->posicionY), 1);
	}
	rect.setPosition(sf::Vector2f(t->renderingPositionX*16*zoom-x, t->renderingPositionY*16*zoom-y));
	mapView.draw(rect);

	if(!moving && repos && activeTroops.size() > 0){
		TropaInst troop = activeTroops.front();
		reposition((troop.posicionX-7)*16*zoom, (troop.posicionY-6)*16*zoom);
		repos = false;
	}
	mapView.display();
}

void MapWindow::onClose(){
	guardarTropas("resources/troopSave.dat");
}
void MapWindow::onResize(int newWidth, int newHeight){
	reposition(x, y);
}
void MapWindow::onKeyDown(int keycode){
	std::cout << "active player= " << activeTroops.front().idJugador <<", you= " << menuEjemplo::logeado.id << "\n";
	if(activeTroops.front().idJugador==menuEjemplo::logeado.id && !moving && keycode >= 33 && keycode <= 40){
		TropaInst troop = activeTroops.front();
		troopMove(&troop,(Position)keycode);
		repos = true;
	}
}
void MapWindow::onMenu(UINT_PTR menuId){
}
