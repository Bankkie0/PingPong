#include "common.h"

int process_input(App *app){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.key.repeat == 0){
			Uint8 const *keys = SDL_GetKeyboardState(NULL);
			if(event.type == SDL_KEYDOWN && keys[SDL_SCANCODE_SPACE] && app->ball.momentum_x == 0){
				app->is_space = TRUE;
				app->ball.momentum_x = rspeed();
				app->ball.momentum_y = rspeed();
				if(app->is_winner){
					app->player1.score = 0;
					app->player2.score = 0;
					app->is_winner = FALSE;
					app->player1.rect.y = (WINDOW_HEIGHT / 2) - (PLAYER_SIZE_Y / 2);
					app->player2.rect.y = (WINDOW_HEIGHT / 2) - (PLAYER_SIZE_Y / 2);
				}
			}
			if(app->is_space){
				if(event.type == SDL_KEYDOWN && keys[SDL_SCANCODE_W]){
					app->player1.momentum_y = -PLAYER_SPEED;
				}
				if(event.type == SDL_KEYDOWN && keys[SDL_SCANCODE_S]){
					app->player1.momentum_y = PLAYER_SPEED;
				}
				if(event.type == SDL_KEYDOWN && keys[SDL_SCANCODE_UP]){
					app->player2.momentum_y = -PLAYER_SPEED;
				}
				if(event.type == SDL_KEYDOWN && keys[SDL_SCANCODE_DOWN]){
					app->player2.momentum_y = PLAYER_SPEED;
				}
				if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_w){
					app->player1.momentum_y = 0;
				}
				if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_s){
					app->player1.momentum_y = 0;
				}
				if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP){
					app->player2.momentum_y = 0;
				}
				if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN){
					app->player2.momentum_y = 0;
				}

			}
			if(event.type == SDL_KEYDOWN && event.type == SDL_QUIT){
							return  FALSE;
			}
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
					return  FALSE;
			}
		}
	}
	return TRUE;
}

