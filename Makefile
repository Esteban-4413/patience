jogo: parser.o utils.o gamestate.o card.o game.o undo.o display.o input.o game/src/main.c
	gcc -Wall -g $^ -o $@ -lncursesw

mac: parser.o utils.o gamestate.o card.o game.o undo.o display.o input.o game/src/main.c
	gcc -Wall -g $^ -o jogo -lncurses

parser.o: game/dsl/parser.c
	gcc -Wall -g $^ -c -o $@ 

utils.o: game/src/utils.c
	gcc -Wall -g $^ -c -o $@ 

gamestate.o: game/src/gamestate.c
	gcc -Wall -g $^ -c -o $@

card.o: game/src/card.c
	gcc -Wall -g $^ -c -o $@

game.o: game/src/game.c
	gcc -Wall -g $^ -c -o $@

undo.o: game/src/undo.c
	gcc -Wall -g $^ -c -o $@

display.o: game/ui/display.c
	gcc -Wall -g $^ -c -o $@

input.o: game/ui/input.c
	gcc -Wall -g $^ -c -o $@

clean:
	-rm -f parser.o utils.o gamestate.o card.o game.o undo.o display.o input.o jogo