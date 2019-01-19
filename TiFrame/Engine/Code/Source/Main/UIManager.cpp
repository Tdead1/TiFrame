#include <GameState.h>

#include <Utility/Logger.h>

using namespace Ti;


UIManager::UIManager(DrawManager* _dm, ECManager* _ecm) : dm(_dm), ecm(_ecm)
{
	level = new LevelWindow(this);
	header = new HeaderWindow(this);
	inspector = new InspectorWindow(this);
	content = new ContentWindow(this);
}

UIManager::~UIManager()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

bool UIManager::Init()
{
	// Setup window
	// Setup Dear ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui_ImplGlfwGL3_Init(dm->window, true);
	ImGui::StyleColorsDark();
	Logger::Print("ImGui Version: " + std::string(ImGui::GetVersion()));
	Logger::Print("UI manager initialized.", LogType::SUCCESS);
	return true;
}

void UIManager::Update(double _dt)
{
	dt = _dt;
	ImGui_ImplGlfwGL3_NewFrame();

	level->Update(dm->screenSize);
	header->Update(dm->screenSize);
	inspector->Update(dm->screenSize);
	content->Update(dm->screenSize);

	Draw();
}

void Ti::UIManager::Draw()
{
	// Rendering
	int display_w, display_h;
	glfwGetFramebufferSize(dm->window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(dm->window);
}
