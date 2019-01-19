#include <Windows/LevelWindow.h>
#include <GameState.h>
#include <Main/UIManager.h>
using namespace Ti;

LevelWindow::LevelWindow(UIManager * _uim)
{
	uim = _uim;
}
LevelWindow::~LevelWindow(){}

void Ti::LevelWindow::Update(ImVec2 _screensize)
{
	if(show)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
		ImGui::ShowDemoWindow(&show);
	}
}

void LevelWindow::addEntity()
{
	uim->ecm->CreateEntity();
}

void LevelWindow::addComponent()
{
	//uim->gs->ecm->entityList[0]->AddComponent<ModelComponent>();
}
