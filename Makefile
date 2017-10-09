test: project.c test_program.c
	gcc -o $@ $^ -Wall -Wextra
