#pragma once
#include "Fruta.h"
class Manzana : public Fruta
{
public:

	Manzana();
	~Manzana();

	int manzanidad = 0;

	virtual Json::Value Code() override;
	virtual void Decode(Json::Value json) override;
};

