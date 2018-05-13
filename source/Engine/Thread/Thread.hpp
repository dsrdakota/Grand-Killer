#pragma once

#include <SFML/Graphics.hpp>
#include <thread>

class Thread
{
public:

	Thread();
	~Thread();

	bool isRunning();

private:

	std::thread *thread;

	bool run;

	template <class T>
	T function;

	void execute();
};