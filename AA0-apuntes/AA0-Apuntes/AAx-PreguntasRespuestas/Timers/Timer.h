#pragma once
#include <functional>
#include <thread>
#include <chrono>

// Temporizador sencillo: espera X milisegundos en otro hilo y ejecuta la lambda.
class Timer
{
public:
	typedef std::function<void()> OnTimerEnd;

	static void Start(int milliseconds, OnTimerEnd onEnd)
	{
		std::thread([milliseconds, onEnd]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
				onEnd();
			}).detach();
	}
};