

game : game.o
	gcc -o game game.o -lm

game_san.o : game.h game.c
	gcc -c game.c -fsanitize=address -static-libasan -g

game_test_san.o : game.h game_test.c 
	gcc -c game_test.c -fsanitize=address -static-libasan -g

game_test_san : game_test_san.o game_san.o
	gcc game_test.o game.o -o game_test -fsanitize=address -static-libasan -g
	./game_test

game.o : game.h game.c
	gcc -c game.c 

game_test.o : game.h game_test.c 
	gcc -c game_test.c 

game_test: game_test.o game.o
	gcc game_test.o game.o -o game_test -lm
	./game_test


clean: 
	rm game.o game_test.o
