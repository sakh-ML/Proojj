#include <stdio.h>
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(){

	printf("Hey \n");

	SDL_Surface* screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
	}

	SDL_Window* window = SDL_CreateWindow("Fluid Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(!window){
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
	}
	
	screenSurface = SDL_GetWindowSurface(window);


	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 255));

	SDL_UpdateWindowSurface(window);

	SDL_Delay(5000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
