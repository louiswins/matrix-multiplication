#include <stdio.h>
#include <stdlib.h>

int p[] = {40, 20, 50, 25, 15}; /* sizes of matrices */



#define NMAT (sizeof p / sizeof p[0] - 1)
int m[NMAT+1][NMAT+1] = {{0}}; /* number of multiplications needed */
int s[NMAT+1][NMAT+1] = {{0}}; /* best split location */

void print_expr(int l, int r) {
	int split = s[l][r];
	if (split == 0) {
		printf("A%d", l);
		return;
	}
	/* We don't want parenthesis around the WHOLE expression */
	if (l != 1 || r != NMAT) putchar('(');
	print_expr(l, split);
	putchar('*');
	print_expr(split+1, r);
	if (l != 1 || r != NMAT) {
		putchar(')');
	} else {
		putchar('\n');
	}
}

void fill_matrices() {
	int len, i, j, k;
	for (len = 2; len <= NMAT; ++len) {
		for (i = 1; i <= NMAT - len + 1; ++i) {
			j = i + len - 1;
			m[i][j] = m[i][i] + m[i+1][j] + p[i-1]*p[i]*p[j];
			s[i][j] = i;
			for (k = i+1; k <= j-1; ++k) {
				int cur = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (cur < m[i][j]) {
					m[i][j] = cur;
					s[i][j] = k;
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int i, j;
	fill_matrices();
	for (j = NMAT; j >= 1; --j) {
		for (i = 1; i <= j; ++i) {
			printf("%5d ", m[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
	for (j = NMAT; j >= 2; --j) {
		for (i = 1; i <= j-1; ++i) {
			printf("%d ", s[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');

	print_expr(1, NMAT);

	return 0;
}
