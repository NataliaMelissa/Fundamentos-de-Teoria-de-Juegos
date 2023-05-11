#include "ImageLoader.h"
#include "IOManager.h"
#include "PicoPNG.h"
#include "Error.h"



GLTexture ImageLoader::LoadPNG(string FilePath) {
	vector<unsigned char> in;
	vector<unsigned char> out;
	unsigned long width;
	unsigned long height;
    GLTexture texture = {};

	//Validar que se leyó la ruta del buffer correctamente
	if (!IOManager::ReadFileToBuffer(FilePath, in)) { //Terminó en error
		FatalError("Couldn't read " + FilePath);
	}

	//Variable que almacena si se cargó y decodigicó la imagen correctamente
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

	//Validar que no terminó en error
    if (errorCode != 0) {
        FatalError("decode PNG with error " + std::to_string(errorCode));
    }

    glGenTextures(1, &(texture.id)); //Inicializar y generar una textura

    glBindTexture(GL_TEXTURE_2D, texture.id); //Indicar el tipo de textura

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, &(out[0])); //Indicar las propiedades de la textura

    //Mandar los parámetros de la textura
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Agrandar y que se repita la textura
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Achicar y que se repita la textura
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Mantenga sus propiedades cuando se haga mucho zoom
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //Cuando sigue igual que mantenga sus propiedades

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    //Asignar ancho y alto a la textura
    texture.width = width;
    texture.height = height;

    return texture;
}
