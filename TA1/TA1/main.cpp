#include <SDL/SDL.h>
#include "MainGame.h"

int main(int argc, char** argv) {
	MainGame mainGame; 
	
	mainGame.run(); //Ejecutar la clase game:

	system("pause"); //La pantalla no haga poof luego de un segundo
	return 0;
}