#include <stdio.h>
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#include <stdbool.h>


typedef struct Particle{
	float x, y;
 	float vx, vy; // velocity
	int radius;
} Particle;


void drawCircle(SDL_Surface* surface, int cx, int cy, int radius, Uint32 color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) { // inside circle
                int px = cx + x;
                int py = cy + y;
                if (px >= 0 && px < surface->w && py >= 0 && py < surface->h) {
                    Uint32* pixels = (Uint32*)surface->pixels;
                    pixels[py * surface->w + px] = color;
                }
            }
        }
    }
}


int main(){

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

	//velcoity for now is 0
	Particle particle = {SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, 0,0, 20};
	Uint32 blue = SDL_MapRGB(screenSurface->format, 0, 0, 255);
	Uint32 black = SDL_MapRGB(screenSurface->format, 0, 0, 0);
	
	bool running = true;
	while(running){
		
		SDL_FillRect(screenSurface, NULL, black);
		drawCircle(screenSurface, particle.x, particle.y, particle.radius, blue);

		SDL_UpdateWindowSurface(window);
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				running = false;
			}
			else if(event.type == SDL_KEYDOWN){

				if(event.key.keysym.sym == SDLK_DOWN){
					particle.y += 5;
	
				}
				else if(event.key.keysym.sym == SDLK_UP){
					particle.y -= 5;
	
				}
				else if(event.key.keysym.sym == SDLK_LEFT){
					particle.x -= 5;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT){
					particle.x += 5;
				}
			}
		}
		if(!running){

			SDL_DestroyWindow(window);
			SDL_Quit();
			break;
		}
	}

	return 0;
}