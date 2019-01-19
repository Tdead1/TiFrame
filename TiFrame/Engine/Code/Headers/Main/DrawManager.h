#include <Static/MaterialLoader.h>
#include <Static/MeshLoader.h>
#include <Static/TextureLoader.h>

#include <Components/ModelComponent.h>
#include <Components/CameraComponent.h>
#include <Main/ECManager.h>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
Learning opengl from this tutorial website: https://learnopengl.com/
- Using OpenGL version 3.3 core w/ GLFW
*/

//! Namespace used for the Titanium Framework 
namespace Ti
{
	class GameState;

	//! The draw manager is the main class for rendering anything. Init it, then update it. That should take care of all rendering.
	class DrawManager
	{
	public:
		DrawManager(GameState * _gs, ECManager * _ecs);
		~DrawManager();

		bool Init();
		void Update(double dt);
		void Draw();

		GameState *gs;
		ECManager *ecm;
		CameraComponent *mainCamera;

		Material	*AddMaterial(std::string _filePath, std::string _name);
		Texture		*AddTexture(std::string _filePath, std::string _name);
		Mesh		*AddMesh(std::string _filePath, std::string _name);
		Model		*AddModel(Material* mat, Texture* tex, Mesh* model);
		void		RemoveModel(ModelComponent *_modelComponent);

		void		CreateDrawData(ModelComponent *_modelComponent);


		std::vector <Material*>			materialList;
		std::vector <Texture*>			textureList;
		std::vector <Mesh*>				meshList;
		std::vector <ModelComponent*>	modelList;

		Vec2 screenSize;

		// Opengl variables:
		GLFWwindow* window;
		std::vector<unsigned int> VAO, VBO, EBO;
		std::vector<unsigned int> TBO;
		unsigned int modelCounter;


		unsigned int fragmentShader;
		unsigned int vertexShader;
		unsigned int shaderProgram;
		

		// Temporary variables
		unsigned int textureAmount;
		unsigned int meshAmount;
		unsigned int materialAmount;
		unsigned int modelAmount;
	};
}