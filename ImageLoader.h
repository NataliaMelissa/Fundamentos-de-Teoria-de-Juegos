#pragma once
#include "GLTexture.h"
#include <string>

using namespace std;

class ImageLoader {
//Métodos
public:
	//Función para cargar la imágen
	static GLTexture LoadPNG(string FilePath);

};

