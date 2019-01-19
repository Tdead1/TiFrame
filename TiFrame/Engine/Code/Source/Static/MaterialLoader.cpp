#include <Static/MaterialLoader.h>
#include <fstream>
#include <iostream>
using namespace Ti;
using namespace std;

Material *MaterialLoader::LoadMaterial(std::string _filePath, std::string _modelName)
{
	Material* material = new Material;
	material->filePath = _filePath;

	ifstream in(material->filePath);
	string line;
	string *data = new string;

	while (getline(in, line))
	{
		for (int i = 0; i < (int)line.length(); i++)
		{
			*data += line.at(i);
		}
		*data += '\n';
	}
	material->data = data->c_str();
	return material;
}