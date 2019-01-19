#include <Windows/ContentWindow.h>

#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Ti::ContentWindow::ContentWindow(UIManager * _uim)
{
	uim = _uim;
	path = "../Game/Resources/";
}

Ti::ContentWindow::~ContentWindow()
{
}

void Ti::ContentWindow::Update(ImVec2 _screensize)
{
	if (show)
	{
		ImGui::SetNextWindowPos(ImVec2(0, _screensize.y - 200));
		ImGui::SetNextWindowSize(ImVec2(_screensize.x, 200));

		if (ImGui::Begin("Content", &show, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::Text("Selected file (with path):");
			if (selectedFile.empty())
				ImGui::Text("None.");
			else
				ImGui::Text(selectedFile.c_str());

			ImGui::Separator();
			unsigned int pathSize = (unsigned int) path.size();

			if (ImGui::Button("..."))
			{
				for (int i = pathSize - 2; i > 0; i--)
				{
					if (path[i] == '/')
					{
						path = path.substr(0, i) + "/";
						//std::cout << path + "\n";
						pathSize = (unsigned int) path.size();
						break;
					}
				}
			}
			//std::string path = "../Game/Resources/";
			
			for (const auto & p : fs::directory_iterator(path))
			{
				filename = p.path().generic_string().substr(pathSize, p.path().generic_string().size());
				if (ImGui::Button(filename.c_str()))
				{
					if (filename.size() > 5)
					{
						char letteron2 = filename[filename.size() - 3];
						char letteron3 = filename[filename.size() - 4];
						char letteron4 = filename[filename.size() - 5];

						if (letteron2 == '.' ||	letteron3 == '.' ||	letteron4 == '.')
						{
							//std::cout << "it's a file.";
							selectedFile = path + filename;
						}
						else
						{
							//std::cout << "it's a folder.";
							path += filename + "/";
						}
					}
					else
					{
						//std::cout << "it's a folder.";
						path += filename + "/";
					}
				}
				//std::cout << p.path().generic_string() << std::endl;
			}

			ImGui::End();
		}
	}
}
