#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 

int main() {
    int n;
    scanf("%d", &n);


    int stock[101] = { 0 };
    int input_qty[101] = { 0 };
    int sales_qty[101] = { 0 };
    int i;

    for (i = 1; i <= n; i++) {
        scanf("%d", &input_qty[i]);
    }

    for (i = 1; i <= n; i++) {
        scanf("%d", &sales_qty[i]);
    }

    for (i = 1; i <= n; i++) {
        stock[i] = input_qty[i] - sales_qty[i];
    }

    printf("재고수량 : ");
    for (i = 1; i <= n; i++) {
        printf("%d", stock[i]);
        if (i < n)printf(" ");
    }
    printf("\n");

    int total_sales = 0, total_input = 0;
    for (i = 1; i <= n; i++) {
        total_sales += sales_qty[i];
        total_input += input_qty[i];
    }
    double sales_rate = (total_input > 0) ? (total_sales * 100.0 / total_input) : 0;
    printf("총 판매량 : %d (판매율 %.2f%%)\n", total_sales, sales_rate);

    int max_sales = sales_qty[1], min_sales = sales_qty[1];
    int max_id = 1, min_id = 1;

    for (i = 2; i <= n; i++) {
        if (sales_qty[i] > max_sales) {
            max_sales = sales_qty[i];
            max_id = i;
        }
        if (sales_qty[i] < min_sales) {
            min_sales = sales_qty[i];
            min_id = i;
        }
    }

    printf("가장 많이 판매된 상품 : ID %d, 판매량 %d\n", max_id, max_sales);
    printf("가장 적게 판매된 상품 : ID %d, 판매량 %d\n", min_id, min_sales);

    for (i = 1; i <= n; i++) {
        if (stock[i] <= 2) {
            printf("상품 ID %d : 재고부족(%d)\n", i, stock[i]);
        }
    }

    return 0;

}