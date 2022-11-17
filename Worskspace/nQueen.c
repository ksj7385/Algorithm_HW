#pragma warning(disable: 4996)
#include <stdio.h>

int n, cnt = 0;
int temp[16] = { 0, };

void nqueen(int col);

int main(void) {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        temp[0] = i;
        nqueen(1);
    }

    printf("%d\n", cnt);

    return 0;
}

void nqueen(int col) {
    if (col == n) {
        cnt += 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        int check = 1;
        for (int j = 0; j < col; j++) {
            temp[col] = i;
            if (temp[j] == temp[col] || ((j - col) == (temp[j] - temp[col])) || ((j - col) == (temp[col] - temp[j]))) {
                check = 0;
                break;
            }
        }

        if (check) {
            nqueen(col + 1);
        }
    }
}