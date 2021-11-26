#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 6386)
#pragma warning(disable: 6385)

int check_con(int** arr, int edge, int knot, int n, int* check_arr) {
	int con = 1;
	for (int i = 0; i < edge; i++)
		if (arr[n][i] != 0) {
			check_arr[n] = 1;
			for (int j = 0; j < knot; j++) {
				if(arr[j][i] != 0 && check_arr[j] != 1)
					con += check_con(arr, edge, knot, j, check_arr);
			}
		}
			
	return con;
}

void make_file(int** arr, int knot, int edge) {
	int n = 0, check = 0;

	FILE* f = fopen("graph.txt", "w");
	fputs("graph G{\n", f);
	for (int i = 0; i < knot; i++)
		fprintf(f, "\t%d\n", i + 1);
	for (int i = 0; i < edge; i++) {
		for (int j = 0; j < knot; j++) {
			if (arr[j][i] == 1 && check == 0) {
				fprintf(f, "\t%d--", j + 1);
				check++;
				n = j + 1;
			}
			else if (arr[j][i] == 1 && check == 1) {
				fprintf(f, "%d\n", j + 1);
				check++;
			}
		}
		if (check == 1)
			fprintf(f, "%d\n", n);
		check = 0;
	}
	fprintf(f, "}");
	fclose(f);
}

int main(void) {
	char word = 'a';
	int knot, edge, con = 0;
	int** arr = NULL;

	printf("Number of your knots: ");
	if (scanf("%d", &knot) != 1)
		exit(1);
	printf("Number of your edges: ");
	if (scanf("%d", &edge) != 1)
		exit(1);

	arr = (int**)malloc(knot * sizeof(int*));
	if (arr == NULL)
		exit(1);
	for (int i = 0; i < knot; i++)
		arr[i] = (int*)malloc(edge * sizeof(int));

	printf("Complete array:\n  |");
	for (int i = 0; i < edge; i++)
		printf("%c ", word++);
	printf("\n");
	for (int i = 0; i < knot; i++) {
		printf(" %d|", i + 1);
		if (arr[i] == NULL)
			exit(1);
		for (int j = 0; j < edge; j++)
			if (scanf("%d", &arr[i][j]) != 1)
				exit(1);
	}

	make_file(arr, knot, edge);
	int* check_arr = (int*)malloc(knot * sizeof(int));
	if (check_arr == NULL)
		exit(1);
	con = check_con(arr, edge, knot, 0, check_arr);
	if (con == knot)
		printf("Graph is connected\n");
	else printf("Graph is not connected\n");

	for (int i = 0; i < knot; i++)
		free(arr[i]);
	free(arr);
	return 0;
}