void update(App *app){

	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - app->last_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
		SDL_Delay(time_to_wait);
	}
	app->delta_time = ((SDL_GetTicks() - app->last_frame_time) / 1000.0f);
	app->last_frame_time = SDL_GetTicks();

	if(app->ball.rect.x + BALL_SIZE_X  >= WINDOW_WIDTH){
		app->ball.rect.x = (WINDOW_WIDTH / 2) - (BALL_SIZE_X / 2);
		app->ball.rect.y = (WINDOW_HEIGHT / 2) - (BALL_SIZE_Y / 2);
		app->ball.momentum_x = 0;
		app->ball.momentum_y = 0;
		app->player1.score++;
		app->ball.count = 0;
		app->ball_color = 255;
	}
	if(app->ball.rect.x <= 0){
		app->ball.rect.x = (WINDOW_WIDTH / 2) - (BALL_SIZE_X / 2);
		app->ball.rect.y = (WINDOW_HEIGHT / 2) - (BALL_SIZE_Y / 2);
		app->ball.momentum_x = 0;
		app->ball.momentum_y = 0;
		app->player2.score++;
		app->ball.count = 0;
		app->ball_color = 255;
	}

	if(app->ball.rect.y + BALL_SIZE_Y  >= WINDOW_HEIGHT){
		app->ball.momentum_y *= -1;
	}

	if(app->ball.rect.y <= 0){
		app->ball.momentum_y *= -1;
	}


	if(detect_collision(&app->player1, &app->ball)){
		app->ball.momentum_x -= 20;
		app->ball.momentum_x *= -1;
		app->ball.rect.x = PLAYER_SIZE_X;
		app->ball.count++;
		app->ball_color -= 20;
		printf("count: %d\n", app->ball.count);
		printf("speed: %d\n", app->ball.momentum_x);
		printf("speed: %d\n", app->ball.momentum_y);
	}
	if(detect_collision(&app->player2, &app->ball)){
		app->ball.momentum_x *= -1;
		app->ball.rect.x = WINDOW_WIDTH - PLAYER_SIZE_X - BALL_SIZE_X;
		app->ball.count++;
		app->ball_color -= 20;
		app->ball.momentum_x -= 20;
		printf("count: %d\n", app->ball.count);
		printf("speed: %d\n", app->ball.momentum_x);
		printf("speed: %d\n", app->ball.momentum_y);
	}

	app->ball.rect.x += app->ball.momentum_x * app->delta_time;
	app->ball.rect.y += app->ball.momentum_y * app->delta_time;


	app->player1.rect.y += app->player1.momentum_y * app->delta_time;
	app->player2.rect.y += app->player2.momentum_y * app->delta_time;

	if(app->player1.rect.y <= 0){
		app->player1.rect.y = 0;
	}
	if(app->player1.rect.y >= (WINDOW_HEIGHT - PLAYER_SIZE_Y)){
		app->player1.rect.y = (WINDOW_HEIGHT - PLAYER_SIZE_Y);
	}
	if(app->player2.rect.y <= 0){
		app->player2.rect.y = 0;
	}
	if(app->player2.rect.y >= (WINDOW_HEIGHT - PLAYER_SIZE_Y)){
		app->player2.rect.y = (WINDOW_HEIGHT - PLAYER_SIZE_Y);
	}
	if(app->ball.momentum_x > WINDOW_WIDTH){
		app->ball.momentum_x = WINDOW_WIDTH;
	}

	if(app->player1.score >= 3){
		app->is_winner = TRUE;
		app->winner_rect.x = SCORE_SIZE;
		app->is_space = 0;
	}
	if(app->player2.score >= 3){
		app->is_winner = TRUE;
		app->winner_rect.x = WINDOW_WIDTH - SCORE_SIZE - WINDOW_WIDTH / 3;
		app->is_space = 0;
	}
	char score1[2] = "";
	char score2[2] = "";
	sprintf(score1, "%d", app->player1.score);
	sprintf(score2, "%d", app->player2.score);
	app->player1.score_surface = TTF_RenderText_Solid(app->bitfont, score1, app->bitfontcolor);
	app->player2.score_surface = TTF_RenderText_Solid(app->bitfont, score2, app->bitfontcolor);
}
void render(App *app){
	SDL_SetRenderDrawColor(app->renderer, 0, 0, 50, 255);
	SDL_RenderClear(app->renderer);
	if(app->ball_color < 0){
		app->ball_color = 0;
	}
	//SDL_SetRenderDrawColor(app->renderer, 255, app->ball_color, app->ball_color, 255);
	SDL_SetRenderDrawColor(app->renderer, 0, 200, 150, 255);

	SDL_RenderFillRect(app->renderer, &app->player1.rect);
	SDL_RenderFillRect(app->renderer, &app->player2.rect);
	//SDL_RenderClear(app->renderer);
	app->player1.score_texture = SDL_CreateTextureFromSurface(app->renderer, app->player1.score_surface);
	app->player2.score_texture = SDL_CreateTextureFromSurface(app->renderer, app->player2.score_surface);

	SDL_RenderCopy(app->renderer, app->player1.score_texture, NULL, &app->player1.score_rect);
	SDL_RenderCopy(app->renderer, app->player2.score_texture, NULL, &app->player2.score_rect);

	//app->ball_color = SDL_MapRGBA(NULL, 0, 255, 0, 255);
	app->ball_surface = SDL_CreateRGBSurface(0, BALL_SIZE_X, BALL_SIZE_Y, 4, 0, 0, 0, 0);
	//SDL_FillRect(app->ball_surface, &app->ball.rect, 100);
	app->ball_texture = SDL_CreateTextureFromSurface(app->renderer, app->ball_surface);
	SDL_RenderCopy(app->renderer, app->ball_texture, NULL, &app->ball.rect);

	if(!app->is_space){
		SDL_RenderCopy(app->renderer, app->start_texture, NULL, &app->start_rect);
	}
	if(app->is_winner){
		SDL_RenderCopy(app->renderer, app->winner_texture, NULL, &app->winner_rect);
	}
	SDL_RenderPresent(app->renderer);

	SDL_FreeSurface(app->player1.score_surface);
	SDL_DestroyTexture(app->player1.score_texture);
	SDL_FreeSurface(app->player2.score_surface);
	SDL_FreeSurface(app->ball_surface);
	SDL_DestroyTexture(app->player2.score_texture);
	SDL_DestroyTexture(app->ball_texture);
	//printf("momentum: %d\n", app->ball.momentum_x);
}

