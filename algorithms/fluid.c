#include <stdio.h>
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#include <stdbool.h>


typedef struct Particle{
	float x, y;
 	float vx, vy; // velocity
} Particle;


int main(){

	printf("Hey \n");

	Particle p1;
	p1.x = SCREEN_WIDTH / 2;
	p1.y = SCREEN_HEIGHT / 2;
	p1.vx = 11;
	p1.vy = 12;

	printf("X: %f, Y: %f, VX: %f, VY: %f", p1.x, p1.y, p1.vx, p1.vy);
	SDL_Surface* screenSurface = NULL;
	SDL_Window* window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
	}

	window = SDL_CreateWindow("Fluid Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(!window){
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
	}
	
	screenSurface = SDL_GetWindowSurface(window);

	SDL_Rect rect = {(int) p1.x, (int) p1.y, 30, 20};

	
	bool running = true;
	while(running){

		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0) );
		SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0, 0, 255) );

		SDL_UpdateWindowSurface(window);
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				running = false;
			}
			else if(event.type == SDL_KEYDOWN){

				if(event.key.keysym.sym == SDLK_DOWN){
					rect.y += 2;
	
				}
				else if(event.key.keysym.sym == SDLK_UP){
					rect.y -= 2;
	
				}
				else if(event.key.keysym.sym == SDLK_LEFT){
					rect.x -= 2;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT){
					rect.x += 2;
				}

				//SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0, 0, 255) );
				//SDL_UpdateWindowSurface(window);
			}
		}
		if(!running){

			SDL_DestroyWindow(window);

			SDL_Quit();
			break;
		}
	}
	//SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0, 0, 255) );

	//SDL_UpdateWindowSurface(window);

	//SDL_Delay(5000);

	//SDL_DestroyWindow(window);

	//SDL_Quit();

	return 0;
}
