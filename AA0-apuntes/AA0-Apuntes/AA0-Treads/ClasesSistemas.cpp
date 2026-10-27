#include <iostream>
#include "2InputSystem/InputsConsts.h"
#include "Utils/ConsoleControl.h"
//#include "2InputSystem/InputSystem.h"

#include "4Json/Banana.h"
#include "4Json/Manzana.h"
#include <fstream>

/*class Player
{
public:

	int life = 0;
	std::string name = "Test Player";
	unsigned int coins = 0;

	Player();
	~Player();

	void Decode(Json::Value json) {
		coins = json["coins"].asUInt();
		life = json["lfie"].asInt();
		name = json["name"].asString();
	}

	static Player* FromJson(Json::Value json) {
		Player* player = new Player();
		player->Decode(json);
		return player;
	}

	Json::Value Encode() {
		Json::Value json;

		json["coins"] = coins;
		json["life"] = life;
		json["name"] = name;

		return json;
	}

private:

};

Player::Player()
{
}

Player::~Player()
{
}

/*

void CuandoPresiono1() {
	CC::Lock();
	std::cout << "Pressed 1" << std::endl;
	CC::Unlock();
}

typedef std::function<int(int a, int b)> TestSum;

void keyName() {
	int key = CC::WaithForReadNextKey();
	std::cout << key;
}
*/


int main()
{

	ICodable::SaveDecodeProcess<Banana>();
	ICodable::SaveDecodeProcess(typeid(Manzana).name(), []() { return new Manzana(); });

	std::vector<Fruta*> frutas{
		new Banana(),
		new Manzana(),
		new Fruta()
	};

	Json::Value jsonArray = Json::Value(Json::arrayValue);

	/*InputSystem* iS = new InputSystem();

	InputSystem::KeyBinding* kb1 = iS->AddListener(K_1, CuandoPresiono1);

	int i = 2;

	InputSystem::KeyBinding* kb3 = nullptr;

	InputSystem::KeyBinding* kb2 = iS->AddListener(K_2,
		[iS, &kb3]() {

			CC::Lock();
			std::cout << "Pressed 2" << std::endl;
			CC::Unlock();

			kb3 = iS->AddListener(K_3,
				[]() {
					CC::Lock();
					std::cout << "Pressed 3" << std::endl;
					CC::Unlock();
				});

		});

	InputSystem::KeyBinding* kb4 = iS->AddListener(K_4,
		[iS]() {

			CC::Lock();
			std::cout << "Pressed 4" << std::endl;
			CC::Unlock();

		});

	iS->StartListen();

	TestSum testFunc = [](int a, int b) {
		return a + b;
	};

	CC::Lock();
	std::cout << "Pressed " << testFunc(5, 3) << std::endl;
	CC::Unlock();

	while (true) {

	}
	*/

	/*Player* player = new Player();
	player->coins = 5;
	player->life = 50;
	player->name = "Capitana Test";

	Json::Value newJSON;

	player->Encode();

	// China social credit +1.000.000 pt
	//newJSON["coins"] = player->coins;
	//newJSON["life"] = player->life;
	//newJSON["name"] = player->name;

	// China social credit -647.829.365.789.345.426.394.465.794.057.458.923.564.789.479.502.357.849.230.657.429.065 pt


	std::ofstream* JSONWrite = new std::ofstream("PlayerParseTest.json", std::ifstream::binary);

	if (!JSONWrite->fail()) {
		// (*JSONWrite) << newJSON;
		// JSONWrite->close();

		Json::Value readValue;

		delete JSONWrite;
	}

	std::ifstream* JSONRead = new std::ifstream("PlayerParseTest.json", std::ifstream::binary);
	if (!JSONRead->fail()) {
		Json::Value readedJson;
		*JSONRead >> readedJson;
		JSONRead->close();
		delete JSONRead;

		//Player* player2 = new Player();
		//player2->Decode(readedJson);

		Player* player2 = Player::FromJson(readedJson);

		//player2->coins = readedJson["coins"].asUInt();
		//player2->life = readedJson["lfie"].asInt();
		//player2->name = readedJson["name"].asString();
	}

	std::cout << "Finished Writing JSON.";

	// Practica 2: Snake con threads, mapa prehecho para guardar con json.
	*/

	for (Fruta* fruta : frutas) {
		jsonArray.append(fruta->Code());
	}

	std::ofstream jsonWriterFile = std::ofstream("Frutatest.json", std::ifstream::binary);

	if (!jsonWriterFile.fail()) {
		jsonWriterFile << jsonArray;
		jsonWriterFile.close();
	}

	std::cout << "Finish Write" << std::endl;

	std::ifstream jsonReadFile = std::ifstream("Frutatest.json", std::ifstream::binary);
	std::vector<Fruta*> readFrutas;

	if (!jsonReadFile.fail()) {
		Json::Value readedJson;

		jsonReadFile >> readedJson;

		jsonReadFile.close();

		for (Json::Value value : readedJson) {
			Fruta* f = ICodable::FromJson<Fruta>(value);
			readFrutas.push_back(f);
		}
	}

	while (true) {

	}
}