#pragma once

#include <string>
#include <map>
#include <fstream>

class PropertyFile {
private:
	std::string _path;
	std::map<std::string, std::string> _properties;

	void parseFile(std::ifstream& file);
public:
	PropertyFile();
	PropertyFile(std::string path);

	void load(std::string path);

	std::string operator [](std::string prop);
};