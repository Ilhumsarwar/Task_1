#include <SDL.h>
#include<stdio.h>
#include <math.h>

#define screen_width 1080
#define screen_height 520
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// global variables
bool gameisrunning = false;
SDL_Window * window = NULL;
SDL_Renderer* renderer = NULL;
float r = 1.0 ;
float   rin = r;

void draw_circle_simple(SDL_Renderer* renderer, int cx, int cy, int r) {
    // go around 360 degrees
    for (int angle = 0; angle < 360; angle++) {
        // convert angle to radians
        float rad = angle * (3.14159 / 180.0);

        // calculate x and y on the circle
        int x = cx + r * cos(rad);
        int y = cy + r * sin(rad);

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int r){
    for(int y = -r; y<=r;y++){
        int x = sqrt(r*r - y*y);
        SDL_RenderDrawLine(renderer,
        cx - x, cy+y, //left
        cx+x, cy+y //right coordinates
        );
    }
}
int initialize_window(void){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        return 0;
    }
    window = SDL_CreateWindow("Task 102", SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,
    SDL_WINDOW_BORDERLESS);

    if(!window){
        fprintf(stderr,"ERROR creating sdl window.\n");
        return 0;
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        fprintf(stderr, "Error creating SDL renderer.\n");
        return 0;
    }

    return 1;
}

void setup(){

}


void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
        gameisrunning = false; break;
        case SDL_KEYDOWN:
        //inside event there is key inside key for the escape symbol
        if(event.key.keysym.sym == SDLK_ESCAPE)
        gameisrunning = false; 
        break;

    }
}

void update(){
    if(r < WINDOW_HEIGHT/2)
    r+=0.2;
    else r = rin;
}

void render(){
    //colour and clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //set the colour to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //draw a circle in the middle of the screen with radius 100
    int cx = WINDOW_WIDTH / 2;
    int cy = WINDOW_HEIGHT / 2;
    //SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    //draw_circle_simple(renderer, cx, cy, 100);
    
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    draw_filled_circle(renderer,cx,cy,r);
    //present the back buffer to the screen
    SDL_RenderPresent(renderer);

}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]){
    gameisrunning = initialize_window();
    
    setup();

    while(gameisrunning){
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}