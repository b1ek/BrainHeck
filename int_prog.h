#ifndef INT_PROG_H
#define INT_PROG_H

#include <stdlib.h>

struct int_prog {
	unsigned char* memory;
	size_t ptr;
	size_t mem_sz;
	
	char* src;
	size_t src_sz;
	size_t src_ptr;
	
	char* filename;
	
	int* loops;
	size_t loops_sz;
	size_t scope;
};

void int_err(struct int_prog* this, char* err) {
	
}
void int_wrn(struct int_prog* this, char* msg) {
	
}

struct int_prog* int_prog_create() {
	struct int_prog* this = malloc(sizeof(struct int_prog));

	this->memory = malloc(sizeof(unsigned char));
	if (this->memory == NULL) {
		printf("Can\'t allocate memory for program.\n");
		exit(-1);
	}
	this->memory[0] = 0;
	this->ptr = 0;
	this->mem_sz = 1;
	
	this->src = malloc(0);
	this->src_sz  = -1;
	this->src_ptr = -1;
	
	this->filename = malloc(0);
	
	this->loops = malloc(sizeof(size_t));
	if (this->loops == NULL) {
		printf("Can\'t allocate memory for program.\n");
		exit(-1);
	}
	this->loops[0] = 0;
	this->loops_sz = 1;
	this->scope = 0;
}
void int_cmd(struct int_prog* this) {
	
}

void int_prog_rst(struct int_prog* this) {
	//free(this->memory);
	this->memory = malloc(sizeof(unsigned char));
	if (this->memory == NULL) {
		printf("Can\'t allocate memory for program.\n");
		exit(-1);
	}
	this->memory[0] = 0;
	this->ptr = 0;
	this->mem_sz = 1;
	
	//free(this->src);
	this->src = malloc(0);
	this->src_sz  = 0;
	this->src_ptr = 0;
	
	//free(this->filename);
	this->filename = malloc(sizeof(char));
	this->filename[0] = '\0';
	
	this->loops = malloc(sizeof(int));
	if (this->loops == NULL) {
		printf("Can\'t allocate memory for program.\n");
		exit(-1);
	}
	this->loops[0] = 0;
	this->loops_sz = 1;
	this->scope = 0;
}

void int_inc_ptr(struct int_prog* this) {
	if (this->ptr == 0x7FFFFFFF) {
		int_wrn(this, "Its not recommended to increase your pointer that much (more than 2147483647).");
	}
	if (this->ptr + 2 > this->mem_sz) {
		this->mem_sz++;
		this->memory = realloc(this->memory, this->mem_sz);
	}
	this->ptr++;
}
void int_dec_ptr(struct int_prog* this) {
	if (this->ptr == 0) {
		int_err(this, "Attempt to decrese pointer to negative value");
		int_prog_rst(this);
		return;
	}
	this->ptr--;
}

#endif//INT_PROG_H