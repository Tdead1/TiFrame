#pragma once
#include <Windows/Window.h>
namespace Ti
{
	//! Not used yet.
	class HeaderWindow : public Window
	{
	public:
		HeaderWindow(UIManager * _uim);
		~HeaderWindow();

		void Update(ImVec2 _screensize) override;
		
	private:
		//bool   show_demo_window = true;
		//bool   show_another_window = true;
		//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	};
}