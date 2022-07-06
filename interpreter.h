#ifndef INT_H
#define INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

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
"\\j() - Jump to char at index\n"
"\\i() - Include contents of another file\n"
"---\n"
);
}

// this function gets the contents of the brackets
// pr - the whole program
// open_bracket - 1st argument char, NOT OPENING BRACKET
char* int_cmd_brackets(char* pr, size_t open_bracket) {
	char* buffer = malloc(sizeof(char));
	open_bracket++;
	if (pr[open_bracket] == ')') return "";
	buffer[0] = pr[open_bracket];
	
	size_t buffer_sz = sizeof(char);
	
	for (size_t int_program_index = open_bracket+1;; int_program_index++) {
		if (pr[int_program_index] != ')') {
			buffer_sz++;
			buffer = realloc(buffer, buffer_sz*sizeof(char));
			buffer[buffer_sz-1] = pr[int_program_index];
		} else break;
		if (int_program_index == strlen(pr) + 1) {
			bh_err(open_bracket, "?", "Unmatched bracket \"(\"");
			exit(0);
		}
	}
	buffer_sz++;
	buffer = realloc(buffer, buffer_sz*sizeof(char));
	buffer[buffer_sz-1] = '\0';
	return buffer;
}

int int_get_close_bracket(char* pr, size_t i) {
	for (; pr[i] != ')'; i++);
	return i;
}

int str_is_int(char* in) {
	size_t i = 0;
	if (in[0] == '-') i++;
	for (; in[i] != '\0'; i++) {
		if (!(in[i] >= 48 && in[i] <= 57)) {
			return 0;
		}
	}
	return 1;
}

int int_proc_string(char* input, char* __filename);

int int_proc_cmd(char* pr, size_t index) {
	if (pr[index-1] == '\\') return 0;
	index++;
	switch(pr[index]) {
		case 'd':
			printf("%d", int_program[int_ptr]);
			break;
		case 'q':
			if (pr[index+1] == '(') {
				char* args = int_cmd_brackets(pr, index+1);
				
				if (!str_is_int(args)) {bh_err(index, "?", "Invalid argument format at \\q(...)");exit(-1);}
				exit(bh_stod(args));
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
			if (pr[index + 1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			char* args = int_cmd_brackets(pr, index+1);
			printf(args);
			
			return int_get_close_bracket(pr, index+1);
		}
		case 's': {
			if (pr[index + 1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			char* args = int_cmd_brackets(pr, index+1);
			system(args);
			return int_get_close_bracket(pr, index+1);
		}
		case 'j': {
			if (pr[index + 1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			char* args = int_cmd_brackets(pr, index+1);
			if (!str_is_int(args)) {
				bh_err(index, "?", "Invalid arguments format: put a number of pointer to which jump to");
				exit(-1);
			}
			if (int_pr_sz-1 >= bh_stod(args)) {
				int_ptr = bh_stod(args);
			} else {
				printf("Warning: jumping to non-allocated pointer at index %d", index);
			}
			return int_get_close_bracket(pr, index+1);			
		}
		
		case 'f':
			if (pr[index + 1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			char* args = int_cmd_brackets(pr, index+1);
			FILE* fp = fopen(args, "a");
			if (fp == 0) {
				bh_err(index, "?", "Cannot open file!");
			}
			fputc(int_program[int_ptr], fp);
			fclose(fp);
			return int_get_close_bracket(pr, index+1);
		case 'a':
			if (pr[index+1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			remove(int_cmd_brackets(pr, index + 1));
			return int_get_close_bracket(pr, index + 1);
		case 'l': {
			if (pr[index+1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			char* args = int_cmd_brackets(pr, index + 1);
			if (!str_is_int(args)) {
				bh_err(index, "?", "Invalid arguments format: put a number");
				exit(-1);
			}
			return bh_stod(args) - 1;
		}
		case 'i': {
			if (pr[index + 1] != '(') {
				bh_err(index, "?", "This function requires arguments");
				exit(-1);
			}
			char* args = int_cmd_brackets(pr, index + 1);
			
			FILE* file = fopen(args, "r");
			if (file) {
				
				signed char c = 0;
				char* buffer = malloc(0);
				size_t buffer_sz = 0;
				while ((c = fgetc(file)) != EOF) {
					buffer_sz++;
					buffer = realloc(buffer, buffer_sz);
					buffer[buffer_sz - 1] = c;
				}
				int_proc_string(buffer, args);
				
				fclose(file);
			}
			
			return int_get_close_bracket(pr, index + 1);
		}
		
		case '\\': break;
		case '\n':
			bh_err(index, "?", "No command.");
			break;
		case '\r':
			bh_err(index, "?", "No command.");
			break;
		case '\0':
			bh_err(index, "?", "No command.");
			break;
		default:
			printf("Unknown BrainHeck \\%c command.", pr[index]);
			if (pr[index + 1] == '(') {
				return int_get_close_bracket(pr, index + 1);
			}
			break;
	}
	return 0;
}

#define array_resize(arr, unitsize, newsz) arr = realloc(arr, (newsz) * (unitsz)); arr[newsz] = 0;

int int_proc_string(char* input, char* __filename) {	
	size_t* loops = malloc(sizeof(size_t));
	loops[0] = 0;
	size_t scope = 0;
	size_t loop_sz = 1;
	int ptr = 0;
	
	for (size_t i = 0; i != strlen(input); i++) {
		switch (input[i]) {
			case '+':
				if (input[ptr] == 0xFF) {
					bh_err(i, __filename, "Attempt to increase pointer to more than max char value (255).");
				} else {
					input[ptr]++;
				}
				break;
			case '-':
				if (input[ptr] == 0) {
					bh_err(i, __filename, "Attempt to decrease pointer value to negative");
				} else {
					input[ptr]--;
				}
				break;
			case '.':
				putchar(input[ptr]);
				break;
			case ',':
				input[ptr] = getchar();
				break;
			case '>':
				int_inc_ptr();
				break;
			case '<':
				int_dec_ptr(__filename, i);
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
				if (input[ptr] == 0){
					scope--;
				} else {
					i = loops[scope];
				}
				break;
			case '\\':;
				int newIndex = int_proc_cmd(input, i);
				if (newIndex != 0) {
					i = newIndex;
				}
				break;
		}
	}
}

int int_run() {
	printf("BrainHeck interpreter\n  v. 1.0.0 - made by blek\n  Use \\h to display help menu.\n");
	int_reset();
	while (1) {
		printf("\n> ");
		char in[1024];
		fgets(in, 1024, stdin);
		int_proc_string(in, "<stdin>");
	}
}

#endif // INT_H