#pragma once
#include <Windows/Window.h>
#include <string>
namespace Ti
{
	//! Not used yet.
	class ContentWindow : public Window
	{
	public:
		ContentWindow(UIManager * _uim);
		~ContentWindow();

		void Update(ImVec2 _screensize) override;
		std::string path;
		std::string filename;
		std::string selectedFile;
	};

}