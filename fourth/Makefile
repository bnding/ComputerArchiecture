all: test

test: fourth.c
	gcc -Wall -Werror -fsanitize=address -std=c99  fourth.c -o fourth.out

clean: rm -rf fourth
