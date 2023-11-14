#ifndef MAIN_H
#define MAIN_H
#include "common.h"

typedef struct{
		SDL_Rect rect;
		int momentum_y;
		int momentum_x;
		int count;
		int score;
		SDL_Surface *score_surface;
		SDL_Rect score_rect;
		SDL_Texture *score_texture;
	}Entity;

typedef struct{

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Surface *start_screen;
	SDL_Texture *start_texture;
	SDL_Rect start_rect;

	SDL_Surface *winner_screen;
	SDL_Texture *winner_texture;
	SDL_Rect winner_rect;

	TTF_Font *bitfont;
	SDL_Color bitfontcolor;
	SDL_Color startfontcolor;
	SDL_Color winnerfontcolor;

	Entity ball, player1, player2;

	SDL_Surface *ball_surface;
	SDL_Texture *ball_texture;
	Uint32 ball_color;

	int is_space;
	int is_winner;

	float delta_time;
	int last_frame_time;

}App;

#endif
