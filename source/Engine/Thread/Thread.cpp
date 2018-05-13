#include "Thread.hpp"

#include "../../Game.hpp"

Thread::Thread()
{
	thread = new std::thread(&Thread::execute);
}

Thread::~Thread()
{
	delete thread;
}

bool Thread::isRunning()
{
	return run;
}

template <class T>
void Thread::execute()
{
	while (Game::Instance().getStatus() != Game::status::CleaningUp)
	{
		if (run)
			function(/*args*/);
	}
}
