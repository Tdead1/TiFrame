#pragma once

#include <Main/DrawManager.h>

#include <windows/LevelWindow.h>
#include <windows/HeaderWindow.h>
#include <windows/InspectorWindow.h>
#include <Windows/ContentWindow.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

namespace Ti
{
	//! UI manager. Takes care of all imGui related drawing etc. Call Init and Update to make it work.
	class UIManager
	{
	public:
		UIManager(DrawManager* _dm, ECManager* _ecm);
		~UIManager();

		bool Init();
		void Update(double _dt);


		double dt;

		DrawManager *dm;
		ECManager *ecm;

		GLFWwindow *window;

		LevelWindow *level;
		HeaderWindow *header;
		InspectorWindow *inspector;
		ContentWindow *content;

	private:
		void Draw();
		//template<typename TWindow>
		//TWindow * ShowWindow();


	};
}