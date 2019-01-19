#pragma once
#include <Main/UIManager.h>

#include <Utility/Timer.h>
namespace Ti
{
	//! The main class in which everything engine related happens. Call Init() to fire it up, call update every frame to keep running it.
	class GameState
	{
	public:
		GameState();
		~GameState();

		DrawManager *dm;
		ECManager	*ecm;
		UIManager	*uim;

		Timer timer;
		bool running = true;
		bool Init();
		bool Update();

		float dt;
	};
}