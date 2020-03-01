all: battleship

battleship: battleship.c
	gcc battleship.c -o battleship -lncurses
clean: battleship
	rm battleship
run : battleship
	./battleship
run-def-args: battleship player_map1 player_map2 player_map3
	./battleship player_map1 player_map2 player_map3


