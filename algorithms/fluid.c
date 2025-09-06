#include <stdio.h>
#include <SDL2/SDL.h>

int main(){

	printf("Hey \n");

	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
	}

	SDL_Window* window = SDL_CreateWindow("Fluid Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	window = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);

	if(!window){
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
	}

	SDL_Quit();

	return 0;
}
