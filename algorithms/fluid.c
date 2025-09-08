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


typedef struct Color{
	int r, g, b;
} Color;


typedef struct Particle{
	float x, y;
 	float vx, vy; // velocity
	int radius;
	float mass;
	Color color;
} Particle;


void draw_circle(SDL_Renderer* renderer, int cx, int cy, int radius, Color color) {

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE); 


    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x*x + y*y <= radius*radius) { // inside circle
				SDL_RenderDrawPoint(renderer, cx + x, cy + y);
     
            }
        }
    }
}

int random_bettwen_0_255(){
	return rand() % 256;
}


void draw_particles(SDL_Renderer* renderer,Particle particles[]){

   
    for(int i = 0; i < g_particle_count; ++i){
        draw_circle(renderer, particles[i].x, particles[i].y, particles[i].radius, particles[i].color);
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
			if(compute_distance(particles[i], particles[j]) < particles[i].radius + particles[j].radius){

				float dx = particles[j].x - particles[i].x;
				float dy = particles[j].y - particles[i].y;

				float distance = compute_distance(particles[i], particles[j]);
				if (distance == 0) distance = 0.01f; // prevent division by zero

				float overlap = particles[i].radius + particles[j].radius - distance;

				float nx = dx / distance;
				float ny = dy / distance;

				// correct the posostion of the two particles like push them away from each other
				float correction = overlap / 2.0f;
				particles[i].x -= correction * nx;
				particles[i].y -= correction * ny;

				particles[j].x += correction * nx;
				particles[j].y += correction * ny;

				//update the velocity of the two aprticles

				//relative velocity of the two particles
				float rel_vel = ((particles[j].vx - particles[i].vx) * nx) + 
								((particles[j].vy - particles[i].vy) * ny);
				
				//change it only when the two particle going towarding each other
				if (rel_vel < 0) {
					float impulse = -(1.0f + DAMPING) * rel_vel / 2.0f;

					float ix = impulse * nx;
					float iy = impulse * ny;

					particles[i].vx -= ix;
					particles[i].vy -= iy;

					particles[j].vx += ix;
					particles[j].vy += iy;
				}
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
					particle.color.r = random_bettwen_0_255();
					particle.color.g = random_bettwen_0_255();
					particle.color.b = random_bettwen_0_255();


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
