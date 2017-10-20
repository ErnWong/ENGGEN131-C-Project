test: test_program.c project.c
	gcc -o $@ $^ -Wall -Wextra
