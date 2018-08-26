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

class Board
{
    protected:
        int player;
        int grid[9];
        void updatePlayer();
        void scoreBoard();
        const static int X=0;
        const static int Y=1;
        const static int E=-1;

    public:
        Board();
        void updateBoard(int col, int row);
        void printBoard();
};

Board::Board()
{
    this->player = 0;
    this->grid[0] = -1;
    this->grid[1] = -1;
    this->grid[2] = -1;
    this->grid[3] = -1;
    this->grid[4] = -1;
    this->grid[5] = -1;
    this->grid[6] = -1;
    this->grid[7] = -1;
    this->grid[8] = -1;
}

void Board::updatePlayer(){
    Board::player = (Board::player + 1) % 2;
}

void Board::updateBoard(int col, int row)
{
    int loc = col + 3*row;
    if(this->grid[loc] == -1){
        this->grid[loc] = this->player;
        this->updatePlayer();
    }
}

void Board::scoreBoard()
{

}

void Board::printBoard()
{
    std::cout << this->grid[0] << " " << this->grid[1] << " " << this->grid[2] << std::endl;
    std::cout << this->grid[3] << " " << this->grid[4] << " " << this->grid[5] << std::endl;
    std::cout << this->grid[6] << " " << this->grid[7] << " " << this->grid[8] << std::endl;
}

int main(int, char**){
    if(!init()){
        return 1;
    }
    
    bool quit = false;
    SDL_Event e;
    int x = 0, y = 0;

    Board b = Board();
    b.printBoard();

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_MOUSEBUTTONUP){
                SDL_GetMouseState(&x, &y);
                int col = x / (SCREEN_WIDTH / 3); 
                int row = y / (SCREEN_HEIGHT / 3);
                std::cout << "x position is: " << col << std::endl;
                std::cout << "y position is: " << row << std::endl;
                b.updateBoard(col, row);
                b.printBoard();

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
