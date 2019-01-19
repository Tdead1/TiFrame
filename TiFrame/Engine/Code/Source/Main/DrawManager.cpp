#include <Main/DrawManager.h>


#include <Utility/Logger.h>
#include <stb/stb_image.h>

using namespace Ti;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}



DrawManager::DrawManager(GameState * _gs, ECManager * _ecm) : gs(_gs), ecm(_ecm)
{
	screenSize = Vec2(1920, 1080);
	modelAmount = 0;
	modelCounter = 0;

	VAO	= std::vector<unsigned int>(999);
	VBO = std::vector<unsigned int>(999);
	EBO = std::vector<unsigned int>(999);
	TBO = std::vector<unsigned int>(999);
}
DrawManager::~DrawManager()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

bool DrawManager::Init()
{
	///* OpenGL init here. */
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	window = glfwCreateWindow((int)screenSize.x, (int)screenSize.x, "TiFrame Main Window", NULL, NULL);

	glfwSetErrorCallback(glfw_error_callback);

	if (window == NULL)
	{
		Logger::Print("Failed to create GLFW window", LogType::PROBLEM);
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::Print("Failed to initialize GLAD", LogType::PROBLEM);
		return false;
	}
	glViewport(0, 0, 800, 600);
	// Adding the default shaders:
	AddMaterial("Resources/Shaders/BasicVS.glsl", "< not implemented >");
	AddMaterial("Resources/Shaders/BasicFS.glsl", "< not implemented >");
	// Setting up Vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &materialList[0]->data, NULL);
	glCompileShader(vertexShader);
	// Setting up Fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &materialList[1]->data, NULL);
	glCompileShader(fragmentShader);
	// Creating the combination of the two
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	meshAmount		= meshList.size();
	textureAmount	= textureList.size();
	materialAmount	= materialList.size();
	
	// Creating a VBO and VAO for all precreated objects.
	for (unsigned int i = 0; i < modelAmount; i++)
	{
		CreateDrawData(modelList[i]);
	}

	for(unsigned int i = 0; i < textureAmount; i++)
		stbi_image_free(textureList[i]->data);

	
	Logger::Print("Draw manager initialized.", LogType::SUCCESS);
	return true;
}

void DrawManager::Update(double dt)
{
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	mainCamera->screenSize = Vec2((float)x, (float)y);
	screenSize = Vec2((float)x, (float)y);

	/* Rendering code			 */
	Draw();

	/* Input handeling			 */
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}
}

void DrawManager::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	int MPVLocation = glGetUniformLocation(shaderProgram, "MVP");
	int colorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
	glUseProgram(shaderProgram);
	
	
	modelAmount = modelList.size();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (unsigned int i = 0; i < modelAmount; i++)
	{
		if (modelList[i] != nullptr && modelList[i]->model != nullptr)
		{
			Mat4 modelMatrix = modelList[i]->owner->GetComponent<TransformComponent>()->matrix;
			Mat4 MVP = mainCamera->projection * mainCamera->view * modelMatrix;
			Vec4 color(0, 0, 0.5, 1);
			glUniformMatrix4fv(MPVLocation, 1, GL_FALSE, &MVP.f[0]);
			glUniform4f(colorLocation, color.f[0], color.f[1], color.f[2], color.f[3]);
		
			glBindTexture(GL_TEXTURE_2D, TBO[i]);
			glBindVertexArray(VAO[i]);
			glDrawElements(GL_TRIANGLES, (GLsizei)modelList[i]->model->mesh->indices.size(), GL_UNSIGNED_INT, &modelList[i]->model->mesh->indices.front());
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	
	// Draw all meshes, with materials and everything.
	//for (unsigned int i = 0; i < (unsigned int)meshList.size(); i++)
	//{
	//	meshList[i]->material;	// Load this shader.
	//	meshList[i]->model;		// With this vertex / texture / normal data.
	//	meshList[i]->texture;	// Add this (these) textures.
	//}

	/* call events */

	glfwPollEvents();
}

Material	* DrawManager::AddMaterial	(std::string _filePath, std::string _name)
{
	//for (unsigned int i = 0; i < materialList.size(); i++)
	//{
	//	if (materialList[i]->filePath == _filePath)
	//		return materialList[i];
	//}
	Material *material = MaterialLoader::LoadMaterial(_filePath, _name);
	materialList.push_back(material);
	return material;
}
Texture		* DrawManager::AddTexture	(std::string _filePath, std::string _name)
{
	//for (unsigned int i = 0; i < textureList.size(); i++)
	//{
	//	if (textureList[i]->filePath == _filePath)
	//	return textureList[i];
	//}
	Texture *texture = TextureLoader::loadTexture(_filePath, _name);
	textureList.push_back(texture);
	return texture;
}
Mesh		* DrawManager::AddMesh		(std::string _filePath, std::string _name)
{
	// Check if file is already in the list of models
	for (unsigned int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i]->filePath == _filePath)
			return meshList[i];
	}

	// Load in the mesh from file
	Mesh *mesh = MeshLoader::LoadMesh(_filePath, _name);
	meshList.push_back(mesh);
	
	return mesh;
}
Model		* DrawManager::AddModel(Material * mat, Texture * tex, Mesh * mesh)
{
	Model *model = new Model();
	model->material = mat;
	model->texture = tex;
	model->mesh = mesh;

	return model;
}

void Ti::DrawManager::RemoveModel(ModelComponent * _modelComponent)
{
	for (int i = 0; i < modelList.size(); i++)
	{
		if (modelList[i] == _modelComponent)
		{
			modelList.erase(modelList.begin() + i);
			VAO.erase(VAO.begin() + i);
			VBO.erase(VBO.begin() + i);
			EBO.erase(EBO.begin() + i);
			TBO.erase(TBO.begin() + i);
			modelCounter--;
			break;
		}
	}
}

void Ti::DrawManager::CreateDrawData(ModelComponent * _modelComponent)
{
	///////////////////////////
	// Mesh for model:       //
	glGenVertexArrays(1, &VAO[modelCounter]);
	glGenBuffers(1, &VBO[modelCounter]);
	glGenBuffers(1, &EBO[modelCounter]);

	glBindVertexArray(VAO[modelCounter]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[modelCounter]);
	glBufferData(GL_ARRAY_BUFFER, modelList[modelCounter]->model->mesh->vertices.size() * sizeof(Vertex), &modelList[modelCounter]->model->mesh->vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[modelCounter]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelList[modelCounter]->model->mesh->indices.size() * sizeof(unsigned int), &modelList[modelCounter]->model->mesh->indices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	///////////////////////////
	// Texture for model:    //

	glGenTextures(1, &TBO[modelCounter]);
	glBindTexture(GL_TEXTURE_2D, TBO[modelCounter]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Keeping in mind the amount of channels.
	if (modelList[modelCounter]->model->texture->channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, modelList[modelCounter]->model->texture->width, modelList[modelCounter]->model->texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, modelList[modelCounter]->model->texture->data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, modelList[modelCounter]->model->texture->width, modelList[modelCounter]->model->texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, modelList[modelCounter]->model->texture->data);

	glGenerateMipmap(GL_TEXTURE_2D);

	modelCounter++;
}
