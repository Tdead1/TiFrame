#include <Windows/InspectorWindow.h>
#include <GameState.h>
#include <Main/UIManager.h>

using namespace Ti;

InspectorWindow::InspectorWindow(UIManager * _uim)
{
	uim = _uim;
}
InspectorWindow::~InspectorWindow() {}

void Ti::InspectorWindow::Update(ImVec2 _screensize)
{
	if (show)
	{
		ImGui::SetNextWindowPos(ImVec2(_screensize.x - 500, 28));
		ImGui::SetNextWindowSize(ImVec2(500, _screensize.y - 228));
		if (ImGui::Begin("Inspector", &show, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			unsigned int entityAmount = (unsigned int)uim->dm->ecm->entityList.size();
			static int selected = 0;

			// left
			if (ImGui::Button("Add Entity"))
			{
				uim->ecm->CreateEntity("Entity #" + std::to_string(entityAmount));
			}

			ImGui::BeginChild("left pane", ImVec2(150, 0), true);
			for (unsigned int i = 0; i < entityAmount; i++)
			{
				char label[128];
				sprintf_s(label, uim->dm->ecm->entityList[i]->name.c_str(), i);
				if (ImGui::Selectable(label, selected == i))
					selected = i;
			}
			ImGui::EndChild();
			ImGui::SameLine();

			// right
			ImGui::BeginGroup();
			unsigned int componentAmount = (unsigned int)uim->dm->ecm->entityList[selected]->componentList.size();
			if (ImGui::InputText("", uim->dm->ecm->entityList[selected]->namebuffer, 64))
			{
				uim->ecm->entityList[selected]->name= std::string(uim->dm->ecm->entityList[selected]->namebuffer);
			} 
			
			

			if (ImGui::Button("Add Component..."))
			{
				ImGui::OpenPopup("ComponentAddingWindow");
			} ImGui::SameLine();
			if (ImGui::Button("Delete Entity..."))
			{
				if (uim->ecm->entityList[selected]->GetComponent<CameraComponent>() != uim->dm->mainCamera)
				{
					uim->ecm->DestroyEntity(uim->ecm->entityList[selected]);
					selected = 0;
					componentAmount = (unsigned int)uim->ecm->entityList[selected]->componentList.size();
				}
			}
			if(ImGui::BeginPopup("ComponentAddingWindow"))
			{
				if (ImGui::Button("ModelComponent"))
				{
					uim->dm->ecm->entityList[selected]->AddComponent<ModelComponent>(nullptr, uim->dm);
				}
				if (ImGui::Button("CameraComponent"))
				{
					uim->dm->ecm->entityList[selected]->AddComponent<CameraComponent>();
				}
				if (ImGui::Button("TransformComponent"))
				{
					uim->dm->ecm->entityList[selected]->AddComponent<TransformComponent>();
				}
				ImGui::EndPopup();
			}
			for (unsigned int i = 0; i < componentAmount; i++)
			{
				Entity* currentEntity = uim->ecm->entityList[selected];
				Component* currentComponent = uim->ecm->entityList[selected]->componentList[i];
				ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
				ImGui::Separator();
				ImGui::PushID(i);
				
				// Delete current component
				if (!((dynamic_cast<TransformComponent*>(currentComponent) != nullptr && currentEntity->componentList.size() > 1)
					|| (dynamic_cast<CameraComponent*>(currentComponent) != nullptr && currentEntity->GetComponent<CameraComponent>() == uim->dm->mainCamera)))
				{
					if (ImGui::Button("X"))
					{
					// If the component in question is not a transformcomponent that other components rely on...
					// or if it's the current main camera component...
						currentEntity->DeleteComponent(currentComponent);
						componentAmount = (unsigned int)uim->ecm->entityList[selected]->componentList.size();
						ImGui::PopID();
						ImGui::EndChild();
						continue;
					} ImGui::SameLine();
				}	

				// Transform component
				if (dynamic_cast<TransformComponent*>(uim->dm->ecm->entityList[selected]->componentList[i]))
				{
					ImGui::Text("Transform Component\n");

					ImGui::Text("Pos"); ImGui::SameLine();
					ImGui::PushID("transformpos");
					ImGui::InputFloat3("", uim->dm->ecm->entityList[selected]->GetComponent<TransformComponent>()->transform.position.f);
					ImGui::PopID();

					ImGui::Text("Rot"); ImGui::SameLine();
					ImGui::PushID("transformrot");
					ImGui::InputFloat3("", uim->dm->ecm->entityList[selected]->GetComponent<TransformComponent>()->transform.rotation.f);
					ImGui::PopID();

					ImGui::Text("Sca"); ImGui::SameLine();
					ImGui::PushID("transformsca");
					ImGui::InputFloat3("", uim->dm->ecm->entityList[selected]->GetComponent<TransformComponent>()->transform.scale.f);
					ImGui::PopID();
					ImGui::TextWrapped(" ");
				}
				
				// Camera component
				if (dynamic_cast<CameraComponent*>(uim->dm->ecm->entityList[selected]->componentList[i]))
				{
					ImGui::TextWrapped("Camera Component\n");

					ImGui::Text("Pos"); ImGui::SameLine();
					ImGui::PushID("cameyelocation");
					ImGui::InputFloat3("", uim->dm->ecm->entityList[selected]->GetComponent<CameraComponent>()->eyeLocation.f);
					ImGui::PopID();

					ImGui::Text("Dir"); ImGui::SameLine();
					ImGui::PushID("camcenterlocation");
					ImGui::InputFloat3("", uim->dm->ecm->entityList[selected]->GetComponent<CameraComponent>()->centerLocation.f);
					ImGui::PopID();

					ImGui::Text("Up "); ImGui::SameLine();
					ImGui::PushID("camupdirection");
					ImGui::InputFloat3("", uim->dm->ecm->entityList[selected]->GetComponent<CameraComponent>()->up.f);
					ImGui::PopID();
					ImGui::TextWrapped(" ");
				}

				// Model component
				if (dynamic_cast<ModelComponent*>(uim->dm->ecm->entityList[selected]->componentList[i]))
				{
					ImGui::TextWrapped("Model Component\n");
					if (uim->ecm->entityList[selected]->GetComponent<ModelComponent>()->model == nullptr)
					{
						ImGui::TextWrapped(std::string("Mesh: None applied yet. (currently selected: "    + meshPath + ")").c_str());
						ImGui::TextWrapped(std::string("Texture: None applied yet. (currently selected: " + texturePath + ")").c_str());
						if (meshPath != "" && texturePath != "")
						{
							if (ImGui::Button("Apply mesh and texture"))
							{
								uim->ecm->entityList[selected]->GetComponent<ModelComponent>()->model = uim->dm->AddModel(nullptr, uim->dm->AddTexture(texturePath, " "), uim->dm->AddMesh(meshPath, " "));
								uim->dm->CreateDrawData(uim->ecm->entityList[selected]->GetComponent<ModelComponent>());
							}
						}
					}
					else
					{
						ImGui::TextWrapped(uim->ecm->entityList[selected]->GetComponent<ModelComponent>()->model->mesh->filePath.c_str());
						ImGui::TextWrapped(uim->ecm->entityList[selected]->GetComponent<ModelComponent>()->model->texture->filePath.c_str());
						ImGui::TextWrapped(" ");
					}

					if (uim->content->show && uim->content->selectedFile.size() > 4)
					{
						if (uim->content->selectedFile.substr(uim->content->selectedFile.size() - 4, uim->content->selectedFile.size()) == ".obj")
						{
							if (ImGui::Button(" Set Mesh "))
							{
								meshPath = uim->content->selectedFile;
							}
						}
						if (uim->content->selectedFile.substr(uim->content->selectedFile.size() - 4, uim->content->selectedFile.size()) == ".jpg" ||
							uim->content->selectedFile.substr(uim->content->selectedFile.size() - 4, uim->content->selectedFile.size()) == ".png")
						{
							if (ImGui::Button("Set Texture"))
							{
								texturePath = uim->content->selectedFile;
							}
						}
					}
					//ImGui::TextWrapped(uim->dm->ecm->entityList[selected]->GetComponent<ModelComponent>()->model->material->filePath.c_str());
				}

				ImGui::PopID();
				ImGui::EndChild();
			}
			ImGui::EndGroup();
		}
		ImGui::End();
	}
}
