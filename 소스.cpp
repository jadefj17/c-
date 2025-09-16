#include <stdio.h>

#define PRODUCT_COUNT 5

int stock[PRODUCT_COUNT] = { 0 };
int sold[PRODUCT_COUNT] = { 0 };

// 안전한 입력 처리 함수
int safeScanInt(const char* msg, int* var) {
    printf("%s", msg);
    if (scanf("%d", var) != 1) {
        printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
        while (getchar() != '\n'); // 버퍼 비우기
        return 0; // 실패
    }
    return 1; // 성공
}

// 메뉴 출력 함수
void printMenu() {
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("원하는 메뉴를 선택하세요.\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 상품현황\n");
    printf("4. 종료\n");
    printf(">> ");
}

// 입고 함수
void inputStock() {
    int choice;
    if (!safeScanInt("\n(출력)입고수량 입력 : 전체 상품 입력 1, 개별 상품 입력 2를 선택\n>> ", &choice))
        return;

    if (choice == 1) {
        int qty;
        if (!safeScanInt("(입력) 전체 상품 입고수량 입력 : ", &qty))
            return;
        for (int i = 0; i < PRODUCT_COUNT; i++) {
            stock[i] += qty;
        }
    }
    else if (choice == 2) {
        int id, qty;
        if (!safeScanInt("상품 ID (0~4) 입력 : ", &id))
            return;
        if (id >= 0 && id < PRODUCT_COUNT) {
            if (!safeScanInt("입고수량 입력 : ", &qty))
                return;
            stock[id] += qty;
        }
        else {
            printf("잘못된 상품 ID입니다.\n");
        }
    }
    else {
        printf("잘못된 선택입니다.\n");
    }
}

// 판매 함수
void sellProduct() {
    int choice;
    if (!safeScanInt("\n(출력)판매수량 입력 : 전체 상품 입력 1, 개별 상품 입력 2를 선택\n>> ", &choice))
        return;

    if (choice == 1) {
        int qty;
        if (!safeScanInt("전체 상품 판매수량 입력 : ", &qty))
            return;
        for (int i = 0; i < PRODUCT_COUNT; i++) {
            if (stock[i] >= qty) {
                stock[i] -= qty;
                sold[i] += qty;
            }
            else {
                printf("상품 %d: 재고 부족으로 판매 불가\n", i);
            }
        }
    }
    else if (choice == 2) {
        int id, qty;
        if (!safeScanInt("상품 ID (0~4) 입력 : ", &id))
            return;
        if (id >= 0 && id < PRODUCT_COUNT) {
            if (!safeScanInt("판매수량 입력 : ", &qty))
                return;
            if (stock[id] >= qty) {
                stock[id] -= qty;
                sold[id] += qty;
            }
            else {
                printf("재고 부족으로 판매 불가\n");
            }
        }
        else {
            printf("잘못된 상품 ID입니다.\n");
        }
    }
    else {
        printf("잘못된 선택입니다.\n");
    }
}

// 상품 현황 출력
void showStatus() {
    printf("\n[상품 현황]\n");
    printf("상품ID\t재고수량\t판매수량\n");
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        printf("%d\t%d\t\t%d\n", i, stock[i], sold[i]);
    }
}

// 메인 함수
int main() {
    int menu;

    while (1) {
        printMenu();
        if (!safeScanInt("", &menu))
            continue;

        switch (menu) {
        case 1:
            inputStock();
            break;
        case 2:
            sellProduct();
            break;
        case 3:
            showStatus();
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }

    return 0;
}
