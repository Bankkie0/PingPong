#include "common.h"

int main(int argc, char *argv[]){

	App app;

	int game_is_running = initialize_window(&app);

	setup(&app);

	while(game_is_running){
		game_is_running = process_input(&app);
		update(&app);
		render(&app);
	}

	destroy_window(&app);
	return 0;
}
