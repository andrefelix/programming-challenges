#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 15

void initialize_matrix(int matrix[MAX][MAX], int rows, int cols);

int main() {
	int T, A;
	int matrix[MAX][MAX];

	scanf("%d", &T);

	while (T--) {
		scanf("%d", &A);

		int rows = (int) sqrt(A);
		int cols = rows;

		while ((rows * cols) < A)
			cols += 1;

		initialize_matrix(matrix, rows, cols);

		// begin setup
		int i_in;
		int j_in;
		int i_out = 1;
		int j_out = 1;
		int sub_row = rows - 1;
		int sub_col = cols - 1;
		int offset = 1;

		while (1) {
			printf("%d %d\n", i_out + offset, j_out + offset);
			fflush(stdout);
			scanf("%d %d", &i_in, &j_in);

			if (i_in == 0)
				break;
			else if (i_in == -1)
				exit(EXIT_SUCCESS);

			matrix[i_in - offset][j_in - offset] = 1;

			if (i_out < sub_row - 1) {
				if (j_out < sub_col - 1) {
					// verifica: diagonal superior esquerda
					if (matrix[i_out - 1][j_out - 1] == 1)
						j_out += 1;
				}
				else {
					// j_out == sub_col
					// verifica: os 3 superiores
					if (matrix[i_out - 1][j_out - 1] == 1 &&
						matrix[i_out - 1][j_out + 1] == 1 &&
						matrix[i_out - 1][j_out])
					{
						j_out = 1;
						i_out += 1;
					}
				}
			}
			else {
				//i_out == sub_row
				if (j_out < sub_col - 1) {
					// verifica: os 3 do lado esquerdo
					if (matrix[i_out - 1][j_out - 1] == 1 &&
						matrix[i_out][j_out - 1] == 1 &&
						matrix[i_out + 1][j_out - 1] == 1)
					{
						j_out += 1;
					}
				}
				// else j_out == sub_col and i_out == sub_row
				// try this position until receive 0 0
			}
		}
	}

	return 0;
}

void initialize_matrix(int matrix[MAX][MAX], int rows, int cols) {
	int i, j;

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			matrix[i][j] = 0;

	return;
}