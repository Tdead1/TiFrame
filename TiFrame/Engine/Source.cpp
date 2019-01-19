#include <GameState.h>

#define PI 3.14159265359

int main()
{
	Ti::GameState gameState;
	
	Ti::Mesh* meshes[6];
	Ti::Model* models[6];
	Ti::Texture* textures[6];


	meshes[0] = gameState.dm->AddMesh("Resources\\Models\\miku.obj",	"< not implemented >");
	meshes[1] = gameState.dm->AddMesh("Resources\\Models\\box.obj",		"< not implemented >");
	meshes[2] = gameState.dm->AddMesh("Resources\\Models\\torus.obj",	"< not implemented >");
	meshes[3] = gameState.dm->AddMesh("Resources\\Models\\circle.obj",	"< not implemented >");
	meshes[4] = gameState.dm->AddMesh("Resources\\Models\\sphere.obj",	"< not implemented >");
	meshes[5] = gameState.dm->AddMesh("Resources\\Models\\monkey.obj",	"< not implemented >");
	//meshes[6] = gameState.dm->addMesh("Resources\\Models\\sponsa.obj", "< not implemented >");

	textures[0] = gameState.dm->AddTexture("Resources\\Textures\\sand.jpg", "sand");
	textures[1] = gameState.dm->AddTexture("Resources\\Textures\\straw.jpg", "straw");
	textures[2] = gameState.dm->AddTexture("Resources\\Textures\\wood.jpg", "wood");
	textures[3] = gameState.dm->AddTexture("Resources\\Textures\\stone.jpg", "stone");

	models[0] = gameState.dm->AddModel(nullptr, textures[2], meshes[0]);
	models[1] = gameState.dm->AddModel(nullptr, textures[3], meshes[1]);
	models[2] = gameState.dm->AddModel(nullptr, textures[3], meshes[5]);
	//models[3] = gameState.dm->addModel(nullptr, textures[2], meshes[2]);
	//models[4] = gameState.dm->addModel(nullptr, textures[2], meshes[2]);
	//models[5] = gameState.dm->addModel(nullptr, textures[2], meshes[2]);

	Ti::Entity* player = gameState.ecm->CreateEntity("Player");
	//player->AddComponent<Ti::ModelComponent>(models[0]);
	//Ti::Entity* floor = gameState.ecm->CreateEntity("Floor");
	//floor->AddComponent<Ti::ModelComponent>(models[1]);
	//Ti::Entity* monkey = gameState.ecm->CreateEntity("Monkey");
	//monkey->AddComponent<Ti::ModelComponent>(models[2]);

	gameState.dm->mainCamera = player->AddComponent<Ti::CameraComponent>();

	// Do this right before the update.
	float counter = 0.f;
	float speed = 0.3f;
	float dt = 0.f;
	//floor->GetComponent<Ti::TransformComponent>()->transform.scale = Ti::Vec3(4.f, 0.01f, 4.0f);
	//floor->GetComponent<Ti::TransformComponent>()->transform.position = Ti::Vec3(0, -0.5f, 0);


	gameState.Init();
	while (gameState.Update())
	{
		dt = gameState.dt;
		counter += dt * speed;

		//player->GetComponent<Ti::TransformComponent>()->matrix = Ti::Vec3::(Ti::Vec3(0, 0, 1), Ti::Vec3(0, 1, 0), Ti::Vec3(1, 0, 0));
		//player->GetComponent<Ti::TransformComponent>()->transform.position = Ti::Vec3(3 * cos(counter), 0, 3 * sin(counter));
		//player->GetComponent<Ti::TransformComponent>()->transform.rotation = Ti::Vec3(-counter - 0.5 * PI, 0, 0);
	}
	return 0;
}