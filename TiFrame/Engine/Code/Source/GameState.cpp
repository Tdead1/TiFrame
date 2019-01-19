#include <GameState.h>
#include <iostream>
using namespace Ti;

GameState::GameState()
{
	ecm = new ECManager(this);
	dm = new DrawManager(this, ecm);
	uim = new UIManager(dm, ecm);

	timer = Timer();
}
GameState::~GameState() {}

bool GameState::Init()
{
	if (ecm->Init() && dm->Init() && uim->Init())
	{
		return true;
	}
	else
	{
		std::cout << "Compiling engine failed! Try rebuilding the engine." << std::endl;
		return false;
	}
}

bool GameState::Update()
{
	if (running == true)
	{
		timer.start();
		if (dt < 0.5f)
		{
			ecm->Update(dt);
			uim->Update(dt);
			dm->Update(dt);
		}
		dt = timer.stop();

		if (glfwWindowShouldClose(dm->window))
		{
			glfwTerminate();
			return false;
		}
	}
	//timer.print();

	//Return false if escape is pressed.
	return true;
}