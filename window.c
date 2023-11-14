#include "common.h"

int initialize_window(App *app){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return FALSE;
	}
	if(TTF_Init() < 0){
		fprintf(stderr, "Error starting ttf: %s\n", TTF_GetError());
		return FALSE;
	}
	app->bitfont = TTF_OpenFont("presstart2p.ttf", 48);
	if(!app->bitfont){
		fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
		return FALSE;
	}
	app->window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if(!app->window){
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		return FALSE;
	}
	app->renderer = SDL_CreateRenderer(app->window, -1, 0);
	if(!app->renderer){
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		return FALSE;
	}
	return TRUE;
}

void setup(App *app){

	app->is_space = FALSE;
	app->is_winner = FALSE;

	app->start_rect.x = WINDOW_WIDTH / 8;
	app->start_rect.y = WINDOW_HEIGHT / 3;
	app->start_rect.w = WINDOW_WIDTH - (WINDOW_WIDTH / 4);
	app->start_rect.h = WINDOW_HEIGHT / 3;

	app->winner_rect.x = WINDOW_WIDTH - SCORE_SIZE - WINDOW_WIDTH / 3;
	app->winner_rect.y = WINDOW_HEIGHT / 12;
	app->winner_rect.w = WINDOW_WIDTH / 3;
	app->winner_rect.h = WINDOW_HEIGHT / 8;

	app->bitfontcolor.r = 0;
	app->bitfontcolor.g = 0;
	app->bitfontcolor.b = 255;
	app->bitfontcolor.a = 255;

	app->startfontcolor.r = 255;
	app->startfontcolor.g = 255;
	app->startfontcolor.b = 255;
	app->startfontcolor.a = 255;

	app->start_screen = TTF_RenderText_Solid_Wrapped(app->bitfont, "Press [SPACE] to start\n\n\nPress [ESC] to exit", app->startfontcolor, 1120);
	app->start_texture = SDL_CreateTextureFromSurface(app->renderer, app->start_screen);

	app->winnerfontcolor.r = 205;
	app->winnerfontcolor.g = 127;
	app->winnerfontcolor.b = 50;
	app->winnerfontcolor.a = 255;

	app->winner_screen = TTF_RenderText_Solid_Wrapped(app->bitfont, "!!!WINNER!!!", app->winnerfontcolor, 1120);
	app->winner_texture = SDL_CreateTextureFromSurface(app->renderer, app->winner_screen);

	app->player1.score = 0;
	app->player1.score_rect.x = SCORE_X;
	app->player1.score_rect.y = SCORE_Y;
	app->player1.score_rect.w = SCORE_SIZE;
	app->player1.score_rect.h = SCORE_SIZE;

	app->player2.score = 0;
	app->player2.score_rect.x = (WINDOW_WIDTH - SCORE_X - SCORE_SIZE);
	app->player2.score_rect.y = SCORE_Y;
	app->player2.score_rect.w = SCORE_SIZE;
	app->player2.score_rect.h = SCORE_SIZE;

	app->ball_surface = SDL_CreateRGBSurface(0, BALL_SIZE_X, BALL_SIZE_Y, 8, 255, 255, 255, 255);
	app->ball_texture = SDL_CreateTextureFromSurface(app->renderer, app->ball_surface);
	app->ball.rect.x = (WINDOW_WIDTH / 2) - (BALL_SIZE_X / 2);
	app->ball.rect.y = (WINDOW_HEIGHT / 2) - (BALL_SIZE_Y / 2);
	app->ball.rect.w = BALL_SIZE_X;
	app->ball.rect.h = BALL_SIZE_Y;
	app->ball.momentum_x = 0;
	app->ball.momentum_y = 0;
	app->ball.count = 0;
	app->ball_color = 255255255;

	app->player1.rect.x = 0;
	app->player1.rect.y = (WINDOW_HEIGHT / 2) - (PLAYER_SIZE_Y / 2);
	app->player1.rect.w = PLAYER_SIZE_X;
	app->player1.rect.h = PLAYER_SIZE_Y;
	app->player1.momentum_y = 0;
	app->player1.momentum_x = 0;

	app->player2.rect.x = WINDOW_WIDTH - PLAYER_SIZE_X;
	app->player2.rect.y = (WINDOW_HEIGHT / 2) - (PLAYER_SIZE_Y / 2);
	app->player2.rect.w = PLAYER_SIZE_X;
	app->player2.rect.h = PLAYER_SIZE_Y;
	app->player2.momentum_y = 0;
	app->player2.momentum_x = 0;

	srand(time(0));
}

void destroy_window(App *app){

	SDL_DestroyRenderer(app->renderer);
	//SDL_FreeSurface(app->player1.score_surface);
	//SDL_FreeSurface(app->player2.score_surface);
	SDL_FreeSurface(app->start_screen);
	SDL_FreeSurface(app->winner_screen);
	//SDL_FreeSurface(app->ball_surface);
	//SDL_DestroyTexture(app->player1.score_texture);
	//SDL_DestroyTexture(app->player2.score_texture);
	SDL_DestroyTexture(app->start_texture);
	SDL_DestroyTexture(app->winner_texture);
	SDL_DestroyWindow(app->window);
	TTF_CloseFont(app->bitfont);
	SDL_Quit();
}
