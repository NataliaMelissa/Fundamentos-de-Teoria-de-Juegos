#pragma once
#include "GLTexture.h"
#include <string>

using namespace std;

class ImageLoader {
//M�todos
public:
	//Funci�n para cargar la im�gen
	static GLTexture LoadPNG(string FilePath);

};

