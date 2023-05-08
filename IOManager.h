#pragma once
#include <string>
#include <vector>

using namespace std;

class IOManager {

//Métodos
public:
	static bool ReadFileToBuffer(string FilePath, vector<unsigned char>& buffer);
};

