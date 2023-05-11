#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <String>

using namespace std;

enum WindowFlags {
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

class Window {
	SDL_Window* window;
	int screenWidth; //ancho
	int screenHeight; //alto

//Métodos
public:
	Window();

	~Window();

	//Cambiar de ventana
	void swapWindow();

	//Obtener el ancho
	int getScreenWidth() {
		return screenWidth;
	}

	//Obtener el alto
	int getScreenHeight() {
		return screenHeight;
	}

	int create(string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
};

