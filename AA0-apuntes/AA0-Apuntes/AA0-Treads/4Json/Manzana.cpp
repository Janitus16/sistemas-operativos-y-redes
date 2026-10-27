#include "Manzana.h"

Manzana::Manzana()
{}

Manzana::~Manzana()
{}

Json::Value Manzana::Code() {
	Json::Value json = Fruta::Code();
	json[DecodeKey()] = typeid(Manzana).name();


	json["manzanidad"] = manzanidad;

	return json;
}

void Manzana::Decode(Json::Value json) {
	Fruta::Decode(json);
	manzanidad = json["manzanidad"].asInt();
}