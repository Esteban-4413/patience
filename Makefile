jogo: parser.o utils.o gamestate.o card.o game.o move.o undo.o display.o input.o loader.o saveload.o game/src/main.c
	gcc -Wall -g $^ -o $@ -lncursesw

mac: parser.o utils.o gamestate.o card.o game.o move.o undo.o display.o input.o loader.o saveload.o game/src/main.c
	gcc -Wall -g $^ -o jogo -lncurses

parser.o: game/dsl/parser.c
	gcc -Wall -g $^ -c -o $@ 

utils.o: game/src/utils.c
	gcc -Wall -g $^ -c -o $@ 

gamestate.o: game/src/gamestate.c
	gcc -Wall -g $^ -c -o $@

loader.o: game/dsl/loader.c
	gcc -Wall -g $^ -c -o $@

card.o: game/src/card.c
	gcc -Wall -g $^ -c -o $@

game.o: game/src/game.c
	gcc -Wall -g $^ -c -o $@

move.o: game/src/move.c
	gcc -Wall -g $^ -c -o $@

undo.o: game/src/undo.c
	gcc -Wall -g $^ -c -o $@

display.o: game/ui/display.c
	gcc -Wall -g $^ -c -o $@

input.o: game/ui/input.c
	gcc -Wall -g $^ -c -o $@

saveload.o: game/src/saveload.c
	gcc -Wall -g $^ -c -o $@


# TESTES  

TEST_FILES = tests/test_main.c tests/test_cards.c tests/test_game.c tests/test_undo.c 

testes: card.o game.o move.o undo.o utils.o display.o input.o gamestate.o saveload.o loader.o parser.o $(TEST_FILES)
	gcc -Wall -g $^ -o test_jogo -lncurses -I/opt/homebrew/include -L/opt/homebrew/lib -lcunit
	./test_jogo

clean:
	-rm -f parser.o utils.o gamestate.o card.o game.o move.o undo.o display.o input.o loader.o saveload.o test_jogo jogo save.txt
