#ifndef BH_STR_H
#define BH_STR_H

#include <stdlib.h>
#include <string.h>

#ifndef strrev
// Some compilers dont support strrev()
char* strrev(char *str) {
	char *p1;
	char *p2;

	if (! str || ! *str) return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}
#endif //strrev

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

int bh_stod(char* in) {
	int out = 0;
	
	for (size_t i = 0; in[i] != '\0'; i++) {
		if (in[i] >= 48 && in[i] <= 57) {
			out *= 10;
			out += in[i] - 48;
		}
	}
	if (in[0] == '-') return -out;
	return out;
}

const char* bh_str_replace(const char* source, const char* search, const char* replace) {
	
}

#endif//BH_STR_H