#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

class Texture
{
    public:
        Texture();
        ~Texture();

        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y);
        int getWidth();
        int getHeight();

    private:
        SDL_Texture* texture;
        int width;
        int height;
};

Texture xTexture;
Texture oTexture;

bool init();
bool loadMedia();
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

bool loadMedia()
{
    if(!xTexture.loadFromFile("/home/zero/game-clones/tic-tac-toe/tic-tac-toe/resources/theX.png"))
    {
        // TODO: logging
        std::cout << "could not load theO.png" << std::endl;
        return false;
    }

    if(!oTexture.loadFromFile("/home/zero/game-clones/tic-tac-toe/tic-tac-toe/resources/theO.png"))
    {
        // TODO: logging
        std::cout << "could not load theO.png" << std::endl;
        return false;
    }
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
        int scoreBoard();
        int check_row(int row);
        int check_col(int col);

    public:
        Board();
        int updateBoard(int col, int row);
        void resetBoard();
        void printBoard();
        int getSquare(int x, int y);
};

Board::Board()
{
    this->resetBoard();
}

void Board::resetBoard()
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

int Board::updateBoard(int col, int row)
{
    int loc = col + 3*row;
    if(this->grid[loc] == -1){
        this->grid[loc] = this->player;
        this->updatePlayer();
        return this->scoreBoard();
    }
    return -1;
}

int Board::check_row(int row)
{
    if(this->grid[3*row]!=-1 && this->grid[3*row]==this->grid[3*row+1] && this->grid[3*row+1]==this->grid[3*row+2])
    {
        return grid[3*row];
    }
    else{
        return -1;
    }
}

int Board::check_col(int col)
{
    if(this->grid[col]!=-1 && this->grid[col]==this->grid[col+3] && this->grid[col+3]==this->grid[col+6])
    {
        return grid[col];
    }
    else{
        return -1;
    }
}

int Board::scoreBoard()
{
    //check rows
    if(this->check_row(0)!=-1){return this->check_row(0);}
    if(this->check_row(1)!=-1){return this->check_row(1);}
    if(this->check_row(2)!=-1){return this->check_row(2);}

    //check columns
    if(this->check_col(0)!=-1){return this->check_col(0);}
    if(this->check_col(1)!=-1){return this->check_col(1);}
    if(this->check_col(2)!=-1){return this->check_col(2);}

    //check diagonals
    if(this->grid[0]!=-1 && this->grid[0]==this->grid[4] && this->grid[4]==this->grid[8])
    {
        return this->grid[0];
    }

    if(this->grid[2]!=-1 && this->grid[2]==this->grid[4] && this->grid[4]==this->grid[6])
    {
        return this->grid[2];
    }

    return -1;
}

void Board::printBoard()
{
    std::cout << this->grid[0] << " " << this->grid[1] << " " << this->grid[2] << std::endl;
    std::cout << this->grid[3] << " " << this->grid[4] << " " << this->grid[5] << std::endl;
    std::cout << this->grid[6] << " " << this->grid[7] << " " << this->grid[8] << std::endl;
}

int Board::getSquare(int x, int y)
{
    return this->grid[3*y + x];
}


Texture::Texture()
{
    this->texture = NULL;
    this->width = 0;
    this->height = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(std::string path)
{
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        // TODO: log message
        return false;
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture == NULL)
    {
        //TODO: log message
        return false;
    }

    this->width = loadedSurface->w;
    this->height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    
    this->texture = newTexture;
    return this->texture != NULL;
}

void Texture::free()
{
    if(this->texture != NULL)
    {
        SDL_DestroyTexture(texture);
        this->texture=NULL;
        this->width=0;
        this->height=0;
    }
}

void Texture::render(int x, int y)
{
    SDL_Rect renderQuad = {x, y, this->width, this->height};
    SDL_RenderCopy(gRenderer, this->texture, NULL, &renderQuad);
}

int Texture::getWidth()
{
    return this->width;
}

int Texture::getHeight()
{
    return this->height;
}

int main(int, char**){
    if(!init()){
        return 1;
    }

    if(!loadMedia()){
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
                int winner = b.updateBoard(col, row);
                if(winner != -1)
                {
                    std::cout << std::to_string(winner) << std::endl;
                    std::cout << ((winner==0)?"X":"Y") << " won the game!" << std::endl;
                    b.resetBoard();
                }
                b.printBoard();

            }
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        
        int val = -1;
        //Render the Xs and the Os on the board
        for(int x=0; x<3; x++)
        {
            for(int y=0; y<3; y++)
            {
               val = b.getSquare(x, y);
               if(val==0)
               {
                   xTexture.render(x*SCREEN_WIDTH/3, y*SCREEN_HEIGHT/3);
               }
               else if(val==1)
               {
                   oTexture.render(x*SCREEN_WIDTH/3, y*SCREEN_HEIGHT/3);
               }
            }
        }
         

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
