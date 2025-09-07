//Kompiliern :- gcc fluid.c -o sdl2_test `sdl2-config --cflags --libs`
//Ausführen :- ./sdl2_test

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define MAX_PARTICLES 10

int particle_count = 0;

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


void drawParticles(SDL_Surface* surface,Particle particles[]){

    Uint32 blue = SDL_MapRGB(surface->format, 0, 0, 255);
   
    for(int i = 0; i < particle_count; ++i){
        drawCircle(surface, particles[i].x, particles[i].y, particles[i].radius, blue);
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
	Particle particle = {SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, 0, 0.5, 20};
    Particle particels[MAX_PARTICLES];
    Uint32 blue = SDL_MapRGB(screenSurface->format, 0, 0, 255);
    Uint32 black = SDL_MapRGB(screenSurface->format, 0, 0, 0);
   
	
	bool running = true;
	while(running){
		
		SDL_FillRect(screenSurface, NULL, black);
		drawParticles(screenSurface, particels);

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

			else if(event.type == SDL_MOUSEBUTTONDOWN){

                if(particle_count < MAX_PARTICLES){
                    
                    int mx = event.button.x;
                    int my = event.button.y;

                    Particle particle;
                    particle.x = mx;
                    particle.y = my;
                    particle.vx = 0;
                    particle.vy = 0;
                    particle.radius = 20;

                    particels[particle_count++] = particle;
                }
			}
		}
		if(!running){

			SDL_DestroyWindow(window);
			SDL_Quit();
			break;
		}

		particle.y += particle.vy;
	}

	return 0;
}
