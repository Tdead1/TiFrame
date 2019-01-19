#pragma once
#include <Windows/Window.h>

namespace Ti
{
	//! Not used yet.
	class LevelWindow : public Window
	{
	public:
		LevelWindow(UIManager * _uim);
		~LevelWindow();

		void Update(ImVec2 _screensize) override;

		// Add button functions:
		void addEntity();
		void addComponent();
	};

}