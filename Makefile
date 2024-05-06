lexer:
	gcc -o lexer lexer.c -Wall -Wextra -pedantic

array:
	gcc -o array array.c -Wall -Wextra -pedantic

asan:
	gcc -g -fsanitize=address -o array array.c
	
