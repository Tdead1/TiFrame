#pragma once
#include <Windows/Window.h>
#include <string>

namespace Ti
{
	//! Not used yet.
	class InspectorWindow : public Window
	{
	public:
		InspectorWindow(UIManager * _uim);
		~InspectorWindow();

		void Update(ImVec2 _screensize) override;


	private:
		std::string meshPath;
		std::string texturePath;
	};



}