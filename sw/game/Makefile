

game : game.o
	gcc -o game game.o

game.o : game.h game.c
	gcc -c game.c
	
game_test : game_test.o game.o
	gcc -o game_test game_test.o game.o

game_test.o : game.h game_test.c 
	gcc -c game_test.c 
