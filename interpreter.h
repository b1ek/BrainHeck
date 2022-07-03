#ifndef INT_H
#define INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brainheck.h"

unsigned char* int_program;
size_t int_ptr = 0;
size_t int_pr_sz = 0;

char* int_user_input;
size_t int_program_index = 0;

int int_reset() {
	free(int_program);
	int_program = malloc(sizeof(char));
	int_program[0] = 0;
	int_ptr = 0;
	int_pr_sz = 1;
	
	free(int_user_input);
	int_program_index = 0;
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

int int_print_help() {
	printf(
"\n"
"---\n"
"BrainHeck commands\n"
"\\h   - Display help about functions (should be used in the interpreter only)\n"
"\\d   - Print the current pointer value as decimal number\n"
"\\n   - Print the current pointer position\n"
"\\q   - Exit the program\n"
"\\\\   - No-op, if you want to use \\ symbol in comments about code so desperately\n"
"\\s() - Run some system command, like \\s(clear) will clear the screen\n"
"\\p() - Print message, like \\p(Hello world) is a basic hello world in brainHeck\n"
"\\q() - Exit program with exit code, like \\q(60) will exit the program with exit code 60.\n"
"\\j() - Jump to pointer value, like \\j(2) will jump to pointer at index 2 (3rd position in array)\n"
"\\f() - Write the pointer value to file in append mode.\n"
"\\a() - Delete file\n"
"\\s() - Jump to char at index\n"
"\\i() - Include contents of another file\n"
"---\n"
);
}

// this function gets the contents of the brackets
char* int_cmd_brackets(char* pr, size_t open_bracket) {
	char* buffer = malloc(sizeof(char));
	open_bracket++;
	buffer[0] = pr[open_bracket];
	
	size_t buffer_sz = sizeof(char);
	
	for (size_t i = open_bracket+1;; i++) {
		if (pr[i] != ')') {
			buffer_sz++;
			buffer = realloc(buffer, buffer_sz*sizeof(char));
			buffer[buffer_sz-1] = pr[i];
		} else break;
		if (i == strlen(pr) + 1) {
			bh_err(open_bracket, "?", "Unmatched bracket \"(\"");
			exit(0);
		}
	}
	buffer_sz++;
	buffer = realloc(buffer, buffer_sz*sizeof(char));
	buffer[buffer_sz-1] = '\0';
	return buffer;
}

int int_proc_cmd(char* pr, size_t index) {
	if (pr[index-1] == '\\') return;
	index++;
	switch(pr[index]) {
		case 'd':
			printf("%d", int_program[int_ptr]);
			break;
		case 'q':
			if (pr[index+1] == '(') {
				int exitCode = 0;
				int offset = 1;
				if (pr[index+2] == '-') offset=2;				
				
				for (size_t i = index+offset; pr[i] != ')'; i++) {
					if (pr[i] >= 48 && pr[i] <= 57) {
						exitCode = (exitCode * 10) + (pr[i] - 48);
					}
					if (i == strlen(pr)) {
						printf("\nError: unmatched \"(\" at index %d\n", index);
						exit(-1);
					}
				}
				if (offset == 2) exitCode *= -1;
				exit(exitCode);
			}
			printf("Bye\n");
			exit(0);
			break;
		case 'h':
			int_print_help();
			break;
		case 'n':
			printf("%d", int_ptr);
			break;
		case 'p': {
			;char* args = int_cmd_brackets(pr, index+1);
			printf(args);
			break;
		}
		case 's': {
			;char* args = int_cmd_brackets(pr, index+1);
			system(args);
			break;
		}
		case '\\': break;
		default:
			printf("Unknown BrainHeck \\%c command.", pr[index]);
			break;
	}
}

#define array_resize(arr, unitsize, newsz) arr = realloc(arr, (newsz) * (unitsz)); arr[newsz] = 0;

int int_run() {
	printf("BrainHeck interpreter\n  v. 1.0.0 - made by blek\n  Use \\h to display help menu.\n");
	int_reset();
	while (1) {
		printf("\n> ");
		char in[1024];
		fgets(in, 1024, stdin);
		int_user_input = in;
		int_program_index = 0;
		
		size_t* loops = malloc(sizeof(size_t));
		loops[0] = 0;
		size_t scope = 0;
		size_t loop_sz = 1;
		
		for (size_t i = 0; i != strlen(in); i++) {
			int_program_index = i;
			switch (in[i]) {
				case '+':
					if (int_program[int_ptr] == 0xFF) {
						bh_err(i, "<stdin>", "Attempt to increase pointer to more than max char value (255).");
					} else {
						int_program[int_ptr]++;
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
						i = loops[scope];
					}
					break;
				case '\\':
					int_proc_cmd(in, i);
			}
		}
	}
}

#endif // INT_H