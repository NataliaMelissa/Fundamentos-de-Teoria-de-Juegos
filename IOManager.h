#pragma once
#include <string>
#include <vector>

using namespace std;

class IOManager {

//M�todos
public:
	static bool ReadFileToBuffer(string FilePath, vector<unsigned char>& buffer);
};

