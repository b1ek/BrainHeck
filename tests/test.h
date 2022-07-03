#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

int failedTest = 0;

int tests(const char* nm, const char* res, const char* exp) {
	printf("\n------\nTest \"%s\" [%s]\nGot value: %s\nExpected: %s\n", nm, strcmp(res, exp) == 0 ? "Passed" : "Failed", res, exp);
	if (strcmp(res, exp) != 0) failedTest = 1;
}
int testn(const char* nm, int res, int exp) {
	printf("\n------\nTest \"%s\" [%s]\nGot value: %d\nExpected: %d\n", nm, res == exp ? "Passed" : "Failed", res, exp);
	if (res != exp) failedTest = 1;
}

#endif//TEST_H