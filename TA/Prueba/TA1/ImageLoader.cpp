#include "ImageLoader.h"
#include "IOManager.h"
#include "Error.h"

GLTexture ImageLoader::LoadPNG(string FilePath) {
	vector<unsigned char> in;
	vector<unsigned char> out;
	unsigned long width;
	unsigned long height;

	//Validar que se ley� la ruta del buffer correctamente
	if (!IOManager::ReadFileToBuffer(FilePath, in)) { //Termin� en error
		FatalError("Couldn't read " + FilePath);
	}

	return GLTexture();
}
