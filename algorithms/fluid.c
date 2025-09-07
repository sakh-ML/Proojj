//Kompiliern :- gcc fluid.c -o sdl2_test `sdl2-config --cflags --libs` -lm
//Ausführen :- ./sdl2_test


#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define MAX_PARTICLES 30
#define DAMPING 0.9
#define G 1.5

int g_particle_count = 0;

typedef struct Particle{
	float x, y;
 	float vx, vy; // velocity
	int radius;
	float mass;
} Particle;


void draw_circle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x*x + y*y <= radius*radius) { // inside circle
				SDL_RenderDrawPoint(renderer, cx + x, cy + y);
     
            }
        }
    }
}


void draw_particles(SDL_Renderer* renderer,Particle particles[]){

	//blue color
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
   
    for(int i = 0; i < g_particle_count; ++i){
        draw_circle(renderer, particles[i].x, particles[i].y, particles[i].radius);
    }
}

void add_veloctiy(Particle particles[]){
	
	for(int i = 0; i < g_particle_count; ++i){
		particles[i].vy += G;
		particles[i].y += particles[i].vy;
	}
}

float compute_distance(Particle p1, Particle p2){

	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

void handle_collosions(Particle particles[]){
	for(int i = 0; i < g_particle_count - 1; ++i){
		for(int j= i + 1; j < g_particle_count; ++j){
			//check collosion bettwen the two particles
			if(compute_distance(particles[i], particles[j]) <= particles[i].radius + particles[j].radius){

				/*float tempVx = particles[i].vx;
				float tempVy = particles[i].vy;
				particles[i].vx = particles[j].vx;
				particles[i].vy = particles[j].vy;
				particles[j].vx = tempVx;
				particles[j].vy = tempVy;
				*/
				
				particles[i].x = -100;
				particles[i].y = -100;
				particles[j].x = -100;
				particles[j].x = -100;

				float dx = particles[j].x - particles[i].x;
				float dy = particles[j].y - particles[i].y;

				float distance = compute_distance(particles[i], particles[j]);

				float overlap = particles[i].radius + particles[j].radius - distance;

				float nx = overlap / distance;
				float ny = overlap / distance;

				particles[i].x -= nx * (overlap / 2);
				particles[i].y -= ny * (overlap / 2);

				particles[j].x += nx * (overlap/ 2);
				particles[j].y += ny * (overlap / 2);


 			}
		}
	}

	//collison
	for(int i = 0; i < g_particle_count; ++i){
		//ground collosion
		if(particles[i].y + particles[i].radius >= SCREEN_HEIGHT){
			particles[i].y = SCREEN_HEIGHT - particles[i].radius;
			particles[i].vy *= -DAMPING;
		}
		//cieling collosion
		if(particles[i].y - particles[i].radius <= 0){

		}

		//right collosion
		if(true){}
		//left collosion
		if(true){}
	}

}


int main(){

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
	}

	window = SDL_CreateWindow("Fluid Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(!window){
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
        exit(1);
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Particle particels[MAX_PARTICLES];
	memset(particels, 0, sizeof(particels));

	bool running = true;

	while(running){
		
		//clear background to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		SDL_RenderClear(renderer);

		// draw all particles on the screen
		draw_particles(renderer, particels);
		SDL_RenderPresent(renderer);

		//SDL_UpdateWindowSurface(window);
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				running = false;
			}

			else if(event.type == SDL_MOUSEBUTTONDOWN){

                if(g_particle_count < MAX_PARTICLES){
                    
                    int mx = event.button.x;
                    int my = event.button.y;

                    Particle particle;
                    particle.x = mx;
                    particle.y = my;
                    particle.vx = 0.5;
                    particle.vy = 0.5;
                    particle.radius = 20;

                    particels[g_particle_count++] = particle;
                }
			}
		}
		if(!running){

			SDL_DestroyWindow(window);
			SDL_Quit();
			break;
		}

		add_veloctiy(particels);
		handle_collosions(particels);
		SDL_Delay(5); 
	}

	return 0;
}
