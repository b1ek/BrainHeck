#ifndef INT_LEX_H
#define INT_LEX_H

#include <stdlib.h>
#include "int_prog.h"

int int_parse_src(struct int_prog* this) {
	for (; this->src_ptr-1 != this->src_sz; this->src_ptr++) {
		switch (this->src[this->src_ptr]) {
			case '+': {
				if (this->memory[this->ptr] == 0xff) {
					int_err(this, "Can\'t increase pointer: max value reached.");exit(0);
					break;
				}
				this->memory[this->ptr]++;
				break;
			}
			case '-': {
				if (this->memory[this->ptr] == 0) {
					int_err(this, "Can\'t increase pointer: min value reached.");
					break;
				}
				this->memory[this->ptr]++;
				break;
			}
			case '>': {
				int_inc_ptr(this);
				break;
			}
			case '<': {
				int_dec_ptr(this);
				break;
			}
			case '[': {
				if (this->scope + 2 > this->loops_sz) {
					this->loops_sz++;
					this->loops = realloc(this->loops, this->loops_sz * sizeof(int));
				}
				this->scope++;
				this->loops[this->scope] = this->src_ptr;
				break;
			}
			case ']': {
				if (this->scope == 0) {
					int_err(this, "Unmatched \"[\"");
					int_prog_rst(this);
					return 0;
				}
				if (this->memory[this->ptr] == 0) {
					this->scope--;
				} else this->src_ptr = this->loops[this->scope];
			}
			case '.': {
				putchar(this->memory[this->ptr]);
				break;
			}
			case ',': {
				this->memory[this->ptr] = getchar();
				break;
			}
			case '\\': {
				exit(0);
				break;
			}
		}
	}
}

#endif//INT_LEX_H