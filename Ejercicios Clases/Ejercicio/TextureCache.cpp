#include "TextureCache.h"
#include "ImageLoader.h"
using namespace std;

//M�todo: Constructor 
TextureCache::TextureCache() {}

//M�todo: Destructor
TextureCache::~TextureCache() {}

//M�todo: Obtener la imagen en base a la direcci�n/path de la textura
GLTexture TextureCache::getTexture(string texturePath) {
	auto mit = textureMap.find(texturePath);

	//Validar si ya tiene la textura almacenada
	if (mit == textureMap.end()) { //No tiene la textura almacenada
		GLTexture texture = ImageLoader::LoadPNG(texturePath); //Textura a cargar

		pair<string, GLTexture> newPair(texturePath, texture); //Crear la textura con su direcci�n

		textureMap.insert(newPair); //Agregar la textura al map

		return texture; //Retornar la textura almacenada
	}

	return mit->second; //Retorna la textura que encontr�
}
