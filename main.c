#include <stdio.h>

#include "interpreter.h"
#include "compiler.h"

void main(int argc, char** argv) {
	if (argc == 1) {
		int_run();
		return;
	}
}