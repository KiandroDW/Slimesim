all:
	gcc src/*.c src/configs/config1.c -I include/ -lraylib -lm

run: all
	./a.out

debug:
	gcc -g src/*.c src/configs/config1.c -I include/ -lraylib -lm

.PHONEY: all run debug
