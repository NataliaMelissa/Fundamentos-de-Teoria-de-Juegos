#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

//M�todo: Obtener la textura en base a su TexturePath/direcci�n
GLTexture ResourceManager::getTexture(string texturePath) {
	return textureCache.getTexture(texturePath);
}