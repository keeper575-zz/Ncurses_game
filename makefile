game: game.c
	gcc -o game game.c -lncurses
clean:
	rm game
