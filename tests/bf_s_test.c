#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "../bh_str.h"

int main() {
	srand(time(0));
	tests("Number to string", bh_dtos(123), "123");
	tests("Negative number to string", bh_dtos(-123), "-123");
	tests("Zero number to string", bh_dtos(0), "0");
	int r = (rand() * 52 << 8) ^ 1;
	char numbf[160];
	sprintf(numbf, "%d", r);
	tests("Random number to string", bh_dtos(r), numbf);
	int nr = ((rand() * 52 << 8) ^ 10) * -1;
	char nnumbf[160];
	sprintf(nnumbf, "%d", nr);
	tests("Random negative number to string", bh_dtos(nr), nnumbf);
	
	if (!failedTest) {
		printf("\nAll bh_dtos(..) tests are passed.\n");
	}
}