#ifndef INT_H
#define INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brainheck.h"

char* int_program;
size_t int_ptr = 0;
size_t int_pr_sz = 0;

int int_reset() {
	free(int_program);
	int_program = malloc(sizeof(char));
	int_program[0] = 0;
	int_ptr = 0;
	int_pr_sz = 1;
}
int int_inc_ptr() {
	if (int_ptr + 2 > int_pr_sz) {
		int_pr_sz++;
		int_program = realloc(int_program, int_pr_sz);
		int_program[int_ptr+1] = 0;
	}
	int_ptr++;
}
int int_dec_ptr(char* fn, int index) {
	if (int_ptr == 0) {
		bh_err(index, fn, "Fatal error: attempt to decrease pointer to negative\n");
		exit(-1);
	}
	int_ptr--;
}

int int_proc_char() {
	
}

#define array_resize(arr, unitsize, newsz) arr = realloc(arr, (newsz) * (unitsz)); arr[newsz] = 0;

int int_run() {
	printf("BrainHeck interpreter\n  v. 1.0.0 - made by blek\n  Use \\h to display help menu.\n");
	int_reset();
	while (1) {
		printf("\n> ");
		char in[1024];
		fgets(in, 1024, stdin);
		
		size_t* loops = malloc(sizeof(size_t));
		loops[0] = 0;
		size_t scope = 0;
		size_t loop_sz = 1;
		
		for (size_t i = 0; i != strlen(in); i++) {
			switch (in[i]) {
				case 'q': exit(0);
				case '+':
					int_program[int_ptr]++;
					if (int_program[int_ptr] == 0xFF) {
						bh_err(i, "<stdin>", "Attempt to increase pointer to more than max char value (255).");
					}
					break;
				case '-':
					if (int_program[int_ptr] == 0) {
						bh_err(i, "<stdin>", "Attempt to decrease pointer value to negative");
					} else {
						int_program[int_ptr]--;
					}
					break;
				case '.':
					putchar(int_program[int_ptr]);
					break;
				case ',':
					int_program[int_ptr] = getchar();
					break;
				case '>':
					int_inc_ptr();
					break;
				case '<':
					int_dec_ptr("<stdin>", i);
					break;
				case '[':
					if (loop_sz < scope + 1) {
						loop_sz++;
						loops = realloc(loops, loop_sz * sizeof(size_t));
					}
					scope++;
					loops[scope] = i;
					break;
				case ']':
					if (int_program[int_ptr] == 0){
						scope--;
					} else {
						i = loops[scope]+1;
					}
					break;
			}
		}
	}
}

#endif // INT_H