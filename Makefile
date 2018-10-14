build:
	gcc -Wall -g main.c -o tema2
run: tema2
	./tema2 input output
clean:
	rm -rf tema2
val: tema2
	valgrind --leak-check=full ./tema2 input output
