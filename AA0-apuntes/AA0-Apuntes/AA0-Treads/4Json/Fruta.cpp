#include "Fruta.h"

Json::Value Fruta::Code() {
	Json::Value json;

	json["semillas"] = semillas;
	json["hexColor"] = hexColor;

	return json;
}

void Fruta::Decode(Json::Value json) {
	json["semillas"].asUInt();
	json["hexColor"].asString();
}