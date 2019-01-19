#include "Input.h"

#include <Main/DrawManager.h>

Input::Input(Ti::DrawManager* _dm) : dm(_dm)
{
}

Input::~Input()
{
}

void Input::ProcessPlayerInput(Ti::Entity* _player)
{
	if (glfwGetKey(dm->window, GLFW_KEY_W))
	{
		_player->GetComponent<Ti::TransformComponent>()->transform.position += Ti::Vec3(0.01f, 0, 0);
	}
	if (glfwGetKey(dm->window, GLFW_KEY_S))
	{
		_player->GetComponent<Ti::TransformComponent>()->transform.position += Ti::Vec3(-0.01f, 0, 0);
	}
	if (glfwGetKey(dm->window, GLFW_KEY_A))
	{
		_player->GetComponent<Ti::TransformComponent>()->transform.position += Ti::Vec3(0, 0, -0.01f);
	}
	if (glfwGetKey(dm->window, GLFW_KEY_D))
	{
		_player->GetComponent<Ti::TransformComponent>()->transform.position += Ti::Vec3(0, 0, 0.01f);
	}
}
