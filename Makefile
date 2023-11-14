build:
	gcc ./*.c -o ./pong `sdl2-config --cflags --libs` -Werror -lSDL2_ttf
run:
	./pong
clean:
	rm ./pong
