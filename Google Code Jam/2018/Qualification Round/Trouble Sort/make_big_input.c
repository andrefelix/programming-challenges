#include <stdio.h>

int main() {
	int i = 100000;
	int j = 1;

	while (j <= i) {
		if (j != i)
			printf("%d ", j);
		else
			printf("%d\n", j);

		j += 1;
	}

	return 0;
}
