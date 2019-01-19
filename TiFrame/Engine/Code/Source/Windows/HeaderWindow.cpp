#include <Windows/HeaderWindow.h>

#include <Main/UIManager.h>

using namespace Ti;

HeaderWindow::HeaderWindow(UIManager * _uim)
{
	uim = _uim;
	show = true;
}
HeaderWindow::~HeaderWindow() {}

void Ti::HeaderWindow::Update(ImVec2 _screensize)
{
	if (show)
	{
		ImVec2 drawPos = ImVec2(0,0);
		ImVec2 drawSize = ImVec2(_screensize.x, 28);
		
		ImGui::SetNextWindowSize(drawSize);
		ImGui::SetNextWindowPos(drawPos);


		ImGui::Begin("Header", &show, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

		if (ImGui::Button("Windows"))
		{			
			ImGui::OpenPopup("HeaderWindowsPopup");

			drawPos = ImVec2(0, drawSize.y);
			drawSize = ImVec2(100, 300);
			ImGui::SetNextWindowPos(drawPos);
			ImGui::SetNextWindowSize(drawSize);
		} 
		if (ImGui::BeginPopup("HeaderWindowsPopup"))
		{
			ImGui::Selectable("Toggle imGui demo Window", &uim->level->show);
			ImGui::Selectable("Toggle inspector Window", &uim->inspector->show);
			ImGui::Selectable("Toggle content Window", &uim->content->show);

			ImGui::EndPopup();
		}
		//drawSize = drawSize = ImVec2(100, 250);
		//drawPos = ImVec2(drawSize.x * 1, 0);
		//ImGui::SetNextWindowSize(drawSize);
		//ImGui::SetNextWindowPos(drawPos);
		//ImGui::SameLine();
		//if (ImGui::Button("HeaderEdit"))
		//{
		//} 
		

		ImGui::SameLine(_screensize.x - 160);
		ImGui::TextWrapped("%.3f ms, %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); ImGui::SameLine();
		ImGui::End();
	}
}
