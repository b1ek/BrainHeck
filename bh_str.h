#ifndef BH_STR_H
#define BH_STR_H

#include <stdlib.h>

size_t bh_strlen(char* s) {
	int i = 0;
	for (; s[i] == '\0'; i++) {}
	return i;
}

const char* bh_dtos(int d) {
	// calculate size
	size_t buffer_sz = 2;
	int dt = d;
	if (d < 0) {
		buffer_sz++;
		dt *= -1;
	}
	while (dt > 10) {
		buffer_sz++;
		dt /= 10;
	}
	
	// make buffer
	char* buffer = malloc(buffer_sz * sizeof(char));
	
	// fill the buffer
	size_t stop = buffer_sz-1;
	if (d < 0) {
		stop--;
		buffer[stop] = '-';
		d *= -1;
	}
	for (size_t i = 0; i != stop; i++) {
		buffer[i] = (d % 10) + 48;
		d /= 10;
	}
	buffer[buffer_sz-1] = '\0';
	
	return strrev(buffer); // the string has to be reversed
}

#endif//BH_STR_H