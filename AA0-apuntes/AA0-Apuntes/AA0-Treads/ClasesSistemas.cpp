#include <iostream>
#include "2InputSystem/InputsConsts.h"
#include "Utils/ConsoleControl.h"
#include "2InputSystem/InputSystem.h"


class Patata {
public:
	Patata();
	~Patata();

private:

};

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

int main()
{
	InputSystem* iS = new InputSystem();

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

	Patata* patata = new Patata();

	Node* node = new Node(Vector2(0, 0));

	node->SetContent(patata);

	patata = node->GetContent<patata>();

	while (true) {

	}
}

// Practica 2: Snake con threads, mapa prehecho para guardar con json.
