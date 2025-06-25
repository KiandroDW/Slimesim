all:
	gcc src/*.c -I include/ -lraylib -lm

run: all
	./a.out

debug:
	gcc -g src/*.c -I include/ -lraylib -lm

.PHONEY: all run debug
