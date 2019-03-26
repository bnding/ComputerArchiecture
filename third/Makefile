all: third fourth

third: third.c
	gcc -Wall -Werror -fsanitize=address third.c -o third

fourth: third-2.c
	gcc -Wall -Werror -fsanitize=address third-2.c -o third-2

clean: 
	-rm -rf third third-2
