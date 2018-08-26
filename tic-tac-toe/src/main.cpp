#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init();
void clean();

bool init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        //TODO: error logging
        return false;
    }

    gWindow = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        //TODO: error logging
        SDL_Quit();
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL){
        //TODO: error logging
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    return true;
}

void clean(){
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    SDL_Quit();
}

int main(int, char**){
    if(!init()){
        return 1;
    }
    
    bool quit = false;
    SDL_Event e;
    int x = 0, y = 0;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_MOUSEBUTTONUP){
                SDL_GetMouseState(&x, &y);
                std::cout << "x position is: " << x / (SCREEN_WIDTH / 3) << std::endl;
                std::cout << "y position is: " << y / (SCREEN_HEIGHT / 3) << std::endl;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT/3, SCREEN_WIDTH, SCREEN_HEIGHT/3);
        SDL_RenderDrawLine(gRenderer, 0, 2*SCREEN_HEIGHT/3, SCREEN_WIDTH, 2*SCREEN_HEIGHT/3);
        SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH/3, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT);
        SDL_RenderDrawLine(gRenderer, 2*SCREEN_WIDTH/3, 0, 2*SCREEN_WIDTH/3, SCREEN_HEIGHT);

        SDL_RenderPresent(gRenderer);
    }

    clean();
    return 0;
}
