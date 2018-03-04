#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/_gui.h"
#include "../include/game.h"
#include "../include/minimax_alphabeta.h"

/*
 * gcc -o sdl_main main_gui.c state.c game.c utility.c minimax_alphabeta.c -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -mwindows -O3 -std=c99
 */

bool init()
{
    window  = NULL;
    surface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    return true;
}

void create_window()
{
    window   = SDL_CreateWindow("TicTacToe | author: http:://github.com/DispatchCode",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    surface  = SDL_GetWindowSurface(window);
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void draw_board()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE );
    SDL_RenderDrawLine(renderer, 200, 0, 200, 600);
    SDL_RenderDrawLine(renderer, 400, 0, 400, 600);
    SDL_RenderDrawLine(renderer, 0, 200, 600, 200);
    SDL_RenderDrawLine(renderer, 0, 400, 600, 400);
    SDL_RenderPresent(renderer);
}

int get_clicked_square(int x, int y)
{
    int pos = 0;

    if(y > 0 && y<200)
    {
        if(x > 0 && x < 200)
            pos = 0;
        else if(x > 200 && x < 400)
            pos = 1;
        else if(x > 400 && x < 600)
            pos = 2;
    }
    else if(y > 200 && y < 400)
    {
        if(x > 0 && x < 200)
            pos = 3;
        else if(x > 200 && x < 400)
            pos = 4;
        else if(x > 400 && x < 600)
            pos = 5;
    }
    else if(y > 400 && y < 600)
    {
        if(x > 0 && x < 200)
            pos = 6;
        else if(x > 200 && x < 400)
            pos = 7;
        else if(x > 400 && x < 600)
            pos = 8;
    }

    return pos;
}

int move_x_player(int x, int y)
{
    return get_clicked_square(x,y);
}

void draw_players(_state state)
{
    int x1 = 10, y1 = 10;

    for(int i=0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            SDL_Rect texr;
            texr.x = x1 + (200*j);
            texr.y = y1 + (200*i);
            texr.w = 172;
            texr.h = 172;

            spatial_coords coord;
            coord.x = i;
            coord.y = j;

            int index = spatial_coords_2_index(coord);

            if (state.board[index] == PLAYER_X)
                SDL_RenderCopy(renderer, img_x, NULL, &texr);
            else if (state.board[index] == PLAYER_O)
                SDL_RenderCopy(renderer, img_o, NULL, &texr);
        }
    }

    SDL_RenderPresent(renderer);
}

void print_message(SDL_Texture* texture)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect texr;
    texr.x = 150;
    texr.y = 100;
    texr.w = 350;
    texr.h = 440;

    SDL_RenderCopy(renderer, texture, NULL, &texr);
    SDL_RenderPresent(renderer);
}

void game_ended(double val)
{

    if(val == 0.5)
    {
        SDL_Texture* draw = IMG_LoadTexture(renderer, DRAW);
        print_message(draw);
    }
    else if(val == 0)
    {
        SDL_Texture* o_win = IMG_LoadTexture(renderer, O_WIN);
        print_message(o_win);
    }
    else if(val == 1)
    {
        SDL_Texture* x_win = IMG_LoadTexture(renderer, X_WIN);
        print_message(x_win);
    }
}

void game()
{
    _state state = _game_start();
    int board_index = 0;

    // Load texture
    img_x = IMG_LoadTexture(renderer, IMG_X);
    img_o = IMG_LoadTexture(renderer, IMG_O);

    running = true;
    while(running)
    {
        if(!_game_is_terminal(state))
            draw_board();

        while (SDL_PollEvent(&event))
        {
            int x, y;
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                break;

                case SDL_MOUSEBUTTONDOWN:
                    // Lettura coordinate click mouse
                    SDL_GetMouseState(&x, &y);
                    board_index = move_x_player(x, y);
                    // player move in (x,y)
                    _state_move(&state, index_to_xy(board_index));
                    // IA turn
                    spatial_coords coords = _minimax_alpha_beta_search(state);
                    _state_move(&state, coords);

                    draw_players(state);

                    if (state.utility != -1)
                        game_ended(state.utility);

                    SDL_Delay(10);
                break;
            }
        }
    }
}

void quit()
{
    SDL_DestroyTexture(img_o);
    SDL_DestroyTexture(img_x);

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

int main(int argc, char* argv[])
{
    init();
    create_window();
    game();

    quit();

    return 0;
}