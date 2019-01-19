#pragma once

namespace Ti
{
	class DrawManager;
	class Entity;
}

class Input
{
public:
	Input(Ti::DrawManager* _dm);
	~Input();

	Ti::DrawManager* dm;

	void ProcessPlayerInput(Ti::Entity* _player);
};