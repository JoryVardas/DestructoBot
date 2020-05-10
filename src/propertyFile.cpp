#include "propertyFile.h"

void PropertyFile::parseFile(std::ifstream& file) {
	std::string line;
	while (std::getline(file, line)) {
		size_t split = line.find_first_of(" ");
		_properties[line.substr(0, split)] = line.substr(split + 1);
	};
};

PropertyFile::PropertyFile() {};
PropertyFile::PropertyFile(std::string path) {
	_path = path;
	load(path);
};

void PropertyFile::load(std::string path) {
	std::ifstream file;
	file.open(path, std::ifstream::in);

	bool test = file.is_open();

	parseFile(file);
	file.close();
};

std::string PropertyFile::operator [](std::string prop) {
	if (_properties.count(prop) == 0) {
		return "";
	};

	return _properties[prop];
};