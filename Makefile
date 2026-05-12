jogo: parser.o utils.o game/src/main.c
	gcc -Wall -g $^ -o $@ -lncursesw

mac: parser.o utils.o game/src/main.c
	gcc -Wall -g $^ -o jogo -lncurses

parser.o: game/dsl/parser.c
	gcc -Wall -g $^ -c -o $@ 

utils.o: game/src/utils.c
	gcc -Wall -g $^ -c -o $@ 

gamestate.o: game/src/gamestate.c
	gcc -Wall -g $^ -c -o $@

clean:
	-rm -f parser.o utils.o jogo