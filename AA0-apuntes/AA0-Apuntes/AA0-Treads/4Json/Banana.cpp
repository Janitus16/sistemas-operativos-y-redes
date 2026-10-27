#include "Banana.h"

Banana::Banana()
{}

Banana::~Banana()
{}

Json::Value Banana::Code() {
	Json::Value json = Fruta::Code();
	json[DecodeKey()] = typeid(Banana).name();

	json["bananidad"] = bananidad;

	return json;
}

void Banana::Decode(Json::Value json) {
	Fruta::Decode(json);
	bananidad = json["manzanidad"].asInt();
}