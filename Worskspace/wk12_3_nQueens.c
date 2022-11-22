#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>

#define MAX_N 30

/* global variables */
int board[MAX_N] = { 0, }; //index: column of queen, value: row of queen
int cnt = 0; //of solution
int n;

/* function prototypes */
int is_promising(int level); //check if the position is ok
void n_queens(int level); //backtracking solution of n-queens
void print_board(); //print current board (бс-queen, бр-empty)

/* main function */
int main(void) {
	//read input
	printf("Enter the value of n: ");
	scanf("%d", &n);
	//backtracking
	n_queens(0);
	//print result
	printf("Total count of solutions: %d\n", cnt);
	return 0;
}


//backtracking solution of n-queens
void n_queens(int level) {
	//base condition
	if (level == n) { //if found a solution
		print_board(); //print the solution
		cnt++;
		return;
	}
	//recursive step
	for (int i = 0; i < n; i++) {
		board[level] = i; //place queen at ithcolumn
		if (is_promising(level)) { //check if it's promising
			n_queens(level + 1); //check next row
		}
	}
}

//check if the position is ok
int is_promising(int level) {
	//vertically, diagonally check
	for (int i = 0; i < level; i++) {
		if (board[level] == board[i] || abs(level - i) == abs(board[level] - board[i])) return 0;
	} return 1;
}
//print current board
void print_board() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i] == j) printf("бс"); //queen
			else printf("бр"); //empty cell
		} printf("\n");
	} printf("\n");
}

