#pragma once
#include <imgui/imgui.h>


namespace Ti
{
	class UIManager;

	//! Main window class for imGui to use.
	class Window
	{
	public:
		Window();
		Window(UIManager *_uim);
		~Window();

		virtual void Update(ImVec2 _screensize) = 0;
		bool show = false;

		UIManager * uim;
	};
}
