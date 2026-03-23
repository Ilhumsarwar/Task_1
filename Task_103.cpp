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
float r = 25.0,r2 = 30.0;
float cx = 0,cx2 =  WINDOW_WIDTH/2;
float cy = WINDOW_HEIGHT/2,cy2 = r2;

void draw_circle_simple(SDL_Renderer* renderer, float cx, float cy, float r) {
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

void draw_filled_circle(SDL_Renderer* renderer, float cx, float cy, float r){
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
    window = SDL_CreateWindow("Task 103", SDL_WINDOWPOS_CENTERED, 
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
int flag = 0;
void update(){
    
    float d = sqrt((cx2-cx)*(cx2-cx)+ (cy2-cy)*(cy2-cy));
    if(d>r+r2)cx+=0.5;
    else{ flag = 1;
    r2 = 0;}
    if(cx > WINDOW_WIDTH ) cx = 0;
    
    
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if(keystates[SDL_SCANCODE_UP] && cy2>r2) cy2 -=0.5;
    if(keystates[SDL_SCANCODE_DOWN] && cy2<WINDOW_HEIGHT-r2) cy2 +=0.5;
    if(keystates[SDL_SCANCODE_LEFT] && cx2>r2) cx2 -=0.5; 
    if(keystates[SDL_SCANCODE_RIGHT] && cx2<WINDOW_WIDTH-r2) cx2 +=0.5;
}

void render(){
    //colour and clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //set the colour to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   
    //circle1
    if(flag==1){SDL_SetRenderDrawColor(renderer, 0,255,0,255);}
    else SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    draw_filled_circle(renderer, cx, cy,r);
    
    //circle2
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    draw_filled_circle(renderer,cx2,cy2,r2);

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