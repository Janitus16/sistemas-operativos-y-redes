#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

#include "InputSystem/InputsConsts.h"
#include "InputSystem/InputSystem.h"
#include "ConsoleControl/ConsoleControl.h"
#include "Timers/Timer.h"

// ---------- Datos ----------

struct Question
{
	std::string text;
	std::vector<std::string> answers;
	int correct; // indice (0-based) de la respuesta correcta
};

enum Phase { Asking, Revealing, Finished };

const int POINTS_CORRECT = 2;
const int POINTS_WRONG = 1;
const int REVEAL_MS = 3000;

// ---------- Estado compartido (protegido por gameMutex) ----------

std::vector<Question> questions;
int current = -1;
int selected = -1; // -1 = ninguna
int score = 0;
Phase phase = Asking;
std::string resultMsg;
bool finished = false;

std::mutex gameMutex;
std::condition_variable finishedCv;

void ShowQuestion(int index);
void Reveal();

// ---------- Dibujado (llamar con gameMutex cogido) ----------

void Draw()
{
	CC::Lock();
	CC::Clear();

	CC::SetColor(CC::CYAN);
	std::cout << "Puntuacion: " << score << "\n\n";

	if (phase == Finished)
	{
		CC::SetColor(CC::YELLOW);
		std::cout << "Fin del juego. Puntuacion final: " << score << "\n";
	}
	else
	{
		const Question& q = questions[current];

		CC::SetColor(CC::WHITE);
		std::cout << "Pregunta " << current + 1 << "/" << questions.size() << ": " << q.text << "\n\n";
		std::cout << "Posibles respuestas\n";

		for (int i = 0; i < (int)q.answers.size(); ++i)
		{
			CC::ConsoleColor color = CC::WHITE;

			if (phase == Asking)
			{
				if (i == selected) color = CC::DARKYELLOW; // el "naranja" de la consola
			}
			else // Revealing
			{
				if (i == q.correct) color = CC::GREEN;
				else if (i == selected) color = CC::RED;
			}

			CC::SetColor(color);
			std::cout << "(R" << i + 1 << ") -> " << q.answers[i] << "\n";
		}

		CC::SetColor(CC::WHITE);
		if (phase == Revealing)
		{
			std::cout << "\n" << resultMsg << "\n";
		}
	}

	CC::SetColor(CC::WHITE);
	std::cout.flush();
	CC::Unlock();
}

// ---------- Flujo del juego (encadenado con temporizadores) ----------

void ShowQuestion(int index)
{
	int seconds = 0;

	{
		std::lock_guard<std::mutex> lock(gameMutex);

		if (index >= (int)questions.size())
		{
			phase = Finished;
			Draw();
			finished = true;
			finishedCv.notify_all();
			return;
		}

		current = index;
		selected = -1;
		phase = Asking;
		resultMsg.clear();
		seconds = 2 + (int)questions[index].answers.size() * 2;
		Draw();
	}

	Timer::Start(seconds * 1000, []() { Reveal(); });
}

void Reveal()
{
	int next = 0;

	{
		std::lock_guard<std::mutex> lock(gameMutex);

		phase = Revealing;
		const Question& q = questions[current];

		if (selected == -1)
		{
			resultMsg = "No has respondido. Sin penalizacion.";
		}
		else if (selected == q.correct)
		{
			score += POINTS_CORRECT;
			resultMsg = "Correcto! +" + std::to_string(POINTS_CORRECT);
		}
		else
		{
			score -= POINTS_WRONG;
			resultMsg = "Incorrecto! -" + std::to_string(POINTS_WRONG);
		}

		next = current + 1;
		Draw();
	}

	Timer::Start(REVEAL_MS, [next]() { ShowQuestion(next); });
}

// ---------- Acciones de input (se ejecutan en hilos del InputSystem) ----------

void SelectAnswer(int index)
{
	std::lock_guard<std::mutex> lock(gameMutex);

	if (phase != Asking) return;
	if (index < 0 || index >= (int)questions[current].answers.size()) return;

	selected = index;
	Draw();
}

void ClearSelection()
{
	std::lock_guard<std::mutex> lock(gameMutex);

	if (phase != Asking) return;

	selected = -1;
	Draw();
}

void MoveSelection(int delta)
{
	std::lock_guard<std::mutex> lock(gameMutex);

	if (phase != Asking) return;

	int n = (int)questions[current].answers.size();

	if (selected == -1) selected = (delta > 0) ? 0 : n - 1;
	else selected = (selected + delta + n) % n;

	Draw();
}

// ---------- Main ----------

int main()
{
	questions =
	{
		{ "Cuantas vocales tiene la palabra Ornitorrinco", { "3", "5", "7", "12" }, 1 },
		{ "Cual es la capital de Francia", { "Madrid", "Paris", "Roma" }, 1 },
		{ "Cuantos bits tiene un byte", { "4", "8", "16", "32" }, 1 },
		{ "Epstein Folló en su isla a <<Pollos>>", { "Si", "No" }, 0 },
	};

	InputSystem input;

	// Teclas 1..9 -> seleccionar respuesta
	for (int key = K_1; key <= K_9; ++key)
	{
		input.AddListener(key, [key]() { SelectAnswer(key - K_1); });
	}
	// Tecla 0 -> deseleccionar
	input.AddListener(K_0, []() { ClearSelection(); });
	// Flechas (OJO: _getch devuelve 224 y luego 72/80; 72 y 80 tambien son 'H' y 'P')
	input.AddListener(K_UP, []() { MoveSelection(-1); });
	input.AddListener(K_DOWN, []() { MoveSelection(1); });

	input.StartListen();
	ShowQuestion(0);

	// Esperar a que termine el juego
	{
		std::unique_lock<std::mutex> lock(gameMutex);
		finishedCv.wait(lock, []() { return finished; });
	}

	input.StopListen();
	std::this_thread::sleep_for(std::chrono::milliseconds(300)); // dejar morir el hilo de escucha

	CC::SetColor(CC::WHITE, CC::BLACK);
	std::cout << "\nPulsa una tecla para salir...";
	CC::WaithForReadNextKey();

	return 0;
}