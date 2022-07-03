#ifndef BRAINH_H
#define BRAINH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bh_str.h"

int bh_error = 0;

int bh_err(size_t index, char* fn, char* msg) {
	printf("\nError on index %llu in file %s: %s", index+1, fn, msg);
	bh_error = 1;
}
int bh_reset_err() {
	bh_error = 0;
}
int bh_reset_all() {
	bh_reset_err();
}

#endif //BRAINH_H