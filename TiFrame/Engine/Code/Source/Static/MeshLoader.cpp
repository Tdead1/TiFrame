#include <Static/MeshLoader.h>

#include <fstream>

#include <Utility/Timer.h>
#include <Elements/Vector.h>

using namespace Ti;
using namespace std;




Mesh *MeshLoader::LoadMesh(std::string _filePath, std::string _meshName)
{
	Mesh* mesh = new Mesh;
	mesh->filePath = _filePath;
	Timer timer;
	timer.start();

	// Code imported from JK project made by me //
	vector<float> vertexCoords;
	vector<float> textureCoords;
	vector<float> normalCoords;
	vector<unsigned int> indices;
	vector<Vertex> vertices;

	string filePath = _filePath;
	string objectType = filePath.substr(filePath.length() - 4, filePath.length());

	if (objectType == ".obj")
	{
		Logger::Print("Type is .obj file.");

		ifstream in(_filePath);
		string line;
		string numberToStoreString;
		
		bool storeNextNumber		= false;
		float numberToStoreFloat	= 0.0f;
		int numberToStoreInt		= 0;
		int currentVertex			= 0;
		int positionCounter			= 0;

		while (getline(in, line))
		{
			// Ignoring the comments
			if (line.substr(0, 1) == "#")
			{
			}
			// Storing the vertices
			else if (line.substr(0, 2) == "v ")
			{
				Vertex vert;
				for (unsigned int i = 0; i <= line.length(); i++)
				{
					if (i < line.length())
					{
						if (storeNextNumber)
						{
							if (line.at(i) == ' ' || line.at(i) == '/')
							{
								// Run this when I find a space or /, and store the number that came before it.
								numberToStoreFloat = stof(numberToStoreString, 0);
								numberToStoreString.clear();
								vertexCoords.push_back(numberToStoreFloat);
								vert.pos[positionCounter] = numberToStoreFloat;
								positionCounter++;
								storeNextNumber = false;
								numberToStoreFloat = 0;
							}
							else
								numberToStoreString += line.at(i);
						}
						// Determine that I have to store a number next.
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					else if (storeNextNumber)
					{
						// Run this when I am at the end of the line, and I need to store a number.
						numberToStoreFloat = stof(numberToStoreString, 0);
						numberToStoreString.clear();
						vert.pos[positionCounter] = numberToStoreFloat;
						vertexCoords.push_back(numberToStoreFloat);
						storeNextNumber = false;
						numberToStoreFloat = 0;

						// At the end of the vertex line, create a vertex struct.
						vertices.push_back(vert);
						positionCounter = 0;
					}
				}
			}
			// Storing the textures
			else if (line.substr(0, 2) == "vt")
			{
				for (unsigned int i = 0; i < line.length() + 1; i++)
				{
					// If we're not at the end of the line yet.
					if (i < line.length())
					{
						// If I should store a number
						if (storeNextNumber)
						{
							if (line.at(i) == ' ' || line.at(i) == '/')
							{
								numberToStoreFloat = stof(numberToStoreString, 0);
								numberToStoreString.clear();
								textureCoords.push_back(numberToStoreFloat);
								storeNextNumber = false;
								numberToStoreFloat = 0;
							}
							else
								numberToStoreString += line.at(i);
						}
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					// If we are at the end of the line, but we still want to store the next number.
					else if (storeNextNumber)
					{
						numberToStoreFloat = stof(numberToStoreString, 0);
						numberToStoreString.clear();
						textureCoords.push_back(numberToStoreFloat);
						storeNextNumber = false;
						numberToStoreFloat = 0;
					}

				}
			}
			// Storing the normals
			else if (line.substr(0, 2) == "vn")
			{
				for (unsigned int i = 0; i < line.length() + 1; i++)
				{
					// If we're not at the end of the line yet
					if (i < line.length())
					{
						// If we want to store the next number
						if (storeNextNumber)
						{
							if (line.at(i) == ' ' || line.at(i) == '/')
							{
								numberToStoreFloat = stof(numberToStoreString, 0);
								numberToStoreString.clear();
								normalCoords.push_back(numberToStoreFloat);
								storeNextNumber = false;
								numberToStoreFloat = 0;
							}
							else
								numberToStoreString += line.at(i);
						}
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					// If we are at the end of the line, but still want to store a number.
					else if (storeNextNumber)
					{
						numberToStoreFloat = stof(numberToStoreString, 0);
						numberToStoreString.clear();
						normalCoords.push_back(numberToStoreFloat);
						storeNextNumber = false;
						numberToStoreFloat = 0;
					}

				}
			}
			// Storing the facesList
			else if (line.substr(0, 2) == "f ")
			{
				for (unsigned int i = 0; i < line.length() + 1; i++)
				{
					if (i < line.length())
					{
						if (storeNextNumber)
						{
							// storeNextNumber = true && i < line.length && (line.at(i) == ' ' || line.at(i) == '/')
							if (line.at(i) == ' ' || line.at(i) == '/')
							{
								numberToStoreInt = stoi(numberToStoreString, 0);
								numberToStoreString.clear();
								if (positionCounter == 0 || positionCounter == 3 || positionCounter == 6)
								{
									indices.push_back(numberToStoreInt - 1);
									currentVertex = numberToStoreInt - 1;
								}
								if (positionCounter == 1 || positionCounter == 4 || positionCounter == 7)
								{
									vertices[currentVertex].tex[0] = textureCoords[(numberToStoreInt - 1) * 2];
									vertices[currentVertex].tex[1] = textureCoords[(numberToStoreInt - 1) * 2 + 1];
								}
								if (positionCounter == 2 || positionCounter == 5 || positionCounter == 8)
								{
									vertices[currentVertex].nor[0] = normalCoords[(numberToStoreInt - 1) * 3];
									vertices[currentVertex].nor[1] = normalCoords[(numberToStoreInt - 1) * 3 + 1];
									vertices[currentVertex].nor[2] = normalCoords[(numberToStoreInt - 1) * 3 + 2];
								}
								positionCounter++;

								storeNextNumber = false;
								numberToStoreInt = 0;
							
							}
							else
								numberToStoreString += line.at(i);
						}
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					else if (storeNextNumber)
					{
						numberToStoreInt = stoi(numberToStoreString, 0);
						numberToStoreString.clear();
						if (positionCounter == 1 || positionCounter == 4 || positionCounter == 7)
						{
							vertices[currentVertex].tex[0] = textureCoords[(numberToStoreInt - 1) * 2];
							vertices[currentVertex].tex[1] = textureCoords[(numberToStoreInt - 1) * 2 + 1];
						}
						if (positionCounter == 2 || positionCounter == 5 || positionCounter == 8)
						{
							vertices[currentVertex].nor[0] = normalCoords[(numberToStoreInt - 1) * 3];
							vertices[currentVertex].nor[1] = normalCoords[(numberToStoreInt - 1) * 3 + 1];
							vertices[currentVertex].nor[2] = normalCoords[(numberToStoreInt - 1) * 3 + 2];
						}
						storeNextNumber = false;
						numberToStoreInt = 0;
						positionCounter = 0;
					}
				}
			}
		}

		Logger::Print("Successfully read " + filePath + " :", LogType::SUCCESS);
	}
	else
	{
		Logger::Print("File type unknown or unsupported.", LogType::PROBLEM);
	}

	mesh->vertices = vertices;
	mesh->indices = indices;

	vertexCoords.clear();
	textureCoords.clear();
	normalCoords.clear();

	vertexCoords.shrink_to_fit();
	textureCoords.shrink_to_fit();
	normalCoords.shrink_to_fit();

	timer.stop();
	Logger::Print("Total loading time:");
	timer.print();

	return mesh;
}